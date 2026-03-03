// городские тюрьмы
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;
	// belamour для ночного приключения -->
	int i;
	int SoldQty = 0;
	int SoldNum[10];
	// <--

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":
			dialog.text = RandPhraseSimple("Ben hapishane müdürüyüm. Burada ne istiyorsun?","Ne istiyorsun? Neden hapishaneye geldin?");
			NextDiag.TempNode = "First_officer";
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_prison" && !CheckAttribute(pchar, "questTemp.HelenSCprison"))
			{
				dialog.text = "Miss MacArthur? Sizi burada görmek şaşırtıcı. Bildiğim kadarıyla, ne sizin tayfanızdan ne de Kaptan Swenson'ın tayfasından kimseyi tutuklamadık.";
				link.l1 = "Ben sadece buradayım, efendim. Buna izin yok mu? Arkanda mahkumlarla konuşmuyordum.";
				link.l1.go = "Helen_meeting";
				pchar.questTemp.HelenSCprison = true;
				break;
			}
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaTrevoga") && npchar.city == "SentJons")
			{
				dialog.text = "Ah, Charles de Maure... Tutuklanıp subayının yanına gönderilmen gerekirdi, ama... bankadaki olay talihsiz bir yanlış anlama olarak değerlendirildi.";
				link.l1 = "Bu konuşmaya başlama şeklinizi beğendim, Bay. "+GetFullName(NPChar)+". Her şeyi açıklayabilirim.";
				link.l1.go = "DTSG_AntiguaTrevoga_2";
				break;
			}
			// <-- Длинные тени старых грехов
			
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Subay, hapishanenizde Folke Deluc adında bir adam olduğunu duydum. Onun serbest bırakılması için yapabileceğim bir şey var mı?";
                link.l1.go = "Sharlie";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Memur bey, yine Folke Deluc adlı mahkûm hakkında geldim. Borcunun haklarını satın aldım ve bu adamın velayetimi devralmasını istiyorum. İşte borç belgeleri, buyurun bakın.";
                link.l1.go = "Sharlie_3";
				break;
			}	
			//<-- Бремя гасконца
			
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Selamlar, kaptan. Sizi buraya getiren nedir?";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Selamlar, Amiral Yardımcısı! Size nasıl yardımcı olabilirim?";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Sayın Ekselansları, Genel Vali! Bir emriniz var mı?";
			}
			// <-- legendary edition
			link.l1 = "Ah, özel bir şey yok, biliyorsun, sadece şehirde dolaşıyordum, tesadüfen buraya uğradım.";
			link.l1.go = "exit";
			link.l2 = "Biraz iş konuşmak istiyordum.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}		
			}
			else
			{
				if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}	
			}
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Hapishanenin içine girmek istiyorum.";
				link.l4.go = "ForGoodMove";		
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "Hey, bana şu mahkûmun hangi suçu işlediğini söyleyebilir misin, adı "+GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId))+"hangi suçtan hapis yatıyor?";
				link.l5.go = "KnowAboutPrisoner";	
			}
			
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = "Bir devriye gemisinin eski kaptanının "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" burada gözaltında tutuluyor. Onunla konuşabilir miyim?";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "Ben "+GetFullName(pchar)+", vali adına ve onun emirleri doğrultusunda hareket ederek "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+"eski kaptanla konuşmam gerek "+pchar.GenQuest.CaptainComission.Name+".";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}	
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Bu, kızınızla ilgili...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "begin" && NPChar.location == pchar.GenQuest.Marginpassenger.City + "_prison")
			{
				link.l12 = "Sizinle bir işim var, memur bey. Görevlerinizle bağlantılı olduğu için ilginizi çekeceğine inanıyorum.";
				link.l12.go = "Marginpassenger";
			}
			
			// Warship, 16.05.11. Генер "Justice for sale".
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_prison")
			{
				link.l13 = "Seninle belli bir adam hakkında konuşmak istiyorum - "+PChar.GenQuest.JusticeOnSale.SmugglerName+". O senin tutsağın, yanılmıyorsam.";
				link.l13.go = "JusticeOnSale_1";
			}
			
			// --> belamour ночной приключенец
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToJail"))
			{
				link.l14 = "Merhaba memur. Bildiğim kadarıyla, bir süre önce sarhoş bir vatandaş sokakta bir muhafızla kavga etmeye çalıştıktan sonra gözaltına alınmış."; 
				link.l14.go = "NightAdventure_CitizenHomie";
			}
			
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToPrisoner"))
			{
				link.l14 = "Subay, nöbetçiyle konuştum ve iddialarından vazgeçti. İşte ondan aldığım bir makbuz."; 
				link.l14.go = "NightAdventure_HomieToPrisoner";
			}
			// <-- приключенец
			NextDiag.TempNode = "First_officer";
		break;
		
		// --> Jason Похититель
		case "Marginpassenger":
			dialog.text = "Evet? Bana ne söylemek istiyorsun?";
			link.l1 = "Son zamanlarda, sokakta beni durduranlar oldu "+pchar.GenQuest.Marginpassenger.Name+" bana kirli bir iş ayarlamayı teklif etti: birini, yani adı   olan birini yakalayıp fidye karşılığında serbest bırakmak "+pchar.GenQuest.Marginpassenger.q1Name+". Bu "+pchar.GenQuest.Marginpassenger.Text+"...";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Hmm... Bu gerçekten ilginç - lütfen, devam edin!";
			link.l1 = "Bulunduğu geminin adını biliyordu, "+pchar.GenQuest.Marginpassenger.q1Name+" yelken açmayı planlıyordum. Bu "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" adlı '"+pchar.GenQuest.Marginpassenger.ShipName+"'. Ayrıca, o geminin ne zaman yelken açması gerektiğini de söyledi.";
			link.l1.go = "Marginpassenger_2";
		break;
	
		case "Marginpassenger_2":
			dialog.text = "Ve sana yolcuyu yakalayıp ondan fidye istemeni mi önerdi?";
			link.l1 = "Aynen öyle. Fidye parasını toplamak için, ben de giderdim "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+",   belirli bir kişiye, adı   "+pchar.GenQuest.Marginpassenger.q2Name+". Bu bilgi için ona para verdim, ama tabii ki o kişiyi kaçıracak değildim.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Beni görmeye gelip bana haber vermeye karar verdin demek?";
			link.l1 = "Kesinlikle. O alçağın yaptıkları kasabanızın halkını tehdit ediyor, bundan eminim. Umarım gerekli önlemleri alırsınız.";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			dialog.text = "Bana geldiğinde tamamen haklıydın, "+GetAddress_Form(NPChar)+"! Bu alçak, "+pchar.GenQuest.Marginpassenger.Name+", uzun zamandır gözetimimiz altındaydı. Araştıracağım ve eğer söylediklerinin hepsi doğrulanırsa, bu herifi altı ay boyunca hapse atacağız. Bu ona, saygın vatandaşlara karşı böyle oyunlar kurmamayı öğretir!\nDürüstlüğün ve iyi bir amaç için gösterdiğin isteklilik için, elbette bu davranışını valimize bildireceğim, ki bu da onun sana karşı tutumunu... biliyorsun, olumlu yönde etkileyecek. Yardımın için teşekkürler, kaptan!";
			link.l1 = "Hmm... Rica ederim, yardımcı olmak keyifti. Hoşça kal!";
			link.l1.go = "Marginpassenger_5";
		break;
		
		case "Marginpassenger_5":
			DialogExit();
			NextDiag.CurrentNode = "First_officer";
			AddQuestRecord("Marginpassenger", "20");
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			CloseQuestHeader("Marginpassenger");
			pchar.quest.Marginpassenger_InWorld.over = "yes"; //снять таймер
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			ChangeContrabandRelation(pchar, -25);
			if (GetCharacterIndex("MarginCap") != -1)
			{
				sld = characterFromId("MarginCap");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter(sld.id);
				Group_DeleteGroup("Sea_MarginCap1");
			}
		break;
		//<-- Похититель

		case "EncGirl_1":
			dialog.text = "Tamamen kulak kesildim.";
			link.l1 = "Kaçağını getirdim.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Ah kaptan, çok teşekkür ederim! Nasıl o? Yaralandı mı? Neden kaçtı? Neden?\nAnlamıyor mu? Damat zengin ve önemli bir adam! Gençlik saf ve aptal... hatta zalim bile olabilir. Bunu unutma!";
			link.l1 = "Sen onun babasısın ve son karar senin, ama ben düğün konusunda acele etmezdim...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Ne biliyorsun ki? Senin kendi çocuğun var mı? Yok mu? Bir gün olursa, gel benimle konuş, o zaman anlarsın.\nOnu ailesine geri getiren herkese bir ödül vaat etmiştim.";
			link.l1 = "Teşekkürler. Onu göz önünde bulundurmalısın. İçimde bir his var, bununla yetinmeyecek gibi.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "Sizi dinliyorum, kaptan.";
			link.l1 = "Sana garnizonundaki bir subay ile korsanlar arasındaki suç ortaklığından bahsetmek istiyorum (durumu açıklar).";
			if(makeint(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";			
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";	
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Teşekkür ederim,"+GetSexPhrase("bayım","özlemek")+"! Hemen o alçağı tutuklama emrini vereceğim.\nFakat masraflara girdiniz ve ne yazık ki belediyenin kasası bomboş...";
				link.l1 = "Efendim! Bunu para için yapmadım...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Teşekkür ederim, "+GetSexPhrase("bayım","özlemek")+"! Hemen o alçağı tutuklama emrini vereceğim.\nBir düşünsenize! Ona üstün hizmetlerinden dolayı şahsi bir silah vermek üzereydik. Neyse ki her şey açığa kavuştu ve utanacak hiçbir şeyim kalmadı!";
				link.l1 = "Her zaman adaleti sağlamaktan memnuniyet duyarım.";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mi"+GetSexPhrase("ster","ss")+"! O subayla onun alçak tayfasının kirli işlerden şüpheleniyorduk bir süredir, ama onları şahit olmadan halletmen biraz aceleci bir hareket oldu bence.";
				link.l1 = "Efendim! Ama kendimi savunmak zorundaydım...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";	
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";	
			}
		break;
		
		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Kaptan, ne yaptığınızın farkında mısınız?! Bu tuzağı kurmak için bir aydan fazla uğraştık! Ve şimdi, sadece eğlenceniz için, devriyemizle haberci arasındaki buluşmayı mahvettiniz "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" ve şimdi buraya gelip böbürleniyorsun ha?! Belki şimdi bana bu operasyonun tüm masraflarını ve giderlerini nasıl açıklayacağımı da söylersin?!";
				link.l1 = "Majesteleri! Meseleyi görmezden geliyorsunuz...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Şu haritaya bir bakayım...\nŞaka mı bu? Bu yırtık parşömen parçası mı kanıt olacak?";
				link.l1 = "Majesteleri! Meseleyi görmezden geliyorsunuz...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");	
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";	
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Şimdi bu, tüm devriye grubunun yok edilmesi için gerçekten orijinal bir gerekçe. Neyse ki, buraya gelerek katili arama zahmetinden bizi kurtarmış oldun.";
				link.l1 = "Majesteleri! Meseleyi görmezden geliyorsunuz...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "Nonetheless, I think that your efforts should still be rewarded. Here, take this map; it was found in the belongings of a pirate who has recently gone to the gallows. God willing, perhaps you will actually find that treasure, although I find it quite unlikely...";
			link.l1 = "Teşekkür ederim, bu gerçekten çok cömertçe!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "Gayretin gerçekten takdire şayan. Lütfen, bu kılıcı ödül olarak kabul et – senin için yapabileceğim en azı bu. Ah, bu haritayı da kendine saklayabilirsin. Eminim takımadalarda bu tür sahte haritalardan bolca vardır.";
			link.l1 = "Teşekkür ederim, bu gerçekten çok cömertçe!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "Olabilir, olabilir... Şöyle diyelim, bu anlaşma ilahi adalet ve Rabbimizin iradesiyle karara bağlandı.";
			link.l1 = "Teşekkür ederim, bu gerçekten çok cömertçe!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");			
		break;
		
		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "Bana sakın ders vermeye kalkma! Bana göre, senin bu alçaklarla iş birliği içinde olduğun apaçık ortada! Muhafızlar, bu 'iyilikseveri' yakalayın!";
			link.l1 = "Olmaz!";
			link.l1.go = "fight";
			
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;			
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		// ------------------------- Повод для спешки -----------------------------
		
		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "Ve onunla ne işin var?";
			link.l1 = "Konuşmam gereken birkaç özel meselem var.";
			link.l1.go = "CapComission_PrisonBad2";
		break;
		
		case "CapComission_PrisonBad2":
			dialog.text = "Kaptan, bana verilen doğrudan emirler var; bu konuda soru soran herkesi tutuklayıp konağa göndermem gerekiyor "+pchar.GenQuest.CaptainComission.Name+"daha fazla sorgulama için.";
			link.l1 = "Burada güzel bir düzen kurmuşsun! Mahkumların gelip kendi ayaklarıyla teslim olmasını sağlıyorsun!";
			link.l1.go = "CapComission_PrisonBad3";
		break;
		
		case "CapComission_PrisonBad3":
			dialog.text = "Yine de, sizden silahlarınızı teslim etmenizi rica ediyorum!";
			link.l1 = "Siktir git! O zaman zorla al bakalım!";
			link.l1.go = "fight";
			CaptainComission_GenerateCaptainInPrison(); // данила . на всякий случай ,чтобы сгенерился нормально.
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonGood1":
			dialog.text = "Evet, elbette. Validen bu meselede size yardımcı olmam için emir aldım. Artık mahkumu ziyaret edebilirsiniz.";
			link.l1 = "Teşekkür ederim...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonFree1":
		if(CheckAttribute(pchar,"GenQuest.CaptainComission"))// лесник . разделение диалога если кеп убит или нет
		{
			dialog.text = "Ehm, kaptan, bu tutukluyu serbest bırakma yetkim yok. Validen izin istemeniz gerekiyor.";
			link.l1 = "Memur bey, ben soruşturmanın iyiliği için hareket ediyorum. Tutuklu, yetkililerle iş birliği yapmayı ve gizli yeri açıklamayı kabul etti. Zaman çok önemli – kaçakçılar değerli yükü bulabilir, o zaman da halkın elinden kaybolur.";
			link.l1.go = "CapComission_PrisonFree2";
		}
         else
		 {
         	dialog.text = "Onu öldürmemeliydiniz, Kaptan... Ama bana fark etmez. Onun yerine sizi idam edeceğiz. Muhafızlar! Onu yakalayın!";
            link.l2 = "Yanlış adamla uğraştın!...";
             link.l2.go = "fight";
			 NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		 }			 
		break;
		
		case "CapComission_PrisonFree2":
			dialog.text = "Ama ona bir koruma tahsis edebilirim.";
			link.l1 = "Buna gerek yok - yeterince muhafızım var. Ayrıca, gizli yerin ortaya çıkmasını istemem.";
			link.l1.go = "CapComission_PrisonFree3";
		break;
		
		case "CapComission_PrisonFree3":
			dialog.text = "Hmm... peki, öyle olsun. Ama onun yerine senin başınla hesaplaşacağız.";
			link.l1 = "Elbette.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		break;
		// -------------------------- Операция 'Галеон' ----------------------------
		
		case "F_ShipLetters_1":
			dialog.text = "Şimdi konuş, dinliyorum.";
			link.l1 = "Yanımda bazı gemi evrakları var. Sahibi muhtemelen kaybetmiş, ve bunun sizin ilginizi çekebileceğini düşünüyorum.";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;
		
		case "F_ShipLetters_2":			
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Saçmalık! İşimden alıkoyma beni! Umursuyorsan liman yetkililerine git!";
				link.l1 = "Pekâlâ, sanırım teşekkür ederim...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Evet, buranın sahibi o. Belki de bir ödül "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" peso, kaptan, dikkatiniz için yeterli bir ödül olacaktır.";
					link.l1 = "Belki de değil.";
					link.l1.go = "F_ShipLetters_3";	
					link.l2 = "Cömert bir teklif. O halde belgeler sizin!";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Ah, bu gerçekten ilginç! Şehir hazinesi size memnuniyetle ödeme yapacaktır "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" kaçak ticaretle mücadeleye katkınız için pesos.";
						link.l1 = "Belki de değil.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Cömert bir teklif. O halde belgeler sizin!";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Aman Tanrım! Ne büyük şans ki bana geldiniz. Sanırım bahtsız meslektaşım size seve seve ödeme yapacaktır "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" bu olayın duyulmasını önlemek için peso.";
						link.l1 = "Belki de değil.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Cömert bir teklif. O halde belgeler sizin!";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;
		
		case "F_ShipLetters_3":
			dialog.text = "Burası benim şehrim, kaptan.";
			link.l1 = "Bunu unutmayacağım.";
			link.l1.go = "exit";
		break;
		
		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "8");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
        case "ForGoodMove":
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Elbette, her şeyi görebilirsiniz - burada her şey mükemmel bir düzende!";
				link.l1 = "Pekala, bir bakalım Teğmen.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Elbette, Ekselansları. Geçebilirsiniz.";
				link.l1 = "Teşekkür ederim, memur.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// Офицер с патентом
			if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Pekâlâ, seni reddetmem için bir sebep göremiyorum - sonuçta, sen geminin kaptanısın ve     hizmetindesin "+NationNameGenitive(sti(npchar.nation))+". İçeri gel."; 
				link.l1 = "Teşekkür ederim, memur.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// <-- legendary edition
			dialog.text = NPCStringReactionRepeat("Ama neden oraya gitmek istiyorsun? İnan bana, orada hırsızlar ve haydutlardan başka ilgi çekici hiçbir şey yok.","Bu dileğini zaten konuşmuştuk.","Yine mi? Zaten iki kere konuştuk bunu!","Hmm, yine...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Bununla birlikte, cephanelikleri gezmenize katılmak isterim. Çok ilgimi çekiyor!","Evet, tam olarak öyle. Ama bunun hakkında konuşmak istedim.","Belki de üçüncü seferde...","Tutsaklarınızın benden kaçmadığını umarım.",npchar,Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
		
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = 20+hrand(3)*10;
			if (sti(colonies[FindColony(npchar.city)].jail))
			{
				dialog.text = "Pekâlâ, reddetmek için bir sebep göremiyorum. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money))+" - ve hapishaneden çıkana kadar, koridorlarda özgürce dolaşabilir ve hatta mahkumlarla sohbet edebilirsin.";
				if (PCharDublonsTotal() >= sti(sti(pchar.questTemp.jailCanMove.money)))
				{
					link.l1 = "Katılıyorum, işte paralarınız!";
					link.l1.go = "ForGoodMove_agree";
				}
				link.l2 = "Bu işe yaramaz. Koridorlarda amaçsızca dolaşmak için bu çok fazla.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("Hayır, bu yönetmeliklere kesinlikle aykırı. Ne? Burası sirk mi sandın? Defol git ve beni görevimden alıkoyma.","Hapishanemde yabancıların dolaşmasına izin veremem. Lütfen, beni daha fazla rahatsız etmeyin!");
				link.l1 = "Peki, nasıl istersen...";
				link.l1.go = "exit";
			}
		break;
		
        case "ForGoodMove_agree":
            dialog.text = "Pekâlâ, şimdi gezine başlayabilirsin...";
			link.l1 = "Teşekkür ederim, memur.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.money)));
		break;
		
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "For murder."; break;
				case "1": sTemp = "He is accused of piracy."; break;
				case "2": sTemp = "For banditry and robbery."; break;
				case "3": sTemp = "He was caught stealing."; break;
				case "4": sTemp = "For petty theft."; break;
				case "5": sTemp = "For cheating."; break;
				case "6": sTemp = "For vagrancy and begging."; break;
			}
			dialog.text = sTemp;
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				link.l1 = "Anladım... Subay, bu mahkûmu bana teslim et, onun kaderine ben karar vereceğim.";
				link.l1.go = "KnowAboutPrisoner_gengov";
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				link.l1 = "Anladım... Memur, onu bana teslim et, bu mahkumun kaderine ben karar vereceğim.";
				link.l1.go = "KnowAboutPrisoner_admiral";
				DeleteAttribute(pchar, "questTemp.jailCanMove.City");
				break;
			}
			link.l1 = "Anlıyorum... Peki, satın alma, kefalet... ya da başka bir yolla serbest bırakma ihtimali var mı?";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
		
        case "KnowAboutPrisoner_0":
			dialog.text = "Elbette hayır. O cellat kuşu doğruca cehenneme gidecek. Vali onun davasını bizzat takip ediyor!";
			link.l1 = "Heh, anlıyorum...";
			link.l1.go = "notFree_exit";
		break;	
		
		case "KnowAboutPrisoner_1":
			dialog.text = "Şaka mı yapıyorsun? O çoktan darağacına gitmiştir! Yakında ipi boynuna geçirir. Boşver gitsin.";
			link.l1 = "Anladım. Ve çoktan unuttum...";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_2":
			dialog.text = "Bence olmaz. Kasaba halkımıza çok sorun çıkardı. O yüzden bunu isteme.";
			link.l1 = "Hmm, anlıyorum.";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_3":
			dialog.text = "Muhtemelen hayır. O bir hırsız ve hırsız hapiste kalmalı.";
			link.l1 = "Oh!   Güzel söyledin, teğmen!";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_4":
			dialog.text = "Gerçekten bilmiyorum. Sadece önemsiz bir şey çaldı. Onu serbest bırakamam ama onu hapiste çürümeye terk etmek de doğru değil.";
			link.l1 = "O halde onu bana verin, teğmen. Onun için kefalet ödeyeceğim — tabii ki makul bir miktar.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_5":
			dialog.text = "Serbest bırakmak mı? Öyle görünüyor. Bana sorarsan, o küçük hırsızı burada tutmanın hiçbir anlamı yok.";
			link.l1 = "Pekala, o zaman onu bana teslim edin, teğmen. Onun için kefalet ödeyeceğim – tabii ki makul bir miktar.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
		case "KnowAboutPrisoner_6":
			dialog.text = "Hmm... Sözlerinde mantık var. Bu serseri buraya ait değil - sadece pislik ve hastalık yayıyor...";
			link.l1 = "Pekala, o halde onu bana verin, teğmen. Onun için kefalet ödeyeceğim – tabii ki makul bir miktar.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = 50+hrand(10)*10;
			dialog.text = "Pekala, anlaştık. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money))+" hemen peşin ödeyin, ve onu şimdi götürebilirsiniz.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				link.l1 = LinkRandPhrase("Mükemmel! Katılıyorum!","Anlaştık, subay!","Mükemmel. Bu katkı payını ödemeye hazırım.");
				link.l1.go = "KnowAboutPrisoner_agree";
			}
			link.l2 = "Hayır, bu çok pahalı. Sanırım vazgeçeceğim.";
			link.l2.go = "KnowAboutPrisoner_exit";
		break;
		
        case "KnowAboutPrisoner_agree":
			dialog.text = "Pekâlâ, hücresine gidebilirsin ve o serseriyi de yanında götür.";
			link.l1 = "Teşekkürler.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			Log_Info("You have given " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		
        case "KnowAboutPrisoner_exit":
			dialog.text = "Pekâlâ, bu senin seçimin. Sana bir şans daha vermeyeceğim...";
			link.l1 = "Gerek yok.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
		
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// belamour legendary edition -->
		// генерал-губернатор
		case "KnowAboutPrisoner_gengov":
			dialog.text = "Elbette, Ekselansları, eğer öyle arzu ediyorsanız, bu talihsize sahip olun. Yalnız dikkatli olun, hâlâ bir suçlu...";
			link.l1 = "Harika. Merak etme, teğmen, ne yaptığımı biliyorum.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// вице-адмирал
		case "KnowAboutPrisoner_admiral":
			dialog.text = "Yani... Ne desem bilemiyorum... Aslında, mahkumları öylece salıveremem. Ama yine de bir tümamiral olduğunuz için, muhtemelen bu suçluyu almanızda bir sakınca yok.";
			link.l1 = "Harika. Merak etme, teğmen, ne yaptığımı biliyorum.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// <-- legendary edition
		//---------------- Протектор ------------------
        case "First_protector":
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Genel Vali, Ekselansları! Buyurun, ama dikkatli olun: bu suçlulardan her şey beklenir...";
				link.l1 = "Endişelenme asker, bir şey olursa ben hallederim.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Selamlar, Amiral Yardımcısı! Burada görev başındayım: Kimsenin izinsiz girip çıkmamasını sağlıyorum. Ama tabii ki, siz istediğiniz gibi geçebilirsiniz.";
				link.l1 = "Eh, bu harika.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("Geçebilirsiniz, gardiyan izin verdi.","Hapishane müdüründen bir emir aldım. Serbestçe geçebilirsiniz.");
				link.l1 = "Çok iyi.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("Hapishane müdüründen özel izin almadan daha ileri gidemezsiniz!","Ben sadece hapishane müdürüne hesap veririm! Onun izni olmadan daha ileri gitmeye kalkarsan, işin biter!");
				link.l1 = RandPhraseSimple("Anladım","Pekala")+", asker.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("Ben görevdeyim, beni rahatsız etme.","Yoluna devam et, seninle konuşmam yasak.");
			link.l1 = "Pekâlâ, asker.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключенные ------------------
        case "First_prisoner": 
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("Ho-ho, ne güzel bir zaman değil mi!","Kes onları, "+GetSexPhrase("ahbap","kız")+", kes!!!","Vay canına! Gardiyanımın cesedini göreceğimden umudumu tamamen kesmiştim!");
				link.l1 = RandPhraseSimple("Heh!","Arrgh!");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander")) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Bekle, "+GetSexPhrase("dostum","kız")+"Bırak beni!!","Dinle, "+GetSexPhrase("ahbap","kız")+", lütfen hücreyi açın.");
					link.l1 = "Hangi sebeple?";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Soygunla suçlanıyorum, ama suçlu değilim!","Arrgh, sen bakımlı pislik... Biraz hücremde oturmak ister misin?! Kheh-heh-heh...","Suçlu değilim!");
				link.l1 = RandPhraseSimple("Kapa çeneni!","Senin umurunda bile değilim...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn)) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Bekle, "+GetSexPhrase("ahbap","lass")+", bu kadar aceleyle geçip gitme!","Acele etme, "+GetSexPhrase("dostum","kız")+", hadi konuşalım.");
					link.l1 = "Hangi sebeple?";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключённого --------------------
        case "Prisoner_1":
            dialog.text = "Dinle beni, dostum. İyi görünmediğimi falan sanma. Sadece buradan çıkmam lazım...";
			link.l1 = "Ne?!";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
			npchar.nation = PIRATE;
		break;
        case "Prisoner_2":
            dialog.text = "Ne duyduysan! Bana yardım et, ben de sana mutlaka karşılığını öderim...";
			link.l1 = "Bu ilginçmiş. Sen kimsin ve bana ne sunabilirsin?";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "Benim adım "+GetFullName(npchar)+". Güvende sakladığım bazı şeyler var. Sadece beni buradan çıkar ve beni götür "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Acc")+". Orada, bir mağarada, hazinem var. Onu alıp paylaşacağız!";
			link.l1 = "Peki, senin sakladıklarında neler var? Ve bana doğruyu söylediğinden nasıl emin olabilirim?";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "Yemin ederim, doğruyu söylüyorum! Gizli yere gelince – orada hazine ve para var...";
			link.l1 = "Hayır dostum. Şüpheli bir ganimet için canımı tehlikeye atmam. Üzgünüm...";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{			
				// belamour legendary edition адмирал и губернатор может договориться без денег
				bool bAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bool bGenGov = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == GetBaseHeroNation());
				if(!bAdmiral && !bGenGov)
				{
				link.l2 = "Pekâlâ, risk almaya değer olabilir... Şöyle bir teklifim var: Hapishanedeki muhafızları etkisiz hale getirip seni gemime götürebilirim. Her şey yolunda giderse, mağaraya varana kadar sürekli yanımda kalmanı istiyorum. "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". Anlaştık mı?"; // belamour gen
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				}
				link.l3 = "Pekala, sana yardım etmeye çalışacağım. Hapishane müdürüyle konuşacağım. Belki seni kefaletle çıkarabilirim.";
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = "Pekala, sana güvenip hücreni açacağım. Mağaraya varana kadar her zaman yanımda kalmanı istiyorum "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". Anlaştık mı?";
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("Lanet olsun sana, seni alçak!","Kahretsin seni, beni soydun, pislik...");
			link.l1 = RandPhraseSimple("Sana da en iyisini dilerim. Hoşça kal...","Ay, köpeklerin havlamasına aldırmaz...");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "Pekâlâ. Seçme şansım yok şu an.";
			link.l1 = "Pekala. Şimdi kilidini kırıp seni çıkaracağım, sonra birlikte yolumuza devam edeceğiz. Hazır mısın?";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "Evet, "+GetSexPhrase("dostum","kız")+", hazırım!";
			link.l1 = "O zaman başlayalım!";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "Pekâlâ. Seçici olabilecek durumda değilim.";
			link.l1 = "Pekala. Hemen arkamdan gel - hâlâ gemime ulaşmamız gerekiyor. Sakın oyalanma!";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "Pekâlâ, deneyebilirsin. Umarım bu işten sağ çıkarız! Ama vakit kaybetme – birkaç güne kadar buradan gitmiş olacağım...";
			link.l1 = "Burada bekle, her şeyi ayarlayacağım.";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(6); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

        case "ToPrisonHead_canMove":
            dialog.text = "Peki, ne dersin, "+GetSexPhrase("dostum","kız")+"?";
			link.l1 = "Her şey ayarlandı, seni buradan götürebilirim.";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "O zaman hadi buradan gidelim! Aman Tanrım, ne kadar mutluyum!";
			link.l1 = "Özetleyelim. Mağaraya varana kadar her an yanımda olmanı istiyorum "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat")+", sadece bir adım geride kalacaksın. Ne olur ne olmaz. Kabul ediyor musun?";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "Elbette, kabul ediyorum! Zaten seçim şansım da yok.";
			link.l1 = "O halde özgürsün.";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "murder"; break;
				case "1": sTemp = "piracy"; break;
				case "2": sTemp = "brigandry"; break;
				case "3": sTemp = "thievery"; break;
			}
            dialog.text = "Peki, ne dersin, "+GetSexPhrase("dostum","kız")+"?";
			link.l1 = "Seni serbest bırakamadım. Şu suçla itham ediliyorsun: "+sTemp+", bu yüzden kefaletle serbest bırakılamazsınız.";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
		
        case "ToPrisonHead_notFree_1":
            dialog.text = "Ama bana iftira atıldı! Ah, şeytan! Şimdi ne yapacağım? Burada diri diri çürüyüp gideceğim!";
			link.l1 = "Üzgünüm dostum, ama senin için yapabileceğim hiçbir şey yok.";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "Tek bir şansımız kaldı - seni zorla kurtarmak. Şimdi kilidini kırıp seni çıkaracağım, sonra birlikte yolumuzu açacağız. Hazır mısın?";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("Kahrolasıca!","Lanet olsun, beni soydun, seni kaltak...");
			link.l1 = "Sana da en iyisini dilerim. Hoşça kal...";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "Peki, iyi bir haber var mı, "+GetSexPhrase("dostum","kız")+"?";
			link.l1 = "Kefalet bedelin çok yüksek, o kadar param yok. Sana yardım etmeyi bırakmak zorundayım.";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "Dinle, her şeyi kontrol ettim ama hiçbir hazine bulamadım. Ne yazık ki böyle oldu. Biri bizden önce gelip gömmüş olmalı.";
					link.l1 = "Ve bu nasıl olabilir?!";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "Onu buldum! Hazine hâlâ bıraktığım yerde.";
					link.l1 = "Mükemmel. O halde, ayrılalım mı?";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "İşte burada, benim gizli birikimim. Çok fazla değil, ama sahip olduğum her şey bu. Anlaştığımız gibi, bunun yarısı senin.";
					link.l1 = "Evet, hazine gerçekten mütevazı. Yine de, hiç yoktan iyidir.";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "Kaptan, üzgünüm ama... Hazine yok.";
					link.l1 = "Ne?! Beni kandırdın, alçak herif! Seni o adaya götürdüm - peki ne için? Bunun hesabını vereceksin!";
					link.l1.go = "Node_3";
				break;
				case 4:
                    ok = GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(PChar, "map_part2") == 0;
                    if(GetCharacterItem(PChar, "map_part1") > 0 && !ok) // Первая половинка есть, но вторую дать нельзя
                    {
                        dialog.text = "Dinle, her şeyi kontrol ettim ama hiçbir hazine bulamadım. Böyle olması gerçekten üzücü. Biri bizden önce gelip çıkarmış olmalı.";
                        link.l1 = "Ve bu nasıl mümkün olabilir?!";
                        link.l1.go = "PrisonerInPlace_1";
                    }
                    else
                    {
                        dialog.text = "Lanet olsun... Bu nasıl olabilir? Olamaz!";
                        link.l1 = "Ne oluyor, dostum? Hazine nerede? Sakın bana hazine yok deme!";
                        link.l1.go = "Node_4";
                    }
				break;
			}
		break;
			
		case "Node_1":
			dialog.text = "Elbette, anlaştığımız gibi. Hazinenin yarısı senin.";
			link.l1 = "Kutsal Tanrım, burada gerçekten çok değerli şeyler var!";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 4+hrand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry5", 10+rand(10));
			TakeNItems(pchar, "jewelry46", 60+rand(20));
			TakeNItems(pchar, "jewelry47", 40+rand(15));
			TakeNItems(pchar, "jewelry40", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_2":
			dialog.text = "Kaptan, diğer şeylerin arasında o Hint eşyası da var. Payınıza ek olarak onu da alabilirsiniz.";
			link.l1 = "Pekala, en azından serbest kalman için değerli bir şey var! Hadi, ver onu.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry10", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			TakeNItems(pchar, "jewelry11", rand(2)+1);
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_3":
			dialog.text = "Bekle, Kaptan, heyecanlanma, açıklamama izin ver. Ben de senin gibi bir denizciyim. Yanlışlıkla hapse atıldım, yemin ederim. Kaçmak için tek şansım sendin ve hazine hakkında sana yalan söylemek zorunda kaldım.\nBir hazine yok, ama oraya iyi bir şey sakladım. Onu al ve beni huzur içinde bırak. Belki bir gün bir savaşta, bu senin hayatta kalmana yardım eder.";
			link.l1 = "Pekâlâ, zaten senden pek bir şey beklemiyordum. Neyse ki kin tutan biri değilim.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received equipment");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_4":
			dialog.text = "Hayır!!! Burada yok! Kahrolası kağıt parçası... Kaptan, burada bulacağımdan emindim! Ama demek ki yanılmışım! O kağıt parçasındaki bir şey gerçekten belirsizdi...";
			link.l1 = "Eh, neyse... Başın büyük belada, dostum. Ama yine de açıklamanı duymak isterim.";
			link.l1.go = "Node_4_1";
		break;
			
		case "Node_4_1":
			dialog.text = "Haritanın bir parçası vardı elimde. Gerçek bir haritaydı, yemin ederim! Ama üzerinde hangi adanın gösterildiğini anlamak çok zordu... Burası sanmıştım... Ama gördüğün gibi, yanılmışım.";
			link.l1 = "Hangi kağıt parçası? Onu hemen bana ver!";
			link.l1.go = "Node_4_2";
		break;
			
		case "Node_4_2":
			AddMapPart();
			dialog.text = "Elbette, al. Kaptan, beni bırak... lütfen? Hazinenin orada olduğuna gerçekten inanmıştım. Belki sen nerede olduğunu bulursun ve kendin alırsın. Sana yalvarıyorum.";
			link.l1 = "Anladım... Gerçekten de, bu paçavradan bir şey anlamak zor. Haritanın ikinci yarısı lazım. Tamam, şimdi defol. Artık görüyorum, bu senin suçun değildi.";
			link.l1.go = "PrisonerInPlace_4";
		break;
			
		case "PrisonerInPlace_1":
			dialog.text = "Gayet basit, "+GetSexPhrase("dostum","kız")+". Hayatta her şey olur.\nBak, buradasın - istersen kal, istersen daha fazlasını ara. Neyse, benim gitmem gerek!\nHoşça kal, "+GetSexPhrase("arkadaşım","kız")+", hayatımı kurtardığın için teşekkür ederim. Seni asla unutmayacağım!";
			link.l1 = "Alçak! Bununla paçayı sıyırabileceğini mi sandın?! Hey! Dur bakalım, korkak!";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();

            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
		
        case "PrisonerInPlace_3":
			dialog.text = "Buyurun. Teşekkür ederim!";
			link.l1 = "Elveda...";
			link.l1.go = "PrisonerInPlace_2";
		break;
		
        case "PrisonerInPlace_4":
			dialog.text = "Teşekkür ederim, kaptan! Hayatımın geri kalanında sizin için dua edeceğim!";
			link.l1 = "Ah, kapa çeneni! Hadi git, yolun açık olsun...";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        
		// -------------------- освобождение заключённого --------------------
		// ------------------------ передать маляву --------------------------
        case "Deliver_1":
			dialog.text = "Benim adım "+GetFullName(npchar)+". Senden bir ricam var, he-he...";
			link.l1 = "Ne haber?";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "Bir mektubun hapishaneden gönderilmesi gerekiyor. Bunu yapar mısın?";
			link.l1 = "Peki, bundan bana ne fayda var?";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "Adamlar seni hayal kırıklığına uğratmaz, söz veriyorum... Ee? Var mısın?";
			link.l1 = "Hayır, ilgilenmiyorum.";
			link.l1.go = "Prisoner_5";
			link.l2 = "Pekâlâ, eğer benden çok fazla çaba gerektirmiyorsa, yapabilirim.";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "Peki. Şimdi beni dikkatlice dinle. İki arkadaşım bir evde mesajımı bekliyor, böylece baskın sırasında yakalanmayacaklar. Ama hangi ev olduğunu hiç bilmiyorum. Senin araman gerekecek.";
			link.l1 = "Ne demek istiyorsun - aramak mı?";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "Araştırmak dediğim, gerçekten araştırmak. Şehri dolaşacaksın, evlerin içine bakacaksın. Doğru yere vardığında, seni konuşmadan bırakmazlar. Ama unutma, ben orada en fazla iki gün daha kalırım. Yani gecikme.";
			link.l1 = "Anladım. O halde, mektubunu ver bakalım.";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "Hmm, biliyor musun, senden hoşlanmıyorum. Fikrimi değiştirdim. Hadi, öylece durma, gel!";
				link.l1 = "Sana bak! Peki, nasıl istersen...";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "Al bakalım. Teşekkür ederim. "+GetSexPhrase("dostum","kız")+"!";
				link.l1 = "Hiç de bile.";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true; 
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
		
		// Warship, 16.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Evet, kaçakçılıkla suçlanıp tutuklandı. Ama o cellatlık herifle neden ilgileniyorsun, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Çetesi onun kaçışını ayarlamayı ve pis işlerine devam etmeyi planlıyor.";
			link.l1.go = "JusticeOnSale_2";
			link.l2 = "Onun suçlu olmadığını duydum.";
			link.l2.go = "JusticeOnSale_3";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Valiye haber vermelisin, "+GetAddress_Form(NPChar)+", bu alçakların hepsi yakalanmalı!";
			link.l1 = "Tam da öyle yapacağım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Dinle, "+GetFullName(PChar)+", o adam kasabada yasaklı malları satmaya çalışırken yakalandı! Onun suçsuz olduğunu nasıl iddia edebilirsin?";
			link.l1 = "Suçlamanın asılsız olduğunu ve elinizde hiçbir kanıt olmadığını duydum, doğru mu? Haksızlığa uğramış bir adamı öylece tutamazsınız.";
			link.l1.go = "JusticeOnSale_4";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Ne şahitlerimiz var ne de mallar, ama bu hiçbir şeyi değiştirmiyor, Kaptan "+GetFullName(PChar)+"! O kişi kesinlikle suçlu - ve belki de sadece yasa dışı ticaretle sınırlı değil. Her halükarda, mahkûmla neden ilgileniyorsun?";
			link.l1 = "Belki de sözüm o talihsiz mahkum için kefalet olabilir?";
			link.l1.go = "JusticeOnSale_5_WithoutMoney";
			
			if(sti(PChar.money) >= 5000)
			{
				link.l2 = "Belki bu 5000 peso, o talihsiz mahkûmun kefaleti için kullanılabilir?";
				link.l2.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5_WithoutMoney":
			if(GetCharacterSkill(PChar, SKILL_LEADERSHIP) > hrand(100) || sti(PChar.money) < 5000)
			{
				dialog.text = "Pekâlâ, "+GetAddress_Form(NPChar)+", al şu herifi ve defol git, yoksa fikrimi değiştiririm.";
				link.l1 = "Adaletin galip geldiğini görmek harika, sence de öyle değil mi?";
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				dialog.text = "Hayır, "+GetAddress_Form(NPChar)+", bu olmaz.";
				link.l1 = "O halde, belki de bu 5.000 peso daha ikna edici bir sebep olabilir?";
				link.l1.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Pekâlâ, "+GetAddress_Form(NPChar)+", al şu herifi ve git, yoksa fikrimi değiştiririm.";
			link.l1 = "Adaletin yerini bulduğunu görmek güzel, sence de öyle değil mi?";
			link.l1.go = "JusticeOnSale_6";
			AddMoneyToCharacter(PChar, -5000);
			PChar.GenQuest.JusticeOnSale.PrisonMoney = true;
		break;
		
		case "JusticeOnSale_6":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Smuggler", "mercen_"+(rand(9)+1), "man", "man", sti(PChar.rank)+5, PIRATE, -1, true, "marginal"));
			SetFantomParamFromRank(sld, sti(PChar.rank)+5, true);
			sld.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
			sld.lastName = "";
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "Enc_Raiders"; 
			AddPassenger(PChar, sld, false);
			SetCharacterRemovable(sld, false);
			PChar.GenQuest.JusticeOnSale.SmugglerModel = sld.model;
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.function = "JusticeOnSale_ShoreEnterWithSmuggler";
			Log_Info("Smuggler's captain on a board");
			PlaySound("interface\notebook.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,0,60); // 280313 // лесник. прокрутка времени было так WaitDate("",0,0,0,2,5);
		break;
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomie":
			dialog.text = "Evet, öyle biri vardı, çok hırçındı. Bir nöbetçiye kaba davrandı, sonra da kavgaya karıştı. Hepsi bu kadar: ayılana kadar birkaç gün hücrede kalacak. Neden onunla ilgileniyorsunuz? Siz kaptana benziyorsunuz, bu ayyaş ise denizciye hiç benzemiyor.";
			link.l1 = "Evet, doğru, ben bir kaptanım. Şu mesele de, bu sarhoş eski bir tanıdığım. Lütfen, bunu kimseye söylemeyin. Yanlış anlamadıysam, silahını bile çekmemiş. Belki bu seferlik, bana bir iyilik olarak onu bırakırsınız?";
			link.l1.go = "NightAdventure_CitizenHomie_1";
		break;
		
		case "NightAdventure_CitizenHomie_1":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomie") // отпустил под честное слово
			{
				dialog.text = "Evet, o benim iyi bir dostumdur. Merak etme, kimseye bir şey söylemem. Aslında, doğru düzgün bir darbe bile indiremedi, sadece bir girişimdi - bu yüzden hapse attılar. Madem sen istiyorsun, sana saygımdan dolayı onu serbest bırakacağım. Ama ona bir dahaki sefere kendine hakim olmasını söyle. Hatta en iyisi, daha az içmesini sağla.";
				link.l1 = "Teşekkür ederim, memur.";
				link.l1.go = "NightAdventure_CitizenHomieOK";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM" || pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM") // поговорить с солдатом
			{
				dialog.text = "Evet, iyi dostum. Merak etme, kimseye söylemem. Sadece, onu bağlamadan önce nöbetçiye bir yumruk atmayı başardı. Bu yüzden onu serbest bırakamam. Tabii ki, nöbetçi şikayetini geri çekmeye razı olursa başka. Kendin de konuşabilirsin, bugün şehirde devriye geziyor.";
				link.l1 = "Hayır, korkarım ki eğer gardiyana vurduysa ona yardımcı olamam. Birkaç gün içeride kalmak zorunda. Sizi rahatsız ettiğim için üzgünüm, memur bey.";
				link.l1.go = "CitizenHomieEnd";
				link.l2 = "Pekala, gidip nöbetçiyle pazarlık yapmayı deneyeceğim.";
				link.l2.go = "NightAdventure_CitizenHomieSolder";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieOfficer") // выплата офицеру
			{
				dialog.text = "Evet, iyi dostum. Merak etme, kimseye söylemem. Ama mesele şu ki, görev başındaki bir askere saldırmak suçtur. Sana bir jest yapabilirim ve onu serbest bırakabilirim, ama kefaletle.";
				link.l1 = "Ve bunun için ne kadar ödemem gerekiyor?";
				link.l1.go = "NightAdventure_CitizenHomieOfficer";
			}
		break;
		
		case "NightAdventure_CitizenHomieOK":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
		break;
		
		case "NightAdventure_CitizenHomieEnd":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_CitizenHomieSolder":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				if(Characters[i].location != npchar.City+"_town") continue;
				if(Characters[i].chr_ai.type != "patrol") continue;
				while(SoldQty < 10) // на всякий случай, чтобы не было выхода за границы массива
				{                   // генерируется 7 солдат + 3 мушкетера
					SoldNum[SoldQty] = Characters[i].index;
					SoldQty++;
				}
			}
			iTemp = rand(SoldQty);
			pchar.GenQuest.NightAdventureSolNum = SoldNum[iTemp];
		break;
		
		case "NightAdventure_HomieToPrisoner":
			DeleteAttribute(pchar,"GenQuest.NightAdventureToPrisoner");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "*okur* Yani... yani... Nöbetçi şikayetçi olmadığına göre, benim de bir şikayetim yok. Arkadaşını alabilirsin. Ama ona bir dahaki sefere kendine hakim olmasını söyle. Hatta, en iyisi, daha az içmesini sağla.";
			link.l1 = "Teşekkür ederim, memur.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieOfficer":
			dialog.text = "Silahını çekmediğine göre, bu sadece 1.500 peso.";
			link.l1 = "Sanırım o kadarını vermeye hazır değilim. Neyse, burada sadece birkaç gün kalacaksa, ona bir zararı dokunmaz herhalde. Belki de daha az içer.";
			link.l1.go = "NightAdventure_CitizenHomieEnd";
			if(sti(pchar.money) >= 1500)
			{
				link.l2 = "Pekala, kefaleti ödemeye hazırım.";
				link.l2.go = "NightAdventure_CitizenHomieOfficer_1";
			}
		break;
		
		case "NightAdventure_CitizenHomieOfficer_1":
			AddMoneyToCharacter(pchar, -1500);
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "Arkadaşını alabilirsin. Ama ona bir dahaki sefere kendine hakim olmasını söyle. Hatta en iyisi, daha az içmesini sağla.";
			link.l1 = "Teşekkür ederim, memur.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		// --> Sinistra Путеводная звезда
		case "PZ_BasTer_ComendantDialog":
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerOpozdal"))
			{
				dialog.text = "Katliam başlatmak yerine gelmeyi kabul ettiğin için teşekkür ederim. Şu günlerde en azından birileri mantıklı davranıyor.";
				link.l1 = "Ee, bu ilginin sebebi nedir, Mösyö Subay? Çinli bir adam arıyor olmamla bir ilgisi var mı?";
				link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_1";
			}
			else
			{
				dialog.text = "Bize isteyerek gelmen iyi oldu. Son zamanlarda başımıza yeterince bela çıktı zaten.";
				link.l1 = "Gördüğünüz gibi, ben şiddete başvuran biri değilim. Fakat... neden buradayım, memur? Adamlarınıza da sordum ama hâlâ bir cevap alamadım - şehirde belirli bir Çinliyi aradığım için mi buradayım?";
				link.l1.go = "PZ_BasTer_ComendantDialog_1";
			}
			DeleteQuestCondition("PZ_BasTerPeshera");
			npchar.Dialog.Filename = "Common_Prison.c";
			npchar.Dialog.CurrentNode = "First_officer";
		break;
		// <-- Путеводная звезда
		case "Helen_meeting":
			dialog.text = "Olur mu öyle şey! Lütfen, içeri buyurun. Zindanlarımıza her zaman hoş geldiniz. Yani, tabii ki iyi anlamda söylüyorum. Peki, sizi buraya ne getirdi?";
			link.l1 = "Ah, özel bir şey yok, biliyorsun, sadece şehirde dolaşıyordum, tesadüfen buraya uğradım.";
			link.l1.go = "exit";
			link.l2 = "Biraz iş konuşmak istedim.";
			link.l2.go = "quests";
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Hapishaneye girmek istiyorum.";
				link.l4.go = "ForGoodMove";		
			}
			NextDiag.TempNode = "First_officer";
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1: 
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2: 
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3: 
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест мэра по поиску шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(7))
	{
		case 0:
			itemID = "indian_5";
		break;
		case 1:
			itemID = "indian_7"; 
		break;
		case 2:
			itemID = "indian_8"; 
		break;
		case 3:
			itemID = "indian_9"; 
		break;
		case 4:
			itemID = "indian_10"; 
		break;
		case 5:
			itemID = "indian_11"; 
		break;
		case 6:
			itemID = "indian_3"; 
		break;
		case 7:
			itemID = "indian_6"; 
		break;
	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade_16");
		break;
		case 1:
			itemID = GetGeneratedItem("blade_15"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_13"); 
		break;
		case 3:
			itemID = "cirass2"; 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_10"); 
		break;
		case 5:
			itemID = "spyglass3"; 
		break;
		case 6:
			itemID = "cirass6"; 
		break;
		case 7:
			itemID = "cirass7"; 
		break;
		case 8:
			itemID = "cirass1"; 
		break;	
		
	}
	return itemID;
}
