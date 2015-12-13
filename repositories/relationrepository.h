#ifndef RELATIONREPOSITORY_H
#define RELATIONREPOSITORY_H


class Relationrepository
{
public:
	    Relationrepository();

		/* @brief Adds/removes relation between scientist and computers in database
		 * @param idScientists is the PK of scientist to add relation findForComputer
		 * @param idPkComputer vector of id's of computers to add(vector if case more than one)
		 * @return returns true if sucsessfully added to database, false if not */
		bool addRelation(int idScientist, int idComputer);
		bool removeRelation(int idScientist, int idComputer);

		int sizeOfTable();
};

#endif // RELATIONREPOSITORY_H
