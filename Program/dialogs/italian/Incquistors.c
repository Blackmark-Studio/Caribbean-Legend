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
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple("Fratelli, c'è un nemico tra le file dell'Inquisizione!","Suonate l'allarme, fratelli!");
					link.l1 = "Effettivamente, i nemici dell'Inquisizione sono all'erta...";
					link.l1.go = "fight";			
			}
			else
			{	
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ciao là, "+GetSexPhrase("mio figlio","mia figlia")+". Cosa ti ha portato qui?..","Sono contento di vederti nella nostra dimora, "+GetSexPhrase("mio figlio","mia figlia")+". . Cosa ti ha portato qui?"),""+GetSexPhrase("Mio figlio","Mia figlia")+", abbiamo già parlato oggi. Hai bisogno di altro?",""+GetSexPhrase("Mio figlio","Mia figlia")+", gli accoliti del nostro ordine non sono noti per la loro pazienza infinita. Quindi, ti chiedo ancora una volta: c'è qualcosa di cui hai bisogno?",RandPhraseSimple("Stai distrarre gli altri dai loro doveri. Non parlerò più con te.",""+GetSexPhrase("Mio figlio","Mia figlia")+", non mi piacciono le chiacchiere inutili e senza senso. Non ho intenzione di parlarti più."),"block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Sono appena passato..","Totalmente pieno di affari..."),"Oh, no, Padre......","No, padre, volevo solo parlare...",RandPhraseSimple("Mmm...","Bene, come desideri, Padre..."),npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //гарды на камерах
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = "Alle armi! È una spia! Prendetelo!";
					link.l1 = "Caspita!";
					link.l1.go = "fight";
				}
				else
				{
					dialog.text = LinkRandPhrase("Questa è una cella sorvegliata, e l'accesso è severamente vietato.","Non pensare nemmeno di entrare, è punibile con la morte.","Basta un passo in questa cella e sei finito.");
					link.l1 = RandPhraseSimple("Capisco, soldato.","Capito...");	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //заключенные
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("Oho, non è divertente guardare quei 'santi' andare dritti all'inferno?!","Oh mio, davvero qualcuno ha osato sfidarli?!","Mi hanno torturato fino alla morte, e morirò presto, ma mi hai reso felice per l'ultima volta nella mia vita...");
					link.l1 = RandPhraseSimple("Eh!","Di nulla...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("Quegli ipocriti sono totalmente inumani. Bruceranno all'inferno per tutto quello che hanno fatto a noi...","Mi torturavano e tormentavano ogni giorno! Ma non sono colpevole di fronte al nostro Signore!","È morto il mio compagno di cella ieri... Lo stavano torturando sulla ruota per due giorni... E chi sa quanto tempo ancora riuscirò a resistere ...");
					link.l1 = RandPhraseSimple("Mmm... Beh, non lo so...","Oh, capisco...");
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
