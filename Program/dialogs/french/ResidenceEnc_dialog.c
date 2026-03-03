void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- леди в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (LAi_grp_playeralarm <= 0 && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Done") && !CheckAttribute(npchar, "quest.chickengod") && sti(npchar.nation) == SPAIN) {
				link.chickengod = "Senora, please excuse me, but I was asked to tell you that you have... a date inside an old pagan pyramid.";
				link.chickengod.go = "chickengod";
			}
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Jesus! Un homme méprisable dans mes chambres! Éloignez-vous d'ici ou j'appellerai les gardes!","Cela ne peut pas se passer... Qui a laissé ce rat entrer dans ma maison? Sortez d'ici, espèce de salaud! Vous n'avez rien à faire ici! Allez-vous en!","De tels temps étranges sont arrivés. Les rats entrent dans ma chambre! Va-t'en!");
				link.l1 = RandPhraseSimple("Doucement là...","Surveille ta bouche...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Que faites-vous dans ma chambre? Allez-vous en d'ici!","Quelle honte ! Je vous demande de quitter cet endroit immédiatement !","Excusez-moi, monsieur, mais vous n'avez pas été invité ici. S'il vous plaît, quittez ma chambre!");
				link.l1 = RandPhraseSimple("Pardonnez-moi... Je pars.","Désolé, mauvaise porte. Je dois y aller.");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "Oh, qu'est-ce que c'était?! Je suis un tel imbécile! Marchant sans voir quoi que ce soit... Gardes!!!";
			link.l1 = "Tais-toi !";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Dégage d'ici, rat !","Dégage de la propriété du gouverneur immédiatement, rat!","Je m'en fiche de ce que tu fais chez le gouverneur de "+XI_ConvertString("Colony"+npchar.city+"Gen")+"Mais mon conseil est de te perdre, maintenant !");
				link.l1 = RandPhraseSimple("Garde ça simple, pote...","Surveille tes mots !");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Salutations! Je suis un serviteur du gouverneur. Mon nom est "+GetFullName(NPChar)+".","Je surveille cet endroit, "+GetAddress_Form(NPChar)+".","Tu sais, "+GetAddress_Form(NPChar)+", notre gouverneur est un bon homme et nous paye bien...");
				link.l1 = RandPhraseSimple("Agréable.","Hm, très bien...");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "Alors, tu as décidé de voler le gouverneur?! Gardes, attrapez le voleur!!";
			link.l1 = "Ferme ta bouche!";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Vous feriez mieux de partir d'ici, "+GetSexPhrase("copain","fille")+"...","Va-t'en !","Manqué la porte, "+GetSexPhrase("pote","fille")+"? ? Cette propriété appartient au gouverneur de "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				link.l1 = RandPhraseSimple("Je partirai quand je le voudrai!","Ce n'est pas ton affaire...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Aujourd'hui, on m'a ordonné de servir ici. Bel endroit...","Je protège la propriété de "+GetAddress_Form(NPChar)+".","Mon ordre est de protéger la propriété du gouverneur.");
				link.l1 = RandPhraseSimple("Bonne chance, alors...","Hmm, je vois...");
				link.l1.go = "exit";
			}
		break;
		
		case "chickengod":
			pchar.questTemp.ChickenGod.Tasks.o2.Counter = sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) + 1;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) >= 3) {
				dialog.text = "Ah, oui. Enfin! Je suis prêt à partir avec vous, capitaine.";
				link.l1 = "Comme ça? Senora, êtes-vous sûre que c'est ce que vous voulez?";
				link.l1.go = "chickengod_accept";
			} else {
				sld = CharacterFromID(npchar.city + "_Mayor");
				dialog.text = "Quoi?! Êtes-vous ivre, monsieur? Quelle blague idiote! S'il vous plaît, partez, je vous en supplie!"+sld.name+"! Gardes ! Aidez-moi !";
				link.l1 = "Merde, il est temps de partir.";
				link.l1.go = "chickengod_decline";
			}
			npchar.quest.chickengod = true;
		break;
		
		case "chickengod_accept":
			dialog.text = "Eh bien, bien sûr! Ah, le Señor Aruba et moi entretenons une relation épistolaire depuis longtemps!";
			link.l1 = "Puisque c'est le cas, montez à bord, s'il vous plaît!";
			link.l1.go = "chickengod_accept_take";
			link.l2 = "Non, senora, cela ne conviendra pas. Mon honneur ne permettra pas de mettre une femme en danger, et vous avez clairement été induite en erreur!";
			link.l2.go = "chickengod_accept_nottake";
		break;
		
		case "chickengod_accept_take":
			DialogExit();
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			pchar.questTemp.ChickenGod.Tasks.o2.Lady = npchar.id;
			AddDialogExitQuestFunction("ChickenGod_TakeLady");
		break;
		
		case "chickengod_accept_nottake":
			dialog.text = "Dans ce cas, mon cher capitaine, prenez votre sens rural de l'honneur et foutez-le dans votre cul ! J'attendrai un autre messager, quelqu'un pas aussi borné que vous !";
			link.l1 = "Charmant !";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			SetFunctionTimerCondition("ChickenGod_NotTakeLadyConsequence", 0, 1, 0, false);
		break;
		
		case "chickengod_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_LadyRefuse");
		break;
		
	}
}
