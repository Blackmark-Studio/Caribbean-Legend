// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref FortChref;
	FortChref = GetFortCommander(NPChar.City);
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsunuz? Sorunuzu sorun.","Dinliyorum, sorunuz nedir?"),"Bu, ikinci kez sormaya çalışmanız...","Bu, üçüncü kez sormaya çalıştığınız oldu...","Bu ne zaman bitecek?! Ben meşgul bir adamım, sömürge işleriyle uğraşıyorum ve sen hâlâ beni rahatsız ediyorsun!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şimdi değil. Yeri ve zamanı değil."),"Doğru... Ama sonra, şimdi değil...","Soracağım... Ama biraz sonra...","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_6")
			{
				link.l1 = "Ekselansları, hapsedilen subay Lope Montoro hakkında buradayım...";
                link.l1.go = "Mtraxx";
			}
		break;
		
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Zaten her şeyi aldınız. Daha ne istiyorsunuz?","Almadığınız bir şey kaldı mı?");
            link.l1 = RandPhraseSimple("Sadece etrafa bakıyorum...","Sadece kontrol ediyorum, belki bir şeyi almayı unutmuş olabilirim...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "Slavetrader_HavanaAttack":
			dialog.text = "Kahrolası haydutlar! Havana'ya saldırmaya cüret mi ediyorsunuz?! Ne istiyorsunuz?!";
			link.l1 = "Bir an düşün, anlayacaksın.";
			link.l1.go = "Slavetrader_HavanaAttack_1";
			pchar.quest.Slavetrader_HavanaOver.over = "yes";
			AfterTownBattle();
        break;
		
		case "Slavetrader_HavanaAttack_1":
			dialog.text = "Altın, elbette! Sizi ilgilendiren başka ne olabilir ki altından başka?! Ve bizim elimizde yok... Sadece dükkanda birkaç ölçek kadar var.";
			link.l1 = "Ha-ha... Hayır, altınla ilgilenmiyoruz. Buraya fildişi için geldik... siyah olanından. Ne demek istediğimi anlıyor musun?";
			link.l1.go = "Slavetrader_HavanaAttack_2";
        break;
		
		case "Slavetrader_HavanaAttack_2":
			if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)//для особо хитрых - нефиг лезть с суши
			{
				dialog.text = "Ha! Buraya köleler için geldiğinden şüphelenmiştim. Ama onlar kalede tutuluyor. Takviyelerimiz yolda ve çeten bir an önce yok edilecek.";
				link.l1 = "Kahretsin! Peki, burada otur ve kıpırdama... Hadi buradan gidelim! Lanet olsun...";
				link.l1.go = "Slavetrader_HavanaAttack_lose";
			}
			else
			{
				dialog.text = "Ama nasıl... Bunu nasıl bildiniz?";
				link.l1 = "Ha! Ancak bir aptal 5.000 köleyi bir araya toplayıp kimsenin bunu fark etmeyeceğini umar. Buradan lanet Tortuga'ya kadar kokuları geliyor... Umarım onları senden alacağımızı anlıyorsun.";
				link.l1.go = "Slavetrader_HavanaAttack_3";
			}
        break;
		
		case "Slavetrader_HavanaAttack_3":
			dialog.text = "Pekâlâ, zaten kazandınız ve şiddetinize boyun eğmek zorundayız. Ama o soygundan ve iki İspanyol savaş gemisini batırdıktan sonra adaletten kaçacağınızı sanmayın.";
			link.l1 = "Böyle gerilme yoksa kalp krizi geçireceksin. Buraya otur ve sakın kıpırdama...";
			link.l1.go = "Slavetrader_HavanaAttack_4";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 50);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
        break;
		
		 case "Slavetrader_HavanaAttack_4":
			string sTemp;
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//теперь можно на карту
            SetCharacterGoods(pchar, GOOD_SLAVES, 5000+rand(500));// c перегрузом пойдёт
            Log_SetStringToLog("Slaves have been put onto your ship");
			Log_SetStringToLog("You've got 30 days to deliver the slaves to your employer");
			chrDisableReloadToLocation = false;
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			AddQuestRecord("Slavetrader", "27");
			AddQuestUserData("Slavetrader", "sQty", sTemp);
			SetFunctionTimerCondition("Slavetrader_FiveTSlavesOver", 0, 0, 30, false);	//таймер
			pchar.questTemp.Slavetrader = "Win_HavanaFort";
        break;
		
		case "Slavetrader_HavanaAttack_lose":
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			chrDisableReloadToLocation = false;
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//можно на карту
			pchar.quest.Slavetrader_HavanaAttack.over = "yes";//если из Сантьяго по суше пришёл - уберем корабли
			AddQuestRecord("Slavetrader", "27_1");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
        break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "Mtraxx":
            dialog.text = "Ne garip... yine şikayetler mi?";
			link.l1 = "Hayır, hayır, tam tersi, Ekselansları. Lope eski bir ordu arkadaşım, Avrupa'da birlikte savaştık... Ona yardımcı olmayı çok isterim ve bu konuda sizin yardımınızı istemeye geldim.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_1":
            dialog.text = "Hm... Pekâlâ, bana geldiğine göre, bu... saçma hikayeyi zaten biliyorsun, değil mi?";
			link.l1 = "Evet, Ekselansları.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Don Rosario Gusman ile iletişime geçmeni öneririm. O da senin gibi don Lope Montero'ya yardım etmek istiyor. Mağdurla iletişim kurmaya çalışmış, ancak görüşmeler sonuçsuz kalmış. Onunla buluş, sana ayrıntıları anlatacaktır. Don Rosario'yu her gün öğleden sonra dört ile sekiz arasında sokaklarda bulabilirsin. Şehir muhafızlarının karakollarını her gün tamamen denetler.";
			link.l1 = "Teşekkür ederim, Ekselansları!";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_7";
			AddQuestRecord("Roger_1", "17");
			Mtraxx_CreateRosario();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
