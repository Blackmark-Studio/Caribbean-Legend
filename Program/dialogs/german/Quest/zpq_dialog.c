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
			dialog.text = "Ich will nicht reden.";
			link.l1 = "Hm, ich verstehe.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "Nur eine Minute, Senor, sind Sie "+GetFullName(pchar)+"?";
			link.l1 = "Ja.. Wie kann ich Ihnen helfen??";
			link.l1.go = "zpq_sld2_1";
		break;
		case "zpq_sld2_1":
			dialog.text = "Wir brauchen dich. Genauer gesagt, dein Geld. Und versuch nicht, stur zu sein, denn ich bin heute nicht gut gelaunt, ich kann wütend werden.";
			link.l1 = "Oh, bitte, von welchem Geld sprichst du? Glaubst du wirklich, dass ich den Schatz bei mir tragen werde?";
			link.l1.go = "zpq_sld2_2";
		break;
		case "zpq_sld2_2":
			dialog.text = "Versuch nicht, mich zu täuschen. Gib mir einfach das Geld - "+FindRussianMoneyString(int(pchar.questTemp.zpq.sum))+" und du kannst deinen Weg gehen. Oder wir nehmen es mit Gewalt.";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "Hast du nicht für diese Fort-Ratte gearbeitet? Ich habe dann gute Nachrichten für dich, ich habe ihn zur Hölle geschickt.";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "Arbeitest du nicht für diese Fort-Ratte? Sag ihm, dass das Geld in zuverlässige Hände gegeben wurde, also kann er sie vergessen.";
			link.l1.go = "zpq_sld2_3";
			}
			if(int(Pchar.money) >= int(pchar.questTemp.zpq.sum))
			{
				link.l2 = "Gut, nimm dein schmutziges Geld, Bastard!";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "Ich habe sie nicht...";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		case "zpq_sld2_3":
			dialog.text = "Das ist also dein Schicksal - jung zu sterben wegen deiner Gier. Es ist zu gefährlich, dich am Leben zu lassen.";
			link.l1 = "Eine solche Selbstsicherheit.";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_3_1":
			dialog.text = "He-he, dein Schicksal ist es dann, wegen deiner Gier zu sterben. Das passt uns, wir wollen nicht teilen.";
			link.l1 = "Es ist deine Gier, die dich töten wird...";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_4":
			dialog.text = "He, Leute!! Steckt ihm einen Sack über den Kopf!";
			link.l1 = "Nun, es war deine Wahl...";
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
			dialog.text = "Schön. Gib sie ihnen und verschwinde, Kapitän!";
			link.l1 = "...";
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
