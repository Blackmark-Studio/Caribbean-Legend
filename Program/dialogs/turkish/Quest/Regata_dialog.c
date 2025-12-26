void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//вестовой
		case "Regata_Cureer":
			dialog.text = "İyi günler. Siz kaptan mısınız "+GetFullName(pchar)+"?";
			link.l1 = "Evet, benim. Peki mesele ne?";
			link.l1.go = "Regata_Cureer_1";
		break;
		
		case "Regata_Cureer_1":
			dialog.text = "Jamaika Valisi Sir Edward D'Oyley'den size bir mektup getirdim.";
			link.l1 = "Vay canına! Bunu beklemiyordum... Peki vali benden ne istiyor?";
			link.l1.go = "Regata_Cureer_2";
		break;
		
		case "Regata_Cureer_2":
			dialog.text = "Mektubu okuyun, efendim. Kısacası, tüm takımadada düzenlenen bir regattaya, yani bir yarışa katılmanız için davet edildiniz. Denizcilikteki yetenekleriniz ve denizdeki olağanüstü hızınızın söylentileri gözden kaçmadı.";
			link.l1 = "İnanılmaz! Şey, ben... Bunu düşüneceğim.";
			link.l1.go = "Regata_Cureer_3";
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_Regata");
			AddQuestRecordInfo("RegataLetter", "1");
		break;
		
		case "Regata_Cureer_3":
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
			{
				dialog.text = "Ayrıca, Port Royal limanına ücretsiz giriş hakkı da sana verildi. İşte 30 günlük bir ruhsat. Artık görevim tamamlandı. Hoşça kal, kaptan.";
				link.l1 = "Teşekkür ederim. Ruhsat çok makbule geçti. Hoşça kal!";
				link.l1.go = "Cureer_exit";
				GiveNationLicence(HOLLAND, 30);
			}
			else
			{
				dialog.text = "İyi. Şimdi görevim tamamlandı. Hoşça kal, Kaptan.";
				link.l1 = "Elveda!";
				link.l1.go = "Cureer_exit";
			}
		break;
		
		case "Cureer_exit":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.Regata.ToPortRoyal = "true";
			SetQuestHeader("Regata");
			AddQuestRecord("Regata", "1");
		break;
		
		//распорядитель регаты
		case "Regata_Head":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Günaydın. Regattaya katılıyorsunuz, öyle mi?";
				link.l1 = "Kesinlikle, efendim. Benim adım "+GetFullName(pchar)+". Davetiyeyi aldım.";
				link.l1.go = "Regata_Head_1";
			}
			else
			{
				dialog.text = "Bir şey ister misiniz, efendim?";
				link.l1 = "Hayır, bir şey yok. Zaten gidiyorum.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_1":
			iTest = FindColony("PortRoyal"); 
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				dialog.text = "Sizi tanıdığıma memnun oldum, Kaptan "+GetFullName(pchar)+" . O halde başlayalım. Zaten mektuptan temel bilgileri biliyorsun, değil mi? Sadece lüver tipi gemiler ve filonda yalnızca o gemi olmalı, yoksa regattaya katılamazsın. Bu şartları yerine getirdin mi?";
				// belamour legendary edition допускаем курьерский люггер 
				ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
				if((GetCompanionQuantity(pchar) > 1) || !ok)
				{
					link.l1 = "Henüz değil. Şimdi halledeceğim ve yakında döneceğim.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
				else
				{
					link.l1 = "Evet, var.";
					link.l1.go = "Regata_Head_2";
				}
			}
			else
			{
				dialog.text = "Regattaya katılmaya geldiniz, ama geminiz nerede, kaptan?";
				link.l1 = "Affedersiniz efendim. Gemimi hemen limana getireceğim.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head_repeat";
			}
		break;
		
		case "Regata_Head_repeat":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				iTest = FindColony("PortRoyal"); 
				if (iTest != -1)
				{
					rColony = GetColonyByIndex(iTest);
				}
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
				{
					ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
					dialog.text = "Ah, yine sen. Regata için gereken her şeyi hallettin mi?";
					// belamour legendary edition допускаем курьерский люггер 
					if ((GetCompanionQuantity(pchar) > 1) || !ok)
					{
						link.l1 = "Henüz değil. Şimdi halledip yakında dönerim.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Regata_Head_repeat";
					}
					else
					{
						link.l1 = "Evet, var.";
						link.l1.go = "Regata_Head_2";
					}
				}
				else
				{
					dialog.text = "Kaptan, geminizi demirlemiş görmeden konuşacak bir şeyimiz yok. Beni anladınız mı, yoksa tekrar etmemi ister misiniz?";
					link.l1 = "Affedersiniz efendim. Gemimi hemen limana getireceğim.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
			}
			else
			{
				dialog.text = "Bir şey ister misiniz, efendim?";
				link.l1 = "Hayır... bir şey değil. Zaten gidiyorum.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_2":
			dialog.text = "Pekâlâ. Şimdi, sıradaki soru. Geminizin adı nedir?";
			link.l1 = "'"+pchar.Ship.Name+"'.";
			link.l1.go = "Regata_Head_3";
		break;
		
		case "Regata_Head_3":
			dialog.text = "Regatta İngiliz yetkilileri tarafından düzenlendiği ve kurallar sabit olduğu için, etkinlik süresince geminizin adı değiştirilmeli. Merak etmeyin, bu tüm katılımcılar için geçerli.";
			link.l1 = "Geminin adını değiştirmek uğursuzluk getirir derler.";
			link.l1.go = "Regata_Head_4";
		break;
		
		case "Regata_Head_4":
			dialog.text = "Regatta bittikten sonra ismini tekrar değiştirebilirsin. Yani, lugger'ın 'Azize Catherine' adını taşıyacak.";
			link.l1 = "Anladım, efendim. İsmi değiştireceğim.";
			link.l1.go = "Regata_Head_5";
			pchar.Ship.Name = "Saint Catherine";
		break;
		
		case "Regata_Head_5":
			dialog.text = "Şimdi gelelim regattanın kendisine. Dikkatlice dinle. Sana ayrıca kuralları yazılı olarak da vereceğim.\nRegatta Port Royal'da başlar ve biter. Uğraman gereken beş nokta var\nİlki Port Royal'dan Belize, West Main'e\nİkincisi Belize'den Port-au-Prince, Hispaniola'ya\nÜçüncüsü Port-au-Prince'den St. John's, Antigua'ya\nDördüncüsü St. John's'tan Bridgetown, Barbados'a\nVe sonuncusu Bridgetown'dan Port Royal'a\nAnlaştık mı?";
			link.l1 = "Açık ve net, efendim.";
			link.l1.go = "Regata_Head_6";
		break;
		
		case "Regata_Head_6":
			dialog.text = "Harika. Şu şehirlerin liman ofislerinde yoklama yaptırmalısınız: Belize, Port-au-Prince, St. John's, Bridgetown. Bu şehirlerden birini atlar veya doğru sırayı bozarsanız diskalifiye edilirsiniz\nYarış süresince ofisler yirmi dört saat açık olacak. Kapıyı çalın, sizi içeri alacaklar.";
			link.l1 = "Anlaşıldı.";
			link.l1.go = "Regata_Head_7";
		break;
		
		case "Regata_Head_7":
			dialog.text = "Gemini değiştirmek veya filonuza yeni gemiler eklemek yasaktır. Bu her şehirde kontrol edilecek, aklınızda bulundurun.";
			link.l1 = "Düşüneceğim. Genelde kazanan kim olur, ödüller hakkında konuşabilir miyiz?";
			link.l1.go = "Regata_Head_8";
		break;
		
		case "Regata_Head_8":
			dialog.text = "Regatta'da sadece bir kazanan var - gemisi Port Royal'a ilk ulaşan kaptan. Ödül ise oldukça değerli. Kazanan, 250.000 peso gibi büyük bir meblağ alacak. Ayrıca, ona değerli hediyelerden oluşan bir set sunulacak.";
			link.l1 = "Yani, kaybedenler hiçbir şey alamıyor mu?";
			link.l1.go = "Regata_Head_9";
		break;
		
		case "Regata_Head_9":
			dialog.text = "Aynen öyle. Ayrıca, İngiliz kolonilerinin hem zengin hem de fakir birçok vatandaşı regatta'nın kazananı üzerine bahis oynar. Sen de... kendine bahis oynayabilirsin. Genelde her kaptan böyle yapar. Kazanırsan, daha da fazla kazanırsın—bir de motivasyonu unutma. Normalde bahisleri ben kabul ediyorum. Kendi zaferine bahis oynayacak mısın?";
			link.l1 = "Ha! Tabii ki, öyleyim. Ne kadar bahis oynayabilirim?";
			link.l1.go = "Regata_rate";
			link.l2 = "Düşüneceğim. Belki bir bahse girerim.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_Head_10":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Düşünmek istersen düşün. Regatta başlamadan önce biraz vaktin var.";
				link.l1 = "Pekala. Ne zaman başlıyor?";
				link.l1.go = "Regata_Head_11";
				DeleteAttribute(pchar, "questTemp.Regata.Rate");
				pchar.questTemp.Regata.Ratenext = "true";
			}
			else
			{
				dialog.text = "Düşünmek istiyorsan düşün. Regatta başlamadan önce biraz vaktin var.";
				link.l1 = "Pekala.";
				link.l1.go = "exit";
			}
		break;
		
		case "Regata_Head_11":
			CreateRegataAdversaries();
			dialog.text = "Üç gün sonra, saat on ikide, öğlen. İskelenin orada ol, sakın geç kalma. Beş rakibin olacak.\n"+pchar.questTemp.Regata.AdversaryName.a+", of the "+pchar.questTemp.Regata.AdversaryShipName.a+"\n"+pchar.questTemp.Regata.AdversaryName.b+", of the "+pchar.questTemp.Regata.AdversaryShipName.b+"\n"+pchar.questTemp.Regata.AdversaryName.c+", of the "+pchar.questTemp.Regata.AdversaryShipName.c+"\n"+pchar.questTemp.Regata.AdversaryName.d+", of the "+pchar.questTemp.Regata.AdversaryShipName.d+"\n"+pchar.questTemp.Regata.AdversaryName.e+",   olan "+pchar.questTemp.Regata.AdversaryShipName.e+"\nHepsi deneyimli kaptanlar. Görünüşe bakılırsa bu kadar. Kurallar sayfasını da al, ne olur ne olmaz. Başlangıçta görüşürüz!";
			link.l1 = "Hoşça kalın, efendim.";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND) link.l1.go = "Regata_Head_13";
			else link.l1.go = "Regata_Head_12";
		break;
		
		case "Regata_Head_12":
			DialogExit();
			pchar.quest.RegataToPortRoyalTimeOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("Regata_SetTime", 0, 0, 3, false);
			pchar.quest.Regata_Lost.win_condition.l1 = "Timer";
			pchar.quest.Regata_Lost.win_condition.l1.date.hour  = 13.0;
			pchar.quest.Regata_Lost.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Lost.function = "Regata_Lost";
			pchar.quest.Regata_Start.win_condition.l1 = "Timer";
			pchar.quest.Regata_Start.win_condition.l1.date.hour  = 12.0;
			pchar.quest.Regata_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l2 = "locator";
			pchar.quest.Regata_Start.win_condition.l2.location = "Portroyal_town";
			pchar.quest.Regata_Start.win_condition.l2.locator_group = "reload";
			pchar.quest.Regata_Start.win_condition.l2.locator = "reload1_back";
			pchar.quest.Regata_Start.function = "Regata_Start";
			AddQuestRecordInfo("RegataRules", "1");
			NextDiag.CurrentNode = "Regata_Prepare";
			DeleteAttribute(pchar, "questTemp.Regata.Begin");
			pchar.questTemp.Regata.Prepare = "true";
			AddQuestRecord("Regata", "2");
		break;
		
		case "Regata_Head_13":
			dialog.text = "Bekle! Sana İngiliz ve Fransız limanlarını ziyaret etmen için 30 günlük bir izin vereceğim. Regatta bir aydan fazla sürmez. Lütfen, al bunu.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "Regata_Head_12";
			GiveNationLicence(HOLLAND, 30);
		break;
		
		case "Regata_rate":
			dialog.text = "Ne kadar bahis oynuyorsun?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Regata_rate_1";
			link.l2 = "Sanırım hâlâ biraz düşünmeye ihtiyacım var.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_1":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Regata.Rate = sti(iQty);
			if (iQty < 10000)
			{
				dialog.text = "Beyim, bu hiç komik değil, şaka da değil. Böyle az bir paraya çalışmam.";
				link.l1 = "Affedersiniz... Bahsi tekrar gözden geçirelim.";
				link.l1.go = "Regata_rate";
				break;
			}
			if (iQty > 100000)
			{
				dialog.text = "Efendim, regatta kuralları gereği böyle bir bahsi kabul edemem. Lütfen makul bir değere düşürün.";
				link.l1 = "Ne yazık. O zaman tutarı tekrar gözden geçirelim.";
				link.l1.go = "Regata_rate";
				break;
			}
			dialog.text = ""+iQty+"? Bu güzel bir bahis. Kabul etmeye hazırım. Paranız nerede, efendim?";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Regata.Rate))
			{
				link.l1 = "Lütfen, al bunu.";
				link.l1.go = "Regata_rate_2";
			}
			link.l2 = "Şu anda yeterince param yok. Sonra tekrar uğrar, bir bahse gireriz. Biraz daha düşüneceğim, belki miktarı tekrar gözden geçiririm.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.Rate));
			pchar.questTemp.Regata.Advantage = sti(pchar.questTemp.Regata.Rate)*(1.5+frand(1.5)); // dlc
			dialog.text = "Splendid! Now all you need to do is be the first, and the prize will be yours. Its final value may vary; it all depends on how many people stake on you in the end.";
			if (!CheckAttribute(pchar, "questTemp.Regata.Ratenext"))
			{
				link.l1 = "Anladım. Regatta ne zaman başlıyor?";
				link.l1.go = "Regata_Head_11";
			}
			else
			{
				link.l1 = "Anladım. Başlangıcı bekleyeceğim. Görüşürüz!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata.Ratenext");
				NextDiag.TempNode = "Regata_Prepare";
			}
		break;
		
		case "Regata_Prepare":
			dialog.text = "Ah, yine geldiniz, kaptan "+GetFullName(pchar)+"? Ne istiyorsun?";
			if (!CheckAttribute(pchar, "questTemp.Regata.Rate"))
			{
				link.l1 = "Zaferime bahse girmek istiyorum.";
				link.l1.go = "Regata_rate";
			}
			link.l2 = "Hayır, önemli bir şey değil. Sadece seni selamlamak istedim.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Regata_Prepare";
		break;
		
		//старт регаты
		case "Regata_CitMan":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Kaptan, bu ilk seferiniz mi? Size söyleyeyim, dikkatli olmalısınız. Rakipleriniz sizin için hiç hoş olmayan sürprizler hazırlamış olabilir...","Kaptan, umudumu sana bağladım. Beni hayal kırıklığına uğratma!","Kaptan, regatta limanlarındaki yerliler sana bir şeyler satmayı teklif edebilir. Bunlar çoğu zaman gerçekten işe yarar. Bunu aklında bulundur."),LinkRandPhrase("İyi yolculuklar, kaptan!","Kaptan, lütfen dikkatli olun, Kastilyalılar genellikle İspanyol sularında seyredenlerin lügerlerini avlarlar.","Bazı karanlık tiplerin regatta kaptanlarına sık sık 'hizmetlerini' teklif ettiğini duydum. Bu teklifleri kabul edip etmeyeceğine karar vermek sana kalmış."));
			link.l1 = "Evet, evet, tabii ki... sanırım teşekkür ederim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitMan";
		break;
		
		case "Regata_CitWom":
			dialog.text = LinkRandPhrase("Kaptan, kocamla birlikte senin zaferine on bin bahse girdik. Bizi hayal kırıklığına uğratma! Senin için dua edeceğim!","Kaptan! Sana bol şans diliyorum!","Uhm...   sen gerçekten cesur ve yürekli bir kaptansın...");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitWom";
		break;
		
		case "Regata_CitHorse":
			dialog.text = LinkRandPhrase("Hey, denizci! Güzelliğe el salla! Dönüşünü bekliyor olacağım!","Hey, denizci! Madam, beni regatta kazananına ödül olarak bedavaya vereceğini söyledi... Kazanmaya çalış, çok yakışıklısın!","Buralara tekrar uğramayı unutma, yakışıklı, seni en yüksek standartlarda memnun edeceğiz!");
			link.l1 = "Pekala, hah... Düşüneceğim, teşekkürler!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitHorse";
		break;
		
		case "Regata_Prepare_1":
			if (sti(environment.time) < 12.0)
			{
				dialog.text = "Kaptan, regatta saat on ikide başlayacak. Şimdi dinlenebilirsiniz, biz şenlikleri hazırlıyoruz. Öğle vakti geri dönün, rakipleriniz de aynısını yapacak.";
				link.l1 = "Pekâlâ, efendim! Başlangıcı bekliyor olacağım...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Buyurun, kaptan.";
				link.l1 = "Mürettebatım ve ben hazırız, efendim! Sinyali bekliyorum...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_Prepare_1";
		break;
		
		case "Regata_Start":
			dialog.text = "Efendiler, işte buradayız. Regattayı başlatıyorum. Kuralları biliyorsunuz. Kim buraya ilk dönerse, kazanan ilan edilecek. Hanımefendiler ve beyefendiler, cesur kaptanlarımıza bol şans dileyelim!\nBeyler! Hazır mısınız? Hazır! Başla! Gidin!";
			link.l1 = "...";
			link.l1.go = "Regata_Start_1";
		break;
		
		case "Regata_Start_1":
			DialogExit();
			PlaySound("people fight\mushketshot.wav");
			log_info("The regatta has started! Get aboard! Head to Belize!");
			for (i=1; i <=5; i++)
			{
				sld = characterFromId("Regata_Cap_F"+i);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			Island_SetReloadEnableGlobal("Jamaica", false);//на остров нельзя
			SetFunctionTimerCondition("ReturnJamaicaNorm", 0, 0, 1, false);//таймер на возврат нормы
			LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false);//откроем выход в море
			DeleteAttribute(pchar, "questTemp.Regata.Prepare");
			pchar.questTemp.Regata.Go = "true";
			pchar.questTemp.Regata.Town = "Beliz";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
			//ситуации
			pchar.quest.Regata_ShYarder.win_condition.l1 = "location";
			pchar.quest.Regata_ShYarder.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_ShYarder.function = "RegataShipyarder";
			sld = characterFromId("Beliz_shipyarder");
			LAi_RemoveLoginTime(sld);
			AddQuestRecord("Regata", "3");
		break;
		//старт регаты
		
		//верфист с парусами
		case "Regata_Shipyarder":
			dialog.text = "Selamlar, kaptan! Karayipler regattasına katıldığınız bana bildirildi.";
			link.l1 = "Doğru. Haberler gerçekten de takımadada rüzgardan hızlı yayılıyor.";
			link.l1.go = "Regata_Shipyarder_1";
		break;
		
		case "Regata_Shipyarder_1":
			dialog.text = "Evet, kaptan. Size bir teklifim var. Geminiz ve regatta ile ilgili.";
			link.l1 = "Heh! İlginç. Sizi dinliyorum, bayım.";
			link.l1.go = "Regata_Shipyarder_2";
		break;
		
		case "Regata_Shipyarder_2":
			dialog.text = "Bir lugger için mükemmel yelkenlerim var, en kaliteli pamuktan yapılmış. Bu yelkenler geminizin hızlanmasını artıracak ve rakipleriniz karşısında size zaman kazandıracak.\nEğer almak isterseniz, size satmaya hazırım.";
			link.l1 = "Bu yelkenler için ne kadar istiyorsun?";
			link.l1.go = "Regata_Shipyarder_3";
		break;
		
		case "Regata_Shipyarder_3":
			dialog.text = "Sadece 15.000 peso. Böyle bir... durum için bunun oldukça mütevazı bir fiyat olduğunu kabul etmelisiniz.";
			if (makeint(Pchar.money) >= 15000)
			{
				link.l1 = "Katılıyorum. Bu yeni yelkenleri luggerim için alıyorum. Alın, paranız burada efendim. Ben giriş işlemlerimi hallederken, onları gemime teslim edebilir misiniz?";
				link.l1.go = "Regata_Shipyarder_4";
			}
			link.l2 = "Bu kadar param yok. Yani yelkenlerini satın alamayacağım.";
			link.l2.go = "Regata_Shipyarder_exit";
		break;
		
		case "Regata_Shipyarder_4":
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = "Emredersiniz, efendim. Adamlarım sadece işareti bekliyor, size söz veriyorum, pişman olmayacaksınız. Üstelik, bu yelkenler maviye çok güzel boyanmış. Güzelliğiniz bunu beğenecektir.";
			link.l1 = "Pekala o zaman! Ben gitmeliyim ve sen yelkenlerle ilgilen.";
			link.l1.go = "Shipyarder_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp))+12;//выиграл 12 часов у всех
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
			}
			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = 3;
			SetSailsColor(Pchar, 5);
			AddQuestRecord("Regata", "28");
		break;
		
		case "Regata_Shipyarder_exit":
			dialog.text = "Ne yazık. Peki, bu senin seçimin. Hoşça kal, kaptan.";
			link.l1 = "Hoşça kal!";
			link.l1.go = "Shipyarder_exit";
			pchar.questTemp.Regata.AdversarySecondTransition.Time.d = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.d)-16;//четвертый соперник выиграл 16 часов
			log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.e));
			AddQuestRecord("Regata", "29");
		break;
		
		case "Shipyarder_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "Beliz_Shipyard", "sit", "sit1", "ReturnRegataSYNorm", 5);
		break;
		//верфист с парусами
		
		//контрики с пушками
		case "Regata_Contra":
			dialog.text = "Merhaba, Kaptan "+GetFullName(pchar)+". Sizinle konuşmamız lazım... aslında, bu sadece bir... iş teklifi.";
			link.l1 = "Hm. İlginç, peki benim kim olduğumu nereden biliyorsun?";
			link.l1.go = "Regata_Contra_1";
		break;
		
		case "Regata_Contra_1":
			dialog.text = "Ne diyebilirim ki, her zaman yetenekli olduğumu söylerlerdi... Ha-ha, Regatta tam gaz devam ediyor ve sen de katılıyorsun, ünlü bir Kaptansın!";
			link.l1 = "Anladım. Peki, söyle bakalım ne düşünüyorsun.";
			link.l1.go = "Regata_Contra_2";
		break;
		
		case "Regata_Contra_2":
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				sTemp = pchar.questTemp.Regata.ContraIndex;
				dialog.text = "Önünüzde bir katılımcı daha olduğunu biliyoruz - "+pchar.questTemp.Regata.AdversaryName.(sTemp)+" of the "+pchar.questTemp.Regata.AdversaryShipName.(sTemp)+". Limandan çok uzun zaman önce ayrılmadı, yakında Gonaives Burnu'ndan geçiyor olacak.";
			}
			else
			{
				dialog.text = "Arkanızda bir katılımcı daha olduğunu biliyoruz - "+pchar.questTemp.Regata.AdversaryName.b+" of the "+pchar.questTemp.Regata.AdversaryShipName.b+". Birkaç saat içinde burada olacak.";
			}
			link.l1 = "Hmm... oldukça iyi bilgilendirilmişsiniz.";
			link.l1.go = "Regata_Contra_3";
		break;
		
		case "Regata_Contra_3":
			if (sti(pchar.questTemp.Regata.Index != 1)) sTemp = "letting you pass ahead of him and take his position";
			else sTemp = "therefore you will be taking a lead for a long time";
			dialog.text = "Kesinlikle. Şimdi sadede gelelim. Sana yardımımızı, senin paran karşılığında sunuyoruz. Gemimizden dört topu Gonaives Körfezi'nin arkasındaki buruna yerleştirdik. Herhangi bir regatta gemisi oradan geçmek zorunda\nToplar zincirli güllelerle yüklü. Anlaşırsak, topçu dostlarımıza rakibinin yelkenlerini parçalamalarını söylerim, böylece o da tamirle vakit kaybetmek zorunda kalır, "+sTemp+".";
			link.l1 = "Bu hizmet için ne kadar istiyorsun?";
			link.l1.go = "Regata_Contra_4";
			link.l2 = "Hayır. Kazanmak için böyle yöntemlere başvurmayacağım. Benim hakkımda yanılmışsınız. Hoşça kalın, baylar.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_exit":
			dialog.text = "Pekala, kaptan, seçim sizin. Hoşça kalın.";
			link.l1 = "Burun hakkındaki bilgi için teşekkür ederim. Ondan uzak duracağım.";
			link.l1.go = "Contra_exit";
			AddQuestRecord("Regata", "31");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Regata_Contra_4":
			if (sti(pchar.questTemp.Regata.Index != 1)) iTemp = 50000;
			else iTemp = 30000;
			dialog.text = "Pek bir şey değil. Sadece "+iTemp+" peso. Ve rakiplerinden biri neredeyse iki gün kaybedecek çünkü... bir kaza olacak, ha-ha!";
			if (makeint(Pchar.money) >= iTemp)
			{
				link.l1 = "Heh! Akıllıca konuşuyorsun, dostum! Parayı ben veriyorum. Ama bana ne garanti veriyorsun ki işini yapacaksın? Ya da burnu geçerken gemime ateş açmayacağından nasıl emin olabilirim?";
				link.l1.go = "Regata_Contra_5";
			}
			link.l2 = "Bu kadar param yok. Yani hizmetlerinizden yararlanamayacağım.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_5":
			dialog.text = "Kaptan, lütfen, biz kaçakçıyız, korsan değiliz. Hepimiz dürüst insanlarız... kendimize göre. Hizmetlerimizden daha önce yararlanmış olmalısınız, değil mi? Size söz veriyorum. Güvenebilirsiniz.";
			link.l1 = "Pekâlâ, tamam, al paranı.";
			link.l1.go = "Regata_Contra_6";
		break;
		
		case "Regata_Contra_6":
			AddQuestRecord("Regata", "30");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "Bu anlaşmadan memnun kalacaksınız, kaptan. Ben de topçularıma hemen haber vereceğim. Bol şans!";
			link.l1 = "Sana da...";
			link.l1.go = "Contra_exit";
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				AddMoneyToCharacter(pchar, -50000);
				sTemp = pchar.questTemp.Regata.ContraIndex;
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp))+48;//задержка на 48 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
			}
			else
			{
				AddMoneyToCharacter(pchar, -30000);
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.b = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b)+36;//задержка на 36 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b));
			}
		break;
		
		case "Contra_exit":
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("RegataContra_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest2", "none", "", "", "", 10.0);
			}
		break;
		//контрики с пушками
		
		//падре
		case "Regata_Padre":
			pchar.questTemp.Regata.BranderName = GenerateRandomNameToShip(ENGLAND);
			dialog.text = "Sana iyi günler evladım. Seni selamlamak ve mütevazı bir ricada bulunmak isterim: İngiltere'nin ve ulu Rabbimizin sadık bir hizmetkârı olarak cemaat hazinesine katkıda bulunmak ister misin?";
			link.l1 = "Padre, insanlar hayır işlerini ruhları istediği için yapar, zorunluluktan değil. Şu sıralar, takımadadaki herkes regatta kaptanlarını soymaya karar vermiş gibi geliyor bana...";
			link.l1.go = "Regata_Padre_exit";
			link.l2 = "Elbette, kutsal baba. Ne kadar yeterli olur?";
			link.l2.go = "Regata_Padre_1";
		break;
		
		case "Regata_Padre_1":
			dialog.text = "İmkanların ve gönlün neye elveriyorsa, oğlum. Cemaatimiz en küçük bağışa bile minnettar kalacaktır.";
			Link.l1.edit = 4;			
			link.l1 = "";
			link.l1.go = "Regata_Padre_2";
		break;
		
		case "Regata_Padre_2":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Bu yanlış bir tavır, oğlum. Hepimizin günahları var, ruhunu unutma. Yaratıcımızın huzuruna çıkacaksın... belki de çok yakında.";
				link.l1 = "Vaazlarına ihtiyacım yok, kutsal baba. Elveda.";
				link.l1.go = "Padre_exit";
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				AddQuestRecord("Regata", "35");
				break;
			}
			if (iTemp > 0 && iTemp <= 1000)//ничего не скажет
			{
				dialog.text = "Cemaatimiz ve ben bu mütevazı hediye için size teşekkür ediyoruz.";
				link.l1 = "Hoş geldiniz, kutsal baba.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "35");
			}
			if (iTemp > 1000 && iTemp <= 5000)//1 категория - намекнет
			{
				dialog.text = "Cemaatimiz ve ben bu hediyeniz için size teşekkür ediyoruz. Ve seni uyarmak isterim evladım, bazı günahkâr adamlar sana zarar vermeyi planlıyor. Denizde dikkatli ol!";
				link.l1 = "Peder, her gün birileri bana karşı bir şeyler planlıyor... Ama kaderim için endişelendiğiniz için teşekkür ederim.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "34");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 5000 && iTemp <= 10000)//2 категория - скажет
			{
				dialog.text = "Bu değerli hediye için cemaatimiz adına sana teşekkür ediyorum. Karşılığında, seni uyarmak isterim: gerçekten kötü niyetli bazı insanlar sana karşı komplo kuruyor. Duyduğuma göre, bu alçak sapkınlar gemini tam bu limanda batırmayı planlıyorlar.\nBu hain iş için barut yüklü bir gemi bile hazırlamışlar. Dikkatli ol evladım, bu yoldan çıkmış ruhlar niyetlerinde çok ciddiler... Tanrı seni korusun!";
				link.l1 = "Teşekkür ederim, kutsal baba. Dikkatli olacağım.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "33");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 10000)//3 категория - расскажет полностью
			{
				dialog.text = "Çok cömertsin, oğlum. Tanrı'nın alçakgönüllü bir hizmetkârı olarak, kilisemizin iyiliği için vermeye razı olduğun tüm parayı kabul etmem mümkün değil. Sadece 10.000 peso alacağım\nBunun karşılığında, sana karşı kötü niyetli insanların komplo kurduğunu bildirmek isterim. Bu alçak mürtedlerin, gemini tam bu limanda batırmayı planladıklarını duydum\nBarutla dolu bir lugger hazırlamışlar, adı '"+pchar.questTemp.Regata.BranderName+"', İngiliz bayrağı altında yaklaşıyor ki şüphe uyandırmasın. Dikkatli ol, oğlum, bu yoldan çıkmış ruhlar kötü niyetlerinde ciddiler.\nOnları yok et, bu günah için seni bağışlıyorum. Tanrı seni korusun! Senin için dua edeceğim, oğlum.";
				link.l1 = "Teşekkür ederim, kutsal baba. Bu alçaklar herhangi bir kötülük yapmaya kalkarsa, onları doğrudan cehenneme yollarım!";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -10000);
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddQuestRecord("Regata", "32");
				AddQuestUserData("Regata", "sText", pchar.questTemp.Regata.BranderName);
			}
		break;
		
		case "Regata_Padre_exit":
			dialog.text = "Öfkelenme, oğlum. Öfke bir günahtır. Hayır yapmamak senin hakkın. Huzurla yürü, oğlum.";
			link.l1 = "Elveda, kutsal baba.";
			link.l1.go = "Padre_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddQuestRecord("Regata", "35");					  
		break;
		
		case "Padre_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "SentJons_church", "barmen", "stay", "ReturnRegataPadreNorm", 5);
		break;
		
		case "Regata_Spyglass":
			dialog.text = "İyi günler kaptan! Benim adım "+npchar.name+" ve ben de isterim...";
			link.l1 = "... bana bir şey teklif etmek için... Doğru muyum, genç hanımefendi?";
			link.l1.go = "Regata_Spyglass_1";
		break;
		
		case "Regata_Spyglass_1":
			dialog.text = "Elbette, kaptan! Neden bu kadar şaşırdın ki? Yakışıklı bir denizcisin ve regattaya katılıyorsun, bu yüzden herkes sana işe yarar denizcilik malzemeleri satmaya dünden razı.";
			link.l1 = "Pekâlâ, güzelim, haklısın. Bana ne teklifin var?";
			link.l1.go = "Regata_Spyglass_2";
		break;
		
		case "Regata_Spyglass_2":
			if(hrand(11) > 10)//отличная труба
			{
				pchar.questTemp.Regata.Spy = "spyglass4";
				sTemp = "an excellent spyglass";
				pchar.questTemp.Regata.SpyPrice = 20000;
				pchar.questTemp.Regata.SpyIndex = 12;//выигрыш - 12 часов
			}
			else
			{
				if(hrand(11) < 6)//обычная труба
				{
					pchar.questTemp.Regata.Spy = "spyglass2";
					sTemp = "an ordinary spyglass";
					pchar.questTemp.Regata.SpyPrice = 1800;
					pchar.questTemp.Regata.SpyIndex = 4;//выигрыш - 4 часа
				}
				else//хорошая труба - как пригодится
				{
					pchar.questTemp.Regata.Spy = "spyglass3";
					sTemp = "a good spyglass";
					pchar.questTemp.Regata.SpyPrice = 10000;
					pchar.questTemp.Regata.SpyIndex = 8;//выигрыш - 8 часов
				}
			}
			dialog.text = "Bak, bir göz at. Bunu babamdan miras aldım. O da senin gibi bir denizciydi ve birçok seyir aleti vardı. Benim ihtiyacım yok, ama senin işine yarayacağından eminim. Sadece şunu istiyorum "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" bunun için.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Regata.SpyPrice))
			{
				link.l1 = "Pekâlâ, pekâlâ..."+sTemp+"! İlginç! Sana şunu söyleyeyim, bunu senden alacağım. Güzel gözlerin hatrına. Peki, istiyor musun "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" bunun için mi? Lütfen, paranı al.";
				link.l1.go = "Regata_Spyglass_3";
			}
			link.l2 = "Hm..."+sTemp+"? Hayır, kızım, üzgünüm ama buna ihtiyacım yok. Zaten kendime ait çok güzel bir dürbünüm var. Yani... maalesef!";
			link.l2.go = "Regata_Spyglass_exit";
		break;
		
		case "Regata_Spyglass_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.SpyPrice));
			GiveItem2Character(pchar, pchar.questTemp.Regata.Spy);
			dialog.text = "Teşekkür ederim, kaptan. Umarım işinize yarar. Onu faydalı bulmanıza sevindim. Regatta’da bol şanslar!";
			link.l1 = "Teşekkür ederim, "+npchar.name+"! Elveda.";
			link.l1.go = "Spyglass_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp))+sti(pchar.questTemp.Regata.SpyIndex);//купил трубу - выиграл время
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
		break;
		
		case "Regata_Spyglass_exit":
			dialog.text = "Ne yazık, kaptan. Umarım işinize yarardı. Neyse, onu başkasına satmaya çalışacağım. Hoşça kalın!";
			link.l1 = "Hoşça kal, "+npchar.name+".";
			link.l1.go = "Spyglass_exit";
			pchar.questTemp.Regata.AdversaryFourthTransition.Time.c = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.c)-sti(pchar.questTemp.Regata.SpyIndex);//третий соперник выиграл время
		break;
		
		case "Spyglass_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "Regata_SiegeOfficer":
			dialog.text = "Selamlar, kaptan. Regatta'ya katılanlardan biri değil misiniz? Doğru mu anladım?";
			link.l1 = "Evet. Ve mesele nedir, memur?";
			link.l1.go = "Regata_SiegeOfficer_1";
		break;
		
		case "Regata_SiegeOfficer_1":
			dialog.text = "Zaten biliyorsunuzdur, kolonimiz şu anda İspanyol kuşatması altında. Bu yüzden valimiz sizinle görüşmek istiyor. Ona bir ziyarette bulunur musunuz? Mesele oldukça acil.";
			link.l1 = "Hm... Pekala, hemen Ekselanslarının yanına gideceğim, gerçi askeri operasyonlarla nasıl bir ilgim olabileceğini pek anlamıyorum.";
			link.l1.go = "Regata_SiegeOfficer_2";
		break;
		
		case "Regata_SiegeOfficer_2":
			dialog.text = "Artık işin içindesiniz, kaptan. Zaman kaybetmeyelim ve konağa gidelim. Beni takip edin.";
			link.l1.go = "Regata_SiegeOfficer_3";
		break;
		
		case "Regata_SiegeOfficer_3":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Bridgetown_townhall", "goto", "governor1", "RegataSiegeHover", -1);
		break;
		
		case "Regata_SiegeOfficer_4":
			dialog.text = "Efendim! Sivilleri geminize göndermeye hazırım. Şimdi gidiyor muyuz?";
			link.l1 = "Evet, elbette. Hemen yelken açıyoruz. Herkese sandallara binmelerini söyle.";
			link.l1.go = "Regata_SiegeOfficer_5";
		break;
		
		case "Regata_SiegeOfficer_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "RegataSiegeOpen", -1);
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "quest", "quest1", "none", "", "", "", 30);
			}
		break;
		
		case "Regata_SiegeOfficer_6":
			dialog.text = "Başardık... Görünüşe göre bu şalopa filonun gözcüsüymüş ve bu Kastilyalı alçaklar etrafta dolanıyormuş. Kaptan, lütfen kadınları mağaralara götürmeme yardım edin, başka İspanyol birlikleri de olabilir.";
			link.l1 = "Pekala. Hadi gidelim!";
			link.l1.go = "Regata_SiegeOfficer_7";
		break;
		
		case "Regata_SiegeOfficer_7":
			DialogExit();
			sld = characterFromId("SiegeOfficer");
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_SiegeOfficer_8":
			dialog.text = "Gratitude for your help, captain! If it weren't for you and your courage... You are a true hero; you completed this operation despite all dangers and your own interests. I have been thinking about how to reward you... and there is a way to improve your chances in the regatta.";
			link.l1 = "İlginç.   Peki, bu yol nedir?";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_Hovernor":
			dialog.text = "Selamlar, kaptan "+GetFullName(pchar)+". Geldiğin iyi oldu. Kasabamız senin yardımına muhtaç.";
			link.l1 = "Efendim, eğer şu anda koloninize saldıran İspanyol filosundan bahsediyorsanız, size nasıl yardımcı olabileceğimi gerçekten bilmiyorum. Ben bir lugger komuta ediyorum, hat gemisi değil...";
			link.l1.go = "Regata_Hovernor_1";
		break;
		
		case "Regata_Hovernor_1":
			dialog.text = "Listen to me, captain, and you will understand. We are in serious trouble. The city is under Spanish siege. A decisive battle for the fort is about to begin. Besides, a few hundred Spaniards have already landed and blocked every exit from the city; now they can attack us from both sea and land\nThe fort's garrison is preparing to defend the city from the squadron, and there are not enough soldiers in the settlement itself. Every man capable of handling a weapon is mobilised, but what about the others?\nThere are a hundred souls of women in Bridgetown. Can you imagine what will happen to them if we fail to protect our colony? I believe that you understand.";
			link.l1 = "Efendim, sizi anlıyorum, ama tekrar soruyorum, size nasıl yardımcı olabilirim? Benden ne istiyorsunuz? Savaş gemileriyle mi çarpışayım, yoksa mürettebatımı kasabanın milislerine mi yazdırayım?";
			link.l1.go = "Regata_Hovernor_2";
		break;
		
		case "Regata_Hovernor_2":
			switch (sti(Pchar.BaseNation))
			{
				case ENGLAND: sTemp = "You are English , help us to save English citizens and what is important - women!" break;
				case FRANCE: sTemp = "You are French, so you basically are our ally, help us to save English citizens and what is more important - women!" break;
				case SPAIN: sTemp = "I know that you are Spanish and these are your people in the sea, so I know that I am already asking for a lot, but these women are innocent and have nothing to do with this battle. So please I beg of you, help them!" break;
				case HOLLAND: sTemp = "I know that you are Dutch and our nations are at war, but you are participating in the English regatta under the English flag. Don't you think that it is right to fight for innocent and peaceful people, for women? Please captain, help them!" break;
			}
			dialog.text = "Neither. I ask only one thing of you. Take the women and children away from here on your ship. There are not many of them, about a hundred. Take them to Harrison Cape along with Lieutenant Mahony; he will make sure they are safe in the cave\nI am sure the Spanish won't search for them. I have no ships to spare; everything we had was sunk by the Spanish squadron. You are my last hope. You can take them to the cape in a single voyage, even though your vessel will be overloaded. Ships of the line won't follow you.\nI can't ask anyone else to do it. "+sTemp+"";
			link.l1 = "Üzgünüm efendim, ama gemim zaten haddinden fazla yüklü ve bu kadar insanı, iki seferde bile, taşıyamaz. Yakına düşecek rastgele bir top güllesi gemimi de, kadınlarınızı da denizin dibine yollar. Affedin beni, ama size yardımcı olamam.";
			link.l1.go = "Regata_Hovernor_exit";
			link.l2 = "Pekâlâ, efendim. Size yardım edeceğim. Bir denizcinin onuru bunu gerektirir.";
			link.l2.go = "Regata_Hovernor_3";
		break;
		
		case "Regata_Hovernor_3":
			dialog.text = "Kabul ettiğine sevindim. Gerçekten cesur bir askersin. Teğmen Mahony kadınları ve çocukları gemine getirecek. Yolun açık olsun, Kaptan!";
			link.l1 = "Teşekkür ederim, efendim. Hadi vakit kaybetmeyelim!";
			link.l1.go = "Regata_Hovernor_4";
		break;
		
		case "Regata_Hovernor_wait":
			dialog.text = "Acele et, kaptan. Zaman tükeniyor.";
			link.l1 = "Zaten yelken açtım!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Hovernor_wait";
		break;
		
		case "Regata_Hovernor_exit":
			dialog.text = "Bu inanılmaz. Denemeye bilecek misin? Peki, bu senin hakkın. Senden bir şey talep edemem. Eğer sıradan bir kaptan olsaydın, yüzlerce kadının hatırı için gemini el koyardım, ama sen regattaya katılıyorsun ve bu yüzden İngiliz kolonilerinin genel valisinin koruması altındasın\nVicdanının galip geleceğini ummuştum, ama yanılmışım. Git, ve Tanrı ruhuna merhamet etsin!";
			link.l1 = "Elveda, efendim.";
			link.l1.go = "Hovernor_exit";
		break;
		
		case "Hovernor_exit":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			pchar.questTemp.Regata.AdversaryFifthTransition.Time.e = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.e)-36;//пятый противник выиграл 36 часов
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			ChangeCharacterNationReputation(pchar, ENGLAND, -5);
			//вертаем губера в норму
			npchar.Dialog.Filename = "Common_Mayor.c";
			npchar.dialog.currentnode = "First time";
			//удаляем лейтенанта
			sld = characterFromId("SiegeOfficer");
			sld.lifeday = 0;
			//открываем ворота и выход в море
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			//остров в норму
			n = FindIsland("Barbados");	
			DeleteAttribute(Islands[n], "DontSetShipInPort");
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			for (i=1; i <=9; i++)//девок счистим
			{
				sld = characterFromId("RegataBridgWom_"+i);
				sld.lifeday = 0; // patch-7
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Regata", "38");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_Hovernor_4":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			NextDiag.CurrentNode = "Regata_Hovernor_wait";
			sld = characterFromId("SiegeOfficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "Bridgetown_town", "goto", "goto4", "", 10);
			pchar.quest.Regata_evacuation.win_condition.l1 = "location";
			pchar.quest.Regata_evacuation.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_evacuation.function = "RegataSiegeEvacuation";
			AddQuestRecord("Regata", "36");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_BridgWom":
			dialog.text = "İspanyollar peşimizde! Tanrım, yardım et!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_BridgWom";
		break;
		
		case "Regata_BridgWom_1":
			dialog.text = "Teğmen Mahony öldü... bu bir kâbus olmalı. Cesur bir subaydı. Kaptan, lütfen bizi bir mağaraya götürür müsünüz? Bizi oraya götürün, gerisini biz hallederiz.";
			link.l1 = "Tabii. Beni takip et!";
			link.l1.go = "Regata_BridgWom_2";
		break;
		
		case "Regata_BridgWom_2":
			DialogExit();
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_BridgWom_3":
			dialog.text = "İşte geldik... teşekkür ederim kaptan! Hepimizi kurtardınız! Sizi nasıl ödüllendirebileceğimi düşündüm... regatta'da şansınızı artırmanın bir yolu var.";
			link.l1 = "Devam et.";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_skiper":
			pchar.questTemp.Regata.Name = GetFullName(npchar);
			dialog.text = "Are you heading to Port Royal? The shortest route lies through Curaçao. Return to Bridgetown. Find a man named Woodrow Dougherty; he is an old sailor and an experienced navigator. He knows the area between Barbados and Jamaica perfectly, and he'd be a great help to you\nThis will save you a lot of precious time, which you so desperately need to win. Find the man in the local church and tell him that "+GetFullName(npchar)+" - has sent you, he won't turn you away. Take him to Port Royal, he was planning to sail there anyway.";
			link.l1 = "Pekâlâ! İyi bir kılavuz bana faydalı olur. Hoşça kal.";
			link.l1.go = "Regata_skiper_1";
		break;
		
		case "Regata_skiper_1":
			dialog.text = "Elveda, kaptan! İyi şanslar!";
			link.l1 = "Belki, tekrar karşılaşırız...";
			link.l1.go = "Regata_skiper_2";
		break;
		
		case "Regata_skiper_2":
			DialogExit();
			AddQuestRecord("Regata", "37");
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			LAi_SetStayType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0; // patch-8
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0; // patch-8
			}
			//вертаем губера в норму
			sld = characterFromId("Bridgetown_Mayor");
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
			//открываем ворота и выход в море
			LocatorReloadEnterDisable("Shore4", "boat", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Barbados_cave", "reload1", false);
			bQuestDisableMapEnter = false;
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			RegataSiegeSkiper();//поставим Вудро в церковь
		break;
		
		case "Regata_SiegeSkiper":
			dialog.text = "Günaydın. Bir şey ister misiniz?";
			link.l1 = "Adınız Woodrow Dougherty, doğru mu?";
			link.l1.go = "Regata_SiegeSkiper_1";
		break;
		
		case "Regata_SiegeSkiper_1":
			dialog.text = "Haklısınız. Size nasıl yardımcı olabilirim?";
			link.l1 = "Barbados ile Curacao arasındaki suları iyi bilen, deneyimli bir denizci olduğunu biliyorum. Port Royal'a gitmek istediğini de biliyorum. Ben regattanın bir katılımcısıyım ve son bir durak kaldı - Port Royal. Bu son yolculukta rotacı olarak ekibime katılmanı istiyorum.";
			link.l1.go = "Regata_SiegeSkiper_2";
		break;
		
		case "Regata_SiegeSkiper_2":
			dialog.text = "İlginç... Peki, neden senin tayfana katılmamı isteyesin ki?";
			link.l1 = "Şey, çünkü senin hakkında şuradan duydum "+pchar.questTemp.Regata.Name+"   tüm garantilerle, reddetmeyeceğine dair. Ve bu kritik anda Bridgetown'a yaptığım yardım sayesinde...";
			link.l1.go = "Regata_SiegeSkiper_3";
		break;
		
		case "Regata_SiegeSkiper_3"://а тут - как уж свезет
			if(hrand(2) != 2)
			{
				dialog.text = "From "+pchar.questTemp.Regata.Name+"? Şimdi anladım, tabii. Pekâlâ Kaptan, sizi Port Royal'e en kısa yoldan götürmenize yardım edeceğim. Şimdi yelken açacak mısınız?";
				link.l1 = "Evet.";
				link.l1.go = "Regata_SiegeSkiper_4";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.Regata.Name+"? Anlıyorum. Ama kaptan, böyle tehlikeli zamanlarda şehrimi bırakamam. Bize karşılıksız yardım eden bir asker olarak beni anlamalısınız\nİnsanların arkamdan, yaşlı Woodrow İspanyollara karşı son savaştan kaçtı diye fısıldamasını istemem. Burada kalacağım. Bana darılmayın, kaptan.";
				link.l1 = "Ve bu senin son sözün mü? Ama kolonine yardım ettim...";
				link.l1.go = "Regata_SiegeSkiper_6";
			}
		break;
		
		case "Regata_SiegeSkiper_4":
			dialog.text = "O halde vakit kaybetmeyelim. Sadece eşyalarımı toplayayım, hemen emrinizde olacağım.";
			link.l1 = "Denizcilerim iskelede seni bekliyor olacak ve seni 'Saint Catherine'e götürecekler. Teşekkürler, Woodrow!";
			link.l1.go = "SiegeSkiper_hire";
		break;
		
		case "Regata_SiegeSkiper_6":
			dialog.text = " Kaptan, bir regatta bir spordur, ama İspanyolların evime uyguladığı kuşatma hayat memat meselesi. Seninle hiçbir yere gitmiyorum. Ve tekrar ediyorum, beni anlamalısın – onur ve görev hâlâ bu dünyada bir anlam ifade ediyor. Bu son sözüm ve değiştirmeyeceğim. Yine de, oraya en güvenli yoldan nasıl hızlıca gideceğin konusunda sana bir tavsiye verebilirim: kuzeybatıya, Dominika'ya doğru yelken aç, oradan da rüzgâr ve senin kararına göre ya Martinik'e ya da Guadeloupe'a geç. Sonra doğrudan Port Royal'a yelken açabilirsin, ya da Curaçao'dan geçebilirsin – ki bunu önermem – ama Hollandalılarla aranda bir sorun yoksa, o zaman elbette.";
			link.l1 = "Pekala, teşekkür ederim... ama hayal kırıklığına uğradım. Elveda, Woodrow.";
			link.l1.go = "SiegeSkiper_exit";
		break;
		
		case "SiegeSkiper_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
		break;
		
		case "SiegeSkiper_hire":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = 25;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			//пересчитываем время пятого перехода
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp))+18+(rand(18));//выигрыш до 1.5 суток
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
			SetFunctionTimerCondition("SiegeSkiperOver", 0, 0, 15, false);//чтобы не присвоил офицера
			DialogExit();
		break;
		
		case "Regata_Finish":
		iTest = FindColony("Portroyal"); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//снимаем запреты
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Bridgetown") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Regatanın son aşamasında kuralları çiğnediniz. Sonucunuz diskalifiye edildi. Size söyleyecek başka bir şeyim yok, kaptan.";
				link.l1 = "Eh... ne yapalım! Artık yapılacak bir şey yok, fazla dikkatliydin. Elveda!";
				link.l1.go = "exit";
				npchar.lifeday = 1;
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				n=1;
				for (i=1; i <=5; i++)
				{
					if (i==1) sTemp = "a";
					if (i==2) sTemp = "b";
					if (i==3) sTemp = "c";
					if (i==4) sTemp = "d";
					if (i==5) sTemp = "e";
					if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime)) n++;
					pchar.questTemp.Regata.Result = n;//место в регате
				}
				if (n==1)
				{
					dialog.text = "Kaptan "+GetFullName(pchar)+", tebrikler! Bu iş "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" saat içinde yarışı bitirdin ve tüm rakiplerini geride bıraktın. Bu gerçekten etkileyici bir sonuç!";
					link.l1 = "Güzel sözleriniz için teşekkür ederim, efendim!";
					link.l1.go = "First_result";
				}
				else
				{
					if (n==6)
					{
						dialog.text = "Kaptan, ne yazık ki, sonucunuz en kötüsü, harcadınız "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" saatler. Üzülme, gerçekten zorlu rakiplerle karşılaştın.";
						link.l1 = "Üzgün değilim, efendim. Regattaya katılıp yeteneklerimi sınadığım için mutluyum.";
						link.l1.go = "Other_result";
						AddQuestRecord("Regata", "44");
						CloseQuestHeader("Regata");
					}
					else
					{
          				dialog.text = "Kaptan, siz şu anda "+n+"th place. Başarılı sonucun için tebrikler, gerçekten takdire şayan bir süre gösterdin - "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" saat. Kaybettiniz ama tebrikler!";
						link.l1 = "Endişelenmeyin efendim. Bu zorlu rekabette iyi bir sonuç gösterdiğim için memnunum.";
						link.l1.go = "Other_result";
						if (n==2) AddQuestRecord("Regata", "40");
						if (n==3) AddQuestRecord("Regata", "41");
						if (n==4) AddQuestRecord("Regata", "42");
						if (n==5) AddQuestRecord("Regata", "43");
						CloseQuestHeader("Regata");
					}
				}
			}
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
			sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
			CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
			RemovePassenger(Pchar, sld);
			DeleteAttribute(sld, "Payment");
			DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
			log_info("Woodrow Dougherty has landed");
			pchar.quest.SiegeSkiperOver.over = "yes"; //снять таймер
		}
		else
		{
			dialog.text = "Efendim, size bir şey sorabilir miyim - geminiz nerede? Göremiyorum...";
			link.l1 = "Üzgünüm efendim. Onu hemen limana götüreceğim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Finish";
		}
		break;
		
		case "First_result":
			if (CheckAttribute(pchar, "questTemp.Regata.Rate")) sTemp = "Come and see me in my office. I will give you your prize for your stake.";
			else sTemp = "And if you had made a stake on your victory as I offered you to, you would have gotten an extra prize too.";
			dialog.text = "Yarın genel valiyi ziyaret et, sana 250.000 peso ve değerli hediyeler verecek. "+sTemp+" Kasabadan ayrılma, geleneğe göre kazanan ödüllerini bir hafta içinde almazsa, ödüller kasabanın hazinesine aktarılır.";
			link.l1 = "Anladım, efendim. Yarın onu ziyaret edeceğim!";
			link.l1.go = "First_result_1";
		break;
		
		case "First_result_1":
			DialogExit();
			//npchar.lifeday = 7;
			Achievment_Set("ach_09");
			npchar.dialog.currentnode = "Other_result_repeat";
			pchar.questTemp.Regata.Win = "true";
			pchar.quest.Regata_Final.win_condition.l1 = "Timer";
			pchar.quest.Regata_Final.win_condition.l1.date.hour  = 6.0;
			pchar.quest.Regata_Final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Regata_Final.function = "RegataFinal";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 8, false);//таймер не снимаем - через 8 дней подчистится все автоматически
			// слухи
			AddSimpleRumour("Ah, you are the legendary captain, the winner of the regatta! It's such a pleasure to see you in flesh!", ENGLAND, 60, 10);
			AddSimpleRumour("Ha, look at this, a master of wind and waves, the winner of the regatta! You have my respect...", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain who is capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Ah, so you are the legendary captain, the winner of the regatta! Pleasure to see you!", FRANCE, 60, 10);
			AddSimpleRumour("Ha, aren't you the master of wind and waves, the winner of the regatta! You have my respects...", FRANCE, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", FRANCE, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", FRANCE, 60, 10);
			// экспа
			AddComplexSeaExpToScill(2000, 300, 300, 0, 500, 500, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 3);
			AddQuestRecord("Regata", "39");
			CloseQuestHeader("Regata");
		break;
		
		case "Other_result":
			dialog.text = "Onurlu bir cevap duymak güzel. İyi şanslar, Kaptan!";
			link.l1 = "Elveda, efendim.";
			link.l1.go = "Other_result_1";
		break;
		
		case "Other_result_1":
			DialogExit();
			npchar.dialog.currentnode = "Other_result_repeat";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 1, false);
			// экспа
			AddComplexSeaExpToScill(500, 100, 100, 0, 100, 100, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "Other_result_repeat":
			dialog.text = "Başka bir şey ister misiniz, kaptan?";
			link.l1 = "Hayır... bir şey değil.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Give_advantage":
			dialog.text = "Ah, işte buradasınız efendim "+GetFullName(pchar)+". Sizi görmek güzel. Ödülünüz için mi geldiniz? Sizin için hazır.";
			link.l1 = "Bunu duymak güzel! Ek ödülümün büyüklüğü nedir?";
			link.l1.go = "Give_advantage_1";
		break;
		
		case "Give_advantage_1":
			dialog.text = "Tüm riskleri göz önünde bulundurursak, nihai ödülün "+FindRussianMoneyString(makeint(pchar.questTemp.Regata.Advantage))+". Lütfen, al bunu. Tebrikler!";
			link.l1 = "Teşekkürler!";
			link.l1.go = "Give_advantage_2";
		break;
		
		case "Give_advantage_2":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Regata.Advantage));
			dialog.text = "Elbette, Port Royal halkı arasında ünün arttı. Bunu sen de fark ediyorsundur... ama ne yazık ki, insanların hafızası çabuk unutur. O yüzden, şanının parladığı bu anların tadını çıkar!";
			link.l1 = "En güzel şeylerden bahsediyorsunuz, efendim... Pekâlâ, bakalım zaferin tadı nasılmış. Hoşça kalın! Tanıştığımıza memnun oldum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Regata_CitMan_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Tebrikler kaptan, zafer sizin! Harika bir sonuç!";
						link.l1 = "Teşekkürler!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Don't be sad, captain. Winning the regatta is no easy feat; even taking part in it is a privilege!";
						link.l1 = "Benim için endişelenme. Sonuçlarımdan memnunum.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Sizi görmek güzel, kaptan! Kayıt olmak için Sir Stevenson ile konuşmalısınız.";
					link.l1 = "Anladım. Ona doğru gidiyorum!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, kaptan, nasıl böyle başarısız olabildin, hem de işin en sonunda!";
				link.l1 = "Evet, ne kadar aptalca davrandım...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitMan_1";
		break;
		
		case "Regata_CitWom_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Tebrikler, kaptan! Harika bir sonuç!";
						link.l1 = "Teşekkür ederim!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Don't be sad, captain. Winning the regatta is no easy feat; even taking part is a privilege!";
						link.l1 = "Benim için endişelenme. Sonucumdan memnunum.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Seni görmek güzel, kaptan! Kendini kaydettirmek için Sir Stevenson'la konuşmalısın.";
					link.l1 = "Anladım. Hemen geliyorum!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, kaptan, neden böyle başarısız oldun, hem de en son aşamada!";
				link.l1 = "Evet, bu gerçekten çok aptalcaydı...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitWom_1";
		break;
		
		case "Regata_CitHorse_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Tebrikler, kaptan! Harika bir sonuç!";
						link.l1 = "Teşekkür ederim!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Don't be sad, captain. It's not easy to win the regatta; even taking part is a privilege!";
						link.l1 = "Benim için endişelenme. Sonucumdan memnunum.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Seni görmek güzel, kaptan! Kendini kaydettirmek için Sir Stevenson ile konuşmalısın.";
					link.l1 = "Anladım. Hemen geliyorum!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, kaptan, nasıl böyle başarısız olabildin, hem de işin en son aşamasında!";
				link.l1 = "Evet, ne kadar da aptalmışım...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitHorse_1";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void CreateRegataAdversaries()
{
	string sTemp;
	for (int i=0; i<=4; i++)
	{
	if (i==0) sTemp = "a";
	if (i==1) sTemp = "b";
	if (i==2) sTemp = "c";
	if (i==3) sTemp = "d";
	if (i==4) sTemp = "e";
	pchar.questTemp.Regata.AdversaryName.(sTemp) = GenerateRandomName_Generator(i, "man");
	pchar.questTemp.Regata.AdversaryShipName.(sTemp) = GenerateRandomNameToShip(ENGLAND);
	pchar.questTemp.Regata.AdversarySpeed.(sTemp) = 0.4+frand(0.9);
	log_testinfo(FindRussianDaysString(stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp))));
	}
}
