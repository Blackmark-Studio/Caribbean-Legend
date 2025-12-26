// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Devam et, ne istiyorsun?","Biz de tam bundan bahsediyorduk. Herhalde unuttunuz...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Bakın, burası bir dükkân. İnsanlar burada alışveriş yapar. Lütfen beni rahatsız etmeyin!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Doğru, nedense unutmuşum...","Evet, gerçekten de üçüncü kez...","Hm, yapmayacağım...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Dinle, "+npchar.name+", son zamanlarda Isla Tesoro'da Miguel Dichoso'yu gördün mü?";
				link.l1.go = "tieyasal";
			}
			// Addon 2016-1 Jason пиратскаЯ линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_start")
			{
				link.l1 = ""+npchar.name+", Marcus Tyrex adına buradayım. Bir iş için adama ihtiyacınız olduğunu söyledi.";
				link.l1.go = "mtraxx";
			}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_win")
			{
				link.l1 = ""+npchar.name+", 'Rosbohom' bulundu ve ele geçirildi. Yükü boşaltıp saymaya başlayalım mı?";
				link.l1.go = "mtraxx_5";
			}
		break;
				
		// город майя
		case "tieyasal":
			dialog.text = "Evet, geldi. Buradan gemisi için erzak aldı. Hem de çok yakın bir zamanda. Birkaç günle birbirinizi kaçırmışsınız. Bu arada, hâlâ bu yerleşimde olabilir. Ben kimseye casusluk yapmam, bilirsiniz. Biraz daha soruşturun, kim bilir, belki de donunuzu bulursunuz.";
			link.l1 = "Pekala. Bilgi için teşekkürler!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
			pchar.quest.Mtraxx_PasqualeLate.over = "yes";
            dialog.text = "Kesinlikle! Zamanında geldiğine sevindim. Şimdi sana işin özünü anlatayım...";
			link.l1 = "Tamamen sizi dinliyorum.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
			string sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")));
            dialog.text = "Şu anda bir "+sTemp+", 'Rosbohom' adındaki Hollanda gemisi, bir muhafız gemisi eşliğinde sularımıza yaklaşıyor. Gemide abanoz yüklü ve Willemstad'dan Avrupa'ya güvenli bir yolculuk için başka bir muhafız gemisiyle buluşmaya gidiyorlar. Hangi rotayı seçeceklerini bilmiyorum, Sint Maarten üzerinden mi yoksa Espanyol üzerinden mi, ama buluşma noktalarının koordinatlarını biliyorum\nGörevin, Hollanda gemisini orada bulmak, ticaret gemisine çıkmak ve yükünü bana getirmek. Yük teslim edildiğinde ödemeni alacaksın.";
			link.l1 = "Anladım. Zaman ve yer?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			int i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
			int n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
            dialog.text = ""+sti(pchar.questTemp.Mtraxx.Crdn.degN)+" "+i+" Kuzey ve "+sti(pchar.questTemp.Mtraxx.Crdn.degW)+" "+n+" Batı. Isla Tesoro'nun güneyinde ya da güneybatısında bir yerde olmalı. Ben bu işlerden pek anlamam, denizci değilim, ama sen öylesin. Bu işi halletmek için yaklaşık beş günün var.";
			link.l1 = "Anlaşıldı... Mesajı aldım. O halde vakit kaybetmeyelim!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Yolun açık olsun, kaptan. Seni ve yükü bekliyor olacağım.";
			link.l1 = "...";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_convoy";
		   i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
           n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
		   AddQuestRecord("Roger_4", "3");
		   AddQuestUserData("Roger_4", "sShip", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")+ "Gen")));
		   AddQuestUserData("Roger_4", "sdegN", sti(pchar.questTemp.Mtraxx.Crdn.degN));
		   AddQuestUserData("Roger_4", "sminN", i);
		   AddQuestUserData("Roger_4", "sdegW", sti(pchar.questTemp.Mtraxx.Crdn.degW));
		   AddQuestUserData("Roger_4", "sminW", n);
		   SetFunctionTimerCondition("Mtraxx_PasqualeTimeConvoy", 0, 0, 6, false);
		   SetFunctionTimerCondition("Mtraxx_PasqualeConvoyOver", 0, 0, 7, false);
		break;
		
		case "mtraxx_5":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_EBONY);
			if (iTotalTemp < 1)
			{
				dialog.text = "Benimle dalga mı geçiyorsun, genç adam? Ambarlarında tek bir abanoz kerestesi bile yok! Bu düpedüz sahtekârlık! Defol buradan! Marcus'a bunu bildireceğim! Çık dışarı!!!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < makeint(sti(pchar.questTemp.Mtraxx.Crdn.Ebony)/4))
			{
				dialog.text = "Benimle dalga mı geçiyorsun, evlat? Ambarında sadece birkaç abanoz kıymığı var! Bu düpedüz sahtekârlık! Defol buradan! Marcus'a bunu bildireceğim! Çık dışarı!!!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < sti(pchar.questTemp.Mtraxx.Crdn.Ebony)-20)
			{
				dialog.text = "Rosbohom'un en azından "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.Crdn.Ebony))+" abanozdan. Neden bana daha az getirdin?";
				link.l1 = "Şey... biliyorsunuz, çatışma sırasında bir kısmından kurtulmak zorunda kaldım. Bir de o fareler, kahrolsunlar...";
				link.l1.go = "mtraxx_7";
				break;
			}
            dialog.text = "Pekala. Ne kadarınız var? "+FindRussianQtyString(iTotalTemp)+"? Harika! Her bir parça için sana 150 peso ödeyeceğim.";
			link.l1 = "150 sekizlik mi? Demek ki abanoz çok daha pahalıya geliyor.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_6":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_angry";
		   DoQuestReloadToLocation("Pirates_town", "reload", "reload6", "");
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_7":
            dialog.text = "Fareler mi? Hımm... Peki. Parça başı 100 peso, sonra gidebilirsin.";
			link.l1 = "Yalnızca 100 peso mu? Bu resmen soygun!";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			AddMoneyToCharacter(pchar, iTotalTemp*100);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Soygun sizin işiniz kaptan, ben ise basit bir tüccarım. Paranızı alın ve daha fazla tartışmayalım, zaten yükümün bir kısmını başka yerde satarak iyi bir kazanç elde ettiniz.";
			link.l1 = "Öyleyse cehenneme git!";
			link.l1.go = "mtraxx_9";
		break;
		
		case "mtraxx_9":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_fail";
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_10":
            dialog.text = "And you are right, captain, but first, try selling stolen goods and see how much other merchants will pay you for them. The price I am offering is very high. Second, it was my lead; you would never have found that caravan on your own. Besides, there were other valuables and goods on it, and I am not claiming them. Third, I will give you the highest credit in the eyes of Marcus Tyrex, and that is worth a great deal, trust me. And finally, fourth, a poor merchant must make a living somehow.";
			link.l1 = "Vay canına! Böyle argümanlar karşısında geri çekilmeliyim "+npchar.name+". Biraz hesap yapalım.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
			AddMoneyToCharacter(pchar, iTotalTemp*150);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Harika. Alın paralarınızı. Memnun oldum. Ara sıra dükkânıma uğramayı unutmayın. Denizde şansınız bol olsun!";
			link.l1 = "Ve siz de kendi işinizde...";
			link.l1.go = "mtraxx_12";
		break;
		
		case "mtraxx_12":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_complete";
		   AddQuestRecord("Roger_4", "9");
		   pchar.quest.mtr_pasq_fin.win_condition.l1 = "location";
		   pchar.quest.mtr_pasq_fin.win_condition.l1.location = "Pirates_town";
		   pchar.quest.mtr_pasq_fin.function = "Mtraxx_PasqualeJeffry";
		   bDisableFastReload = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
