// Якоб Джекман
int iBarbazonTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                    if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sen deli misin? Kasap mı olmak istedin? Bütün korsanlar sana öfkeli, oğlum, buradan gitmen en iyisi...","Aklını kaçırmışsın anlaşılan, oğlum. Biraz kolunu bacağını açmak mı istedin? Alınma ama burada işin yok. Kaybol!");
				link.l1 = RandPhraseSimple("Dinle, durumu düzeltmek istiyorum...","Bu sorunu çözmeme yardım et...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", denizdeki güvenliğim hakkında" + GetSexPhrase("", " konuşmak istiyorum") + ". Sahil Kardeşliği tayfası benim mütevazı varlığıma fazla ilgi gösteriyor. Onları biraz dizginleyebilir misin?";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat("Bana söyleyecek bir şeyin var mı? Yok mu? O zaman defol buradan!",
						"Bence kendimi açıkça ifade ettim, beni rahatsız etmeyi bırak.",
						"Ne kadar açık konuşsam da, hâlâ sinirimi bozuyorsun!","Doğrusu, bu kabalıktan bıktım artık.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Zaten gidiyorum.",
						"Tabii, "+npchar.name+"...",
						"Üzgünüm, "+npchar.name+"...",
						"Ah...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "maruntown")
			{
				link.l1 = "Jimmy Higgins'i nerede bulabilirim?";
				link.l1.go = "Saga_Jimmy";
			}	
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "jackman")
			{
				link.l1 = "Yine ben, Jackman. Kayıp birkaç kişiyi aradığını duydum...";
				link.l1.go = "Saga_search";
			}	
			//<-- Сага

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Esirin hakkında konuşmak istiyorum.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Merhaba, Jackman. Görevin hakkında konuşalım...";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "Tutsak hakkında konuşmamız lazım.";
					link.l1.go = "CapComission6";
				}
			}	
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sen kafayı mı yedin? Kasaplık mı yapmak istedin? Bütün korsanlar sana öfkeli, oğlum, buradan gitmen en iyisi...");
				link.l1 = RandPhraseSimple("Dinle, durumu düzeltmek istiyorum...","Bu sorunu çözmeme yardım et...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", denizdeki güvenliğim hakkında" + GetSexPhrase("", " konuşmak istiyorum") + ". Sahil Kardeşliği tayfası benim mütevazı varlığıma fazla ilgi gösteriyor. Onları biraz dizginleyebilir misin?";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat("Bana söyleyecek bir şeyin var mı? Yok mu? O zaman defol buradan!",
						"Bence kendimi açıkça ifade ettim, beni rahatsız etmeyi bırak.",
						"Ne kadar açık konuşsam da, hâlâ sinirimi bozuyorsun!","Doğrusu, bu kabalıktan bıktım artık.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Zaten gidiyorum.",
						"Tabii, "+npchar.name+"...",
						"Üzgünüm, "+npchar.name+"...",
						"Ah...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Tutsak hakkında konuşmak istiyorum.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}				
		break;

//-----------------------------------------пиратская сага----------------------------------------------------
		case "Saga_Jimmy":
			dialog.text = "Gerçekten mi! Birinin bu tembel herife ihtiyacı varmış! Kaç gündür kulübesinde tek başına rom içiyor. Onu ziyaret etmeni tavsiye etmem. Ayıkken bile pek matah biri değildir...";
			link.l1 = "Sorun değil, ben de aziz değilim. Kulübesi nerede?";
			link.l1.go = "Saga_Jimmy_1";
		break;
		
		case "Saga_Jimmy_1":
			dialog.text = "Meyhanenin tam önünde. İçki almak için hızlıca gidip gelmek isteyenler için iyi bir yer seçmiş.";
			link.l1 = "Sağ ol!";
			link.l1.go = "Saga_Jimmy_2";
		break;
		
		case "Saga_Jimmy_2":
			DialogExit();
			pchar.quest.Saga_createJimmy.win_condition.l1 = "location";
			pchar.quest.Saga_createJimmy.win_condition.l1.location = "FortOrange_House1";
			pchar.quest.Saga_createJimmy.function = "Saga_CreateJimmy";
			pchar.questTemp.Saga = "jimmy";
		break;
		
		case "Saga_search":
			dialog.text = "Bunu sana kim söyledi? O ayyaş Higgins mi? Gladys Chandler ya da Cellat Henry hakkında bir şey öğrendin mi?";
			link.l1 = "Özel bir şey yok aslında, ama o cellat hakkında belirli bir şeyi öğrenmek istiyorum.";
			link.l1.go = "Saga_search_1";
		break;
		
		case "Saga_search_1":
			dialog.text = "Bilecek pek bir şey yok. Şimdi onu pek hatırlayan kalmadı, ama yirmi yıl önce Henry, Bridgetown'dan Tortuga'ya kadar bütün fahişeler arasında çok popülerdi. Tabii ki! 'Neptune'un lostromosu, bizzat Kaptan Butcher'ın emrinde! Şimdi hayattaysa, kesin çok yaşlıdır.\nŞansı az, ama biliyorsun, imkansız diye bir şey yok. Onun hakkında herhangi bir bilgiye yirmi bin peso ödeyeceğim, onu buraya canlı getirirsen iki katını veririm.";
			link.l1 = "Gladys ve kızına ne kadar ödeyeceksin?";
			link.l1.go = "Saga_search_2";
		break;
		
		case "Saga_search_2":
			dialog.text = "Ah, o onun kızı değil. O kızı sağ getirirsen sana bir yığın dublon öderim. Gladys umurumda değil. Sorun var mı?";
			link.l1 = "Keşke bu tantananın sebebini bilseydim, ama sormayacağım. Görünen o ki, biyografimi kısaltabilir.";
			link.l1.go = "Saga_search_3";
		break;
		
		case "Saga_search_3":
			dialog.text = "Belki de... O sırlar seni ilgilendirmez. Ne kadar az bilirsen, o kadar uzun yaşarsın. Bana bir daha böyle sorular sorma, çünkü sende bir gariplik olduğundan şüphelenmeye başladım. Defol git, yoksa fikrimi değiştiririm.";
			link.l1 = "Görüşürüz, Baron!";
			link.l1.go = "Saga_search_4";
		break;
		
		case "Saga_search_4":
			DialogExit();
			AddQuestRecord("Saga", "6");
			if (CheckAttribute(pchar, "questTemp.Saga.Jimmysecret"))
			{
				AddQuestUserData("Saga", "sText", "To Antigua now. The corvette must be boarded.");
				DeleteAttribute(pchar, "questTemp.Saga.Jimmysecret");
			}
			pchar.quest.Saga_createDonovan.win_condition.l1 = "location";
			pchar.quest.Saga_createDonovan.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_createDonovan.function = "Saga_createDonovan";
			pchar.questTemp.Saga = "donovan";
		break;
		
		// абордаж, в каюте
		case "Jackman_abordage":
			dialog.text = "Ha! Yine karşılaştık, Kaptan "+GetFullName(pchar)+". Kabul ediyorum, Maroon Kasabası'nda kendini saf biri gibi göstermeye çalışmana rağmen, sen dişe dokunur bir rakipsin. Senin hakkında bir şeyler öğrendim, Hollanda Batı Hindistan Şirketi'yle olan entrikaların ortaya çıktı... Artık ne tür biri olduğunu anlıyorum.";
			link.l1 = "Senin gibileri de iyi bilirim, Jacob. O yüzden kendimizi kandırmayalım.";
			link.l1.go = "Jackman_abordage_1";
		break;
		
		case "Jackman_abordage_1":
			dialog.text = "Ve beni 'Marlin' ile nasıl kandırdın! Sanırım zavallı kardeşim ölmüş...";
			link.l1 = "Onun intikamını almak mı istiyorsun? Ama benim de sana uzun bir hesabım var. Köşeye sıkışmış Nathaniel, karısı, fırkateyni, iftiraya uğramış Shark, Blaze Sharp...";
			link.l1.go = "Jackman_abordage_2";
		break;
		
		case "Jackman_abordage_2":
			dialog.text = "Blaze mi? Onu ben öldürmedim.";
			link.l1 = "Doğru olsa bile, geri kalan listem yeterli. Adından bıktım artık. Yeter bu kadar laf, Jackman! Şimdi kılıçlarımız konuşacak!";
			link.l1.go = "Jackman_abordage_3";
		break;
		
		case "Jackman_abordage_3":
			dialog.text = "Böylesine öfkeli bir aptal... Kahrolasıca! Şimdi sıkı dur! Jacob Jackman asla yenilmedi! Carpacho, tam zamanında geldin! Buraya gel!";
			link.l1 = "...";
			link.l1.go = "Jackman_abordage_4";
		break;
		
		case "Jackman_abordage_4":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterJackmanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int iScl = 30 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Saga_JackmanCabinHelper", "citiz_58", "man", "man", iRank, sti(npchar.nation), 0, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl*2+100);
			LAi_SetCheckMinHP(sld, 150, true, "Saga_DannyHurryHelp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			sld = characterFromId("Danielle");
			RemovePassenger(Pchar, sld);
		break;

		//*************************** Генератор "Captain's offer - Ransom" **********************
		case "CapComission1":
			dialog.text = "Ha-ha. Burada tek bir tutsağım olduğunu mu sanıyorsun? Adını söyle.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+" . O burada mı?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "O öyleydi. Onu bir hafta önce buradayken Barbadoslu o plantasyon sahibi Albay Bishop’a sattım.";
				link.l1 = "Lanet olsun...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, sonunda. Onu Barbados'taki o plantasyon sahibine satmayı düşünüyordum, bir iki haftaya burada olacak... Fidyen var mı?";
				link.l1 = "Bak, ufak bir sorun var... Aslında o kadar param yok. Ama çalışmaya hazırım.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Onu satmadığın iyi olmuş. Al, paraların burada - 150.000 peso. Onu nerede bulabilirim?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Çok yavaştın... Ve ona neden bu kadar önem veriyorsun? Ben sadece akrabalarıyla pazarlık yapıyordum.";
			link.l1 = "Beni buraya gelmem için çağırdılar.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Pekâlâ, geç kaldın. Yapabileceğim bir şey yok.";
			link.l1 = "Dinle, ona kaça sattın, eğer sır değilse?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, değil. Ama sana söylemem... Söylersem güleceksin. Ha-ha-ha-ha! Hoşça kal.";
			link.l1 = "Görüşürüz...";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Pekala, pekala... Bir işim var... Nereden başlayacağımı bile bilmiyorum. Sınırı aşan bir korsanı batırmam gerekiyor.";
				link.l1 = "Ormanda basitçe öldürülemez mi?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Pekala, "+pchar.name+", biliyorsun, işler öyle yürümüyor. Parayı getir, o zavallını alırsın, ha-ha.";
				link.l1 = "Pekala. Görüşürüz.";
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "İşler böyle yürümez, biliyorsun... Onun ölmesine gerek yok, sadece bazılarına ganimetimden pay almamayı öğretmem lazım. Ama sonunda köpekbalıklarına yem olursa, üzülmem.";
			link.l1 = "Neden kendi adamlarını onun peşinden göndermiyorsun?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "Hm... Pekala, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" bazı korsanları ganimet paylarının bizim sakladığımız yerde, çok uzakta olmayan bir yerde tutulduğuna inandırmış "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". İki gemileri '"+pchar.GenQuest.CaptainComission.ShipName1+"' ve '"+pchar.GenQuest.CaptainComission.ShipName2+"' demir aldı kısa süre önce ve yelken açtı "+sLoc+". Şimdi neden adamlarıma bu işi emanet edemeyeceğimi anlıyorsun, değil mi?";
			link.l1 = "Evet. Ne kadar vaktim var?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 ila 15 gün, daha fazlası değil, sanırım. Onların ganimete ulaşmasını istemem, yoksa değerli yükle birlikte onları batırmanın bir anlamı kalmaz. O durumda, buraya getirmeleri daha iyi olurdu...";
			link.l1 = "Pekala, varım. Onları yakalamaya çalışacağım.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Merak etme. Adamlarım onu gemine götürecek. Peki, sen neden onunla bu kadar ilgileniyorsun?";
			link.l1 = "Hayır. Akrabaları onu getirmemi istedi.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, sorun değil. Adamın için bu kadar düşük bir fiyat teklif ettiğim için neredeyse üzülüyordum. Ha-ha-ha-ha. Hoşça kal.";
			link.l1 = "Görüşürüz.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen		
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "So, , "+GetFullName(pchar)+", benim adamımı mı batırdın? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Hayır. Onları yakalayamadım. Dönüş yolunda da karşılaşmadım.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Yaptım. Onları köpekbalıklarına yem ettim.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Lanet olsun! Onlarla karşılaşmış olsam da olmasam da, artık bir önemi yok! Peki, sıradaki önerin ne olacak?";
			link.l1 = "Belki bana daha kolay bir işin vardır?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Dinle Jackman, esir için fiyatı düşür...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Hayır.";
			link.l1 = "Öyleyse hoşça kal...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Fiyatı düşürmek mi? Senin beceriksizliğin yüzünden malımı kaybettim! Şimdi ise fiyatı artırabilirim! Onu istiyorsan 200.000 peso verirsin, yoksa defolup gidersin.";
			link.l1 = "Çok pahalı... Elveda...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Lanet olsun, al paralarını.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Pekâlâ, bu zavallıyı alabilirsin...";
			link.l1 = "Elveda.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Aferin! Al şu zayıfını ve bol şans.";
			link.l1 = "Teşekkürler. Hoşça kal.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission6":
			dialog.text = "Parayı getirdin mi, Charles? Adamı plantasyona satmak konusunda şaka yapmıyordum.";			
			link.l1 = "Dinle, "+NPChar.name+", bir sorun var... O kadar param yok. Ama çalışmaya hazırım.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Onu satmamış olman iyi. Al, paraların burada - 150.000 peso. Onu nerede bulabilirim?"link.l2.go ="CapComission2_3";
			}			
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Soygun! Bu kabul edilemez! Hazırlan, "+GetSexPhrase("oğlan","kız")+"...","Hey, ne halt ediyorsun orada?! Beni soyabileceğini mi sandın? İşin bitti...","Bekle, ne oluyor lan? Ellerini çek! Meğer hırsızmışsın! Yolun sonu, pislik...");
			link.l1 = LinkRandPhrase("Siktir!","Caramba!!","Kahretsin!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("Defol buradan!","Defol evimden!");
			link.l1 = "Hay aksi...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Beni ucuz laflarınla oyalama. Bir dahaki sefere sonucu hiç beğenmeyeceksin...";
        			link.l1 = "Anladım.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "Bitti, konuşmak yok.""Seninle artık konuşmak istemiyorum, o yüzden beni rahatsız etmesen iyi olur.";
			link.l1 = RandPhraseSimple("Nasıl istersen...","Pekâlâ o zaman...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Umarım biraz daha saygılı olur ve kaba davranmayı bırakırsın. Aksi takdirde seni öldürmek zorunda kalırım. Bu hiç hoş olmazdı.";
        			link.l1 = "Emin olabilirsin, Jackman, yapacağım.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Fortorange_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = " Sorunu çözmek mi? Ne yaptığının farkında mısın? Neyse, bana bir milyon peso getir, adamlara da senin 'marifetlerini' unutturmaya çalışırım. Bu fikir hoşuna gitmediyse, defol git cehenneme.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Pekala, ödemeye hazırım.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Anladım. Gidiyorum.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Güzel! Kendini tekrar temiz say. Ama umarım bir daha böyle iğrenç şeyler yapmazsın.";
			link.l1 = "Yapmam. Benim için fazla pahalı. Hoşça kal...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("Bugün bu konuyu zaten konuştuk.",
				                                      "Yeterince açık konuşmadım mı?",
				                                      "Israrcılığın can sıkmaya başladı.",
				                                      "Artık sabrım taştı. Defol buradan!",
				                                      "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Başka zaman konuşuruz...",
				                                   "Elbette, "+npchar.name+"...",
				                                   "Üzgünüm, "+npchar.name+"...",
				                                   "Ah...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "Ha! Kardeşlik tayfası seni fena hırpalıyor ha, " + GetSexPhrase("dostum", "dostum") + "? Onları bir süreliğine dizginleyebilirim. Ama bunun bir bedeli var. " + FindRussianDublonString(iBarbazonTotalTemp) + " ver, işi halledelim.";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "Elbette, işte paran.";
					else link.l0 = "Başka çarem yok gibi görünüyor. Al paranı.";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "Sonra tekrar gelirim...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "Aklını mı kaçırdın" + GetSexPhrase("", "") + "? Bizim tayfa seni vebalı gibi kaçıyor. Hadi git, kafamı ütüleme.";
				else
					dialog.text = "Neden bahsediyorsun, " + GetSexPhrase("dostum", "dostum") + "? Sen baş belasının tekisin — köpekler bile bunu hissediyor. Kimse seninle uğraşmak istemiyor.";
				link.l1 = "Anladım...";
				link.l1.go = "exit";
			}
		break;

		case "pirate_threat_pay":
			iGPThreatRate = 0;
			iGPThreat = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
			DialogExit();
			PiratesDecreaseNotif("");
		break;
	}
}
