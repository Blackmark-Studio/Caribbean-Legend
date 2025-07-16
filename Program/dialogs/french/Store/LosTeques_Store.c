void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
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
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Une alerte a été déclenchée dans la ville. Tout le monde vous cherche ! Je ne m'attarderais pas trop ici si j'étais vous.","Tous les gardes de la ville ratissent la ville pour te trouver. Je ne suis pas un idiot et je ne vais pas te parler !","Fuis, camarade, avant que les soldats ne te réduisent en chair à saucisse..."),LinkRandPhrase("Que veux-tu, vaurien ?! La garde de la ville est à tes trousses en ce moment. Tu n'iras pas loin, sale pirate !","Sortez de ma maison, meurtrier ! Gardes !!","Je n'ai pas peur de toi, vaurien ! Bientôt ils te pendront, tu ne t'en sortiras pas..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Hé, je ne suis pas trop inquiet pour l'alarme...","Ils n'ont aucune chance de m'attraper."),RandPhraseSimple("Ferme ta grande gueule, "+GetWorkTypeOfMan(npchar,"")+", ou je te couperai ta maudite langue !","Heh, "+GetWorkTypeOfMan(npchar,"Bonjour, ami.")+", toi aussi tu veux chasser un pirate ! Écoute, l'ami, garde ton calme et tu vivras..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"! Je ne vous ai jamais vu auparavant, señor. Puis-je supposer que vous êtes capitaine... Ai-je deviné juste? Mon nom est "+GetFullName(npchar)+", et mon magasin est à votre service. Or, argent, et bien plus encore pour éveiller l'intérêt d'un homme curieux.";
				Link.l1 = "Je vois. Je suis "+GetFullName(pchar)+"Enchanté de vous rencontrer, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", señor ! Je suis ravi de vous revoir dans ma boutique. Souhaitez-vous acquérir quelques pépites d'or ? Ou peut-être seriez-vous intéressé par des minéraux aujourd'hui ?";
				link.l1 = "Montre-moi ta marchandise, "+npchar.name+".";
				link.l1.go = "trade";
				link.l4 = "Non, je n'ai besoin de rien, "+npchar.name+". Je suis juste passé pour te saluer.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Moi aussi, señor. Voulez-vous jeter un œil à ma marchandise ? Je suis sûr que j'ai quelque chose qui pourrait vous intéresser.";
			link.l1 = "C'est ma première fois ici et j'aimerais en savoir un peu plus sur cette colonie.";
			link.l1.go = "info";
			link.l2 = "Alors montre-moi ce que tu as à vendre.";
			link.l2.go = "trade";
		break;
		
		case "info":
			dialog.text = "Notre petite ville a été construite grâce à la mine d'or. Ils extraient du minerai d'or, de l'argent et des pépites d'or. Parfois même des gemmes. Nous n'avions ici qu'une garnison jusqu'à ce que des Indiens amicaux et quelques colons blancs nous rejoignent\nIgnacio Ortega a construit une taverne et a rendu notre vie un peu plus joyeuse. Toutes sortes d'aventuriers visitent cet endroit avec l'intention idiote de nous voler. Nous n'avons pas de tribunal ici, donc leur nombre a diminué après que nous ayons pendu plusieurs idiots en plein milieu de la ville\nLe minerai d'or est envoyé aux navires sous la protection des soldats et des Indiens amis, les pépites, cependant, vous pouvez les acheter ici même, dans ce magasin\nDe plus, j'ai parfois des minéraux très intéressants à offrir, alors rendez-moi visite quand vous avez le temps, je réapprovisionne toujours mon stock.";
			link.l1 = "Merci pour cette histoire captivante ! Je m'en souviendrai.";			
			link.l1.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Vol en plein jour !!! Qu'est-ce qui se passe ici ?! Attends, attends, l'ami...","Hé, que fais-tu là?! Tu essaies de me voler? Maintenant, tu es fichu...","Attends, que diable fais-tu ? Il s'avère que tu es un voleur ! Considère ceci comme la fin de ta route, salaud...");
			link.l1 = LinkRandPhrase("Diable !!","Caramba !!","Merde!");
			link.l1.go = "fight_owner";
		break;
		
		case "fight_owner": // лесник . выход из диалога . если копался в сундуках. 
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}
