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
			dialog.text = "Bu bir hata. Geliştiricilere haber verin.";
			link.l1 = "Tabii!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Wine_fort":
			dialog.text = "Şişeyi getirdin mi?";
			if (CheckCharacterItem(pchar, "potionwine"))
			{
				link.l1 = "Evet, aynen öyle yaptım. Ona 700 peso ödedim, senden ise 1.000 peso bekliyorum.";
				link.l1.go = "Wine_fort_1";
			}
			link.l2 = "Hayır, üzerinde çalışıyorum.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort";
		break;
	
		case "Wine_fort_1":
			AddMoneyToCharacter(pchar, 1000);
			RemoveItems(PChar, "potionwine", 1);
			dialog.text = "Tanrı'ya şükür, susuzluktan ölüyordum. Çok teşekkür ederim, efendim! Alın şu binliği, ben de şişeyi alıyorum, haha! Şimdi bakın, madem böyle güzel bir alışveriş yaptık, sizden bir ricam daha olacak\nBenim ve arkadaşlarımın... ileride kullanmak üzere biraz daha şarap getirebilir misiniz? Az önce bir kaçakçı çetesini soyduk da, harcayacak paramız var, hehe...";
			link.l1 = "Üzgünüm dostum, senin için bir kez daha içki almaya vaktim yok.";
			link.l1.go = "Wine_fort_exit";
			link.l2 = "Para her zaman makbuldür. Kaç şişe istiyorsun?";
			link.l2.go = "Wine_fort_2";
		break;
	
	case "Wine_fort_exit":
			DelLandQuestMark(npchar);
			WineTraderQMDel();
			dialog.text = "Nasıl istersen. Yine de yardımın için teşekkürler! Şerefe, sağlığına!";
			link.l1 = "İyi iş çıkarmaya devam et, asker!";
			link.l1.go = "exit";
			sld = characterFromId(pchar.questTemp.Wine.id);	
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			pchar.questTemp.Wine.fail = "true";
			CloseQuestHeader("Wine");
	break;
	
		case "Wine_fort_2":
			dialog.text = "Şişesi sekiz yüzlük bin paraya, altmış şişe alabiliriz, ama fazlası olmaz. Ama ondan az getirme sakın - o zaman sadece daha çok susarız!";
			link.l1 = "Anlaşıldı, altmış şişeden fazla ve ondan az olmayacak. Şarabınızı getireceğim.";
			link.l1.go = "Wine_fort_3";
		break;
	
		case "Wine_fort_3":
			dialog.text = "Ne mutlu, iyi içkinin müjdesini getiren ayaklara! Sana güveniyorum, kaptan. Ah, az kalsın unutuyordum! İçkiyi buraya bir haftadan kısa sürede getirmen gerekecek, çünkü deniz piyade birliğim yedi gün içinde filoya katılmak üzere buradan ayrılıyor ve bir kez gittiğimizde birkaç ay boyunca dönmeyeceğiz.";
			link.l1 = "Anladım. Hızlı olmaya çalışacağım.";
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
			dialog.text = "Peki kaptan, şarabı getirdin mi?";
			if (sti(pchar.items.potionwine) >= 10)
			{
				link.l1 = "Evet, var.";
				link.l1.go = "Wine_take";
			}
			link.l2 = "Hayır.   Hâlâ üzerinde çalışıyorum.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_take":
			pchar.questTemp.Wine.Qty = sti(pchar.items.potionwine);
			pchar.questTemp.Wine.Money = sti(pchar.questTemp.Wine.Qty)*1000;
			if (sti(pchar.items.potionwine) > 60)
			{
				dialog.text = "Holy Saint Arnulf, pray for us! That's a lot of wine! Excellent! Regrettably, as I said, we can only afford sixty bottles; unfortunately, we don't have enough money to buy more. Take your pesos and I'll take good care of these sixty bottles. Please keep the rest.";
				link.l1 = "Teşekkür ederim. Sen ve asker arkadaşların, sağlığıma bir kadeh kaldırmayı unutmayın!";
				link.l1.go = "Wine_take_1";
				pchar.questTemp.Wine.Money = 60000;
				RemoveItems(PChar, "potionwine", 60);
			}
			else
			{
				dialog.text = "Tekrar hoş geldin. Bakalım... Getirmişsin "+sti(pchar.questTemp.Wine.Qty)+" şişeler. Güzel! Onları alıyorum. Ödeme ise "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Money))".";
				link.l1 = "Teşekkür ederim. Sen ve asker arkadaşların, sağlığıma bir kadeh kaldırmayı unutmayın!";
				link.l1.go = "Wine_take_1";
				RemoveItems(PChar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			}
		break;
	
		case "Wine_take_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.Wine.Money));
			dialog.text = "Elbette yapacağız, "+GetAddress_Form(NPChar)+"! Davul toplanma işareti çalıyor, şimdi gitmem gerek. Hoşça kal!";
			link.l1 = "Rüzgarın ve denizin hep yanında olsun, dostum!";
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
