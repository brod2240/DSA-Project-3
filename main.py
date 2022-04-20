import numpy as np
import spotipy
import queue
import csv
import pandas as pd

from spotipy.oauth2 import SpotifyClientCredentials

cid = "1c21c38ea0ff4ced9b87e1198f12c254"
secret = "11eb8a7a020a4de180861c104c3a0b23"

client_credentials_manager = SpotifyClientCredentials(client_id=cid, client_secret=secret)
sp = spotipy.Spotify(client_credentials_manager=client_credentials_manager)


def bfs(name):
    visited = set()
    traversed = queue.Queue()
    count = 0
    visited.add(name)
    traversed.put(name)
    while not traversed.empty():
        if len(artistName) > 442:
            break
        curr_artist = traversed.get()
        search = sp.search(q='artist:' + curr_artist, type='artist')
        items = search['artists']['items']
        if len(items) > 0:
            artist = items[0]
            uri_artist = artist['uri']
            related_artists = sp.artist_related_artists(uri_artist)
            for x in related_artists["artists"]:
                if x['name'] not in visited:
                    artistName.add(x['name'])
                    visited.add(x['name'])
                    traversed.put(x['name'])
                    count = count + 1


def get_artist(name):
    results = sp.search(q='artist:' + name, type='artist')
    items = results['artists']['items']
    if len(items) > 0:
        return items[0]
    else:
        return None


def printArtist():
    print(len(artistName))
    print(len(artistPopularityPair))
    print(len(artistGenrePair))
    print(len(artistRelatedPair))


playlist_link = "https://open.spotify.com/playlist/3XiaOE9nIH7jPfUri9ERxM?si=d301d58d5ac14733"
playlist_URI = playlist_link.split("/")[-1].split("?")[0]

track_uris = [x["track"]["uri"] for x in sp.playlist_items(playlist_URI)["items"]]
artistName = set()
artistPopularity = []
artistGenre = []
relatedArtists = []

for track in sp.playlist_items(playlist_URI)["items"]:
    artist_uri = track["track"]["artists"][0]["uri"]
    artist_info = sp.artist(artist_uri)

    artist_name = track["track"]["artists"][0]["name"]
    artist_pop = artist_info["popularity"]
    artist_genres = artist_info["genres"]
    artistName.add(artist_name)

    bfs(artist_name)

artistRelatedPair = {}
artistGenrePair = {}
artistPopularityPair = {}

for names in artistName:
    related_artist_array = []
    artist_info = get_artist(names)
    if artist_info is None:
        artistRelatedPair[names] = ["empty"]
        artistGenrePair[names] = ["empty"]
        artistPopularityPair[names] = -1
        continue
    uri = artist_info['uri']
    artistGenrePair[names] = artist_info['genres']
    artistPopularityPair[names] = artist_info['popularity']
    related = sp.artist_related_artists(uri)
    for y in related['artists']:
        related_artist_array.append(y['name'])
    artistRelatedPair[names] = related_artist_array


pairArtistRelated = []
# for each value in the array, make pair with key
for key, value in sorted(artistRelatedPair.items()):
    for links in value:
        pair = (key, links)
        pairArtistRelated.append(pair)
print(pairArtistRelated)

finalCSVPair = []
# hash function = sum of similar genres + avg of popularity
for index, tuples in enumerate(pairArtistRelated):
    artist1 = get_artist(tuples[0])
    artist2 = get_artist(tuples[1])
    print(artist1, artist2)
    if artist1 or artist2 is None:
        continue

    genreArtist1 = (artist1['genres'])
    genreArtist2 = (artist2['genres'])

    genre = 0
    for i in range(0, max(len(genreArtist1), len(genreArtist2)), 1):
        if genreArtist1[i:i + 1] == genreArtist2[i:i + 1]:
            genre += 1

    print(genre)
    popularity1 = artist1['popularity']
    popularity2 = artist2['popularity']
    avgPopularity = (popularity1 + popularity2)/2

    hashFunction = genre + avgPopularity
    pair = (artist1, artist2, hashFunction)
    finalCSVPair.append(pair)

