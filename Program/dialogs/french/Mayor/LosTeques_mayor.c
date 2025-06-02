void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Tu oses venir ici ?! Action audacieuse...","Comment ces imbéciles ont-ils laissé un ennemi envahir ? Ça me dépasse...","Eh bien, mes gardes ne servent à rien si un imbécile se promène dans ma résidence..."),LinkRandPhrase("Que veux-tu, salaud ?! Mes soldats t'ont déjà retrouvé et tu ne t'échapperas pas."+GetSexPhrase(", sale pirate"," pirate immonde")+" !","Sale meurtrier, éloignez-vous de ma résidence ! Gardes !!!","Je n'ai pas peur de toi, salaud ! Tu seras pendu, tu ne t'en sortiras pas..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Les soldats ne coûtent rien...","Ils ne m'attraperont jamais."),RandPhraseSimple("Ferme ta bouche, "+GetWorkTypeOfMan(npchar,"")+", ou je te couperai la langue et te la fourrerai dans la gorge...","Je te dirais, camarade : reste tranquille, et il se pourrait que tu voies un autre jour..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Ennemi dans ma résidence ! Alerte !!!";
				link.l1 = "Merde !";
				link.l1.go = "fight"; 
				break;
			}			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+" Monsieur. Je suis "+GetFullName(npchar)+", commandant de la mine de Lost-Tekes qui appartient à "+NationKingsName(npchar)+"Maintenant, auriez-vous l'amabilité de me dire l'objet de votre visite, "+GetAddress_Form(NPChar)+".";
				link.l1 = "C'est ma première fois ici et je veux en savoir plus sur cette colonie et ses lois...";
				link.l1.go = "info";
				link.l2 = "Je voulais juste vous saluer, je pars déjà.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = "Vous encore, Monsieur ? Que voulez-vous d'autre ?";
			link.l1 = "Ce n'est rien. Je m'en vais.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Je respecte une telle discipline. Eh bien, je vais vous mettre au courant dans ce cas, puisque vous êtes si intéressé.\nLa mine de Los-Teques est la propriété de la Couronne espagnole. Nous extrayons ici du minerai brut d'argent et d'or, ainsi que des pépites d'argent et d'or. Tout l'or et l'argent appartiennent à l'Espagne et sont transportés vers le Vieux Monde.\nLa mine est bien gardée, une unité de soldats d'élite espagnols y est toujours stationnée. Les pirates ont fait plusieurs tentatives pour piller notre mine, mais les conséquences ont toujours été mauvaises... pour eux.\nComme vous pouvez le voir, c'est une petite ville. Nous avons une taverne et une boutique. Vous pouvez y acheter des lingots d'or et d'argent à bon prix. De plus, notre quartier-maître qui est aussi marchand dans la boutique peut vous vendre d'autres métaux et minerais intéressants.\nLa plupart de nos travailleurs sont des condamnés, mais nous avons aussi une petite quantité d'esclaves noirs. Comme vous pouvez le voir, nous avons toujours besoin de nouvelles forces, chaque jour au moins un de ces sacrés condamnés meurt.\nDonc, si vous nous apportez des esclaves, nous les échangerons contre des pépites. Contactez notre ingénieur en chef pour ce genre de choses. Vous pouvez le trouver dans le puits.\nComportez-vous correctement ici. Ne commencez pas de duels ou de bagarres, n'essayez de voler rien, en particulier l'or ou l'argent. Nous n'avons pas de prison ici mais nous avons un conseil de guerre.\nC'est à peu près tout. Suivez ces règles simples et vous n'aurez aucun problème. Vous êtes autorisé à vous déplacer librement dans la mine. N'oubliez pas de visiter la taverne, ils rendent certains... services avec ma permission. Bienvenue !";
			link.l1 = "Merci bien !";			
			link.l1.go = "exit";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = "Vol!!! C'est inadmissible! Préparez-vous, "+GetSexPhrase("complice","fille")+"...";
			link.l1 = LinkRandPhrase("Merde !","Carramba!!","Merde !");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
