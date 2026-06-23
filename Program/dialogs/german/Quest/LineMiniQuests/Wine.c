void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Das ist ein Fehler. Informiere die Entwickler.";
			link.l1 = "Sicher!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Wine_fort":
			dialog.text = "Hast du die Flasche mitgebracht?";
			if (CheckCharacterItem(pchar, "potionwine"))
			{
				link.l1 = "Aye, das habe ich. Ich habe 700 Pesos dafür bezahlt, also erwarte ich 1000 Pesos von dir.";
				link.l1.go = "Wine_fort_1";
			}
			link.l2 = "Nein, ich arbeite daran.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort";
		break;
	
		case "Wine_fort_1":
			AddMoneyToCharacter(pchar, 1000);
			RemoveItems(PChar, "potionwine", 1);
			dialog.text = "Gott sei Dank, ich war schon ganz ausgetrocknet. Vielen Dank, mein Herr! Hier, nimm deine tausend und ich nehme deine Flasche, haha! Hey, da wir hier schon gute Geschäfte machen, habe ich noch eine Bitte an dich\nKönntest du mehr Wein für mich und meine Freunde für unseren... zukünftigen Gebrauch besorgen? Wir haben gerade eine Bande von Schmugglern ausgenommen, also haben wir Münzen übrig, hehe...";
			link.l1 = "Entschuldigung Kumpel, ich habe keine Zeit, noch einen Schnapslauf für dich zu machen.";
			link.l1.go = "Wine_fort_exit";
			link.l2 = "Geld ist immer gut. Wie viele Flaschen brauchst du?";
			link.l2.go = "Wine_fort_2";
		break;
	
	case "Wine_fort_exit":
			DelLandQuestMark(npchar);
			WineTraderQMDel();
			dialog.text = "Wie du wünschst. Danke trotzdem für deine Hilfe! Prost und auf deine gute Gesundheit!";
			link.l1 = "Mach weiter so, Soldat!";
			link.l1.go = "exit";
			sld = characterFromId(pchar.questTemp.Wine.id);	
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			pchar.questTemp.Wine.fail = "true";
			CloseQuestHeader("Wine");
	break;
	
		case "Wine_fort_2":
			dialog.text = "Bei 1000 Dublonen pro Flasche können wir uns sechzig Flaschen leisten, aber nicht mehr. Aber bring uns auch nicht weniger als zehn - das würde uns nur durstig machen!";
			link.l1 = "Verstanden, nicht mehr als 60 Flaschen und nicht weniger als zehn. Ich bringe Ihren Wein.";
			link.l1.go = "Wine_fort_3";
		break;
	
		case "Wine_fort_3":
			dialog.text = "Gesegnet seien die Füße, die frohe Botschaften guten Trunks bringen! Ich zähle auf dich, Kapitän. Ach, ich habe fast vergessen! Du musst den Schnaps in weniger als einer Woche hierher bringen, denn meine Marinekompanie wird in sieben Tagen zur Flotte versetzt und wir werden für ein paar Monate weg sein, sobald wir abreisen.";
			link.l1 = "Ich verstehe. Ich werde versuchen, schnell zu sein.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.bottles = "true";
			npchar.lifeday = 7;
			AddQuestRecord("Wine", "1");
			AddQuestUserData("Wine", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Wine.City+"Gen"));
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.SName);
			SetFunctionTimerCondition("Soldier_wait", 0, 0, 7, false);
			NextDiag.TempNode = "Wine_fort_check";
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
	
		case "Wine_fort_check":
			dialog.text = "Also, Kapitän, haben Sie den Wein mitgebracht?";
			if (int(pchar.items.potionwine) >= 10)
			{
				link.l1 = "Ja, habe ich.";
				link.l1.go = "Wine_take";
			}
			link.l2 = "Nein. Ich arbeite noch daran.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_take":
			pchar.questTemp.Wine.Qty = int(pchar.items.potionwine);
			pchar.questTemp.Wine.Money = int(pchar.questTemp.Wine.Qty)*1000;
			if (int(pchar.items.potionwine) > 60)
			{
				dialog.text = "Heiliger Sankt Arnulf, bete für uns! Das ist viel Wein! Hervorragend! Bedauerlicherweise, wie ich schon sagte, können wir uns nur sechzig Flaschen leisten, leider haben wir nicht genug Geld, um mehr zu kaufen. Nimm deine Pesos und ich werde gut auf diese sechzig Flaschen aufpassen. Bitte behalte den Rest.";
				link.l1 = "Danke. Stellen Sie sicher, dass Sie und Ihre Soldatenfreunde auf meine Gesundheit anstoßen!";
				link.l1.go = "Wine_take_1";
				pchar.questTemp.Wine.Money = 60000;
				RemoveItems(PChar, "potionwine", 60);
			}
			else
			{
				dialog.text = "Willkommen zurück. Lassen wir mal sehen... Du hast gebracht "+int(pchar.questTemp.Wine.Qty)+" Flaschen. Schön! Ich nehme sie. Die Bezahlung ist "+FindRussianMoneyString(int(pchar.questTemp.Wine.Money))+".";
				link.l1 = "Danke dir. Stell sicher, dass du und deine Soldatenfreunde auf meine Gesundheit anstoßt!";
				link.l1.go = "Wine_take_1";
				RemoveItems(PChar, "potionwine", int(pchar.questTemp.Wine.Qty));
			}
		break;
	
		case "Wine_take_1":
			AddMoneyToCharacter(pchar, int(pchar.questTemp.Wine.Money));
			dialog.text = "Wir werden sicherlich, "+GetAddress_Form(NPChar)+"! Die Trommel ruft zur Versammlung, ich muss jetzt gehen. Auf Wiedersehen!";
			link.l1 = "Günstige Winde und folgende Meere, Kumpel!";
			link.l1.go = "Wine_take_2";
		break;
	
		case "Wine_take_2":
			DelLandQuestMark(npchar);
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info ("You handed over the wine");
			pchar.quest.Soldier_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.City");
			sld = characterFromId(pchar.questTemp.Wine.id);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
