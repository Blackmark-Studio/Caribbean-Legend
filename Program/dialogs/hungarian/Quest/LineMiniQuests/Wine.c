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
			dialog.text = "Ez egy bogár. Szólj a fejlesztôknek.";
			link.l1 = "Persze!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Wine_fort":
			dialog.text = "Elhoztad az üveget?";
			if (CheckCharacterItem(pchar, "potionwine"))
			{
				link.l1 = "Igen, ezt tettem. 700 pezót fizettem érte, ezért 1000 pezót várok tôled.";
				link.l1.go = "Wine_fort_1";
			}
			link.l2 = "Nem, dolgozom rajta.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort";
		break;
	
		case "Wine_fort_1":
			AddMoneyToCharacter(pchar, 1000);
			RemoveItems(PChar, "potionwine", 1);
			dialog.text = "Isten áldjon, kezdtem kiszáradni. Köszönöm szépen, uram! Tessék, vegye el az ezresét, én pedig az üvegét, haha! Hé, ha már így is jól megy az üzlet, lenne még egy kérésem hozzád\nHoznál még bort nekem és a barátaimnak a... jövôbeni használatra? Épp most vertünk le egy csempészbandát, úgyhogy van egy kis pénzünk, hehe...";
			link.l1 = "Sajnálom, haver, de nincs idôm még egy italt elhozni neked.";
			link.l1.go = "Wine_fort_exit";
			link.l2 = "A pénz mindig jól jön. Hány üvegre van szükséged?";
			link.l2.go = "Wine_fort_2";
		break;
	
	case "Wine_fort_exit":
			DelLandQuestMark(npchar);
			WineTraderQMDel();
			dialog.text = "Ahogy akarod. Köszönöm a segítségedet! Egészségedre és a jó egészségedre!";
			link.l1 = "Csak így tovább, katona!";
			link.l1.go = "exit";
			sld = characterFromId(pchar.questTemp.Wine.id);	
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			pchar.questTemp.Wine.fail = "true";
			CloseQuestHeader("Wine");
	break;
	
		case "Wine_fort_2":
			dialog.text = "1000 darab pesó egy üvegért, hatvan palackot tudunk venni, de többet nem. De tíznél kevesebbet ne hozzatok nekünk - attól csak szomjasak leszünk!";
			link.l1 = "Értettem, nem több, mint hatvan üveg, és nem kevesebb, mint tíz. Hozom a bort.";
			link.l1.go = "Wine_fort_3";
		break;
	
		case "Wine_fort_3":
			dialog.text = "Boldogok a lábak, akik jó ital örömhírét viszik! Számítok rád, kapitány. Á, majdnem elfelejtettem! Kevesebb mint egy héten belül ide kell hoznod a piát, mert a tengerészcsapatom hét nap múlva kivonul a flottához, és ha elmegyünk, néhány hónapig nem leszünk itthon.";
			link.l1 = "Értem. Megpróbálok gyors lenni.";
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
			dialog.text = "Szóval, kapitány, hozta a bort?";
			if (sti(pchar.items.potionwine) >= 10)
			{
				link.l1 = "Igen, hoztam.";
				link.l1.go = "Wine_take";
			}
			link.l2 = "Nem. Még dolgozom rajta.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_take":
			pchar.questTemp.Wine.Qty = sti(pchar.items.potionwine);
			pchar.questTemp.Wine.Money = sti(pchar.questTemp.Wine.Qty)*1000;
			if (sti(pchar.items.potionwine) > 60)
			{
				dialog.text = "Szent Szent Arnulf imádkozzon értünk! Ez rengeteg bor! Nagyszerû! Sajnos, mint mondtam, csak hatvan palackot engedhetünk meg magunknak, többre sajnos nincs elég pénzünk. Fogjátok a pezótokat, és én majd vigyázok erre a hatvan palackra. A többit tartsa meg, kérem.";
				link.l1 = "Köszönöm. Legyen biztos benne, hogy Ön és katona barátai emeljék poharukat az egészségemre!";
				link.l1.go = "Wine_take_1";
				pchar.questTemp.Wine.Money = 60000;
				RemoveItems(PChar, "potionwine", 60);
			}
			else
			{
				dialog.text = "Üdvözlöm önöket. Lássuk csak... Hoztál "+sti(pchar.questTemp.Wine.Qty)+" üvegeket. Szép! Elviszem ôket. A fizetés " + FindRussianMoneyString(sti(pchar.questTemp.Wine.Money))".";
				link.l1 = "Köszönöm. Legyen biztos benne, hogy Ön és katona barátai emeljék poharukat az egészségemre!";
				link.l1.go = "Wine_take_1";
				RemoveItems(PChar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			}
		break;
	
		case "Wine_take_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.Wine.Money));
			dialog.text = "Természetesen fogunk, " + GetAddress_Form(NPChar) + "! A dob összeszerelés hangzik, most mennem kell. Viszontlátásra!";
			link.l1 = "Szép szelet és jó vizet, pajtás!";
			link.l1.go = "Wine_take_2";
		break;
	
		case "Wine_take_2":
			DelLandQuestMark(npchar);
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info ("Átadtad a bort");
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
