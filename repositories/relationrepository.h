#ifndef RELATIONREPOSITORY_H
#define RELATIONREPOSITORY_H


class Relationrepository
{
public:
	    Relationrepository();

		/* @brief Adds relation between scientist and computers in database
		 * @param idScientists is the PK of scientist to add relation findForComputer
		 * @param idPkComputer vector of id's of computers to add(vector if case more than one)
		 * @return returns true if sucsessfully added to database, false if not */
		bool addRelation(int idScientist, int idComputer);

		/* @brief Adds relation between scientist and computers in database
		 * @param idScientists is the PK of scientist to add relation findForComputer
		 * @param idPkComputer vector of id's of computers to add(vector if case more than one)
		 * @return returns true if sucsessfully added to database, false if not */
		bool removeRelation(int idScientist, int idComputer);

		/* @brief reads total number of relation record in table
		 * @return number of records in database */
		int sizeOfTable();
};

#endif // RELATIONREPOSITORY_H
