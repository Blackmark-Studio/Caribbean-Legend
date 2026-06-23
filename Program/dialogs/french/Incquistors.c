void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (GetNationRelation2MainCharacter(int(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple("Frères, il y a un ennemi dans les rangs de l'Inquisition!","Levez l'alarme, frères!");
					link.l1 = "En effet, les ennemis de l'Inquisition sont en alerte...";
					link.l1.go = "fight";			
			}
			else
			{	
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Bonjour là, "+GetSexPhrase("mon fils","ma fille")+". Qu'est-ce qui t'a amené ici?..","Je suis ravi de vous voir dans notre demeure, "+GetSexPhrase("mon fils","ma fille")+". . Qu'est-ce qui t'a amené ici?"),""+GetSexPhrase("Mon fils","Ma fille")+", nous avons déjà parlé aujourd'hui. Avez-vous besoin d'autre chose?",""+GetSexPhrase("Mon fils","Ma fille")+", les acolytes de notre ordre ne sont pas connus pour leur patience illimitée. Alors, laissez-moi vous demander encore une fois : avez-vous besoin de quelque chose?",RandPhraseSimple("Tu déranges les autres dans leurs devoirs. Je ne vais plus te parler.",""+GetSexPhrase("Mon fils","Ma fille")+", Je n'aime pas les discussions inutiles et dénuées de sens. Je ne vais plus vous parler."),"bloc",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Je viens de passer..","Complètement plein d'affaires..."),"Oh, non, Père......","Non, père, je voulais juste parler...",RandPhraseSimple("Hmm...","Eh bien, comme vous voulez, Père..."),npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //гарды на камерах
			{
				if (GetNationRelation2MainCharacter(int(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = "Aux armes! C'est un espion! Attrapez-le!";
					link.l1 = "Sacrebleu!";
					link.l1.go = "fight";
				}
				else
				{
					dialog.text = LinkRandPhrase("C'est une cellule gardée, et elle est strictement interdite.","Ne pensez même pas à entrer, c'est punissable de mort.","Juste un pas dans cette cellule et tu es fini.");
					link.l1 = RandPhraseSimple("Je vois, soldat.","Compris...");	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //заключенные
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("Ho-ho, n'est-ce pas drôle de voir ces 'saints' aller droit en enfer?!","Oh là là, quelqu'un a-t-il vraiment osé les défier?!","Ils m'ont torturé presque à mort, et je mourrai bientôt, mais tu m'as rendu heureux pour la dernière fois de ma vie...");
					link.l1 = RandPhraseSimple("Heh !","Tu es le bienvenu...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("Ces hypocrites sont totalement inhumains. Ils brûleront en enfer pour tout ce qu'ils nous ont fait...","Ils me torturaient et me tourmentaient tous les jours! Mais je ne suis pas coupable face à notre Seigneur!","Mon compagnon de cellule est mort hier... Ils l'ont torturé sur le chevalet pendant deux jours... Et qui sait combien de temps je résisterai ...");
					link.l1 = RandPhraseSimple("Hmm... Eh bien, je ne sais pas...","Oh, je vois...");
					link.l1.go = "exit";
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
	}
}
