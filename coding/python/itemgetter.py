from operator import itemgetter

bar = ['a', 'b', 'c', 'd', 'e']
print itemgetter(0, 3, 4)(bar)

teamitems = [{'team':'France'     , 'P':1 , 'GD':-3 , 'GS':1 , 'GA':4},
            {'team':'Uruguay'     , 'P':7 , 'GD':4  , 'GS':4 , 'GA':0},
            {'team':'SouthAfrica' , 'P':4 , 'GD':-2 , 'GS':3 , 'GA':5},
            {'team':'Mexico'      , 'P':4 , 'GD':1  , 'GS':3 , 'GA':2}]

print sorted(teamitems ,key = lambda x:(x['P'],x['GD'],x['GS'],x['GA']),reverse=True)
print sorted(teamitems ,key = itemgetter('P','GD','GS','GA'),reverse=True)  