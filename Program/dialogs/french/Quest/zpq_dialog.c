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
			dialog.text = "Je ne veux pas parler.";
			link.l1 = "Hm, je vois.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "Juste une minute, senor, êtes-vous "+GetFullName(pchar)+"?";
			link.l1 = "Oui.. Comment puis-je vous aider ??";
			link.l1.go = "zpq_sld2_1";
		break;
		case "zpq_sld2_1":
			dialog.text = "Nous avons besoin de toi. De ton argent, pour être précis. Et n'essaie pas de faire le têtu parce que je ne suis pas d'humeur aujourd'hui, je peux me fâcher.";
			link.l1 = "Oh, je vous en prie, de quel argent parlez-vous ? Pensez-vous vraiment que je vais emporter le trésor avec moi ?";
			link.l1.go = "zpq_sld2_2";
		break;
		case "zpq_sld2_2":
			dialog.text = "N'essayez pas de me duper. Donnez-moi juste l'argent - "+FindRussianMoneyString(int(pchar.questTemp.zpq.sum))+" et vous pourrez suivre votre chemin. Ou nous le prendrons par la force.";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "N'es-tu pas au service de ce rat de fort ? J'ai une bonne nouvelle pour toi alors, je l'ai envoyé en enfer.";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "N'es-tu pas au service de ce rat de forteresse ? Dis-lui que l'argent a été confié à des mains sûres, qu'il peut les oublier.";
			link.l1.go = "zpq_sld2_3";
			}
			if(int(Pchar.money) >= int(pchar.questTemp.zpq.sum))
			{
				link.l2 = "Très bien, prends ton sale argent, salaud !";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "Je ne les ai pas...";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		case "zpq_sld2_3":
			dialog.text = "C'est donc ton destin - mourir jeune à cause de ta cupidité. Il est trop dangereux de te laisser en vie.";
			link.l1 = "Une telle confiance en soi.";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_3_1":
			dialog.text = "Hi-hi, ton destin est de mourir à cause de ta cupidité alors. Cela nous convient, nous ne voulons pas partager.";
			link.l1 = "C'est ta cupidité qui te tuera...";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_4":
			dialog.text = "Hé, les gars !! Mettez-lui un sac sur la tête !";
			link.l1 = "Eh bien, c'était ton choix...";
			link.l1.go = "zpq_sld2_5";
		break;
		case "zpq_sld2_5":
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(PChar, true);

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("zpq", "7");

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = "Cumana";
			pchar.quest.zpq_seaBattle.function = "zpq_seaBattle";
		break;
		case "zpq_sld2_6":
			dialog.text = "Bien. Donne-les et fous le camp, capitaine !";
			link.l1 = "... ";
			link.l1.go = "zpq_sld2_7";
			AddMoneyToCharacter(Pchar, -int(pchar.questTemp.zpq.sum));
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("zpq", "8");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
		break;
		case "zpq_sld2_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for(int i = 1; i <= 3; i++)

			{

				sld = CharacterFromID("qp2_" +i);
				LAi_SetImmortal(sld, true);
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 6.0);
			}
		break;
	}
}
