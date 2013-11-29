#### netflix-prize-exp
----------------------
Trials with the netflix-prize dataset

#### Project folder layout
--------------------------
1. _netflixFW_ : A framework built on C++ to tackle Netflix's beautiful dataset. Once all the necessary data are loaded (movie database, user database, probe database), many experiments can be conducted smoothly within a reasonable RAM limit. This folder has a few predictors (Baseline estimate, KNN, SVD) implemented in it. Feel free to extend the `Algorithm` class to implement your own predictor algorithm.
2. _data_ : Contains some useful extracted from the dataset. These were generated using the scripts inside the `scripts` fodler.
3. _scripts_ : Contains some python scripts that can be used initially to get a hang of the dataset.
4. _plots_ : Has some graph plots for visualizing the dataset. More graphs to be added soon.

#####Notes:
----------
1. The training\_set is not included in this folder because of its huge size (~2.2 GB). Hence all the "file/folder" paths mentioned in the scripts and in the framework should be modified accordingly before them. Please note that the "names" of the files and folders are not changed and they are the same as in the original training\_set that was provided by Netflix. Any file/folder name which are found to be new or different from the ones in the training\_set were created by the scripts/framework code.
2. Generation of the databases i.e the movie, user and probe database is left to the user, which can be done by calling appropritate loadDatabase function from the  `main()` of the framework. However these databases are not used by the scripts and hence you can run the scripts independently as long as the paths are correct. Please note that the test\_set data is not touched by this framework because presently we don't have their actual ratings to be compared against our predictions. For the curious minds, generating and loading the test\_set logic would be the same as it is done with other databases mentioned above.

#### Run instructions:
----------------------
To be updated soon..


