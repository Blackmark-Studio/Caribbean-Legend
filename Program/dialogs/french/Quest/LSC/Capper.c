// Чад Каппер - боцман Акулы и тюремщик
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Vous désirez quelque chose ?";
			link.l1 = "Non, ce n'est rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// вариант R
		case "Chimiset":
			dialog.text = "Eh bien, eh bien... Alors, tu es le mystérieux voleur ? Hm... Tu ne ressembles pas à un misérable chapardeur.";
			link.l1 = "Ecoutez, monsieur, vous vous trompez. Je suis un nouveau ici, alors comment pourrais-je savoir que la cale où vos hommes m'ont attrapé était votre zone privée ?";
			link.l1.go = "Chimiset_1";
		break;
		
		case "Chimiset_1":
			dialog.text = "Ah vraiment ? Belle tentative, camarade... D'où viens-tu alors ?";
			link.l1 = "De la terre ferme... Par une étrange statue. Moi-même, je ne sais comment expliquer ce qui s'est passé.";
			link.l1.go = "Chimiset_2";
		break;
		
		case "Chimiset_2":
			dialog.text = "Statue ? Ha-ha ! Tu es un drôle de gars, n'est-ce pas... Très bien, je vais tout t'expliquer moi-même : tu as nagé à travers le trou dans le navire et tu voulais te faufiler dans notre entrepôt. Comment se fait-il que je ne reconnaisse pas ton visage ? Je connais tous les Rivados...";
			link.l1 = "Quels Rivados ? Je ne sais pas de quoi vous parlez ! Écoutez, je suis arrivé ici il y a environ une heure...";
			link.l1.go = "Chimiset_3";
		break;
		
		case "Chimiset_3":
			dialog.text = "N'élève pas la voix, je ne suis pas un idiot. Aye, j'ai assez entendu de tes balivernes à propos de la statue et je trouve cela assez amusant. Je trouve cela foutrement hilarant. Que dirais-tu qu'on en rie ensemble? Ha-ha-ha!... Pourquoi ne ris-tu pas? C'était une bonne blague... Rivados. Mais les plaisanteries sont terminées maintenant. Je te laisserai pourrir en prison, mon pote.";
			link.l1 = "Je ne suis pas Rivados ! Mon nom est Charles de Maure !";
			link.l1.go = "Chimiset_4";
		break;
		
		case "Chimiset_4":
			dialog.text = "Première fois, hein ? Hm... peut-être que tu dis la vérité. Réponds-moi, es-tu l'un des leurs ?!";
			link.l1 = "Je te jure, je n'ai jamais entendu ce nom auparavant, je ne suis pas l'un d'eux !";
			link.l1.go = "Chimiset_5";
		break;
		
		case "Chimiset_5":
			dialog.text = "Vraiment ? Très bien. Prouve-le. Descends, il y a un Rivados assis dans une cage. C'est un sorcier dangereux. Tue-le, alors seulement je serai convaincu. J'oublierai également ton intrusion illégale dans notre entrepôt.\nAlors ? Es-tu prêt ? N'aie pas peur, le sorcier est désarmé et faible. Eh bien, il pourrait te réduire en poussière avec un sort, comme celui qui t'a amené dans la cale de San Augustine...";
			link.l1 = "Si tu avais vu ce sort en action, tu ne serais pas si sceptique. Je doute même que tu y aurais survécu...";
			link.l1.go = "Chimiset_6";
		break;
		
		case "Chimiset_6":
			dialog.text = "Assez de bavardages ! Allez-vous le faire ou non ? Si oui, alors prenez cette machette et occupez-vous du sorcier. Sinon, vous passerez le reste de votre vie en cage. Compris ?";
			link.l1 = "De deux maux, je choisis le moindre. Donne-moi la machette.";
			link.l1.go = "Chimiset_7";
		break;
		
		case "Chimiset_7":
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "slave_02");
			EquipCharacterbyItem(pchar, "slave_02");
			dialog.text = "Bon garçon. Prends ça, va tuer l'homme noir. Sa cage est déverrouillée. Ne fais rien de stupide maintenant, nous n'hésiterons pas à te finir si tu ne fais qu'y penser ! Maintenant, vas-y !";
			link.l1 = "Pourquoi ? As-tu peur que je ne vous éventre, vous et votre bande, avec ce tas de ferraille rouillée ?";
			link.l1.go = "Chimiset_8";
		break;
		
		case "Chimiset_8":
			dialog.text = "Ma patience s'épuise. Va à la cale et fais ce qu'on te dit !";
			link.l1 = "D'accord, d'accord, détends-toi. Je m'en vais...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//разлочим Ф2
		break;
		
		case "Chimiset_9":
			dialog.text = "Tu mets ma patience à l'épreuve, salaud ! Tu ne veux pas m'irriter...";
			link.l1 = "Très bien, très bien, détends-toi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
		break;
		
		case "Fightfail_Final":
			dialog.text = "As-tu tué ce sorcier nègre ? Bien... Je suis content. Tu as prouvé que tu n'es pas Rivados.";
			link.l1 = "Quand vais-je enfin être libéré de cette maudite coque ? Je dois rencontrer Requin immédiatement.";
			link.l1.go = "Fightfail_Final_1";
		break;
		
		case "Fightfail_Final_1":
			dialog.text = "Tu le rencontreras, c'est sûr... Tu le rencontreras sur le chemin de l'enfer !";
			link.l1 = "Quoi?!";
			link.l1.go = "Fightfail_Final_2";
		break;
		
		case "Fightfail_Final_2":
			DialogExit();
			DoQuestCheckDelay("LSC_ChadGuardAttack_Fail", 0.1);
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Ha ! Regarde-moi ça. Que fais-tu ici dans ma prison ?";
			link.l1 = "Ton nom est Chad Kapper, n'est-ce pas? Mon nom est "+GetFullName(pchar)+" et je suis ici de la part de Requin Dodson. Il m'a donné les clés.";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "De la part de l'amiral ? Hm, je vois. Es-tu son nouveau larbin ?";
			link.l1 = "Montrez un peu de respect, monsieur. Je ne sers personne, ni le Requin ni vous, et je ne vais pas tolérer un tel langage.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Ha-ha, tu me plais, l'ami ! Oublie ce que j'ai dit... Alors, que fais-tu ici ?";
			link.l1 = "Le Requin a donné l'ordre de libérer Chimiset, il est emprisonné ici.";
			link.l1.go = "prisoner_3";
		break;
		
		case "prisoner_3":
			dialog.text = "Le sorcier des Rivados ? Hm. C'est étrange, je suis vraiment surpris d'entendre ça...";
			link.l1 = "Le Requin a donné un ordre. Il veut faire la paix avec les Rivados.";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "A-ah, je vois maintenant. Bien, j'enverrai un homme chez les Rivados. Ils viendront ici prendre leur bouffon.";
			link.l1 = "Pourquoi ne peux-tu pas simplement le laisser partir ?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Je pourrais, mais ce serait trop dangereux pour lui. Chimiset est connu ici, sa vie ne vaudra rien une fois qu'il mettra le pied sur l'Esmeralda - un territoire de ses ennemis, les Narvals. Il n'y a pas d'autre moyen depuis le Tartare, nous ne pouvons pas laisser le vieil homme nager autour de l'île !\nEt si quelqu'un le tue, les Rivados nous accuseront, moi en particulier ! Vous voyez, je ne veux pas de problèmes qui peuvent être évités. Alors je ne le laisserai sortir que sous la protection des combattants de son clan. Peut-être souhaitez-vous parler vous-même avec Chimiset ? C'est un drôle de type...";
			if (CheckAttribute(npchar, "quest.chimiset_talk")) link.l1 = "Je lui ai déjà parlé, c'est vraiment un homme étrange. Quoi qu'il en soit, je dois y aller. À bientôt, Chad !";
			else link.l1 = "C'est ce que je comptais faire. Je vais aller lui parler.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			DialogExit();
			sld = characterFromId("Chimiset");
			sld.quest.capper_talk = "true"; // разговор с Каппером состоялся
			if (!CheckAttribute(npchar, "quest.chimiset_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "Je vais envoyer un messager à Rivados et ils prendront leur sorcier. Ne t'inquiète pas, camarade, tu peux y aller.";
			link.l1 = "D'accord.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_7";
		break;
		
		// вариант M
		case "Aeva_attack":
			dialog.text = "...il doit déjà avoir ouvert le tonneau, j'en suis sûr. C'est son whisky préféré, maudit Irlandais. Cela se terminera bientôt, j'y ai mis assez d'arsenic pour tuer un troupeau...";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "Aeva_attack_1";
			CharacterTurnToLoc(npchar, "quest", "quest2");
		break;
		
		case "Aeva_attack_1":
			dialog.text = "Ah? Bon sang, que fais-tu ici? Dégage!";
			link.l1 = "Je te cherchais depuis longtemps... empoisonneur. C'est étrange, je ne vois pas le Cyclope. Tu voulais prendre la place du Requin, n'est-ce pas ?";
			link.l1.go = "Aeva_attack_2";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Aeva_attack_2":
			dialog.text = "Ha-ha, Requin doit être mort à présent ! Et tu le suivras bientôt, espion !";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Aeva_attack_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("ChadNarval_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CapperDieAeva");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;

		case "Aeva_attack_3":
			dialog.text = "Ah, fouineur ! Eh bien, tu mourras le premier alors ! Les gars, aux armes !";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
