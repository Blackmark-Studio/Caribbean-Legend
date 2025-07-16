void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ein Fehler. Stellen Sie sicher, dass Sie die Entwickler informieren.";
			link.l1 = "OK";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarginCap":
			dialog.text = "Grüße, Kapitän. Wünschen Sie etwas von mir?";
			link.l1 = "Ja. Genau, "+GetAddress_FormToNPC(NPChar)+". Es gibt einen Passagier auf Ihrem Schiff, der mich sehr interessiert. Der Name ist "+pchar.GenQuest.Marginpassenger.q1Name+". Ich will, dass dein Passagier mein Passagier wird. Wenn du damit einverstanden bist, dann werden wir uns trennen und uns nie wiedersehen.";
			link.l1.go = "MarginCap_1";
		break;
	
		case "MarginCap_1":
			dialog.text = "Ist das so? Und was ist, wenn ich Nein sage?";
			link.l1 = "Dann werde ich Sie mit einigen Salven meiner Kanonen, die gerade auf Sie gerichtet sind, dazu bringen müssen, Ihre Entscheidung zu überdenken. Fordern Sie Ihr Glück nicht heraus, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "MarginCap_2";
		break;
		
		case "MarginCap_2":
			int MCparam = (7-sti(RealShips[sti(pchar.ship.type)].Class))*100+sti(pchar.ship.Crew.Morale)+sti(pchar.Ship.Crew.Exp.Sailors)+sti(pchar.Ship.Crew.Exp.Cannoners)+sti(pchar.Ship.Crew.Exp.Soldiers);
			int NPCparam = (7-sti(RealShips[sti(npchar.ship.type)].Class))*100+sti(npchar.ship.Crew.Morale)+sti(npchar.Ship.Crew.Exp.Sailors)+sti(npchar.Ship.Crew.Exp.Cannoners)+sti(npchar.Ship.Crew.Exp.Soldiers);
			if (MCparam > NPCparam)//отдаст сам
			{
				dialog.text = "Ich habe dann keine Wahl. Das Schicksal meiner Besatzung ist mir wertvoller als das Schicksal eines Mannes. Aber du wirst nicht so einfach davonkommen! Ich werde es nicht vergessen!";
				link.l1 = "Beruhige dich und bewahre dich vor einem Herzinfarkt... Bring mir meinen neuen Passagier!";
				link.l1.go = "MarginCap_3";
			}
			else
			{
				dialog.text = "Sie sollten mein Schiff verlassen, Herr, solange ich es Ihnen noch erlaube. Versuchen Sie nicht, mich zu erschrecken. Und wagen Sie es nicht, mein Schiff anzugreifen, sonst werden Sie sofort abgewehrt. Raus, solange ich noch guter Laune bin!";
				link.l1 = "Ich habe dich gewarnt. Ich bin unterwegs. Bis bald, "+GetAddress_FormToNPC(NPChar)+"!";
				link.l1.go = "MarginCap_4";
			}
		break;
	
		case "MarginCap_3":
			DialogExit();
			npchar.Dialog.CurrentNode = "MarginCap_repeat";
			//отдаем пассажира
			sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
			sld.Dialog.Filename = "Quest\Marginpassenger.c";
			sld.Dialog.currentnode = "MarginPass";
			sld.name = pchar.GenQuest.Marginpassenger.q1Name;
			sld.lastname = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			Map_ReleaseQuestEncounter(npchar.id);
			npchar.Abordage.Enable = false; // запрет абордажа
			npchar.ShipEnemyDisable = true;
			npchar.AlwaysFriend = true;
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_4":
			DialogExit();
			NextDiag.CurrentNode = "MarginCap_repeat";
			pchar.GenQuest.Marginpassenger.Mustboarding = "true";
			AddQuestRecord("Marginpassenger", "5");
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_repeat":
			dialog.text = "Wir haben bereits gesprochen, erinnerst du dich? Verschwinde von meinem Schiff!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarginCap_repeat";
		break;
		
		case "MarginCap_abordage":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Mustboarding"))
			{
				dialog.text = "Aargh, Schuft! Brenne in der Hölle für deine Taten!";
				link.l1 = "Ich habe euch angeboten, mir den Passagier friedlich zu übergeben... und ihr habt mein Angebot abgelehnt. Jetzt seid ihr alleine Schuld!";
				link.l1.go = "MarginCap_abordage_1";
			}
			else
			{
				dialog.text = "Argh, Schurke! Warum hast du das friedliche Schiff angegriffen? Wir haben kein Gold oder wertvolle Güter!";
				link.l1 = "Aber du hast eine wertvolle Person an Bord..."+pchar.GenQuest.Marginpassenger.q1Name+". Ich will deinen Passagier.";
				link.l1.go = "MarginCap_abordage_2";
			}
		break;
		
		case "MarginCap_abordage_1":
			dialog.text = "Du... bist der dreckige Pirat!";
			link.l1 = "Weniger reden, mein Freund...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_2":
			dialog.text = "Und deswegen hast du ein Massaker auf meinem Schiff verübt? Viele Männer sind tot! Pirat!";
			link.l1 = "Weniger reden, mein Freund...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_3":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Marginpassenger_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "MarginNeed":
			dialog.text = "Was willst du, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Bist du "+pchar.GenQuest.Marginpassenger.q2Name+"?";
			link.l1.go = "MarginNeed_1";
		break;
		
		case "MarginNeed_1":
			dialog.text = "Ja, das bin ich. Möchten Sie einen Antrag stellen? Dann sollten Sie wissen, dass...";
			link.l1 = "Warten Sie einen Moment, Herr. Ich habe eine etwas andere Art von Anwendung... Kennen Sie jemanden namens "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1.go = "MarginNeed_2";
		break;
		
		case "MarginNeed_2":
			switch (pchar.GenQuest.Marginpassenger.sex)
			{
				case "woman":
					dialog.text = "Ja, ich kenne sie... Natürlich kenne ich sie! Was ist los?";
					link.l1 = "Sie hatte sich in eine äußerst unangenehme Geschichte verwickelt: Ihr Schiff wurde von Piraten gekapert. Glücklicherweise hatte ich die Möglichkeit, ihr Schiff zu betreten und die arme Seele zu retten. Sie hat mir Ihren Namen genannt und hier bin ich.";
					link.l1.go = "MarginNeed_woman";
				break;
				case "man":
					dialog.text = "Ja, ich kenne diesen Mann sehr gut. Was ist los?";
					link.l1 = "Er hatte sich in eine höchst unangenehme Geschichte verwickelt: sein Schiff wurde von Piraten gekapert. Glücklicherweise hatte ich die Gelegenheit, ihr Schiff zu entern und diesen Gefangenen zu retten. Er hat mir Ihren Namen genannt und hier bin ich.";
					link.l1.go = "MarginNeed_man";
				break;
			}
		break;
		
		case "MarginNeed_woman":
			dialog.text = "Oh Gott! Wo ist sie jetzt? Warum hast du sie nicht hierher gebracht?";
			link.l1 = "Sie ist sicher. Und zu deiner Frage... es ist nicht so einfach. Ich hätte sie selbst nach Hause bringen können, aber ich kann dir diese Gelegenheit geben. Natürlich gegen eine bescheidene Gebühr.";
			link.l1.go = "MarginNeed_woman_1";
		break;
		
		case "MarginNeed_woman_1":
			dialog.text = "Hm... Ich verstehe es nicht...";
			link.l1 = "Warum tust du es nicht? Du bezahlst mich in Gold, ich gebe dir das Mädchen und du wirst in der Lage sein, diese Situation zu deinen Gunsten zu nutzen... Du willst sie heiraten, habe ich recht? Und ich werde mein Schiff mit diesen Münzen reparieren, sie wurde bei dem Kampf mit den Piraten beschädigt.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_man":
			dialog.text = "Oh Gott! Wo ist er jetzt? Warum haben Sie ihn nicht hierher gebracht?";
			link.l1 = "Er ist sicher. Und zu deiner Frage... es ist nicht so einfach. Ich hätte ihn selbst nach Hause bringen können, aber ich kann dir diese Gelegenheit geben, da du deine eigenen Interessen in seiner Familie hast. Für eine bescheidene Gebühr natürlich.";
			link.l1.go = "MarginNeed_man_1";
		break;
		
		case "MarginNeed_man_1":
			dialog.text = "Hm... Ich verstehe es nicht...";
			link.l1 = "Warum nicht? Du zahlst mir in Gold, ich gebe dir deinen Freund und du kannst diese Situation zu deinen Gunsten nutzen. Ich habe einige Informationen, weißt du... Mit diesen Münzen werde ich mein Schiff reparieren, es wurde bei dem Kampf mit den Piraten beschädigt.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_money":
			dialog.text = "Nun, nun... und wie viel willst du?";
			link.l1 = "Bedenke, dass ich Dublonen will, keine Pesos.";
			link.l1.go = "MarginNeed_money_1";
		break;
		
		case "MarginNeed_money_1":
			dialog.text = "Gut, gut... Also, wie viele Dublonen willst du?";
			Link.l1.edit = 1;			
			link.l1 = "";
			link.l1.go = "MarginNeed_money_2";
		break;
		
		case "MarginNeed_money_2":
		iTemp = sti(dialogEditStrings[1]);
		int iSum = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*5*stf(pchar.GenQuest.Marginpassenger.Chance));
		if (iTemp <= 0)
		{
			dialog.text = "Sehr lustig. Gut, tun wir so, als ob dein Witz lustig wäre. Lebewohl!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 0 && iTemp <= iSum)
		{
			if (hrand(2) > 1) // Addon-2016 Jason уменьшаем раздачу дублонов
			{
				dialog.text = "Gut, ich stimme zu. Ich besitze den erforderlichen Betrag. Wo ist "+pchar.GenQuest.Marginpassenger.q1Name+"?";
				link.l1 = "Muss jetzt am Pier sein. Also kannst du gehen und den Passagier holen.";
				link.l1.go = "MarginNeed_dublon";
			}
			else
			{
				dialog.text = "Es tut mir leid, aber ich habe nicht so viele Dublonen. Sind Pesos auch in Ordnung?";
				link.l1 = "Ich will Dublonen, aber ich nehme an, dass der Schiffsmaster Pesos akzeptieren wird... Gib sie mir.";
				link.l1.go = "MarginNeed_peso";
				link.l2 = "Nein, ich brauche nur Dublonen.";
				link.l2.go = "MarginNeed_dublon_exit";
			}
			break;
		}
		if (iTemp > iSum && iTemp < 1000)
		{
			dialog.text = "Leider habe ich nicht so viel Geld. Daher kann ich Ihr Angebot trotz meines Wunsches nicht annehmen.";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 1000 && iTemp < 3000)
		{
			dialog.text = "Herr, verstehen Sie überhaupt, wovon Sie reden? Ist Ihnen bewusst, dass diese Summe zu groß ist? Verschwinde zum Teufel hier raus!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
			dialog.text = "Nun... Herr, Sie müssen zum Arzt gehen und zwar sofort. Es scheint, dass Sie ein sehr starkes Fieber haben oder... wie auch immer, Sie brauchen einen Arzt. Und ich habe zu viel zu tun. Lebewohl!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_dublon":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1]);
			TakeNItems(pchar, "gold_dublon", iTemp);
			AddQuestRecord("Marginpassenger", "9");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
		
		case "MarginNeed_peso":
			dialog.text = "Hier ist es, die ganze Summe in Pesos, genau das, was du wolltest... Wo ist "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1 = "Muss jetzt am Pier sein. Also kannst du gehen und den Passagier holen..";
			link.l1.go = "MarginNeed_peso_1";
		break;
		
		case "MarginNeed_peso_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1])*100;
			AddMoneyToCharacter(pchar, iTemp);
			AddQuestRecord("Marginpassenger", "10");
			AddQuestUserData("Marginpassenger", "sSum", FindRussianMoneyString(iTemp));
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
		break;
		
		case "MarginNeed_dublon_exit":
			dialog.text = "Ich kann Ihren Vorschlag dann nicht annehmen, auch wenn ich es sehr gerne tun würde. Auf Wiedersehen!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Marginpassenger", "11");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "MarginPass":
			dialog.text = "Was ist... Was passiert hier?!";
			link.l1 = "Es ist sehr einfach, "+NPCharSexPhrase(NPChar,"Kumpel","Mädchen")+". Du bist jetzt mein lieber Passagier. Ein bewachter Passagier. Versuche nicht zu widerstehen, sonst landest du im Laderaum.";
			link.l1.go = "MarginPass_1";
		break;
		
		case "MarginPass_1":
			dialog.text = "Meinen Sie, dass ich Ihr Gefangener bin?";
			link.l1 = "Oh, nein. Natürlich nicht. Nicht ein Gefangener, sondern ein lieber Gast. Ein sehr wertvoller Gast...";
			link.l1.go = "MarginPass_2";
		break;
		
		case "MarginPass_2":
			dialog.text = "Du... du wirst für deine Taten bezahlen!";
			link.l1 = "Du irrst dich schon wieder,"+NPCharSexPhrase(NPChar,", Kumpel",", Lieber")+". Ich werde nicht zahlen, aber ich werde bezahlt. Genug geredet, geh in deine Kabine!";
			link.l1.go = "MarginPass_3";
		break;
		
		case "MarginPass_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "", "", "none", "", "", "", 1.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.Marginpassenger_InWorldOver.over = "yes"; //снять прерывание
			pchar.quest.Marginpassenger_Sink.over = "yes"; //снять прерывание
			pchar.GenQuest.Marginpassenger = "take";
			if (rand(2) == 1) pchar.GenQuest.Marginpassenger.lose = "true";
			else Marginpassenger_CreateNeedman();
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Boarding")) AddQuestRecord("Marginpassenger", "6");
			else AddQuestRecord("Marginpassenger", "4");
			AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
