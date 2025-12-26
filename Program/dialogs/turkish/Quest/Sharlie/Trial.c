// диалоги НПС по квесту 'Карибские нравы'
void ProcessDialogEvent()
{
	ref NPChar, sld, rColony;
	aref Link, NextDiag;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hayır, hiçbir şey.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Жерар Лекруа
		case "lecrua":
			pchar.quest.Trial_LineOver.over = "yes"; //снять таймер
			dialog.text = "İyi günler. Siz olmalısınız "+GetFullName(pchar)+"?";
			link.l1 = "Haklısınız, Mösyö LeCroix. Kaptan "+GetFullName(pchar)+" hizmetinizdeyim. Moskof Fadey sizi bana tavsiye etti...";
			link.l1.go = "lecrua_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lecrua_1":
			iTemp = FindColony("Baster");
			rColony = GetColonyByIndex(iTemp);
			bOk = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			dialog.text = "Evet, evet. Sevgili dostum Fadey bana sizi ve durumunuzu ayrıntılı bir şekilde anlattı. Sizi kapıda görür görmez tanıdım. Söyleyin bakalım Kaptan, ne tür bir geminiz var?";
			if(sti(pchar.ship.type) == SHIP_NOTUSED || !bOk)
			{
				link.l1 = "Ah... Şu anda bir gemim yok, monsieur...";
				link.l1.go = "lecrua_noship";
			}
			else
			{
				link.l1 = "Bir    "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype),"Name")))+", adı   "+pchar.ship.name+".";
				if (6-sti(RealShips[sti(pchar.ship.type)].Class) < 0) link.l1.go = "lecrua_badship";
				else link.l1.go = "lecrua_2";
			}
		break;
		
		case "lecrua_noship":
			dialog.text = "Ha! Peki, gemin yoksa ne biçim kaptansın sen? Üzgünüm, monsieur, ama bu durumda sana verecek bir işim yok. Kendine iyi bak, Fadey'e selamlarımı ilet!";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "I don't have a ship at the moment";
		break;
		
		case "lecrua_badship":
			dialog.text = "Bu, kesinlikle olmaz. O bir gemi değil efendim, o bir sandal! Ne yazık ki, monsieur, bu role uygun değilsiniz. Fadey'e selam söyleyin benim için, iyi günler!";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "My ship wasn't big enough for him";
		break;
		
		case "lecrua_exit":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "3");
			AddQuestUserData("Trial", "sText", sTotalTemp);
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "lecrua_repeat":
			dialog.text = "Biz zaten her şeyi konuştuk, monsieur. Öyle değil mi?";
			link.l1 = "Evet, Monsieur LeCroix... Yoldayım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "lecrua_repeat";
		break;
		
		case "lecrua_2":
			dialog.text = "Mükemmel.   O halde, bana uygunsun.   Hemen denize açılmaya hazır mısın?";
			link.l1 = "Evet, monsieur, hazırım. Ne yapmam gerekiyor?";
			link.l1.go = "lecrua_3";
		break;
		
		case "lecrua_3":
			sld = characterFromId("BasTer_trader");
			dialog.text = "Fransız Hispaniola'sındaki Port-au-Prince'e küçük bir barut ve bomba sevkiyatı yapmalısın. Komutan bir süredir bunu bekliyor, o yüzden vakit kaybetme, yaklaşık on günün kaldı\nSaygılarımla "+GetFullName(sld)+" Teslimatını ve gemine yüklenmesini ben halledeceğim. Komutan bu iş için sana beş bin sekizlik ödeyecek.";
			link.l1 = "Hepsi bu kadar mı?";
			link.l1.go = "lecrua_4";
		break;
		
		case "lecrua_4":
			dialog.text = "Hayır, asla öyle değil, monsieur. Komutan size asıl işi, mühimmatı getirdiğinizde açıklayacak. Bu yük, önünüzdeki işin sadece küçük bir başlangıcı. Ama korkmayın, işi iyi yaparsanız gerçekten iyi para kazanırsınız.";
			link.l1 = "Tüm dikkatim sizde, monsieur. Gemim yükü almak için hazır.";
			link.l1.go = "lecrua_5";
		break;
		
		case "lecrua_5":
			dialog.text = "O halde vakit kaybetmeyelim, kaptan! Gemine git ve yelken açmaya hazırlan.";
			link.l1 = "Gidiyorum!";
			link.l1.go = "lecrua_6";
		break;
		
		case "lecrua_6":
			DialogExit();
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "4");
			pchar.questTemp.Trial = "fraht";
			AddMapQuestMarkCity("PortPax", false);
			// belamour legendary edition халява по чекбоксу
			if(!bImCasual) SetFunctionTimerCondition("Trial_FrahtFail", 0, 0, 17, false); // таймер
			else NewGameTip("Exploration mode: timer is disabled.");
			SetFunctionTimerCondition("Trial_LecruaHide", 0, 0, 1, false); // таймер
			// груз
			SetCharacterGoods(pchar, GOOD_BOMBS, GetCargoGoods(pchar, GOOD_BOMBS)+2500);
			SetCharacterGoods(pchar, GOOD_POWDER, GetCargoGoods(pchar, GOOD_POWDER)+2500);
			// Sinistra Пасхалка с Диего
			pchar.quest.VsD_DiegoNachalo.win_condition.l1 = "Ship_location";
			pchar.quest.VsD_DiegoNachalo.win_condition.l1.location = "PortPax_town";
			PChar.quest.VsD_DiegoNachalo.win_condition = "VsD_DiegoNachalo";
			
			// отключить все враждебные энкаунтеры на глобальной карте
			pchar.worldmapencountersoff = "1";
			SetFunctionTimerCondition("DelNavigatorNoShow", 0, 0, 180, false);
			pchar.systeminfo.tutorial.navigatorTrial = true;
		break;
		
		// Флориан Шоке
		case "florian_deck":
			if(!bImCasual) pchar.quest.Trial_CannonFail.over = "yes"; // belamour legendary edition снять таймер
			DelMapQuestMarkShore("shore47");
			DelLandQuestMark(npchar);
			sld = CharacterFromID("PortRoyal_shipyarder");
			if(CheckAttribute(sld, "TrialDelQuestMark"))
			{
				DeleteAttribute(sld, "TrialDelQuestMark");
				DelLandQuestMark(sld);
				DelMapQuestMarkCity("PortRoyal");
			}
			dialog.text = "Size nasıl yardımcı olabilirim, efendim?";
			link.l1 = "İyi günler, kaptan. Siz Florian Shoke olmalısınız, değil mi?";
			link.l1.go = "florian_deck_1";
		break;
		
		case "florian_deck_1":
			dialog.text = "Evet, benim. Ve siz de yanılmıyorsam Port-au-Prince'ten gelen posta gemisisiniz?";
			link.l1 = "Evet, senin için on beş topum var. Teslim tarihi ucu ucuna yetişti, zor bela başardım...";
			link.l1.go = "florian_deck_2";
		break;
		
		case "florian_deck_2":
			if (GetSquadronGoods(pchar, GOOD_CANNON_24) < 15)
			{
				dialog.text = "Hm. Garip bir mizah anlayışınız var, efendim! Nedense geminizden on beş top indirildiğini göremiyorum...";
				link.l1 = "Şey, bakın, bir sızıntı oldu ve yükün bir kısmını denize atmak zorunda kaldık...";
				link.l1.go = "florian_deck_fail";
			}
			else
			{
				dialog.text = "Seni görmek güzel, kaptan?..";
				link.l1 = ""+GetFullName(pchar)+". Kaptan "+GetFullName(pchar)+".";
				link.l1.go = "florian_deck_3";
			}
		break;
		
		case "florian_deck_3":
			dialog.text = "Tanıştığımıza memnun oldum. Hadi vakit kaybetmeyelim ve şu topları gemiye alalım. Bu iş kolay olmayacak, o yüzden adamlarının yardımına ihtiyacım var.";
			link.l1 = "Biz hallederiz. Sen oradaki, palanga ve makara sistemini serenin üstüne kur!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Trial_TakeCannons");
		break;
		
		case "florian_deck_fail":
			dialog.text = "Sen ne aptal adamsın! Bu basit işi bile beceremiyorsan, bir sonraki fırtınada kesin batarsın. Gemine dön kaptan, ve en iyi yaptığın şeyi yap, mesela asil hanımlara çiçek götürmek gibi. Hatta en iyisi, Avrupa'ya geri dön de Yeni Dünya'yı gerçek adamlara bırak. İyi günler bayım!";
			link.l1 = "Ama...";
			link.l1.go = "florian_deck_fail_1";
		break;
		
		case "florian_deck_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			RemoveCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24));
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "10");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
			ChangeCharacterNationReputation(pchar, FRANCE, -3);
		break;
		
		case "florian_deck_4":
			dialog.text = "Vay be, bu iş gerçekten susattı! Hizmetiniz için teşekkürler, kaptan! Alın ödülünüzü, iki yüz doblon.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "florian_deck_5";
		break;
		
		case "florian_deck_5":
			TakeNItems(pchar, "gold_dublon", 200);
			dialog.text = "Ama hepsi bu değil, kaptan. 75 altın çift eskudo daha kazanmak ister misiniz?";
			link.l1 = "Kulağa umut verici geliyor, ama bunun için benden ne isteyeceğinize bağlı, efendim.";
			link.l1.go = "florian_deck_6";
		break;
		
		case "florian_deck_6":
			dialog.text = "Yalan söylemeyeceğim, bu iş tehlikeli. Bildiğin gibi, değerli bir yük taşıyan İspanyol ağır bir kalyonu pusuya düşürmek için bekliyorum. Gemi tamir için tersaneye çekildi. Aldığım bilgilere göre dün yola çıkması gerekiyordu ama çıkmadı.\nAyrıca, Portobello’daki ajanım da buluşma noktasına gelip beklediğim haberleri ulaştıramadı. Sanırım İspanyollar onu yakaladı. Sana ödeme yapacağım; Portobello’ya gizlice girip iki şeyi öğrenmeni istiyorum: Kalyon neden hâlâ orada ve ajanıma ne oldu. Var mısın?";
			link.l1 = "Böyle bir iş için gerekli eğitime sahip değilim, korkarım. Ben bir centilmenim, casus değilim. Kendim de başımı belaya sokabilirim ve sana yardımcı olamam.";
			link.l1.go = "florian_deck_bye";
			link.l2 = "Kulağa tehlikeli geliyor, ama kârlı da olabilir. Şansımı deneyeceğim. Adamınızın adı ne, geminin adı ne?";
			link.l2.go = "florian_deck_7";
		break;
		
		case "florian_deck_bye":
			dialog.text = "Pekâlâ, ne kadar da kendini ayrıcalıklı sanıyorsun! Seni anlıyorum. O halde hoşça kal, kaptan, ve tekrar yardımın için teşekkürler!";
			link.l1 = "En iyi dileklerimle, Mösyö Shoke.";
			link.l1.go = "florian_deck_bye_1";
		break;
		
		case "florian_deck_bye_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "11");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_deck_7":
			dialog.text = "İyi dinle şimdi. Adamımın adı Sylvan Laforet, ama Portobello’da Jaime Silicio adını kullanıyor, bir tüccar olarak. Galyonun adı 'Alcantara'. Sana tavsiyem, şehre gece vakti, ormandan geçerek girmen. Portobello muhafızları bu aralar çok kuşkulu, üstelik Sylvan’ın kaybolması da onun hâlâ sağ olduğuna dair umut vermiyor. Buradan ayrılmam için iki günüm var, İspanyol devriyeleri bizi bulmadan önce. Bol şans, monsieur!";
			link.l1 = "Yakında görüşürüz, Mösyö Shoke...";
			link.l1.go = "florian_deck_8";
		break;
		
		case "florian_deck_8":
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true; // доступно ожидание и sailto
			DialogExit();
			npchar.DeckDialogNode = "florian_deck_repeat";
			NextDiag.CurrentNode = "florian_deck_repeat";
			pchar.questTemp.Trial = "spy";
			AddQuestRecord("Trial", "12");
			// belamour legendary edition -->
			if(!bImCasual) 
			{
				pchar.quest.trial_spy_over.win_condition.l1 = "Timer";
				pchar.quest.trial_spy_over.win_condition.l1.date.hour  = sti(GetTime() + 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
				pchar.quest.trial_spy_over.function = "Trial_SpyTimeOver";
			}
			else NewGameTip("Exploration mode: timer is disabled.");
			// <-- legendary edition
			//Log_Info("You have received amulet 'Gypsy's fan'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_4");
			pchar.quest.NewGameTip5.win_condition.l1 = "location";
			pchar.quest.NewGameTip5.win_condition.l1.location = "PortoBello_town";
			pchar.quest.NewGameTip5.function = "ShowNewGameTip";
			pchar.quest.NewGameTip5.text = "Guards are less suspicious when you walk at slow pace!";
			
			pchar.quest.Trial_CreatHabitue.win_condition.l1 = "location";
			pchar.quest.Trial_CreatHabitue.win_condition.l1.location = "PortoBello_tavern";
			pchar.quest.Trial_CreatHabitue.function = "Trial_CreatHabitue";
			
			pchar.quest.Tutorial_stealth.win_condition.l1 = "location";
			pchar.quest.Tutorial_stealth.win_condition.l1.location = "PortoBello_ExitTown";
			pchar.quest.Tutorial_stealth.function = "Tutorial_stealth";
			
			QuestPointerToLoc("shore47", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload3_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload4");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload41_back");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload4_back");
		break;
		
		case "florian_deck_repeat":
			dialog.text = "Her şeyi konuştuk, kaptan, değil mi?";
			link.l1 = "Evet. Geliyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_repeat";
		break;
		
		case "florian_failspy":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "İşler nasıl gidiyor, kaptan? Neler öğrenebildiniz?";
			link.l1 = "İşler pek iyi gitmiyor, Mösyö Shoke. Casusluk bana göre değilmiş, hemen fark ettiler. Birkaç muhafızla dövüştükten sonra şehirden kaçmak zorunda kaldım. Öğrenebildiğim tek şey, adamınız Sylvan Laforet'nin tutuklandığı ve hapiste tutulduğuydu.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_failspy_1":
			dialog.text = "Kahretsin! Bu hiç iyi değil... Galyon hakkında bir şey öğrenebildin mi?";
			link.l1 = "Hayır, yapmadım.";
			link.l1.go = "florian_failspy_2";
		break;
		
		case "florian_failspy_2":
			dialog.text = "Lanet olsun. Bu konuda gerçekten bilgiye ihtiyacım var. Ama bu ganimet çok büyük, vazgeçemem! Neyse, oraya başka bir gözcü göndermeyi deneyeceğim... Kaptan, senden şimdi beni yalnız bırakmamanı rica ediyorum. Yardımına ihtiyacım olabilir. Alacantara hakkında bilgi toplarken bir gün daha bekler misin?";
			link.l1 = "Elbette, bekleyeceğim! O başarısızlığı telafi etmek istiyorum.";
			link.l1.go = "florian_9";
			link.l2 = "Bence öyle değil. Görünüşe bakılırsa bu oyunlarda pek iyi değilim. Eve gidiyorum.";
			link.l2.go = "florian_failspy_3";
		break;
		
		case "florian_failspy_3":
			dialog.text = "Peki, bu senin seçimin. Bol şanslar, Kaptan.";
			link.l1 = "Elveda, Mösyö Shoke.";
			link.l1.go = "florian_failspy_4";
		break;
		
		case "florian_failspy_4":
			DialogExit();
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_failspy_5":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Nasıl gidiyor, kaptan? Neler öğrenebildiniz?";
			link.l1 = "İşler pek iyi gitmiyor, Mösyö Shoke. Casusluk bana göre değilmiş, hemen yakalandım. Tek öğrenebildiğim, adamınız Sylvain Laforet'in tutuklandığı ve bir yerde tutulduğuydu.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_9":
			dialog.text = "O halde geminize geçin, kaptan. Yarın aşağı yukarı aynı saatte, belki biraz daha geç, bana uğramanız gerekecek. Belki o zamana kadar bir şeyler öğrenmiş olurum. Karaya çıkmayın, geminizde beni bekleyin!";
			link.l1 = "Pekâlâ. Yapacağım.";
			link.l1.go = "florian_10";
		break;
		
		case "florian_10":
			dialog.text = "Ve kaptan, şu keseyi al. Sonuçta çabaların tamamen boşa gitmedi. En azından zavallı yaşlı Sylvan'a ne olduğunu artık biliyoruz...";
			link.l1 = "...";
			link.l1.go = "florian_11";
		break;
		
		case "florian_11":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", false);//закрыть остров	
			npchar.DeckDialogNode = "florian_deck_wait";
			NextDiag.CurrentNode = "florian_deck_wait";
			pchar.questTemp.Trial = "spy_wait";
			pchar.quest.Trial_spyfail_wait.win_condition.l1 = "Timer";
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.hour  = sti(GetTime()+rand(12));
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.function = "Trial_Spyfail_NextStage";
			TakeNItems(pchar, "purse2", 1);
			Log_Info("You've received a purse of doubloons");
		break;
		
		case "florian_deck_wait":
			dialog.text = "Kaptan, şu anda herhangi bir haber yok. Hâlâ bekliyoruz...";
			link.l1 = "Pekâlâ...";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_wait";
		break;
		
		case "florian_12":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Nasıl gidiyor, kaptan? Neler öğrenebildiniz?";
			link.l1 = "Bitti. Adamın, Sylvain Laforet, tutuklandı ve hapiste tutuluyor. Onun için her şey sona erdi.";
			link.l1.go = "florian_13";
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("shore47", "reload", "boat");
		break;
		
		case "florian_13":
			dialog.text = "Kahretsin! Bu korkunç... Galeon hakkında bir şey öğrenebildin mi?";
			link.l1 = "Evet. Bir süredir sefere hazırlanıyor, fakat Portobello valisi onu limanda tutmak istiyor. Şu anda, 'Alcantara' için barut taşıyan 'Puebla' adlı bir barquentine'nin Cartagena'dan gelmesini bekliyor. Galyondaki bir denizciye göre, ellerinde yeterince barut yok ve vali korsanlardan korkuyor.";
			link.l1.go = "florian_14";
		break;
		
		case "florian_14":
			dialog.text = "Ne kadar ilginç!";
			link.l1 = "Ama eğer Puebla üç gün içinde gelmezse, Alacantara beklemeyi bırakıp denize açılacak.";
			link.l1.go = "florian_15";
		break;
		
		case "florian_15":
			dialog.text = "Harika iş çıkardınız, Kaptan "+GetFullName(pchar)+"! Çok memnun oldum! Al, ödülünü hak ettin. Gerçekten bunu fazlasıyla hak ettin!";
			link.l1 = "Teşekkür ederim!   Benim için başka bir göreviniz var mı?";
			link.l1.go = "florian_16";
		break;
		
		case "florian_16":
			TakeNItems(pchar, "gold_dublon", 75);
			dialog.text = "Aklımdan geçenleri okuyorsun, "+GetFullName(pchar)+"! Yes, damn it! Since Alacantara is low on gunpowder, I can let her sail into the open sea and then force her to engage in a protracted naval fight, in which their powder will run out before ours, haha!\nYou should make sure that the supply barkentine Puebla never reaches Portobello. I can't sail close to the shore; patrols will notice my frigate easily and drive me off before I can intercept Alacantara\nYou can deal with Puebla on your own. Find her and get rid of her. Sink her or take her as a prize, I don't care. Just prevent her from getting here!\nIf you succeed, then go to Guadeloupe and see Gerard LeCroix. I believe that you already know him, don't you? He will pay you the coin you deserve.";
			link.l1 = "Anlaştık! Puebla'nın yolunu keseceğim, hemen yola çıkıyorum!";
			link.l1.go = "florian_19";
			link.l2 = "Wait a moment, Monsieur Choquet. The fact is, I'm still... let's just say, not particularly accustomed to naval battles. And you are the captain of a frigate; you obviously have more than one naval battle behind you. If it's not too much trouble, could you... how should I put it...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_17":
			dialog.text = "İyi ki geldiniz, kaptan. Casusumdan yeni haber aldım ve sizin için önemli bir görevim var.";
			link.l1 = "Tamamen seni dinliyorum.";
			link.l1.go = "florian_18";
		break;
		
		case "florian_18":
			dialog.text = "The Alacantara is ready to set sail, but the galleon's captain is waiting for the barkentine 'Puebla' to arrive from Cartagena loaded with ammunition. Apparently, the Alacantara doesn't have enough gunpowder, so the Spanish are not ready to set sail yet. But the captain's patience has its limits, and if Puebla doesn't come in three days, then the galleon will leave Portobello without her.\nThe Alacantara is low on gunpowder; I can let her sail into the open sea and then force her to engage in a protracted naval fight, in which their powder will run out before ours. Your objective is to intercept the Puebla and destroy her. Sink her or take her as a prize, I don't care. Just prevent that resupply barkentine from getting here!\nIf you succeed, then go to Guadeloupe and see Gerard LeCroix. I believe that you already know him, don't you? He will pay you the coin you deserve.";
			link.l1 = "Anlaştık! Puebla'nın yolunu keseceğim!";
			link.l1.go = "florian_19";
			link.l2 = "Wait a moment, Monsieur Choquet. The fact is, I'm still... Let's just say, not particularly accustomed to naval battles. And you are the captain of a frigate; you obviously have more than one naval battle behind you. If it's not too much trouble, could you... How should I put it...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_19":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", true); // открыть остров
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			Trial_CreatePueblaBarqueInWorld();
			pchar.questTemp.Trial = "puebla";
			AddQuestRecord("Trial", "19");
		break;
		// belamour legendary edition дополнительное обучение -->
		case "florian_guide_01":
			dialog.text = "Benden deniz savaşı taktikleri üzerine bir ders vermemi ister misiniz? Memnuniyetle, kaptan! Özellikle de bu benim de işime gelir: 'Puebla'yı başarıyla ele geçireceğinizden emin olmak istiyorum.";
			link.l1 = "Hayır, öyle demek istemedim. Peki, boşver: Eminim bir barkantin yakalamakta hiç zorlanmam.";
			link.l1.go = "florian_19";
			link.l2 = "Evet, tam olarak bunu kastetmiştim. Eminim bu yeni bilgi bana zarar vermeyecek.";
			link.l2.go = "florian_guide_02";
		break;
		
		case "florian_guide_02":
			dialog.text = "Yani, unutmaman gereken ilk şey şu: savaşın yarısı daha başlamadan kazanılır ya da kaybedilir. Her şey senin ve geminin ne kadar hazır olduğuna bağlı.";
			link.l1 = "...";
			link.l1.go = "florian_guide_03";
		break;
		
		case "florian_guide_03":
			dialog.text = "Öncelikle, geminizin tamir edildiğinden emin olun. Gövdede delikler varsa, düşmanın sizi dibe göndermesi hiç de zor olmaz. Yelkenlerinizin yerinde paçavralar sallanıyorsa, bu da hareket kabiliyetinizi ciddi şekilde kısıtlar. Güç dengesi onun lehine değilse düşman kolayca kaçabilir ya da daha kötüsü, sizi yakalayıp elverişsiz bir çatışmaya sürükleyebilir – hatta hemen güverteye çıkabilir. Ayrıca, yırtık yelkenlerle rüzgarüstü avantajını elde etmekte de zorlanırsınız – yani rakibinizin rüzgarına karşı konuma geçmekte, ki asıl olmak istediğiniz yer orasıdır.";
			link.l1 = "Rüzgar avantajı, anladım. Başka bir şey var mı?";
			link.l1.go = "florian_guide_04";
		break;
		
		case "florian_guide_04":
			dialog.text = "Yeterince adamın olduğundan emin ol. 42 librelik topları olan en güçlü gemi bile, bir topçu üç topu birden doldurmaya koşturuyorsa ve yelkenlerle ilgilenecek kimse yoksa işe yaramaz hale gelir. Açıkçası, ben olsam böyle bir gemiye hemen çıkar, el koyardım.";
			link.l1 = "Yeterince adam var, anladım.";
			link.l1.go = "florian_guide_05";
		break;
		
		case "florian_guide_05":
			dialog.text = "Ayrıca toplarına dikkat et: zamanla aşınır ve patlayabilirler. Namlu durumu bozulur ve topların savaş ortasında patlamaya başlarsa, bu senin için çok kötü sonuçlanabilir. Benim hiç şansım yoktu: yola çıktığım top partisi birkaç döküm hatasıyla doluydu. Sen zamanında yedek getirmeseydin, operasyonu bırakırdım, çünkü Militant, Alcantara'ya karşı ateş gücü bakımından çok zayıf kalırdı. Aletleri zamanında değiştirmek gerekir.";
			link.l1 = "Şimdi neden bu kadar önemli olduğunu anlıyorum!";
			link.l1.go = "florian_guide_06";
		break;
		
		case "florian_guide_06":
			dialog.text = "Topların yanı sıra, mühimmat miktarına da dikkat et. Alcantara bu yüzden benim olacak. Eğer barut stokları azsa, uzun bir savaşa dayanamaz – hemen yakın dövüşe girmek zorunda kalır. Ben de bunu kullanacağım: fırkateynim daha hızlı, ağır bir kalyon ondan kaçamaz. Ama benim de yaklaşmam gerekmiyor: uzun menzilde topçu düellosuna zorlayacağım ve sonra, Alcantara'nın barutu bittiğinde, yaklaşacağım, saçma ile tarayacağım ve gemiye çıkacağım.";
			link.l1 = "Umutsuz bir durum...";
			link.l1.go = "florian_guide_07";
		break;
		
		case "florian_guide_07":
			dialog.text = "Aynen öyle. Barutuna ve cephanene dikkat et. Top güllen biterse, muhtemelen düşman gemisini batıramazsın. Saçma şarjın kalmazsa, sayıca üstünlerse güverteye çıkmaya kalkışamazsın. Zincir güllelerin ya da knipple’ların yoksa, düşmanı yakalayamaz ya da o senden hızlıysa kaçamazsın. Tüm cephane türleri önemlidir.";
			link.l1 = "Öğretici oldu, teşekkürler.";
			link.l1.go = "florian_guide_08";
		break;
		
		case "florian_guide_08":
			dialog.text = "Ve son olarak, kendi geminizin ve düşman gemisinin türüne ve büyüklüğüne göre uygun taktikleri kullanın. Denizde ateş gücüyle hız arasında bir denge vardır. Büyük ve yavaş bir gemiyle, bir brig ya da korveti güverteye çıkmak için kovalamak anlamsızdır - zincir gülleyle onu önce yavaşlatmadan asla yetişemezsiniz. Böyle durumlarda, uzaktan top atışıyla onu parçalamak ve enkazı yağmalamak daha akıllıcadır. Yine de böyle bir gemiye çıkmanız gerekiyorsa, hızlı ve çevik bir gemi kullanmak daha iyidir.";
			link.l1 = "...";
			link.l1.go = "florian_guide_09";
		break;
		
		case "florian_guide_09":
			dialog.text = "Aynı zamanda, bir brig ile hat gemisine kafa tutmaya kalkma. O devasa gemiden gelecek bir salvo, küçük teknelerin gövdelerini paramparça eder. Hız ve manevra kabiliyetindeki üstünlüğünü kullan, direklerini ve donanımını indir, sonra hala gemiye çıkman gerekiyorsa güverteye saçma atışı yaparak yaklaş. Eğer batırman gerekiyorsa... kolay olmayacak, ama mümkün. Gemiye çıkıp barut mahzenini ateşe verebilirsin, ama kaçmak asla utanç değildir. İyi bir kaptan, gereksiz kahramanlık uğruna gemisini ve mürettebatını kesin ölümden kurtarır. Unutma, ihtiyat ve sağduyu çoğu zaman cesaretin en önemli parçasıdır.";
			link.l1 = "Çok teşekkür ederim, Mösyö Choquet!";
			link.l1.go = "florian_guide_10";
		break;
		
		case "florian_guide_10":
			AddCharacterSkillDontClearExp(pchar, SKILL_CANNONS, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_ACCURACY, 1);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_CANNONS));
			notification(XI_ConvertString("Experience Bonus")+": +1 ", SKILL_CANNONS);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_ACCURACY));
			notification(XI_ConvertString("Experience Bonus")+": +1 ",SKILL_ACCURACY);
			dialog.text = "Sana yardımcı olmak güzel, kaptan. Umarım bu bilgi gelecekte işine yarar.";
			link.l1 = "Eminim işe yarayacak. 'Puebla'yı yakalamaya gidiyoruz!";
			link.l1.go = "florian_19";
		break;
		// <-- legendary edition дополнительное обучение

		// испанский офицер в таверне
		case "tavern_officer":
			dialog.text = "Garip bir aksanınız var, señor. Yoksa 'monsieur' mü demeliyim? Jaime Silicio'yu görmek ister misiniz? Belki de aynı hücreyi paylaşabilirsiniz. Alın onu, çocuklar!";
			link.l1 = "Pekâlâ, eğer aksanımı beğenmiyorsan, belki seni Fransız kılıç ustalığıyla tanıştırabilirim!";
			link.l1.go = "tavern_officer_1";
		break;
		
		case "tavern_officer_1":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "Trial_AfterTavernFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
