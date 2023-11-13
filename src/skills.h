
#ifndef SKILLS_H_
#define SKILLS_H_

typedef struct {
	int bombardamento_aereo;
	int colpo_largo_raggio;
	int radar;
} skills;


int leggere_bombardamento_aereo(skills attacchi);
int leggere_colpo_largo_raggio(skills attacchi);
int leggere_radar(skills attacchi);
skills scrivere_bombardamento_aereo(skills attacchi, int value);
skills scrivere_colpo_largo_raggio(skills attacchi, int value);
skills scrivere_radar(skills attacchi, int value);


#endif /* SKILLS_H_ */
