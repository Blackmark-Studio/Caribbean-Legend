#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	bool bLock = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
	bool bLock1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Kasabada alarm verildi. Herkes seni arıyor! Senin yerinde olsam burada fazla oyalanmazdım.","Tüm muhafızlar seni bulmak için kasabayı didik didik arıyor. Ben aptal değilim, seninle konuşacak değilim!","Koş, dostum, askerler seni paramparça etmeden önce..."),LinkRandPhrase("Ne istiyorsun, alçak herif?! Şehir muhafızları zaten peşinde. Uzaklara gidemezsin, korsan!","Pis katil, defol evimden! Muhafızlar!!","Senden korkmuyorum, köpek! İp seni bekliyor, fazla uzağa gidemezsin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, alarm için endişelenmiyorum...","Beni yakalama şansları yok."),RandPhraseSimple("Kapa çeneni, "+GetWorkTypeOfMan(npchar,"")+", yoksa lanet dilini keserim.","Heh, "+GetWorkTypeOfMan(npchar,"")+", sen de bir korsanı avlamak mı istiyorsun? Bak dostum, sakin olursan hayatta kalabilirsin..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"! Hoş geldiniz, "+GetAddress_Form(NPChar)+" Los-Teques Madeni Meyhanesi'ne hoş geldiniz. Yiyecek, içecek ve kızlar, hepsi uygun fiyatlarla! Benim adım "+GetFullName(npchar)+" ve her zaman hizmetinizdeyim.";
				Link.l1 = "Bakalım... Ben "+GetFullName(pchar)+". Tanıştığımıza memnun oldum, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Aha, eski dostum, Kaptan "+GetFullName(pchar)+"! Seni görmek ne güzel, ihtiyar! Rom, kızlar?";
				if (makeint(pchar.money) >= 5)
				{
					link.l1 = "Bana biraz rom koy, "+npchar.name+".";
					link.l1.go = "drink";
				}
				link.l2 = "Biraz kestirmek istiyorum. Boş bir odanız var mı?";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("Bir haberin var mı?"," Buralarda neler var, yeni bir şeyler oldu mu? ","Karada hayat nasıl gidiyor?");
				link.l3.go = "rumours_tavern";
				link.l4 = "Hayır, hiçbir şeye ihtiyacım yok, "+npchar.name+". Sadece sana merhaba demek için uğradım.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ah, çok mutluyum! Şehrimizde yeni yüzler pek nadir görülür. Size biraz rom koyayım da sohbet edelim...";
			link.l1 = "Burada ilk kez bulunuyorum ve bu yerleşim hakkında biraz daha fazla bilgi almak istiyorum.";
			link.l1.go = "info";
			if (makeint(pchar.money) >= 5)
			{
				link.l2 = "Bana biraz rom koy, "+npchar.name+".";
				link.l2.go = "drink";
			}
			link.l3 = "Biraz kestirmek istiyorum. Boş bir odanız var mı?";
			link.l3.go = "room";
		break;
		
		case "info":
			dialog.text = "Anlatacak ilginç bir şey yok. Her gün aynı iş: sıkıntı, güneş ve toz. Burada sadece askerler, zenciler ve yerliler yaşar. Birkaç maceraperest ve altına aç haydut da bulabilirsin\nBazen beyefendiler, senin gibi kaptanlar, külçe karşılığında köle satmak ve değerli maden almak için uğrar. Tüccarımız oldukça ilginç biridir, sadece altın ve gümüş külçeleri değil, yarı değerli taşlar da satar\n Özel bilgiye sahip olanların bu taşları çok faydalı bulabileceğini söyler. Yani dükkânımıza mutlaka göz at. Madenin kendisi ise dağın daha derinlerinde. İstersen ziyaret edebilirsin ama bekçiyi kızdırmamayı tavsiye ederim\nMahkûmlarla konuşma ve Tanrı seni hırsızlıktan korusun. Her neyse, bu yerleşimdeki en iyi yer benim meyhanemdir, bu kavurucu cehennemden kaçıp dinlenmek için en güzel yer!";
			link.l1 = "Bilgi için teşekkürler!";			
			link.l1.go = "exit";
		break;
		
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
			{
				dialog.text = "Kaptan, bence artık durmanız daha iyi olur. Allah korusun, alkolün etkisindeyken ortalığı birbirine katarsınız. Bu konuda burada gerçekten çok katıyız. Sizin yetkiniz bile işe yaramaz.";
				link.l1 = "Hm... Sanırım haklısınız - zaten yeterince içtim. İlginiz için teşekkürler!";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -5);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "Rica ederim, kaptan. En iyi siyah Jamaika romumdan bir pint sadece beş sekizlik!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("Pekâlâ, sağlığınıza ve işletmenizin refahına!","Pekâlâ, denizdekilere!","Pekâlâ, kasabanızın esenliği için!"),LinkRandPhrase("Pekâlâ, talihin rüzgarlarına, bir şans esintisine, hepimiz daha neşeli ve zengin yaşayalım!","Pekâlâ, işlerimizde rüzgâr hep arkamızdan essin!","Pekala, mutluluğa, şansa, neşeye ve kadınlara!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
		break;
		
		case "room":
			if (CheckAttribute(pchar, "GenQuest.LosTequesSex"))
			{
				dialog.text = "Señor, bir oda ve bir kadın için ödeme yaptınız. Yukarı çıkın, bir süredir sizi bekliyor.";
				link.l1 = "Pekâlâ.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Var tabii. Ne kadar kalmayı düşünüyordunuz?";
			if(!isDay())
			{
				link.l1 = "Sabaha kadar.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Gece çökene kadar.";
				link.l1.go = "room_night";
				link.l2 = "Yarın sabaha kadar.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "On parça sekizlik tutar. Odaya bir kız da ister misiniz? Kadın için sadece bin peso.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Hayır, bir kıza ihtiyacım yok. Al, bu oda için.";
				link.l1.go = "room_day_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Odayı ve kızı alıyorum. İşte paran.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Ne yazık ki, odayı karşılayacak param yok.";
			link.l3.go = "exit";
		break;

		case "room_day_next":
			dialog.text = "On parça sekizlik eder. Odaya bir kız da ister misiniz? Kadın için sadece bin peso.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Hayır, bir kıza ihtiyacım yok. Al, bu oda için.";
				link.l1.go = "room_day_wait_next";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Pekâlâ. Odayı ve kızı alıyoruz. Buyur paran.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Ne yazık ki, odayı karşılayacak param yok.";
			link.l3.go = "exit";
		break;

		case "room_night":
			dialog.text = "On parça sekizlik tutar. Odaya bir kız da ister misiniz? Kadın için sadece bin peso.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Hayır, bir kıza ihtiyacım yok. Al, bu oda için.";
				link.l1.go = "room_night_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Pekâlâ. Odayı ve kızı alalım. Buyur paran.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_night";
				}
			}
			link.l3 = "Ne yazık ki, odayı karşılayacak param yok.";
			link.l3.go = "exit";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -20);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "room_girl":
			AddMoneyToCharacter(pchar, -1010);
			dialog.text = "Yukarı çıkın, señor. Kız sizi bekliyor olacak. İyi vakitler geçirin!";
			link.l1 = "Sağ ol, dostum...";
			link.l1.go = "room_girl_1";
		break;
		
		case "room_girl_1":
			DialogExit();
			pchar.GenQuest.CannotWait = true;
			pchar.GenQuest.LosTequesSex = "true";
			LocatorReloadEnterDisable("LosTeques_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("LosTeques_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			sld = GetCharacter(NPC_GenerateCharacter("MineFuckGirl" , "squaw_"+(rand(2)+1), "woman", "woman_B", 1, SPAIN, 1, true, "quest"));
			sld.dialog.FileName = "Tavern\LosTeques_Tavern.c";
			sld.dialog.currentnode = "MineFuckGirl";
			//sld.greeting = "";
			sld.name = GetIndianName(WOMAN);
			sld.lastname = "";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "LosTeques_tavern_upstairs", "goto", "goto1");
		break;
		
		case "MineFuckGirl":
			dialog.text = "Nasıl, beyaz efendi. Bakma öyle "+npchar.name+" böyle, "+npchar.name+" her şeyi o genelevdeki beyaz kadınlardan bile daha iyi biliyor. Ah, señor, ne kadar yakışıklısınız... Söz veriyorum, bu kadın sizi uzun süre sevecek.";
			link.l1 = "Bu kulağa hoş geliyor, bana en güzel Hint tılsımlarını göster. Seni ıslatmak için yağmur duasına ihtiyacım olmayacak...";
			link.l1.go = "MineFuckGirl_sex";
		break;
		
		case "MineFuckGirl_sex":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Gündüz gözüyle soygun mu olur?! Burada neler oluyor?! Dur, bekle, dostum...","Hey, ne yapıyorsun orada?! Beni soymaya mı çalışıyorsun? Şimdi başın belada...","Dur bakayım, ne halt ediyorsun sen? Meğer hırsızmışsın! Buraya kadarmış, herif...");
			link.l1 = LinkRandPhrase("Şeytan!","Siktir!","Ah, kahretsin");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
