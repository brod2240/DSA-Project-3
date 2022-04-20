import spotipy
import queue
import csv

from spotipy.oauth2 import SpotifyClientCredentials

# using the spotify for developers credentials to use the API
cid = "1c21c38ea0ff4ced9b87e1198f12c254"
secret = "8188024083ef495b8ef3b9fc41ce5e8e"

# allows to see the number of users on the API website and use the API library throughout the project
client_credentials_manager = SpotifyClientCredentials(client_id=cid, client_secret=secret)
sp = spotipy.Spotify(client_credentials_manager=client_credentials_manager)

# global variables for the functions to access and modify
artistRelatedPair = {}
artistGenrePair = {}
artistPopularityPair = {}
pairArtistRelated = []
finalCSVPair = []
artistName = set()

# bfs traversal through the artist and their related artist in order to obtain more artists for project
# goes through 3 levels of related artists [20 artists] which is a sum of roughly 442 artists in total
def bfs(name):
    visited = set()
    traversed = queue.Queue()
    visited.add(name)
    traversed.put(name)

    while not traversed.empty():
        # cap the traversal at 442 artists in the list in order to not overload the API and the program
        if len(artistName) > 2000:
            break
        curr_artist = traversed.get()
        # used to get the artists info using the name of the artist
        search = sp.search(q='artist:' + curr_artist, type='artist')
        items = search['artists']['items']
        if len(items) > 0:
            artist = items[0]
            uri_artist = artist['uri']
            related_artists = sp.artist_related_artists(uri_artist)
            # go through related artist list and insert into total artist list to use for project
            for x in related_artists["artists"]:
                # ensures no duplicates in the lists
                if x['name'] not in visited:
                    artistName.add(x['name'])
                    visited.add(x['name'])
                    traversed.put(x['name'])


# given the name of the artist, get the list of information given by the API
def get_artist(name):
    results = sp.search(q='artist:' + name, type='artist')
    items = results['artists']['items']
    if len(items) > 0:
        return items[0]
    else:
        return None


# debugging: to see how many artists have been added to the lists
def print_artist():
    print(len(artistName))
    print(len(artistPopularityPair))
    print(len(artistGenrePair))
    print(len(artistRelatedPair))


# store the artist and the needed info relating to them as a dictionary (map)
# key = artist name, value = related artist list, genre list, popularity integer
def makeDictionary():
    # for the artists in the list artistName get the genre, popularity and the related artists relating to the artist
    for names in artistName:
        related_artist_array = []
        artist_info = get_artist(names)
        # if the artist does not have info currently, load with dummy value
        if artist_info is None:
            artistRelatedPair[names] = ["empty"]
            artistGenrePair[names] = ["empty"]
            artistPopularityPair[names] = -1
            continue
        # getting the uri allows the user to get the information needed, in this case genre, popularity, and related
        uri = artist_info['uri']
        artistGenrePair[names] = artist_info['genres']
        artistPopularityPair[names] = artist_info['popularity']
        related = sp.artist_related_artists(uri)
        # related artists comes in a list with all info, iterate list of related with just names and add to dictionary
        for y in related['artists']:
            related_artist_array.append(y['name'])
        artistRelatedPair[names] = related_artist_array


# for each value in the related artist array, combine with the key of the value
# creating the from and to vertex for graph
def makePairs():
    for key, value in sorted(artistRelatedPair.items()):
        for links in value:
            pair = (key, links)
            pairArtistRelated.append(pair)


# for each tuple in the list, get the genre and popularity and create the weight of the edge for the tuple
def createTupleForCSV():
    for index, tuples in enumerate(pairArtistRelated):
        # get the genres of the two artists
        genreArtist1 = artistGenrePair.get(tuples[0])
        genreArtist2 = artistGenrePair.get(tuples[1])

        # dummy value if genre is none
        if genreArtist1 is None:
            genreArtist1 = []

        if genreArtist2 is None:
            genreArtist2 = []

        # cycle through the genre list to find what genre the two artists have in common
        genre = 0
        for i in range(0, max(len(genreArtist1), len(genreArtist2))):
            if genreArtist1[i:i + 1] == genreArtist2[i:i + 1]:
                genre += 1

        # get the popularity of the two artists
        popularity1 = artistPopularityPair.get(tuples[0])
        popularity2 = artistPopularityPair.get(tuples[1])

        # dummy value if popularity is none
        if popularity1 is None:
            popularity1 = -1

        if popularity2 is None:
            popularity2 = -1

        # get the average popularity
        avgPopularity = (popularity1 + popularity2) / 2

        # weight = sum of same genres between two artist + the average of their popularity
        weight = genre + avgPopularity
        # create a tuple using the information created
        # tuple is in the form of (from, to , weight) for the csv file
        pair = (tuples[0], tuples[1], weight)
        finalCSVPair.append(pair)


def createCSV():
    # header for csv file
    header = ['From Artist', 'To Artist', 'Weight']
    # using the list of tuples to create the csv file to use in c++ program
    with open('Ramadan.csv', 'w', encoding='UTF8', newline='') as f:
        csv.register_dialect("custom", delimiter=",", skipinitialspace=True)
        writer = csv.writer(f, dialect="custom")
        writer.writerow(header)
        for tup in finalCSVPair:
            writer.writerow(tup)


# given a playlist, able to extract the artist from the songs in the playlist to get info for project
def main():
    playlist_link = "https://open.spotify.com/playlist/7l3U7pkcGRgeIJEhMgrXn9?si=b7b0b0fd85f54e9c"
    playlist_URI = playlist_link.split("/")[-1].split("?")[0]

    # get the track uri (the way to get track information) from the playlist
    track_uris = [x["track"]["uri"] for x in sp.playlist_items(playlist_URI)["items"]]
    artistPopularity = []
    artistGenre = []
    relatedArtists = []

    # cycle through the playlist tracks to get the name of the artist to use in bfs traversal
    for track in sp.playlist_items(playlist_URI)["items"]:
        artist_uri = track["track"]["artists"][0]["uri"]
        artist_info = sp.artist(artist_uri)
        artist_name = track["track"]["artists"][0]["name"]
        artistName.add(artist_name)
        # for each artist in the playlist, do a bfs traversal to get related artists
        bfs(artist_name)

    # call functions
    makeDictionary()
    makePairs()
    createTupleForCSV()
    createCSV()


# call program
main()




