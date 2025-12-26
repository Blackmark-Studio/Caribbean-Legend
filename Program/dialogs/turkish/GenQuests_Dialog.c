void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods, iRank, iScl;
	String sTitle, sGroup, sTemp, sText; // belamour 
	float locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bu bir hata. Geliştiricilerle iletişime geçip, bunu nasıl ve nerede bulduğunu bildir.";
					link.l1 = RandSwear()+"Onlara haber vereceğim!";
					link.l1.go = "exit";
					
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // Солдеры по квесту "встреча в бухте"
			{
				dialog.text = "Seninle konuşmaya yetkim yok. Subayımızla konuş.";
					link.l1 = LinkRandPhrase("Elbette...","Anladım.","Elbette!");
					link.l1.go = "exit";
				break;
			}
			
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // Офицер по квесту "встреча в бухте"
			{
				dialog.text = "Kendini tanıt! Kiminle konuştuğumu bilmek istiyorum!";
					link.l1 = "Benim adım "+GetFullName(PChar)+" . Burada neler oluyor?";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}
					
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // Квестовый чел по генеру "meeting in the cove" 
			{
				dialog.text = "Kaptan, senin adın "+GetFullName(PChar)+", değil mi?";
					link.l1 = "Evet, doğru söylüyorsun.";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "Hayır. Beni başka biriyle karıştırdınız.";
					link.l2.go = "exit";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // В комнате таверны после убицства контриков
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name+", çok teşekkür ederim! Sen olmasaydın, halim harap olurdu... Sana nasıl teşekkür edebilirim?";
					link.l1 = "Bir şeye ihtiyacım yok...";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "Küçük bir ödülü reddetmem.";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // Контрик в комнате по квесту "встреча в бухте"
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // Просто платят деньги
				{
					dialog.text = "...Hmm, gerçekten o... Teşekkür ederim, "+GetSexPhrase("ahbap","kız")+"Sensiz başımız gerçekten beladaydı, şehirden çıkmamızın imkânı yoktu. Al, buyur "+FindRussianMoneyString(iMoney)+" ve kaybolabilirsin. Biz de arkadaşımızla bir 'sohbet' edeceğiz...";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "...Hmm, bu gerçekten o... Teşekkürler, "+GetSexPhrase("ahbap","kız")+", senin yardımın olmasaydı işimiz çok zor olurdu, şehirden çıkmamızın imkanı yoktu. Al, buyur "+FindRussianMoneyString(iMoney)+" ve kaybolabilirsin. Bu pis haini şimdi geberteceğiz!";
						link.l1 = "Elbette. Tekrar görüşene dek, beyler...";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "Ne?! Hayır, kim olursa olsun bir adamı öldürmene izin vermem... Ve o kanlı paranı da istemiyorum!";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}
			
			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // Солдер в комнате
			{
				dialog.text = "Demek... Burada ne varmış? Korsanlar mı?! Sorgulanmak üzere bizimle komutanın ofisine gelmeniz gerekecek...";
					link.l1 = "Biz korsan falan değiliz! Bu adamı bile tanımam! Sadece bu odayı kiraladı ve taşındı, ben de eşyalarımı toplayıp çıkmaya fırsat bulamadım!";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}
				
			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "Ne diyordun? Bana bir mesajın mı var?! Bekliyorum!";
					link.l1 = "Al bakalım...";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Hey, sen! Evet, sen. Görüyorum ki saygın ve zengin bir adamsın.";
					link.l1 = "Aynısını senin için söyleyemem.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}
					
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Dur bir dakika! Hey, "+GetSexPhrase("kanka","lass")+", göster bakalım kesenin ne kadar dolu!";
					link.l1 = "Yani, kilisenin bütün parasını çoktan harcadın mı?";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}
			
			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "Hey, teknede! Hık... Yolu açın - adamlarla konuşmam lazım...";
					link.l1 = "Biraz sersemlemiş gibi görünüyorsun, dostum. Git biraz uyu, kendine gelirsin.";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "Hey, Kaptan! Demiri at!";
					link.l1 = "Ve neden lanet olsun ki...";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "Biraz fazla kaba davranmıyor musun!?";
				link.l2.go = "ReasonToFast_Hunter3";	
			}
			
			if(NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = RandPhraseSimple("Selam sana! Sonunda Tanrı dualarımızı işitti ve bu terkedilmiş kıyıya cesur bir kaptan gönderdi!","Tanrı'ya şükür! Artık yerel leşçilerin çürümüş kemiklerimizi kemirmesine gerek kalmayacak!");
				link.l1 = "Merhaba, iyi adam, ben Kaptan "+GetFullName(PChar)+".  Görüyorum ki burada epeyce başın dertte.";
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = "İyi adam, kendi işlerim var ve senin dertlerine ayıracak vaktim yok.";
				link.l2.go = "PiratesOnUninhabited_1";
			}
			
			if(NPChar.id == "ShipWreck_0")
			{
				dialog.text = RandPhraseSimple("Oh, kaptan! Tanrı'nın sana iyi bir rüzgar gönderip seni bu ıssız yere getirmesi gerçekten büyük bir şans!","Kaptan! Bu ıssız kıyıya demir atmaya karar verdiğinize şükürler olsun!");
				link.l1 = "Merhaba, iyi adam, ben Kaptan "+GetFullName(pchar)+". Burada başın gerçekten belada gibi görünüyor.";	
				link.l1.go = "ShipWreck_2";
				link.l2 = "İyi adam, kendi işlerim var ve senin dertlerinle ilgilenecek vaktim yok.";
				link.l2.go = "ShipWreck_1";
			}
			
			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("Bekle, "+GetAddress_Form(pchar)+"! Bize değerli zamanınızdan bir an ayırır mısınız?","Bir soylu kaçırır mıydı"+GetSexPhrase("ter","s")+" bu değersiz adamların alçakgönüllü isteğini dinler misiniz?","Asil hanımefendi"+GetSexPhrase("ter","s")+", lütfen değerli zamanınızdan bir an ayırıp şu zavallıyla konuşun.");
				link.l1 = LinkRandPhrase("Bunun için vaktim yok.","Defol, sensiz de yapacak çok işim var.","Beni rahat bırak, seninle uğraşacak vaktim yok.");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("Ne istiyorsun?","Ne istiyorsun?","Ne oldu, bir sorun mu var?");
				link.l2.go = "Convict_Begin";
			}
			
			// Warship, 15.05.11. Генер "Justice for sale".
			if(HasSubStr(NPChar.id, "JusticeOnSale_Jungle_"))
			{
				dialog.text = "Selam, Kaptan! Sıradan dükkanlarda bulamayacağın Hint süsleri ve mallarıyla ilgilenir misin? Ya da belki nakit parayla?";
					link.l1 = "Sizin gibi serseriler genelde bir şey ister – teklif etmez. Neden bu kadar tuhaf bir şekilde naziksin?";
					link.l1.go = "JusticeOnSale_1";
					link.l2 = "Benim tabancam genellikle senin gibi heriflerle konuşur!";
					link.l2.go = "JusticeOnSale_2";
			}
		break;
		
		// Генератор "Situation in the hold - Ransom"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "Sizi dinliyorum, kaptan. Bir iş için mi geldiniz?";
			link.l1 = "Bay  'i arıyorum "+pchar.GenQuest.Hold_GenQuest.Name+"?";
			link.l1.go = "Hold_GenQuest2";
		break;
		
		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("Ben Bayım "+pchar.GenQuest.Hold_GenQuest.Name+" . Bu onuru kime borçluyum?","Onu bulmuşsun. Senin için ne yapabilirim?");
			link.l1 = "Ben kaptanım "+GetFullName(pchar)+", seninle   hakkında konuşmak istedim "+pchar.GenQuest.Hold_GenQuest.CapName+".";
			link.l1.go = "Hold_GenQuest3";
		break;
		
		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500); 
						
			switch(hrand(3))
			{
				case 0:
					dialog.text = "Ve kimmiş o?";
					link.l1 = "Dur bir dakika... Sen "+pchar.GenQuest.Hold_GenQuest.Name+", ve senin bundan haberin yok "+pchar.GenQuest.Hold_GenQuest.CapName+"?";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "Vay canına! O eski tilkiyle ilgili en son haberleri alalı epey olmuştu. Bu sefer başına ne geldi?";
					link.l1 = "Bu sefer başı gerçekten büyük belada... Esir tutuluyor ve senin yardımına ihtiyacı var.";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "Pekâlâ, seni dinliyorum.";
					link.l1 = "Gemi korsanlar tarafından saldırıya uğramış ve şu anda esir tutuluyor. Fidye konusunda sizinle görüşmemi tavsiye etti.";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "Evet, eski bir dosttan haber almak güzel. Nasıl, iyi mi?";
					link.l1 = "Durumu o kadar vahim ki, hayal etmek bile zor.";
					link.l1.go = "Hold_GenQuest70";
				break;				
			}	
		break;
		
		case "Hold_GenQuest40":
			// dialog.text = "Evet, öyleyim "+pchar.GenQuest.Hold_GenQuest.Name+"! Ama bunun hakkında neden bir şey bileyim ki "+pchar.GenQuest.Hold_GenQuest.CapName+"?!";
			dialog.text = "Evet, doğru, ben "+pchar.GenQuest.Hold_GenQuest.Name+"! Ama isim "+pchar.GenQuest.Hold_GenQuest.CapName+" bana hiçbir şey ifade etmiyor."; // belamour gen
			link.l1 = "Üzgünüm. Belki de yanılmışımdır...";
			link.l1.go = "Hold_GenQuest41";
		break;
		
		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest50":
			dialog.text = "Vay canına! Peki ona nasıl yardım edeceğim? Düşmanlarını öldürüp onu mu kurtaracağım yani? Ha-ha-ha!";
			link.l1 = "Hayır, hayır, bu gerekli değil. Sadece teslim etmen yeterli "+pchar.GenQuest.Hold_GenQuest.RansomSum+" fidye olarak peso.";
			link.l1.go = "Hold_GenQuest51";
		break;		
		
		case "Hold_GenQuest51":
			dialog.text = "Ne cüret! Neden onun için fidye ödeyeyim ki?! Ne akrabam ne de arkadaşım!";
			link.l1 = "Hmm... Bana senin onun tek umudu olduğunu söyledi. Ayrıca ona borcun olduğundan da bahsetti...";
			link.l1.go = "Hold_GenQuest52";
		break;		
		
		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("Ne kadar küstah bir adam! Bilginiz olsun, bana borcu olan o! Ama bu, onu fidyeyle kurtarıp iki borcunu birden ödeyeceğini ummam için bir sebep değil.","Ne alçak adam! İşimizi bölüşürken beni kandırdı, şimdi de kalkmış benden fidye ödememi istiyor!","Bu gerçekten sürpriz oldu! Onun için neden fidye ödeyeyim ki?! O kadar yakın değiliz.");
			link.l1 = "Yani, ona fidyesini ödemeyi reddettiğini ve borcunu kabul etmediğini söyleyebilirim, öyle mi?";	
			link.l1.go = "Hold_GenQuest53";
		break;
		
		case "Hold_GenQuest53":
			dialog.text = "Aman Tanrım! Hangi borçtan bahsediyorsun? Zaten sana her şeyi açıkladım! Eğer bu saçma hikaye dışında başka bir sorunun yoksa, müsaadenle artık gideyim.";
			link.l1 = "Anladım. Sana başka sorum yok, ama o arkadaşına soracaklarım çok.";
			link.l1.go = "Hold_GenQuest54";
		break;
		
		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar)); // НПС вешать собрались? )))
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen				
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest60":
			dialog.text = "Hmm... Ve anladığım kadarıyla, onu elinde tutan sensin... Pekala, sanırım ona yardım edeceğim.";
			link.l1 = "Çok iyi. Fidye miktarı şu olacak "+pchar.GenQuest.Hold_GenQuest.RansomSum+" peso.";
			link.l1.go = "Hold_GenQuest61";
		break;
		
		case "Hold_GenQuest61":
			dialog.text = "Beni yanlış anladınız: Ben şehir meclisinin bir üyesiyim. Biz tüzüğün uygulanmasını sağlarız.\n"+"Gardiyanlar!!! Gardiyanlar! Onu köle ticareti yapmak ve gemilere saldırmak şüphesiyle tutuklayın "+NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation))+"!";
			link.l1 = "Pekâlâ, 'dostum', bırak da sana geleyim...";
			link.l1.go = "Hold_GenQuest62";
		break;
		
		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen	
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");			
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);  
			AddDialogExitQuest("MainHeroFightModeOn"); 
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;
		
		case "Hold_GenQuest70":
			dialog.text = "Ne diyorsun?! Peki, ona nasıl yardım edebilirim?";
			link.l1 = "Onu esir aldılar ve fidyesiyle ilgili sizinle konuşmamı istedi.";
			link.l1.go = "Hold_GenQuest71";
		break;		
		
		case "Hold_GenQuest71":
			dialog.text = "Elbette, elbette. Elimden gelen her şeyi yapacağım. Nerede tutuluyorlar? Ve fidye miktarı ne kadar?";
			link.l1 = " Korsanlar talep ediyor "+pchar.GenQuest.Hold_GenQuest.RansomSum+" peso. Parayı limana teslim etmeliyim, sonra arkadaşın serbest bırakılacak.";
			link.l1.go = "Hold_GenQuest72";
		break;
		
		case "Hold_GenQuest72":
			dialog.text = "İşte para. Neyse ki üzerimde yeterince vardı.";
			link.l1 = "Evet, bu gerçekten şanslı bir durum. O halde limana git, yakında arkadaşını tekrar göreceksin.";
			link.l1.go = "Hold_GenQuest73";
		break;
		
		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sNameChar", GetFullName(NPChar)); // belamour gen 
			AddQuestUserData("HoldQuest", "sName", NPChar.Hold_GenQuest.Name); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;				
		// Генератор "Situation in the hold - Ransom"
		
		// Генератор "Situation in the hold - Partner in crime"
		case "Hold_GenQuest80":
			dialog.text = "Merhaba Kaptan, tanışma şerefine henüz nail olamadım, kusura bakmayın. Sizi beni arıyormuşsunuz dediler.";
			link.l1 = "Gerçekten de, eğer siz Bay "+pchar.GenQuest.Hold_GenQuest.Name+". Ben kaptanım "+GetFullName(pchar)+", seninle konuşmak istedim.";
			link.l1.go = "Hold_GenQuest81";
		break;
		
		case "Hold_GenQuest81":
			dialog.text = "Ne işiymiş bu, Kaptan "+GetFullName(pchar)+"?";
			link.l1 = "Bir şeyin varmış, ondan kolayca vazgeçebileceğin söyleniyor.";
			link.l1.go = "Hold_GenQuest82";
		break;
		
		case "Hold_GenQuest82":
			dialog.text = "Ne demek istiyorsun?";
			link.l1 = "Bu kadar inatçı olma, iyi adamım, gölgeli geçmişini ve hazinenin yerini gösteren o derme çatma haritayı biliyorum"+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_ACC)+" belirtilmiştir.";
			link.l1.go = "Hold_GenQuest83";
		break;
		
		case "Hold_GenQuest83":
			dialog.text = "Kahretsin! O alçağın böyle biri olduğunu hep biliyordum"+pchar.GenQuest.Hold_GenQuest.CapName+" bunu sooner or later ağzından kaçıracaktı! Ona bu teklifi sunarken ne düşünüyordum ki?";
			link.l1 = "Artık sızlanmayı bırak. Sana zarar vermeye niyetim yok... Sadece şu haritayı bana sat ve alışık olduğun hayatına devam et.";
			link.l1.go = "Hold_GenQuest84";
		break;
		
		case "Hold_GenQuest84":
			dialog.text = "Keşke ben de bu kadar emin olabilsem... Peki, bunun için bana ne kadar teklif edeceksin? Sandıkta çok altın olduğunu elbette biliyorsundur. Dört adam taşıdı onu, Allah rahmet eylesin...";
			link.l1 = "Ama "+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_NOM)+" hazinesini çoktan almış olabilirdi...";
			link.l1.go = "Hold_GenQuest85";
		break;
		
		case "Hold_GenQuest85":
			dialog.text = "Doğru... Peki, sana bunu satmaya razıyım, fiyatı "+pchar.GenQuest.Hold_GenQuest.Sum+" peso. Zaten ölüleri rahatsız etmeye cesaret edemem.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "Pekâlâ. Anlaştık.";
				link.l1.go = "Hold_GenQuest86";
			}	
			link.l2 = "Hayır, iyi adamım, o kağıt parçası bu paraya değmez. Hoşça kal...";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;
		
		case "Hold_GenQuest86":		
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest"); 
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);						
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;	
		
		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_GEN)); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);			
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// Генератор "Situation in the hold - Partner in crime"
		
		// Генератор "Shipwrecked"
		case "ShipWreck_1":
			dialog.text = "Bu nasıl mümkün olabilir, kaptan?! Tanrı böyle bir günahı asla affetmez.";
			link.l1 = "Karar O'na kalmış.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
		
		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType(); 		
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));			
			
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Merhaba, ben "+pchar.GenQuest.ShipWreck.Name+",   gemisinin kaptanı "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Acc"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+", gemim kıyıdan çok uzakta olmayan kayalıklarda parçalandı."+"Tüm tayfadan sadece birkaç denizci hayatta kalabildi. Gelgit bizi bu ıssız kıyıya sürükledi. Günlerce aç ve susuz kaldık "+(5+hrand(7))+" haftalardır şimdiye kadar","Merhaba, ben "+pchar.GenQuest.ShipWreck.Name+",   gemisinin kaptanı "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+". Gemimiz buradan çok uzakta değil, karaya oturdu."+"Gemiden sağ kurtulduktan sonra bu kıyıya ulaşmayı başardık, ama burası terkedilmiş görünüyor. Hayatta kalmak için midye ve palmiye meyveleriyle idare etmek zorunda kaldık "+(5+hrand(7))+" haftalardır böyle.");
				link.l1 = RandPhraseSimple("Peki, kaç kişi kaldınız?","Peki, aranızdan kaçı hayatta kalabildi?");
				link.l1.go = "ShipWreck_3";
			}
			else
			{						
				pchar.GenQuest.ShipWreck.Mutiny = "true"; // belamour gen кавычки
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = "Ah kaptan, kayıplarımız gerçekten çok ağır... Merhaba, ben "+pchar.GenQuest.ShipWreck.Name+",   kaptan ve sahibi "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+". Ya da, eski kaptan ve sahibi mi demeliyim. "+"Bu herif "+pchar.GenQuest.ShipWreck.BadName+"  kimi tuttum  "+XI_ConvertString("Colony"+pchar.GenQuest.ShipWreck.City+"Voc")+" mürettebatımı isyana kışkırttı. Sonunda, bu Allah'ın unuttuğu yerde bırakıldık. Olan buydu "+(5+hrand(7))+" hafta önce.";
				link.l1 = "Ve sonra ne oldu? Tüm tayfan isyancılara mı katıldı?";
				link.l1.go = "ShipWreck_4";			
			}
		break;
		
		case "ShipWreck_3":
			dialog.text = RandPhraseSimple("Tüm mürettebattan sadece "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" survived. Other's have perished; several of them died already here of wounds and fever",
				"Only " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " were lucky enough. Others have met their end... either in the deep or in the dunes of this coast.");
			link.l1 = LinkRandPhrase("Evet, bu hiç de imrenilecek bir kader değil. Ama denizcinin payı bu - herkes senin yerinde olabilir.","Anladım... Tanrı her canı elinde tutar, ama herkesin kim olduğunu hatırlayacak kadar vakti yoktur.","Gerçekten öyle. İnsan plan yapar, ama takdir Allah’ındır.");
			link.l1.go = "ShipWreck_5";	
		break;
		
		case "ShipWreck_4":
			dialog.text = "Elbette hayır! Birçoğumuz isyancılara katılmayı reddettik, ama o alçaklar cephaneliği ele geçirdi, ve iyi ki de karşı koymadık, yoksa anında öldürülürdük. Burada zaten pek çoğu ateş ve zehirli böceklerin zehrinden can verdi, sadece "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" hayatta kaldık. Tanrı'ya şükür, sonunda çilemiz bitti.";
			link.l1 = RandPhraseSimple("Evet, bu gerçekten de kötü bir şanstı.","Eh, bu Tanrı'nın unuttuğu yerlerde her türlü garip şey olabilir.");
			link.l1.go = "ShipWreck_5";			
			link.l2 = "Dur hele, dostum. Peki, isyanı başlatanlardan biri olarak karaya çıkarılmadığını nereden bileceğim?";
			link.l2.go = "ShipWreck_6";			
		break;
		
		case "ShipWreck_5":
			dialog.text = RandPhraseSimple("Kaptan, umarım geminizde birkaç boş dolap vardır. Hepimizin aileleri var ve biz burada konuşurken muhtemelen yas tutuyorlar. Size çok minnettar oluruz.","Kaptan, tamamen çaresiziz, tek umudumuz sensin. Lütfen bize yardımını esirgeme, bizi bu lanet topraklardan götür.");
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = "Ah... peki, seni nereye götürmemi istersin?";
				link.l1.go = "ShipWreck_7";			
			}
			link.l2 = RandPhraseSimple(RandPhraseSimple("I am truly sorry, but there isn't a single free hammock, let alone a cabin. The sailors are sleeping on the deck; they can't even get a decent night's rest after their watch...","I would really hate to disappoint you, but the ship is overloaded, and people have to sleep in bad weather. Should there be an outbreak of disease, I will lose half the crew."),RandPhraseSimple("I am truly sorry, but there is absolutely no spare crew space on my ship. I cannot take any more passengers on board.","I'm afraid I must disappoint you, but my ship is overloaded. I fear an epidemic."));
			link.l2.go = "ShipWreck_8";	
			if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Sen deneyimli bir denizcisin ve bir gemi kazasından sağ çıkan birinin varlığının çok kötü bir alamet olduğunu bilmelisin. Benim tayfam sizi hemen denize atar.";
				link.l3.go = "ShipWreck_9";
			}
		break;
		
		case "ShipWreck_6":
			dialog.text = "Ne diyorsun, "+GetAddress_Form(npchar)+" "+pchar.lastname+"?! Biraz insaf et! Ben Karayipler'de tanınmış bir tüccarım! Yani... Eskiden öyleydim. Şimdi değil, ne gemim var ne de param...";
			link.l1 = "Nasıl yani... Bahse girerim isyanın asıl kışkırtıcıları sizdiniz ve şimdi hak ettiğinizi buldunuz.";
			link.l1.go = "ShipWreck_18";
			if(GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Ama ne alçak biri bu "+pchar.GenQuest.ShipWreck.BadName+"! Gerçekten de onun bu yaptıklarına göz yumup kaderine boyun mu eğeceksin?";
				link.l2.go = "ShipWreck_19";
			}	
		break;		
		
		case "ShipWreck_7":
			if(rand(1) == 0)
			{
				if(rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = "Herhangi bir yerleşime "+NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation))+".";
					link.l1 = "Pekâlâ, yeterince boş ranza ve hamak var. Hadi, sandala geç.";
					link.l1.go = "ShipWreck_10";
					link.l2 = "Hmm... Önümüzde çetin savaşlar var, ve senin daha güvende olacağın yerin gemim mi yoksa bu sakin koy mu olacağını bilmiyorum.";
					link.l2.go = "ShipWreck_11";
				}
				else
				{				
					dialog.text = "Dunkirk'e! Annem orada yaşıyor...";
					link.l1 = "Sen deli misin, ne?! Sanırım kafana fazla darbe aldın...";
					link.l1.go = "ShipWreck_12";					
					pchar.GenQuest.ShipWreck.Crazy = true; // получите психа на борт :-)
					
				}				
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = "Nereye istersen, bize fark etmez. Zaten sana ödeyecek hiçbir şeyimiz yok...";
				link.l1 = "Pekâlâ, yeterince boş dolabım ve hamaklarım var. Hadi, kayığa bin.";
				link.l1.go = "ShipWreck_10_1";
				link.l2 = "Hmm... Önümüzde çetin savaşlar var, ve senin için daha güvenli yer neresi olur, gemimde mi yoksa bu sakin koyda mı, bilmiyorum.";
				link.l2.go = "ShipWreck_11";		
			}						
		break;		

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = "Ama reddederseniz, kesinlikle bizi ölüme mahkûm edeceksiniz! Peki, o zaman, hayatımıza mal olsa bile gemiye ulaşmak için savaşmayı deneyeceğiz!";
					link.l1 = "Ne? Kendinize bakın, ayakta zor duruyorsunuz...";
					link.l1.go = "ShipWreck_8_1";
					link.l2 = "Deneyebilirsin...";
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = "Ama bizi burada bırakamazsınız! Yardımınız olmadan hepimiz yakında öleceğiz!";
					if(GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{			
						link.l1 = "Sana yapabileceğim tek şey, sana yeterli erzak ve ilaç bırakmak ve bir sandal vermek. En azından açlıktan ya da susuzluktan ölmeyeceksin. Denizcilik konusunda ise sana bir şey öğretmeme gerek yok.";
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if(rand(1) == 0)
						{
							link.l1 = "Sana yapabileceğim tek şey, sana yeterli erzak ve ilaç bırakıp bir kayık vermek. En azından açlıktan ya da susuzluktan ölmezsin. Denizciliğe gelince, onu sana öğretmeme gerek yok.";
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = "Sana bir ay yetecek kadar ilaç, cephane, rom ve erzak bırakabilirim. Ya kendim dönerim ya da seni almak için birini yollarım.";
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL) // плохиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						dialog.text = "Ama reddederseniz, kesinlikle bizi ölüme mahkûm edeceksiniz! Peki, o zaman canımız pahasına da olsa gemiye ulaşmak için savaşmayı deneyeceğiz!";
						link.l1 = "Ne? Kendinize bakın, ayakta zor duruyorsunuz...";
						link.l1.go = "ShipWreck_8_1";
						link.l2 = "Deneyebilirsin...";
						link.l2.go = "ShipWreck_16";					
					}
					else
					{
						link.l1 = "The only thing I can do for you is leave you enough provisions and medicines and give you a boat. At least you are not going to die of starvation and thirst; as for seafaring, I need not teach you that.";
						link.l1.go = "ShipWreck_8_2";					
					}
				}
				else // кибальчиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						if(rand(1) == 0)
						{
							dialog.text = "Ama eğer reddederseniz, bizi kesinlikle ölüme mahkûm etmiş olacaksınız! Peki, o zaman hayatımıza mal olsa bile gemiye ulaşmak için savaşmayı deneyeceğiz!";
							link.l1 = "Ne? Kendinize bakın, ayakta zor duruyorsunuz...";
							link.l1.go = "ShipWreck_8_1";
							link.l2 = "Deneyebilirsin...";
							link.l2.go = "ShipWreck_16";						
						}
						else
						{
							dialog.text = "Bunu bize nasıl yapabildin?!.. Sadece Deniz Yasası'nı hiçe saymadın, onurunla da oynadın!";
							link.l1 = "Onurumdan bahsedecek son kişi sensin, cüce!";
							link.l1.go = "ShipWreck_16";
						}	
					}
					else
					{
						link.l1 = "Sana yapabileceğim tek şey, sana yeterli erzak ve ilaç bırakıp bir kayık vermek. En azından açlıktan ya da susuzluktan ölmeyeceksin. Denizciliğe gelince, onu sana öğretmeme gerek yok.";
						link.l1.go = "ShipWreck_8_2";											
					}						
				}
			}			
		break;				
	
		case "ShipWreck_8_1":
			dialog.text = "Haklısın, hiç şansımız yok. Peki, Allah seni yargılasın, herkes de hak ettiğini bulsun.";
			link.l1 = "Pekâlâ, bununla başa çıkabilirim...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
	
		case "ShipWreck_8_2":
			dialog.text = "Pekâlâ... Bize başka seçenek bırakmadın... Yağmurlar ve susuzluk, yerleşim yerlerine varmadan canımızı almasın diye dua edeceğiz...";
			link.l1 = "Elveda. Tanrı seni korusun...";
			link.l1.go = "ShipWreck_8_3";
		break;
		
		case "ShipWreck_8_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;			
		break;
	
		case "ShipWreck_8_4":	
			dialog.text = "Görünüşe bakılırsa başka seçeneğimiz yok... Ama yalvarırım Kaptan, lütfen mümkün olan en kısa sürede geri dön ya da bize bir keşif gemisi gönder.";
			link.l1 = "Bir şeyler düşüneceğim. Sadece bekle.";
			link.l1.go = "ShipWreck_8_5";
		break;
	
		case "ShipWreck_8_5":		
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50); 
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");		
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.AmunitionQty + " units of arms.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.RumQty + " units of rum");	
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);			
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;
	
		case "ShipWreck_8_6":			
			dialog.text = RandPhraseSimple("Kaptan, lütfen unutmayın, bizim tek umudumuz sizsiniz...","Neden oyalanıyorsun? Burada geçirilen her dakika bizim için dayanılmaz...");
			link.l1 = "Elimden gelen her şeyi yapacağım. Elveda...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";		
		break;

		case "ShipWreck_8_7":			
			dialog.text = RandPhraseSimple("Elveda, kaptan... Yolculuk için hazırlanmamız gerek.","Elveda... Ve ruhlarımızı kurtarmak için mumları yakın...");
			link.l1 = "Elveda. Tanrı seni korusun...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";		
		break;
		
		case "ShipWreck_9":
			pchar.GenQuest.ShipWreck = "SailorsOnShoreFight"; // belamour gen
			dialog.text = "Bunu bize nasıl yapabildin?! Sadece Deniz Yasası'nı hiçe saymadın, aynı zamanda onurunu da lekeledin!";
			link.l1 = "Onurumdan bahsedecek kişi sen değilsin, cüce!";
			link.l1.go = "ShipWreck_16";
		break;					
		
		case "ShipWreck_10":
			dialog.text = "Teşekkürler, kaptan! Yükleme fazla uzun sürmez. Tanrım, bu anın gelmesi için ne çok dua ettik!";
			link.l1 = "Harika. Umarım sıkıntıların yakında sona erer.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}
			
		break;							

		case "ShipWreck_10_1":
			dialog.text = "Teşekkürler, kaptan! Yükleme fazla uzun sürmez. Tanrım, bu anın gelmesi için ne dualar ettik!";
			link.l1 = "Harika. Umarım sıkıntıların yakında sona erer.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}			
		break;							
				
		case "ShipWreck_11":
			dialog.text = "Hadi ama! Gerçekten mi, kaptan?! Ölümden mi korkuyoruz?! Bir kez kandırdık, yine yaparız. Sadece böyle ölüp gitmek istemiyoruz. Burada, yalnız başımıza çürümek...\nSenin tayfana katılıp bayrağın altında cesurca savaşırız. Yeter ki bizi burada bırakma...";
			link.l1 = "Buradan çıkmak için her şeyi yapmaya hazırsınız, görüyorum. Ama kendinize bir bakın, sizden nasıl denizci olacak ki?";
			link.l1.go = "ShipWreck_14";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = "Bu iyi bir fikir. Sanırım seni işe alabilirim.";
				link.l2.go = "ShipWreck_15";
			}	
		break;									
		
		case "ShipWreck_12":
			dialog.text = "Hayır, hayır, şaka yapmıyorum! Lütfen, beni bu Karayip mezbahasından... bu cehennemden çıkar! Bak, ben zengin bir adamım... hem de çok zengin. Papa bile hayatı boyunca bu kadar altın görmemiştir. Seni altına boğacağım...";
			link.l1 = "Aman Tanrım... Peki, hadi sandala bin...";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
			// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины
			if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			// <-- belamour
		break;							

		case "ShipWreck_13": // берем пассажирами
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			//Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.variant"))
			{
				if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
				if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			}	
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;
		
		case "ShipWreck_13_again":
			dialog.text = LinkRandPhrase("Neden oyalanıyorsun, kaptan? Demir almamız için emir ver.","Üzgünüz kaptan, ama yelken açmaya hazırlanmalıyız.","Buraya gelmeye karar verdiğin için çok şanslıyız!");
			link.l1 = "Acele et. Gemi kimseyi beklemez.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";		
		break;
		
		case "ShipWreck_14":
			dialog.text = "Kaptan, kaybedecek hiçbir şeyimiz yok. Ölüm zaten peşimizde... Pis çakallara yem olmaktansa, adil bir dövüşte ölmeyi tercih ederiz...";
			link.l1 = "Ha, bu bir meydan okuma mı yani?! Peki, o zaman aramızdaki meseleyi çözelim"+GetSexPhrase(", adamlar gibi","")+"!";
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;		
		
		case "ShipWreck_15":
			dialog.text = "Yemin ederim, kaptan, buna pişman olmayacaksınız. Tüm takımadadaki en iyi denizciler biz olacağız.";
			link.l1 = "Harika! Sandala bin...";
			link.l1.go = "ShipWreck_17";			
		break;				
		
		case "ShipWreck_16":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetImmortal(rChar, false);
				if(CheckPassengerInCharacter(pchar, "ShipWreck_" + i)) 
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if(pchar.GenQuest.ShipWreck == "fight" || pchar.GenQuest.ShipWreck == "SailorsOnShoreFight") // belamour gen
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors"); 
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}	
			DialogExit();		
		break;
		
		case "ShipWreck_17": // принимаем в команду
			if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
			if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;			
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			// --> belamour gen по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5) sText = "";	
			else sText = "";
			Log_Info("Your team has increased by " + pchar.GenQuest.ShipWreck.Qty + " man" + sText + ".");
			// <-- belamour gen 
			Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			pchar.quest.ShipWreck_LocExit.over = "yes"; // Снимаем прерывание на выход из локации			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");			
			AddCharacterExpToSkill(pchar, "Leadership", 50); 			
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = LinkRandPhrase("Yemin ederim, kaptan, pişman olmayacaksınız.","Doğru kararı verdiniz, kaptan.","Kaptan, emin olun ki siz de bizim kadar şanslıydınız!");
			link.l1 = RandPhraseSimple("Umarım öyle olur.","Acele et. Gemi kimseyi beklemez.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;
		
		case "ShipWreck_18":
			dialog.text = "Kaptan, neden dürüst insanlara böyle bir güvensizlikle hakaret edesiniz ki? Yüzlerine bir bakın, gerçekten isyancı olabileceklerini mi düşünüyorsunuz?";
			link.l1 = "Peki, şimdi seninle ne yapmam gerekiyor?";
			link.l1.go = "ShipWreck_20";
		break;
		
		case "ShipWreck_19":
			dialog.text = "Ve ben ne yapabilirim? En azından şimdi hayattayım... ve Tanrı'ya buradan sağ çıktığım için şükrediyorum! Ama eğer bana gemimi geri almamda ve yaşadığım aşağılanmanın intikamını almamda yardım edersen, bu alçağın çalıp ambarına sakladığı her şeyi sana vermeye hazırım.";
			link.l1 = "Pekâlâ, anlaştık.";
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			SetFunctionTimerCondition("prosralisrok", 0, 0, 180, false); // таймер лесник тамймер на поиск корабля 																																   
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			// --> belamour окончание по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailors");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailor");
			}
			// <-- belamour
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;
		
		case "ShipWreck_20":
			dialog.text = "Bizim emir verme hakkımız yok. Karar senin, bizi herhangi bir yerleşime götür ya da tayfana kabul et.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = "Pekala, seni tayfama alacağım. Ama sakın numara yapma! Gemimde disiplin şarttır!";
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = "Seni hiçbir yere götürmüyorum. Mürettebatımda zaten yeterince haydut var.";	
			link.l2.go = "ShipWreck_22";
			link.l3 = "Pekala, sandala bin, seni bir yere götüreceğim.";
			link.l3.go = "ShipWreck_10_1";
		break;		
		
		case "ShipWreck_22":
			dialog.text = "Pekala... Bize başka seçenek bırakmadınız... Yüce Kudret’in bize merhamet göstermesi ve bu tehlikeli yerden kurtulmamız için dua edeceğiz. Tanrı isterse, belki de yerleşim olan bir yere ulaşabiliriz...";
			link.l1 = "Elveda. Tanrı seni korusun...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;		
		
		case "ShipWreck_30":
			if(pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = "Çok teşekkür ederim, Kaptan "+GetFullName(pchar)+"! Bizim için o kadar çok şey yaptın ki, sana ne kadar teşekkür etsek az. Gerçi tüm eşyalarımız bir bakır etmez ama, sana bu tılsımı sunmama izin ver. Deniz savaşlarına sıkça giren bir kaptan için çok faydalı olacaktır.";
				link.l1 = "Hediyeniz için teşekkürler! Bu küçük eşya gerçekten çok işe yarayacak! Hoşça kalın, kaptan "+pchar.GenQuest.ShipWreck.Name+" ve yolculuklarında sana bol şans.";
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = "Kaptan, size çok teşekkür ederiz. Bizim için öyle çok şey yaptınız ki, verebileceğimiz hiçbir ödül minnettarlığımızın yanında önemsiz kalır. Lütfen, takdirimizin bir göstergesi olarak bu mütevazı hediyemizi kabul edin.";
				link.l1 = "Gerçekten, zahmet etmeseydin... Senin paraya benden çok daha fazla ihtiyacın var. Yine de, çok naziksin. Teşekkür ederim ve hoşça kal.";
				link.l1.go = "ShipWreck_31";
			}	
		break;
		
		case "ShipWreck_31":
			//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15+hrand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony"+ Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_32":	
			dialog.text = "Captain, know that there are people who would go to the ends of the earth for you, from now on. It's a pity I have nothing with which to thank you. Still... Please, accept this trinket; I found it in that ill-fated cove. I hope it will bring you luck.";
			link.l1 = "Benim yerimde kim olsa aynısını yapardı. Hoşça kal.";
			link.l1.go = "ShipWreck_33";
		break;
		
		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + Locations[FindLocation(PChar.location)].townsack + "Acc")); // belamour gen: просто pchar.location ничего не даст
			CloseQuestHeader("ShipWrecked");		
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_34":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Kaptan, Dunkirk'e çoktan mı vardık?","Gerçekten Dunkirk'ta mıyız, kaptan?"),RandPhraseSimple("Kaptan, burası Avrupa mı?","Avrupa'ya bu kadar hızlı mı geldik?"));
			bTemp = !GetCharacterItem(pchar, "map_full") && !GetCharacterItem(pchar, "map_part2");
			bTemp = !GetCharacterItem(pchar, "map_part1") || bTemp;
			if(rand(100) > 75 && !isDay() && bTemp)
			{
				link.l1 = "A-ha...";
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = LinkRandPhrase("Henüz değil...","Ne Dunkirk'i? Ne Avrupa'sı? Etrafına bak!","Aman Tanrım!");
				link.l1.go = "ShipWreck_35";
			}
		break;
		
		case "ShipWreck_35":
			dialog.text = LinkRandPhrase("Ama kaptan, bir söz vermiştiniz!","Sözünü nasıl tutmazsın, kaptan?"," Peki, Avrupa'ya ne zaman gidiyoruz? ");
			if(rand(100) < 70)
			{
				link.l1 = "Pekâlâ. Bayım, adamlarınızı ve eşyalarınızı toplayın, nereye gitmek isterseniz gidin.";
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = RandPhraseSimple(LinkRandPhrase("Dunkirk'e gerçekten gitmemiz gerektiğinden emin misin?","Biliyor musun, gemim okyanusu aşmak için yapılmadı.","Kaptan, peki Karayipler'in nesi var?"),LinkRandPhrase("Ama benim başka planlarım vardı...","Öncelikle neden Avrupa'ya gitmek istiyorsun...","Şu baştan çıkarıcı melez kadınları bir düşün! Onları Avrupa’da asla göremezsin..."));
			link.l2.go = "ShipWreck_37";	
		break;
		
		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = "Ama nasıl?.. Nasıl cüret edersin?! Bu ne biçim bir hainlik?! Sana sözünde durmayı öğreteceğim!";
			link.l1 = "Pekâlâ, bunu sen istedin...";
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		case "ShipWreck_37":
			dialog.text = LinkRandPhrase(RandPhraseSimple("Hayır! Dunkirk'e gitmem gerekiyor!","Bana coğrafya öğretmek yerine, asıl yapman gerekeni yapmalısın!"),RandPhraseSimple("Bununla ilgili hiçbir şey duymak istemiyorum! Beni Avrupa'ya götüreceğine söz vermiştin!","Hayır, kaptan, bu olmaz. Avrupa'ya yelken açıyoruz."),"Hayatımın geri kalanını bu delikte sefil bir şekilde geçirmeye hiç niyetim yok!");
			link.l1 = "Ah, bunun nasıl biteceğini hiç bilmiyorum...";
			link.l1.go = "ShipWreck_38";
		break;		
		
		case "ShipWreck_38":
			chrDisableReloadToLocation = false;			
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
			if(!CheckAttribute(pchar,"GenQuest.ShipWreck.CrazyRec")) // mitrokosta исправлена блокировка поручения капитана
			{
				pchar.GenQuest.ShipWreck.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;
		
		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			dialog.text = "Bak! İşte bu düzgün bir adam! Avrupa! Lanet olası eski Avrupa! Evet-evet-evet!\nAh, evet! Sen anlaşmanın kendi kısmını yerine getirdin, ben de öyle yapacağım. Al, haritanın bu yarısını al. Diğer yarısı ortağımdaydı. Huzur içinde yatsın mı, suda mı yatsın? Ne fark eder. Bu maceraya katılmam için beni ikna eden oydu.";
			link.l1 = "Dur bir dakika, yani sen denizci değilsin? Arkadaşın kaptan mıydı?";
			link.l1.go = "ShipWreck_41";
		break;
		
		case "ShipWreck_41":
			dialog.text = "Aman Tanrım!.. Tabii ki hayır! Yani, evet, ben denizci değilim. O, kıyıdan uzaklaşmaya karar verdiğinde dev bir dalga tarafından denize sürüklendi. Sonra komutayı ben devraldım ve koya doğru yelken açmamızı emrettim... Kayalıkların arasından geçerken de gayet iyi ilerliyorduk, ta ki her şeyi trajik bir kaza belirleyene kadar. Gemi bir kaya parçasına çarpıp battı...";
			link.l1 = "Şimdi bu tam bir beceriksizlik örneği...";
			link.l1.go = "ShipWreck_42";
		break;
		
		case "ShipWreck_42":
			dialog.text = "Dinle, burası gerçekten Dunkirk mi? Bir düşün, sadece altı ay geçti ve her şey tamamen değişmiş\nAl, haritayı ya da daha doğrusu bir parçasını al. Hazine bir mağaranın içinde! Hangi adada olduğu hakkında hiçbir fikrim yok, ama sen deneyimli bir denizcisin, bir gün tam yerini bulursun... Sana garanti ediyorum, aaarrrrrhg adındaki korsana ait sayısız hazine var...";
			link.l1 = "Teşekkür ederim, iyi adamım. Hiç hazine çıkmasa bile, çok da üzülmem. Elveda, umarım bir daha asla karşılaşmayız...";
			link.l1.go = "ShipWreck_43";
		break;
		
		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddMapPart();
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");	
			AddSimpleRumourCity(LinkRandPhrase(RandPhraseSimple("They say some loony recently showed up on the island. He is telling everyone that he had lost his documents, and no he's attempting to apply for a captain on a ship to Dunkirk.",
				"They say some maniac recently showed up on the island. He stole a spade at the local shop and now is digging a pit past the town gates..."),
				RandPhraseSimple("Just imagine, recently some visiting European in worn and dirty clothes attempted to get an audience with the governor! He claimed that he needed to see the governor of Dunkirk ass soon as possible.",
				"There was a scandal at the town hall recently. Some vagrant was caught, he claimed that he personally knew the governor of Dunkirk."),
				"Some psycho was looking for you recently. He claimed that you owed him money..."), pchar.location, 5, 3,"");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_44":
			dialog.text = RandPhraseSimple("Kaptan, bizi unutmadığınız harika! Hepimiz sizin için dua ediyorduk!","Kaptan, kurtuluşumuz yakın mı? Bunun gelmesi için ne çok dua ettik! Bazı insanlar artık umudunu kaybetmeye başladı...");
			link.l1 = "Selamlar, "+pchar.GenQuest.ShipWreck.Name+"! Meslektaşlarımı böyle bir durumda nasıl bırakabilirim? Nereye?";
			link.l1.go = "ShipWreck_45";
			link.l2 = "Selamlar, "+pchar.GenQuest.ShipWreck.Name+"! Korkarım sana kötü bir haberim var. Planlarda bir değişiklik oldu ve seni gemiye alamayacağım.";
			link.l2.go = "ShipWreck_9";
		break;
		
		case "ShipWreck_45":
			dialog.text = "Biz nereye gideceğimizle ilgilenmiyoruz, yeter ki bu lanetli yerden yeterince uzak olsun... Kendi eşyalarımızı yüklemeye başlamamıza izin verir misiniz?";
			link.l1 = "Evet, devam et. Yakında sınavların sona erecek.";
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterComplexReputation(pchar,"nobility", 4);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}			
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen снять таймер на 30 дней	 
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
			DialogExit();			
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian_10");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");				
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_48":
			dialog.text = "Teşekkür ederiz, kaptan. Umudumuzu yitirmeye başlamıştık ama gerçekten bizi hayata döndürdünüz.";
			link.l1 = "Önemli değildi... Hoşça kal.";
			link.l1.go = "ShipWreck_49";
		break;
		
		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");								
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_50":
			dialog.text = "Benden ne istiyorsun, lanet olsun?";
			link.l1 = "Geldim"+GetSexPhrase("","")+" sana birinden selam getirmemi istedi, adı "+pchar.GenQuest.ShipWreck.Name+" . Onu tanıyor musun?"; // belamour gen
			link.l1.go = "ShipWreck_51";
		break;
		
		case "ShipWreck_51":
			dialog.text = "Keşke o alçağı daha önce boğsaydım. Neyse, demek ki iyiliğimin bedelini ödeme vakti geldi...";
			link.l1 = "Gerçekten de... Ve zaman şimdi doldu...";
			link.l1.go = "ShipWreck_52";
		break;
		
		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = "Harika iş çıkardın, kaptan! Her şey anlaştığımız gibi, değil mi? Biz gemiyi alıyoruz, sen de yükü?";
			link.l1 = "Tabii. Gemiyi al ve iyi kullan.";
			link.l1.go = "exit";

			NextDiag.TempNode = "ShipWreck_53_again";		
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;
		
		case "ShipWreck_53_again":
			dialog.text = "Sizi selamlıyorum, Kaptan "+GetFullName(pchar)+".";
			link.l1 = "Peki, gemini nasıl buluyorsun?";
			link.l1.go = "ShipWreck_53_again1";
		break;
		
		case "ShipWreck_53_again1":
			dialog.text = "Heh, gıcırdıyor ve inliyor, tıpkı benim gibi. Sanırım ikimizin de açık denizlerde fazla zamanı kalmadı...";
			link.l1 = "Öyleyse bol şans...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
		break;
		// Генератор "Shipwrecked"
		
		// Генератор "State convicts"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;
		
		case "Convict_Begin":					
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "Kaptan, lütfen bize bir gemi ya da bir sandal, bir tartan, ne bulabilirseniz ayarlayın, gerçekten hiç fark etmez. Öyle zor durumdayız ki, bu düşmanca yerden kaçmak zorundayız, ama yerleşkeye gidemeyiz.";
					link.l1 = "Peki, bu nasıl bir durumdan bahsediyorsun?";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "Kaptan, bize birkaç yüz peso ödünç verir misiniz? Normalde istemezdik ama gerçekten çok zor durumdayız.";
					link.l1 = "Zorda mısın diyorsun? Bahse girerim sadece romun bitmiştir, bu da gerçekten zor bir durum olsa gerek.";
					link.l1.go = "Convict_12";			
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));	
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "Kaptan, mütevazı grubumuzu deniz fenerine götürme nezaketini gösterebilir misiniz? "+XI_ConvertString("Colony"+pchar.GenQuest.Convict.ToCity+"Gen")+".";
					link.l1 = "Sana bakınca pek alçakgönüllü olduğunu söyleyemem.";
					link.l1.go = "Convict_13";								
				break;
			}						
			link.l2 = LinkRandPhrase("Cuma günleri sadaka vermem.","Bu saçmalıkla uğraşacak vaktim yok.","Yabancılara yardım etmem.");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;
		
		case "Convict_11":
			dialog.text = "Biz kaçaklarız...  "+GetStrSmallRegister(XI_ConvertString("MineType"+pchar.GenQuest.Convict.MineType+"Gen"))+". Yakında eski efendi fark edecek... ve o zaman kesinlikle öleceğiz.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "Yelkenleri nasıl idare edeceğini biliyor musun?";
				link.l1.go = "Convict_11_1";
			}	
			link.l2 = "Peki, neyle ödeyeceksin?";
			link.l2.go = "Convict_11_2";
		break;
		
		case "Convict_12":
			dialog.text = "Şu anda rom düşünmenin zamanı değil. Kaçalı bir hafta oldu, şimdi ormanda saklanıyoruz ve açlıktan kıvranıyoruz.";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "Peki, diyelim ki sana para verdim... sonra ne olacak? Bir devriye seni eninde sonunda bulana kadar saklanmaya mı devam edeceksin?";
				link.l1.go = "Convict_12_1";		
				link.l2 = "Peki, ne kadarına ihtiyacın var?";
				link.l2.go = "Convict_12_2";
			}	
			link.l3 = "Senin gibilerle konuşacak pek bir şeyim yok—celladın kütüğünde kafa, hepsi bu!";
			link.l3.go = "Convict_12_3";
		break;		
		
		case "Convict_12_1":
			if(hrand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "Başka ne yapabiliriz ki? Memnuniyetle denizci olarak çalışırdık, ama kaçak olduğumuz düşünülürse, bizi kim işe alır?";
				link.l1 = "Eğer yelkenleri idare etmeyi biliyorsan ve korkaklık belirtisi göstermiyorsan seni işe alırım.";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "Buradaki denizcilerle zaten anlaştık. Buradan çıkmak için sadece üç bin eksiğimiz var.";
				link.l1 = "Al bakalım, işte üç binin. Gerçekten işine yarayacaksa tabii.";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "Eh, bilmiyorum... Bunlar senin kendi sorunların, ve ben onları çözmene yardım etmeyeceğim.";
			link.l2.go = "Convict_12_1_End"; // выход из локи с закрытием квеста
		break;
		
		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Lütfen, kaptan, bizi işe alın, emin olun pişman olmazsınız! Uzun zamandır korsanlık yapıyoruz "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" Adriyatik'te, sonunda asılana kadar ve biz, "+pchar.GenQuest.Convict.ConvictQty+" adamlar buraya sürüldü.";
			link.l1 = "Pekala. Yakınlarda bir yer var, adı "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+". Gece yarısına doğru seni oradan alacağım. Umarım kaybolmazsın.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";		
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTmp = hrand(3);
			if(iTmp <= 1)
			{
				dialog.text = "Elbette, bu bize çok yardımcı olacak! Eğer rüzgar uygun olursa ve balıkçılar bizi yarı yolda bırakmazsa bugün denize açılacağız. Teşekkürler kaptan, Tanrı yardımcınız olsun...";
				link.l1 = "Sana da bol şans.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "Bu gerçekten büyük bir şans! Parayı bu kadar çabuk alacağımızı hiç ummazdık. Kaptan, eski patronumuzdan aldığımız küçük bir hatırayı size sunmama izin verin. Belki size de uğur getirir.";
				link.l1 = "Teşekkür ederim, bu gerçekten düzgün bir davranış. Sana bol şans.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "İşte, parasını harcamaktan korkmayan, çünkü onu nasıl kazanacağını bilen cömert bir adam var!\nDün gece yerel kaçakçıların yükleme yaptığını gördük "+MerPrm.QuestGoodsIdx+".  Karanlıktı, ama teknelerden birinin yanında geminin adını seçebildik, '"+MerPrm.ShipName+"'... ve o gemi şu bayrak altında yol alıyor: "+MerPrm.nation+"Belki bu bilgi işine yarar, he-he.";			
				link.l1 = "Hmm... Pekala, belki de öyle yaparım. Size de elveda, iz sürücüler.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");			
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;
		
		case "Convict_12_2":
			dialog.text = "Aman Tanrım, isteklerde bulunacak durumda değiliz. Ne verebilirseniz, her şeye minnettar oluruz.";
			link.l1 = "300 peso.";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000 peso.";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "3.000 peso.";
			link.l3.go = "Convict_12_2_3";
		break;
		
		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "Teşekkür ederim, kaptan, Tanrı seni korusun...";
			link.l1 = "Sana da bol şans.";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(hrand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "Bu gerçekten büyük bir şans! Parayı bu kadar çabuk alacağımızı hiç ummazdık. Kaptan, izin verin size eski patronumuzdan aldığımız bir hatıra sunayım. Belki size de uğur getirir.";
				link.l1 = "Teşekkür ederim, bu gerçekten düzgün bir davranış. Sana bol şans.";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "Teşekkür ederim kaptan, Tanrı seni korusun...";
				link.l1 = "Sana da bol şans.";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if(hrand(1) == 0)
			{
				dialog.text = "Bu gerçekten büyük bir şans! Parayı bu kadar çabuk alacağımızı hiç ummazdık. Kaptan, eski patronumuzdan aldığımız bu küçük hatırayı size sunmama izin verin. Belki size de uğur getirir.";
				link.l1 = "Teşekkür ederim, bu gerçekten düzgün bir hareket. Sana bol şans.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "İşte, parasını harcamaktan korkmayan cömert bir adam, çünkü onu nasıl kazanacağını iyi biliyor!\nDün gece yerel kaçakçıların yükleme yaptığını gördük "+MerPrm.QuestGoodsIdx+". Hava karanlıktı, ama yine de sandallardan birinin yanında geminin adını seçebildik '"+MerPrm.ShipName+"'... ve o gemi şu bayrak altında seyrediyor: "+MerPrm.nation+". Belki bu bilgi işine yarar, he-he.";
				link.l1 = "Hmm... Belki de öyle yaparım. Size de elveda, iz sürücüler.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);				
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}			
		break;
		
		case "Convict_12_1_End":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");	
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_12_3":
			if(hrand(1) == 0)
			{
				dialog.text = "Bize felaket getirme kaptan! Güzel bir takımız var, lütfen bunu fidye olarak kabul et ve bizi serbest bırak...";
				link.l1 = "Ver onu, sonra da hâlâ vaktin varken defol.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Artık başka çaremiz yok, bir adam iki kez ölmez. Son savaşa, çocuklar!";
				link.l1 = "Bu bambaşka bir hikaye!";
				link.l1.go = "Convict_Fight";
			}			
		break;
		
		case "Convict_13":
			dialog.text = "Pekâlâ, elbette aziz değiliz, ama durduk yere kavga aramıyoruz... Kaçak durumdayız ve buradan bir an önce gitmemiz gerekiyor.";
			link.l1 = "Geçiş için ödeyecek bir şeyin var mı?";
			link.l1.go = "Convict_13_1";		
			link.l2 = "Anladım... Hayır, senin yüzünden itibarımı lekelemem. Elveda.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Tabii! Böyle şeylere, gemi baskınlarına alışkınız. Neredeyse iki yıldır biz ve merhum "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" yerel tüccarları korkutuyordu, ama ne yazık ki! Onu astılar, ve "+pchar.GenQuest.Convict.ConvictQty+" aramızdaki adamlar kürek mahkûmiyetine çarptırıldı.";
			link.l1 = "Mürettebatıma katılmaya ne dersin? Cömertim"+GetSexPhrase("","")+", ama sana huzurlu bir hayat vaat edemem.";
			link.l1.go = "Convict_11_3";			
		break;
		
		case "Convict_11_2":
			dialog.text = "Evet, bir şeyler kaptık "+GetStrSmallRegister(XI_ConvertString("MineType"+pchar.GenQuest.Convict.MineType+"Gen"))+", bu yüzden iki katı ödeyebiliriz. O halde fiyat konusunda anlaştık diye güveniyorum. Sakın ha muhafız getirmeye kalkma. İhaneti asla affetmeyiz..."; // belamour gen
			link.l1 = "Pekala, sahilde beni bekle "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Gen")+". Gece yarısına doğru senin için bir kayık olacak ... Ve sakın bana numara yapmaya kalkışma!"; // belamour gen
			link.l1.go = "Convict_11_4";
			link.l2 = "Hayır, dostlarım. Ya size gemiyi verirsem ve siz de beni sırtımdan bıçaklarsanız? Hayır, bu işe karışmayacağım.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_3":
			dialog.text = "Büyük bir memnuniyetle, "+GetSexPhrase("bey","kaçırmak")+" kaptan. Buna oldukça aşinayız ve zaten böyle referanslarla Donanma'ya alınacağımız da yok, he-he.";
			link.l1 = "Pekala. Yakınlarda bir yer var, adı da "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+"Gece yarısından sonra orada seni alacağım. Umarım kaybolmazsın.";
			link.l1.go = "Convict_11_6";
		break;
		
		case "Convict_11_4":
			dialog.text = "Ama, "+GetSexPhrase("bayım","özlemek")+" kaptan, daha büyük bir risk almıyor muyuz? Ya bizi komutana teslim etmeye karar verirseniz?";
			link.l1 = "Doğru... Tamam, eğer gün ağarana kadar orada olmazsam, anlaşma iptal olur.";
			link.l1.go = "Convict_11_7";			
		break;
		
		case "Convict_11_5":
			if(makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 79) //макс. репутатция 90
			{
				dialog.text = "Ah kaptan, sana güveniyorduk...";
				link.l1 = " Sorun değil. Paran varsa, bir yolunu bulursun. Hoşça kal.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Akıllı birisin kaptan, bunu görebiliyorum. Eminim hemen komutana koşacaksın, değil mi? Gerçekten de paçayı sıyırabileceğini mi sanıyorsun?";
				link.l1 = "Ve beni durdurmayı mı planlıyorsun, öyle mi?! O zaman hak ettiğini alacaksın!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}	
		break;
		
		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));	// belamour gen	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);	
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");		
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));					
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();		
			AddDialogExitQuestFunction("Convict_DialogDisable");		
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "Bir şey var. Patronumuzun sandıklarını karıştırdık, ama sonra bununla ilgili bir kargaşa çıktı ve kaçmak için dövüşmek zorunda kaldık. Sadece "+PChar.GenQuest.Convict.ConvictQty+" adamlar hayatta kalmayı başardı.";
			link.l1 = "Şartlar göz önüne alındığında, sana bundan daha ucuza yolculuk teklif edemem "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+" kişi başı peso.";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Korkak olmadığınızı görüyorum. Mürettebatıma katılır mısınız?";
				link.l2.go = "Convict_13_3";
			}
		break;
		
		case "Convict_13_2":
			dialog.text = "Ve başka seçeneğimiz var mı? Peki, "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+"...";
			link.l1 = "O zaman git "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Dat")+". Gece yarısından sonra seni almak için bir sandal göndereceğim."; // belamour gen 
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;
		
		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Ve neden olmasın? O işlerden anlarız, zaten korsanlık yapıyoruz "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" in "+RandPhraseSimple("Gibraltar","English Channel")+" buraya sıkışmadan önce.";
			link.l1 = "Pekala. Yakınlarda, adıyla bilinen bir yer var "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+". Gece yarısına doğru orada seni alacağım. Umarım kaybolmazsın.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;
		
		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");					
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat"));	// belamour gen	 	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
				
		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Eh, kaptan, sen de bir zamanlar fakirdin, ceplerin boştı. Şimdi ise bizim gibi sade insanlara tepeden bakıyorsun.","Kaptan, sıradan insanlara böyle davranmak doğru değil. Hepimiz aynı Tanrı'nın kullarıyız."),RandPhraseSimple("Heh, insanlar bu aralar gerçekten fazlasıyla bencil oldu. Sanki önünde iki yüzyıl daha varmış gibi yaşıyorsun.","Ah, görüyorum ki Avrupa'dan yeni geldin, henüz bu tropik çöplüğümüzün pis kokusunu duymadın."));
			link.l1 = LinkRandPhrase("Beni utandırmaya mı çalışıyorsun? Dilini birkaç santim kısaltırım!","Beni korkutmaya mı çalışıyorsun? Şapkan sıkı dursun şimdi!","Filozof musun nesin? Sana akıl fikir öğreteceğim!");
			link.l1.go = "Convict_Fight";	
			pchar.GenQuest.Convict = "fight";
		break;
		
		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	 
			LAi_LockFightMode(pchar, false); 
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "Convict_15":
			dialog.text = LinkRandPhrase("Peki, kaptan? Bize bir gemi bulabildin mi?","Selam, kaptan. Peki, anlaşmamız ne olacak?","Merhaba, kaptan. Endişelenmeye başlamıştık. Her şey yolunda geçti, değil mi?");
			if(Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = "Evet, işte teknen. Ve ödemeyi unutma. Ben ödedim "+pchar.GenQuest.Convict.ShipPrice+" bunun için   sikke ödedim, yani bana borçlusun "+sti(pchar.GenQuest.Convict.ShipPrice)* 2+", tam da anlaştığımız gibi.";
				link.l1.go = "Convict_15_1";
			}	
			link.l2 = "Hayır, fikrimi değiştirdim. Kendine başka bir yardımcı bul. Hoşça kal...";
			link.l2.go = "Convict_15_2";
		break;
		
		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Elbette! Özgürlüğümüzü aldılar, ama vicdanımızı asla! Lütfen paranızı ve sonsuz minnettarlığımızı kabul edin. Bize gerçekten yardımcı oldunuz. Ödemenizi gümüş külçelerle yapsak sakıncası olur mu?";
					link.l1 = "Elbette istemem. Yolculuğunda bol şans. Umarım açık denizde karşılaşmayız, seni hemen alt ederim.";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry6", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "Kaptan, biliyor musun, paranın hayatta o kadar da önemli olmadığını düşündük. Açıkçası, şu anda senin ihtiyacından çok daha fazla bizim ihtiyacımız var. Ama eski patronumuzdan çaldığımız bir şey var. Belki altından çok daha fazla ilgini çeker. Göz atmak ister misin?...";
					link.l1 = "Evet, haklısın. Gerçekten harika bir şey bu. Peki, tamam, anlaştık. Teşekkürler ve hoşça kal.";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					dialog.text = "Neden bu kadar paraya ihtiyacın var ki kaptan? Zaten zenginsin, ama biz bu gemiyi alamazsak mahvoluruz. Yani... bunu senden alacağız, hepsi bu. Kötü bir niyetimiz yok.";
					link.l1 = "Bu senin son hatandı. Gemin olmadan belki yüzerek kaçabilirdin, ama şimdi ya suyun üstünde kalacaksın ya da batacaksın.";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;
	
		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
	
		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;	
	
		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);	
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16":
			dialog.text = RandPhraseSimple("Peki kaptan? Yüklemeye başlayalım mı?","Sonunda! Endişelenmeye başlamıştık, fikrini değiştirdin sandık.");
			link.l1 = "Üzgünüm, planlarım değişti. Artık başka bir kaptan bulman gerekecek.";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "Tekneye bin, fazla vaktim yok.";
				link.l2.go = "Convict_16_2";			
			}			
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "Sandala bin, fazla vaktim yok.";
				link.l2.go = "Convict_16_2";			
			}			
		break;
		
		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "Kahrolasıca! Eminim peşimize çoktan bir devriye gönderdin?! Bunun yanına kalmayacak!";
				link.l1 = "Ne diyorsun sen?! Ölmek mi istiyorsun, ne?! ";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = "Kaptan "+GetSexPhrase(", sözünün eri misin, değil misin?","?")+" Yoksa sadece lanet bir geveze misin...";
				link.l1 = "Ağzına dikkat etsen iyi olur...";
				link.l1.go = "Convict_16_3";
			}
		break;
		
		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");				
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false); 
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;			
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");				
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
						
		case "Convict_17":
			dialog.text = LinkRandPhrase("Ah, çok teşekkür ederim, "+GetSexPhrase("iyi adam","güzel kız")+".","Teşekkür ederim kaptan, gerçekten beni ipten aldınız.","Böylesine güzel bir yolculuk için minnettarım.");
			link.l1 = LinkRandPhrase("Hepsi güzel hoş da, ben parayı bekliyorum.","Ödeme zamanı geldi, biliyorsun.","Anlaştığımız gibi, peşin para.");
			link.l1.go = "Convict_17_1";
		break;
		
		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Elbette, ne sorular ama! İşte paranız altın külçeler halinde, ayrıca en içten teşekkürlerimizi kabul edin lütfen.";
					link.l1 = "Sana da bol şans. Hoşça kal.";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "Kaptan, biliyor musunuz, paranın hayatta o kadar da önemli olmadığını düşündük. Açıkçası, şu anda ona sizden çok daha fazla ihtiyacımız var. Ama eski patronumuzdan çaldığımız bir şey var. Belki bu, altından çok daha fazla ilginizi çeker. Göz atmak ister misiniz?...";
					link.l1 = "Evet, haklısın. Gerçekten harika bir şey bu. Peki, tamam, anlaştık. Teşekkürler ve hoşça kal.";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "Neden bu kadar paraya ihtiyacın var? Zaten zenginsin. Bize yardım ettin, biz de başka bir zaman sana yardım ederiz.";
					link.l1 = "Böyle bir fırsat olmayacak. Duanızı edin, alçaklar, borçlara göz yummam.";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);			
					break;
			}
		break;
		
		
		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	//belamour gen			
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	// belamour gen	
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;		
		// <-- Генератор "State convicts"
		
		// Генератор "A reason to hurry" -->
		// Встреча с ОЗГ на берегу
		case "ReasonToFast_Hunter1":
			dialog.text = "Buraya   gönderildim "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" kendisi...";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" size birkaç saattir cevapla sizi bekliyor. Sizi gördükten hemen sonra beni gönderdi.";
			link.l1.go = "ReasonToFast_Hunter4";
		break;
		
		case "ReasonToFast_Hunter2":
			dialog.text = "Uzun zamandır izini sürüyorum, ama sen gerçekten çok hızlısın.";
			link.l1 = "Peki, ne olmuş yani?";
			link.l1.go = "ReasonToFast_Hunter6";		
		break;
		
		case "ReasonToFast_Hunter3":
			dialog.text = "Valinin adamlarına ne kadar ödediğini söylesen daha iyi olur?";
			link.l1 = "Lanet olsun!";
			link.l1.go = "ReasonToFast_Fight";		
		break;
		
		case "ReasonToFast_Hunter4":
			dialog.text = "İçki içmedim! Lostromoyu arıyordum...";
			link.l1 = "Şimdi git... Söylerim "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+", ormanda kaybolduğunu duydum.";
			link.l1.go = "ReasonToFast_Hunter5";		
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;
		
		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;
		
		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;
		
		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		// бой с кэпом пиратского корабля
		case "ReasonToFast_FightCap": 
			dialog.text = "Ve sen de akıllısın. Dua et ki numaraların başkalarının kulağına gitmesin "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			link.l1 = "Ona söylemezsen bilmez... Ve söylemeyeceksin, değil mi?";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;
		
		case "ReasonToFast_FightCap_1":
			dialog.text = "Neden? Tabii ki yaparım, hem de büyük bir zevkle!";
			link.l1 = "Zaten o aptallığın yüzünden seni asacak. O yüzden vakit kaybetmeyelim, ben de seni darağacından kurtarmana yardım edeyim.";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;
		
		case "ReasonToFast_FightCap_2":
			dialog.text = "Hmm... Peki bunu nasıl yapacaksın?";
			link.l1 = "Seni kendi ellerimle öldüreceğim...";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;
		
		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;		
		
		// встреча с лакеем в резиденции
		case "ReasonToFast_Lakey":
			dialog.text = "Burada bir işin mi var, "+GetSexPhrase("monsieur","mademoiselle")+"?";
			link.l1 = "Hayır, hayır, ben buraya valinin zarif eşinin davetiyle geldim, sadece bu gerçekten lüks konutu hayranlıkla izliyorum.";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "Seni tanıyanlardan bir mesajım var.";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "Evet. Seni adalete teslim etmek istiyorum!";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Ah evet, böyle güzel bir evde hizmet ettiğim için gerçekten çok şanslıydım.";
			link.l1 = "Hiç şaşırmadım...";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Bahçemize göz atmayı unutma!";
			link.l1 = "Teşekkür ederim, iyi adam!";
			link.l1.go = "exit";			
			bDisableFastReload = false;
		break;
		
		case "ReasonToFast_Lakey2":
			dialog.text = "Ehh... "+pchar.questTemp.ReasonToFast.password+"?";
			link.l1.edit = 1;			
			link.l1 = ""; 
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "Bununla paçayı sıyıramayacaksın, hain!";
			link.l1 = "Kıpırdama, alçak!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;			
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Çabuk şimdi! Değerli ne varsa al ve kaç!";
				link.l1 = "Bence sen de kaçmalısın.";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";					
				bDisableFastReload = true;		
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = "Mmm, affedersiniz, müsaadenizi isteyeceğim.";
				link.l1 = "Kıpırdama, alçak!";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}			 
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();	
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //снимаем таймер
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;		
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Sen "+GetSexPhrase("Bir hırsız, görüyorum! Muhafızlar, yakalayın onu","Bir hırsız, demek! Muhafızlar, yakalayın onu")+"!","İnanamıyorum! Bir saniyeliğine arkamı döndüm, sen de sandığımı karıştırıyorsun! Hırsızı yakalayın!","Gardiyanlar! Soygun var! Hırsızı durdurun!");
			link.l1 = "Aaaah, şeytan!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break; 
		// Генератор "A reason to hurry" <--
		
		// ситуации с капитаном захваченного корабля
		// взрыв на корабле
		case "ShipSituation11": // пираты или ДУ
			dialog.text = RandPhraseSimple("Merhaba, "+GetSexPhrase("dostum","kız")+"! Sana bir sürpriz hazırladım, barut odasının fitilini ateşledim. Birazdan havaya uçacak!","Neden orada öylece duruyorsun? Barut odasında yangın var! Birazdan patlayacak, ve havai fişekler Avrupa'dan bile görünecek!");
			link.l1 = RandPhraseSimple("Sen alçak, beni kandıramazsın! Dövüş, korkak!","Gemiyi ilk terk eden fareleri görüyorum, sen de onların arasında mısın?");
			link.l1.go = "ShipSituation12";
		break;
		
		case "ShipSituation12":
			dialog.text = RandPhraseSimple("Sen de canını düşünüyorsan kaçsan iyi edersin... Neyse, vaktim yok, bir kayık beni bekliyor. Balık tutmanın tadını çıkar!","Kahramanlık yapacak vaktim yok, sandaldaki adamlar beni bekliyor. Balık tutarken iyi eğlenceler, şampiyon!");
			link.l1 = RandPhraseSimple("Lanet olsun! Halatları kesin! Demir alın!","Tanrım, nasıl böyle bir belaya bulaştık! Deniz girişlerini açın! Geri çekilin!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation21": // военный корабль (не флагман)
			dialog.text = "Ne olmuş yani?! Kavga bitti mi sandın?! Hiç de bile. Barut mahzenini ateşe verdim, bu gemiden sağ çıkamayacaksın.";
			link.l1 = RandPhraseSimple("Sen alçak, beni kandıramazsın! Dövüş, korkak!","Görüyorum ki fareler gemiyi terk ediyor, sen de ilklerden misin?");
			link.l1.go = "ShipSituation22";
		break;
		
		case "ShipSituation22":
			dialog.text = RandPhraseSimple("Bir yemine bağlıyım, ama bu boş yere öleceğim anlamına gelmez. Seni sandala davet etmediğim için üzgünüm, denizciler bunu anlamazdı.","Gemiler birbirine kenetlendi, artık kaderin belli oldu. Affedersin, ama kayığım beni bekliyor...");
			link.l1 = RandPhraseSimple("Kahretsin! Usturmaçaları kesin! Halatları çözün!","Tanrım, nasıl böyle bir belaya bulaştık! Deniz girişlerini açın! Uzaklaşın!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation31": // ОЗГ
			dialog.text = RandPhraseSimple("Zafer senin! Cehenneme hoş geldin! Barut deposunu ateşe verdim.","Here you are, my good man! And you are done; I have set a powder room on fire.");
			link.l1 = RandPhraseSimple("Sen alçak, beni kandıramazsın! Savaş, korkak!","Gemiyi ilk terk eden fareleri görüyorum, sen de onların başında mısın?");
			link.l1.go = "ShipSituation32";
		break;
		
		case "ShipSituation32":
			dialog.text = RandPhraseSimple("Seni epeydir izliyordum. Gemimi feda etmek zorunda kalmam yazık oldu ama senin kelle iki yeni gemi eder zaten. Balık tutarken iyi eğlenceler!","Nasıl gideceksin bakalım? Havai fişeklerle mi, Hint prensi gibi"+GetSexPhrase("ce","cess")+". But I will not come off as a loser; your head is worth far more than my ship. Farewell now, my boat will not wait for too long...");
			link.l1 = RandPhraseSimple("Lanet olsun! Usturmaçaları kesin! Halatları çözün!","Tanrım, nasıl böyle bir belaya bulaştık! Deniz girişlerini açın! Uzaklaşın!");
			link.l1.go = "ShipSituation_End";			
		break;
		
		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);	
			Log_Info(XI_ConvertString("Ship can explode"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;	
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		// эпидемия
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("Dur bir dakika, kaptan! Sadece bir iki lafım var.","Bir dakika, kaptan! Sanırım bu sizin ilginizi çekebilir.");
			link.l1 = LinkRandPhrase("Neden kavga sırasında konuşuyorsun?!","Ve ben ölü bir adamla ne hakkında konuşmalıyım?","Ne var? Vasiyetini benim adıma mı yazmak istiyorsun?");
			link.l1.go = "ShipEpidemy2";
		break;
		
		case "ShipEpidemy2":
			dialog.text = "Gemiye bir hastalık yayıldı. Yolculuk sırasında mürettebatımın dörtte birini kaybettim. Hepiniz mahvoldunuz...";
			link.l1 = RandPhraseSimple("Seni aşağılık pislik! Geminde bir felaket olduğunu neden haber vermedin?!","Deniz kanununu unuttun mu? Geminde bir felaket olduğunu göstermek için direğe bir işaret çekmeliydin!");
			link.l1.go = "ShipEpidemy3";
		break;
		
		case "ShipEpidemy3":
			dialog.text = "Zaten ölmek üzereydik. Bu yüzden pes etmedik, seni ve şeytanlarını da yanımızda öteki dünyaya götürmek istedik! Şimdi tamamen huzurluyum. Pis işini bitirebilirsin.";
			link.l1 = RandPhraseSimple("Bunun bedelini ödeyeceksin!..","Önce senin ölmeni isterim. Ve izleyeceğim.");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("Kılıcımı senin pis kanınla kirletmeyeceğim, yaşayabilirsin, gerçi... ne için? Mürettebatımı o çürümüş eski gemiden alıp gidiyorum.","Bunun için seni darağacına göndermeliydim, ama artık gerek yok. Adamlarımı alıp gidiyorum... Belki yaşarsın, ama günlerin sayılı, bunu unutma...");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;
		
		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // вражеский кэп на волосок от смерти от переизбытка стали и свинца в организме
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);	
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // вражеский кэп остался в живых
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// ситуации с капитаном захваченного корабля
		
		// Генератор "A damsel in the jungle"
		case "EncGirl_Lover":
			dialog.text = "Merhaba kaptan, beni aradığınızı söylediler.";
			link.l1 = "Ben de – eğer sen de istersen "+pchar.GenQuest.EncGirl.sLoverId+".";
			link.l1.go = "EncGirl_Lover1";
		break;
		
		case "EncGirl_Lover1":
			dialog.text = "Evet, benim. Önemli bir şey mi var?";
			link.l1 = "Bunun senin için önemli olup olmadığını bilmiyorum, ama getirdim "+pchar.GenQuest.EncGirl.name+". Evden kaçtı ve şimdi meyhanenin çok uzağında olmayan bir yerde seni bekliyor.";
			link.l1.go = "EncGirl_Lover2";
		break;
		
		case "EncGirl_Lover2":
			dialog.text = "Ah... Biliyordum böyle olacağını... Peki neden kaçtı? Sana bir şey söyledi mi?";
			link.l1 = "Babası onu tefeci'nin oğluyla evlendirmek istiyor.";
			link.l1.go = "EncGirl_Lover3";
		break;
		
		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "Ah hayır, bunun olmasına izin veremeyiz! Kaptan, biliyorsunuz, öyle aptalca bir durumdayım ki... Sizi bizleri götürmeniz için rica etmek istemiştim "+XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland+"Acc")+"  adında bir kasabaya "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+", ama şu anda hiç param yok ve hâlâ bir iş bulamadım. Varlıklı bir ailem ve umut vadeden bir kariyerim var "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+"...\nEmin olun, ailem beni genç bir nişanlıyla gördüğüne çok sevinecek ve sizi cömertçe ödüllendirecekler. Peki, var mısınız?";
			link.l1 = "...Bak, benim bambaşka planlarım var. Sana bir tavsiye vereyim: bir gemide tayfa olarak iş bul ve maaşınla gelinine bir kamarayı kirala. İnsanlar Avrupa'ya böyle gidiyor, senin o yerleşim yerin de kuş uçuşu mesafede.";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "Ah, gençlik... Benden ne istediğinin farkında mısın? Bir kızı ailesinin rızası olmadan yanına almak mı? ... Ve böyle bir şeyi kim reddeder ki? Elbette varım!";
			link.l2.go = "EncGirl_Lover5";
		break;
		
		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");	
			DialogExit();
		break;
		
		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");	
			DialogExit();
		break;
		
		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("Have you heard, " + pchar.GenQuest.EncGirl.name + " ran off with her lover. She decided not to bind her life to an invalid. That's surely the mistake of her parents, they should not have become tempted with the money of her fiance and try to give such a beauty in marriage to a fright.",  
				"Have you heard?" + pchar.GenQuest.EncGirl.name + " tricked both her dad and her would-be fiance. They say one noble captain helped her and her lover to get to another island, where her lover's parents lived... Imagine that, there still are people, who had not yet forgotten the taste of passion!"), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "Teşekkürler, kaptan. Yardımınızı hayatımız boyunca unutmayacağız.";
			link.l1 = "Önemli değil. Umarım her şey senin için iyi olur.";
			link.l1.go = "EncGirl_Lover7";
		break;
		
		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "the shop";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "the shipyard";					
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "the port office";					
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "the tavern";					
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "the bank";					
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}	
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "Seni ailemle tanıştıracağıma söz vermiştim. Eğer boş bir vaktin olursa, lütfen gel "+sTemp+", babam orada çalışıyor, ve senin bizim için yaptıklarını ona anlatacağım. Eminim seni görmekten çok memnun olacak.";
			link.l1 = "Pekala, bir fırsat bulunca uğrayacağım. İkiniz de mutlu olun ve birbirinize iyi bakın...";
			link.l1.go = "EncGirl_Lover8";
		break;
		
		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // папочка жениха счастлив за сына :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // папочка жениха разъярен за то что сын притащил в дом шалаву :)
			}
			chrDisableReloadToLocation = false; 
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();	
		break;
		// Генератор "A damsel in the jungle"
		
		// Генератор "Captain's request"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("Dur! Dur, kaptan! Lütfen.","Kaptan, lütfen, bekleyin, yalvarıyorum...");
			link.l1 = LinkRandPhrase("Ne oldu? Nefesin mi kesildi?","Kaldır kılıcını, korkak!","Ne oldu? Vasiyetini yazmayı mı unuttun?");
			link.l1.go = "CaptainComission_2";
		break;
		
		case "CaptainComission_2":
			dialog.text = "Bekle... Yaralıyım ve savaşmaya devam edecek gücüm kalmadı... Merhamet istemiyorum, ama yarım kalmış işlerim var. Lütfen, ölmekte olan bir adamın son dileğini yerine getireceğine söz ver.";
			link.l1 = RandPhraseSimple("Korkak olma kaptan, ölümle bir adam gibi yüzleş!","Kaptan, ne duygusallığı? Etrafımızda bir savaş sürüyor, başladığımızı bitirelim.");
			link.l1.go = "CaptainComission_21";
			link.l2 = "Konuş şimdi ve çabuk ol.";
			link.l2.go = "CaptainComission_22";
		break;
		
		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_22":		
			if(rand(1) == 0) // "Ransom"
			{
				CaptainComission_Init(NPChar);
				dialog.text = "Söyle "+pchar.GenQuest.CaptainComission.Name+"  yerleşiminden "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City)+", onun isteğini yerine getiremeden... zamanım olmadan önce... Beni affetsin...";
				link.l1 = RandPhraseSimple("Ve bu kadar mı?! Peki, yapabilirim. Hey, dostum...","Pekala, vaktim olursa ona söylerim. Hey, dostum...");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "Bence olmaz. Böyle saçmalıklara vaktim yok. Başladığımız işi bitirelim.";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "Operation 'Galleon'"
			{			
				CaptainComission_GaleonInit(NPChar);
				dialog.text = "Lütfen, devriye kaptanına söyleyin "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Gen"))+" '"+pchar.GenQuest.CaptainComission.ShipTypeName+"' "+pchar.GenQuest.CaptainComission.Name+", bir daha burada yüzünü göstermemesi gerektiğini "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+"... "+"Yetkililer onun ölümünün gerçek koşullarından haberdar "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"... zaman dar, yakında tutuklanacak...   şuraya yelken açıyor "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Acc")+" from "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+", yolculuk neredeyse on beş gün sürecek... ahh... acele etmeliyiz..."; // belamour gen
				link.l1 = RandPhraseSimple("Bir şey vaat edemem, ama zamanı gelince denerim. Hey, dostum...","Pekala, vaktim olursa ona söylerim. Hey, dostum...");
				link.l1.go = "CaptainComission_300";
			}					
		break;
		
		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));	
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();	
		break;
		
		case "CaptainComission_22_2":
			dialog.text = "Böylesine bir zalimlik! Umarım bunun hesabını verirsin.";
			link.l1 = "Ve çok daha fazlası için...";
			link.l1.go = "CaptainComission_22_3";
		break;
		
		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("Seni dinliyorum, "+GetAddress_Form(pchar)+".","Ne istemiştin?","Size nasıl yardımcı olabilirim?");
			if (pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2") // лесник - доп.проверка если есть квест. для перехода .
			{	
			link.l1 = "Sen misin "+pchar.GenQuest.CaptainComission.Name+"? Seninle işim var, Kaptan "+pchar.GenQuest.CaptainComission.CapName+" sana bazı önemli bilgileri iletmemi istedi.";
			link.l1.go = "CaptainComission_4";
			break;
			}
			link.l2 = "Hayır, hiçbir şey yok...";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_3"; // лесник - переход чтобы не вызывал баг при повтороном обращении
		break;
		
		case "CaptainComission_4":
			dialog.text = "Öyle mi? Peki. Yani, kaptan neyi "+pchar.GenQuest.CaptainComission.CapName+"bilmemi mi istedin?";
			link.l1 = "Sana iletmemi istedi, isteğini yerine getiremeyeceğini söyledi.";
			link.l1.go = "CaptainComission_5";
		break;
		
		case "CaptainComission_5":
			dialog.text = "Ne diyorsun sen?! Onu yıllardır tanırım, çok dürüst bir adamdır. Sana böyle bir şey söylemiş olamaz!";
			link.l1 = "Diyelim ki, kontrolü dışında gelişen sebeplerden dolayıydı. Başka bir deyişle - bu onun son dileğiydi.";
			link.l1.go = "CaptainComission_6";
		break;
		
		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "Ah, bu tamamen yersiz! Ne kadar çok zaman boşa harcandı\n"+"Kaptan, o halde sizden bana yardım etmenizi istemeliyim. Korsanlar  "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Gen")+" akrabamı ele geçirdiniz "+pchar.GenQuest.CaptainComission.SlaveName+" ve onun için fidye talep ediyorlar. Bu görevi üstlenebilir misin? Ödül oldukça cömert olacaktır.";
				link.l1 = "Ne yazık ki, başka planlarım var.";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "Daha ayrıntılı anlatırsan sana yardımcı olmaya çalışırım.";
				link.l2.go = "CaptainComission_6_2";
			}
			
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "Ah, bu tamamen yersiz! Ne kadar zaman boşa gitti\nPeki ya sandıklar?";
				link.l1 = "Umm... hangi sandıklar?";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}	
		break;
		
		case "CaptainComission_6_1":
			dialog.text = "Yazık kaptan... Bana yardım etmeye istekli olmaman gerçekten üzücü.";
			link.l1 = "Bu benim isteğime bağlı bir şey değil, dostum. Anlamalısın. Elveda.";
			link.l1.go = "CaptainComission_6_1End";
		break;
		
		case "CaptainComission_6_2":
			dialog.text = "Dün bir mektup aldım "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", fidyenin daha yüksek olacağını bildirdiği ve ayrıca onu köle olarak satmakla tehdit ettiği bir mektup. Merhum kaptan bildirmeliydi ki "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", önceki şartları kabul edip peşin ödeme yaptığımı hatırlatırım. Ama şimdi korsanların neden işi zorlaştırdığını anlıyorum.";
			link.l1 = "Ve ne öneriyorsun?";
			link.l1.go = "CaptainComission_6_21";
		break;
		
		case "CaptainComission_6_3":
			dialog.text = "Oh, "+GetSexPhrase("dostum","kız")+", burada bir dalavere seziyorum. Seni uyarıyorum, bu çok tehlikeli ve ağır sonuçlara yol açabilir. Kaptan "+pchar.GenQuest.CaptainComission.CapName+" üç sandık dolusu altını vardı, ki bunları teslim etmesi gerekiyordu "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_DAT)+" on "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" bir adamın fidyesi olarak -  "+pchar.GenQuest.CaptainComission.SlaveName+". Ve eğer seni bize göndermek isteseydi, sandıklardan bahsetmeyi unutmuş olamazdı.";
			link.l1 = "Son sözlerini söylerken cümlesini tamamlamış gibi görünmüyordu. Umarım bana daha fazlasını anlatırsın.";
			link.l1.go = "CaptainComission_6_31";
		break;
		
		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			sld = CharacterFromID("CapComission_1"); // удаление если послал нахуй. лесник.
			sld.LifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DialogExit();	
		break;
		
		case "CaptainComission_6_21":
			dialog.text = "Başka bir seçeneğim kalmadı... Gerekli miktarı, 150.000 peso, zaten topladım. Bunu teslim etmeni rica ediyorum "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" ve akrabamı buraya getir. İş biter bitmez sana 40.000 ödeyeceğim.";
			link.l1 = "Pekâlâ, hazırım.";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "Maalesef, başka planlarım var.";
			link.l2.go = "CaptainComission_6_1";			
		break;
		
		case "CaptainComission_6_22":
			dialog.text = "Parayı al o zaman, Tanrı seni korusun. Ama lütfen, acele et. Korkarım ki "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_NOM)+" beklemeyeceğim ve zavallı ruhu köleliğe satacağım.";
			link.l1 = "Burada beni bekle. Sanmıyorum, çok uzun sürmez.";
			link.l1.go = "CaptainComission_6_22End";
		break;
		
		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_6_31":
			dialog.text = "Önemli değil\nFidyeyi toplayanlar umursamaz. Onların tek istediği sonuç: canlı ve sapasağlam - "+pchar.GenQuest.CaptainComission.SlaveName+". O yüzden vakit kaybetme.";
			link.l1 = "Ya reddedersem ne olacak?";
			link.l1.go = "CaptainComission_6_32";
		break;
						
		case "CaptainComission_6_32":
			dialog.text = "Aslında, iznine ihtiyacım yok. Sadece seni uyarıyorum, eğer teslim etmezsen "+pchar.GenQuest.CaptainComission.SlaveName+" hayatta ve sapasağlam meyhaneye, peşine ödül avcılarını salacağım...";
			link.l1 = "Hmm... Bu ciddi bir şey. Peki ya yaparsam?";
			link.l1.go = "CaptainComission_6_33";
		break;
		
		case "CaptainComission_6_33":
			dialog.text = "O zaman bunu daha sonra konuşuruz.";
			link.l1 = "Pekala... Bakalım nasıl olacak.";
			link.l1.go = "CaptainComission_6_33End";
		break;
		
		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Merhaba, Kaptan "+GetFullName(pchar)+" . Yeni bir haber var mı?","Ee, kaptan, fidyeyi çoktan teslim ettin mi?","Merhaba, umarım iyi haberlerle geldin?");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "Ne yazık ki, planlarım değişti, bu yüzden anlaşmamızı bozmak zorundayım.";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "Henüz değil. Hâlâ onunla meşgulüm.";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("Oh, seni görmek ne güzel, kaptan "+GetFullName(pchar)+" . İyi bir haber var mı?","Peki kaptan, acı çeken dostumuzu kurtardın mı?","Seni sağ salim görmek güzel, kaptan. Ortak işimizin durumu nedir?");
					link.l1 = "Henüz bir haber yok, ama ilgileniyorum.";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "Dinle dostum, neden o anlaşmanın sorumluluğunu bana yıkmaya çalışıyorsun?";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Merhaba, Kaptan "+GetFullName(pchar)+" . Bir haber var mı?","Peki kaptan, fidyeyi çoktan teslim ettin mi?","Merhaba, umarım iyi haberlerle geldin?");
					link.l1 = "Evet. İsteğin yerine getirildi, "+pchar.GenQuest.CaptainComission.SlaveName+" gemimde ve karaya çıkmaya hazırlanıyor.";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("Ah, seni görmek güzel, kaptan "+GetFullName(pchar)+" . İyi bir haber var mı?","Peki kaptan, acı çeken dostumuzu kurtardın mı?","Seni sağ ve iyi görmek güzel, kaptan. Ortak işimizin durumu nedir?");	
					link.l1 = "Konuştuğumuz adamı getirdim. Şu anda gemimde.";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Merhaba, Kaptan "+GetFullName(pchar)+" . Bir haber var mı?","Ee, kaptan, fidyeyi çoktan teslim ettin mi?","Merhaba, umarım iyi haberlerle geldin?");
					link.l1 = "Selamlar, "+pchar.GenQuest.CaptainComission.Name+", seni hayal kırıklığına uğratmak zorundayım.";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("Ah, seni görmek ne güzel, kaptan "+GetFullName(pchar)+". İyi bir haber var mı?","Peki kaptan, acı çeken dostumuzu kurtardın mı?","Seni sağ ve sağlam görmek güzel, kaptan. Ortak işimizin durumu nedir?");
					link.l1 = "Aracılık ettiğin adam öldü.";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;
		
		case "CaptainComission_30":
			dialog.text = "Teşekkür ederim kaptan, ailemize büyük bir iyilik yaptınız. İşte ödülünüz... Üç sandık var - bu tam olarak 40.000 peso ediyor. Lütfen beni mazur görün, şimdi onun yanına gitmeliyim.";
			link.l1 = "Elbette, size iyi bir buluşma ve bol şans dilerim.";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "Sabrınızı tamamen anlıyorum, fakat beklenmedik durumlar ortaya çıktı ve bu yüzden fazladan masraflara katlanmak zorunda kaldım.";
				link.l2.go = "CaptainComission_31";
			}	
		break;
		
		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			dialog.text = "Anlamıyorum... Zaten ödemenin miktarı üzerinde anlaşmamış mıydık?";
			link.l1 = "Var, ama 150.000 peso yerine 200.000 ödemek zorunda kaldım, Barbados'a gitmem gerektiğini de saymıyorum.";
			link.l1.go = "CaptainComission_31_1";
		break;
		
		case "CaptainComission_31_1":
			dialog.text = "Kaptan, bu tamamen sizin tembelliğinizin bir sonucu. Korsanlar benden başka bir şey talep etmedi. Başkalarının sıkıntılarından faydalanmaya çalışan tuhaf bir adamsınız, değil mi?";
			link.l1 = "Pekâlâ, sana bir şey anlatmanın boşuna olduğunu görüyorum...";
			link.l1.go = "CaptainComission_31_1End";
		break;
		
		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "Harika! Ve sen bizim iyi anlaşamayacağımızdan şüphe ediyordun.";
			link.l1 = "Ama bu iş için çok harcamak zorunda kaldım.";
			link.l1.go = "CaptainComission_32_1";
		break;
		
		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "Biliyorum, biliyorum... Ama bu da senin suçun. Hazineden resmen zorla çıkardığımız üç sandık altını nasıl batırabildin, söyler misin? "+NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation))+" böyle bir uzmana sahip olabilirdim "+pchar.GenQuest.CaptainComission.SlaveSpeciality+"?";
			link.l1 = "Bil ki, ona karşılık uygun bir ödeme olmadan onu sana vermem.";
			link.l1.go = "CaptainComission_32_2";
		break;
		
		case "CaptainComission_32_2":
			dialog.text = "Sen akıllı bir adamsın, pazarlık yapmak için artık çok geç olduğunu elbette anlarsın. Gemini ve yükünü kolayca ele geçirebilirdik.\nAma tazminat önceden ödendi. Bu nedenle, hükümet "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+" başarılı bir operasyon için sizi tebrik ediyor, bu değerli hediyeyi ve mütevazı bir ödülü takdim ediyor.";
			link.l1 = "Hmm... Eh, hiç yoktan iyidir. Al şu değerli uzmanını.";
			link.l1.go = "CaptainComission_32_2End";
		break;
		
		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");			
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);			
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item); 
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_1":
			dialog.text = "Ah, ne yazık! Zaten çok zaman kaybettim. Beni gerçekten hayal kırıklığına uğrattın, kaptan!";
			link.l1 = "Anlıyorum, ama şartlar elimde değildi. Al paran burada.";
			link.l1.go = "CaptainComission_7_1End";
		break;
		
		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0; 
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_2":
			dialog.text = "Lütfen acele eder misiniz? Korsanların anlaşmanın şartlarını yine değiştirmesinden korkuyorum.";
			link.l1 = "Merak etme, hallederiz.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_3":
			dialog.text = "Umarım zamanla yarıştığının farkındasın?";
			link.l1 = "Yine mi! Hallediyorum. Biraz sabret.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_4":
			dialog.text = "Tanrı bizi korusun! Baskı yok, sadece alçakgönüllü bir Püritenden biraz yardım\nBu senin kendi suçun. Kaptanı sen öldürdün "+pchar.GenQuest.CaptainComission.CapName+", altınımızı kaybettik ve çok değerli bir adamı fidyeyle kurtaramadık. Şimdi bu başımıza dert oldu ve senin sorumluluğun. Affedildiğini bile düşünme... Her şeyin bedelini ödeyeceksin.";
			link.l1 = "Siktir git!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		// диалоги с управляющим на плантации
		case "CaptainComission_10":
			dialog.text = "Merhaba, bir şey mi istedin?";
			link.l1 = "Bu plantasyonun sahibini görebilir miyim?";
			link.l1.go = "CaptainComission_10_1";
		break;
		
		case "CaptainComission_10_1":
			dialog.text = "Burada değil, kaçak bir köleyi arıyor, Blade mi Blood mu, hatırlamıyorum... Ben de buranın yerel kahyasıyım "+npchar.name+" ve patron izindeyken tüm işleri halletme yetkim var.";
			link.l1 = "Öyle mi? Güzel... Peki köle satmak da senin işin mi?";
			link.l1.go = "CaptainComission_10_2";
		break;
		
		case "CaptainComission_10_2":
			dialog.text = "Tabii. Kaç tane almak istiyorsun?";
			link.l1 = "Sadece bir tane.";
			link.l1.go = "CaptainComission_10_3";
		break;
		
		case "CaptainComission_10_3":
			dialog.text = "Ehh... Sadece bir köleye mi ihtiyacın olduğundan emin misin?";
			link.l1 = "Elbette, biliyorum. Adı "+pchar.GenQuest.CaptainComission.SlaveName+".";
			link.l1.go = "CaptainComission_10_4";
		break;
		
		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "Ama elbette, tek bir kölenin fiyatının, daha büyük bir toplu alımdaki köle fiyatına göre daha yüksek olacağını anlıyorsunuzdur?";
				link.l1 = "Elbette biliyorum. Fiyatı söyleyebilir misin?";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "Hmm... Kimin için araya girdiğinin farkındasın umarım?";
					link.l1 = "Ne demek istiyorsun?";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "Ah, o aylakçı. Ona bir bakır para bile vermem. Buraya getirildiğinden beri doğru düzgün bir iş yaptığı yok. Albayın neden bu devlet mahkûplarına para harcadığını hiç anlamıyorum. Şimdi, siyahlar başka mesele. Onlar mükemmel işçiler, hem güçlü hem de itaatkâr olmak kanlarında var. Bana güven, her işi yaparlar. Şeker kamışı hasadından kahyalığa kadar - yeter ki biraz 'ikna' et, hepsini herkes kadar iyi yaparlar...";
					link.l1 = "My friend, I couldn't care less about your black men. I'm only interested in that loafer you mentioned; he won't live long anyway. I need him as cannon fodder, and I'll pay more for him.";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		
		case "CaptainComission_11":
			dialog.text = "Tabii, tabii. Fiyatlara bir bakayım\nAaa! 150.000 peso.";
			link.l1 = "Vay canına...";
			link.l1.go = "CaptainComission_11_1";
		break;
		
		case "CaptainComission_11_1":
			dialog.text = "Fiyat listede olmalı. İşte burada. Biliyor musun, bunu pek anlamıyorum. Diğer köleler makul fiyatlara satılıyor ama o bir servete satılıyor...";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "Sanırım burada neler döndüğünü anladım... Peki, al parayı, onu da yanıma alıyorum.";
				link.l1.go = "CaptainComission_14";
			}	
			link.l2 = "Hmm... Ama ben bir rehineyi fidye karşılığında almıyorum, sıradan bir köle satın almak istiyorum. Böyle bir parayla düzgün, tam donanımlı bir gemi alınmaz mı sence?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_12":
			dialog.text = "Bu sıradan bir köle değil. Albay Bishop onun özel olarak korunmasını emretti.";
			link.l1 = "Yani onu satın almam bile mümkün değil mi?";
			link.l1.go = "CaptainComission_12_1";
		break;
		
		case "CaptainComission_12_1":
			dialog.text = "Elbette yapabilirsin. Albay onun için bir bedel belirledi - fiyat listesine göre 200.000 peso.";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "Vay canına! O albay kesinlikle o kölenin nasıl biri olduğunun farkındadır...";
				link.l1.go = "CaptainComission_16";
			}	
			link.l2 = "Hmm... Ama ben bir rehineyi fidye karşılığında almıyorum, sıradan bir köle satın almak istiyorum. Böyle bir paraya iyi donanımlı bir gemi alınmaz mı sence de?";
			link.l2.go = "CaptainComission_15";	
		break;
		
		case "CaptainComission_13":
			dialog.text = "Ah, evet. Affedersiniz. Bishop'un bıraktığı fiyatlara bir bakayım.\nAha, işte burada. Hmm. Oha!.. 150.000 peso!..";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "Görünüşe göre bu bir hata. Hiçbir kölenin bu kadar pahalı olamayacağını elbette fark etmişsindir. Sanırım fazladan bir sıfır eklenmiş, asıl tutar 15.000 peso olmalı. Ve bu bile fazla, çünkü kendisi hem aylak hem de aptal.";
				link.l1.go = "CaptainComission_17";
			}	
			link.l2 = "Hmm... Ama ben bir rehineyi fidyeyle kurtarmıyorum, sıradan bir köle almak istiyorum. Sence de bu paraya iyi donanımlı bir gemi alınmaz mı?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "Harika! Bu müthiş! Onu hemen buraya getirecekler... Ee... Belki biraz çay ister misiniz?";
			link.l1 = "Hayır, teşekkürler... Albay Bishop'a selam söyle...";
			link.l1.go = "CaptainComission_14_1";
		break;
		
		case "CaptainComission_14_1":
			dialog.text = "Ve kimden, öğrenebilir miyim?";
			link.l1 = "Mmm... Boşver, zahmet etme. Hoşça kal.";
			link.l1.go = "CaptainComission_14_1End";
		break;
		
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_15":
			dialog.text = "Üzgünüm, ama yapabileceğim bir şey yok. İşte fiyat listesi.";
			link.l1 = "Yeter artık, 'fiyat listesi, fiyat listesi...' Hiçbiriniz en basit şeyi bile Bishop olmadan kararlaştıramıyorsunuz. Ona söyleyin... Boşverin, hiçbir şey söylemeyin.";
			link.l1.go = "CaptainComission_15_1";
		break;
		
		case "CaptainComission_15_1":
			dialog.text = "Yani o köleyi satın almayacaksın.";
			link.l1 = "Hayır. Hoşça kal.";
			link.l1.go = "CaptainComission_15_1End";
		break;
		
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_16":
			dialog.text = "Bu konuda hiçbir şey bilmiyorum. Sadece o kölenin satışıyla ilgili özel talimatlarım var.";
			link.l1 = "Saçmalık... Peki, neyse. Al parayı. Köleyi getir.";
			link.l1.go = "CaptainComission_16_1"; 
		break;
		
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "Elbette. Hemen buraya getirilecek.";
			link.l1 = "Elveda.";
			link.l1.go = "CaptainComission_16_1End";
		break;
		
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_17":
			dialog.text = "Hmm... Evet, belki de haklısın. Bir hata olmalı.";
			link.l1 = "Pekala, fiyatta anlaştıysak, onu şimdi yanıma alabilir miyim?";
			link.l1.go = "CaptainComission_17_1";
		break;
		
		case "CaptainComission_17_1":
			dialog.text = "Evet, tabii ki. Birazdan buraya getirilecek.";
			link.l1 = "Çok iyi. Al paranı... Hoşça kal.";
			link.l1.go = "CaptainComission_17_1End";
		break;
		
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_18":
			dialog.text = "Biraz çay ister misiniz, kaptan?";
			link.l1 = "Hayır, teşekkürler.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_19":
			dialog.text = "Onu satın almaya karar verdin mi?";
			link.l1 = "Hayır. Hoşça kal.";
			link.l1.go = "exit";
		break;
		
		// диалоги с рабом
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Merhaba, kaptan. Size nasıl yardımcı olabilirim? Bu işkencenin sonunda bittiğine inanamıyorum.";
				link.l1 = "Bana değil, akrabanıza teşekkür etmelisiniz "+pchar.GenQuest.CaptainComission.Name+" from "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+". Fidye parasını topladı.";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "Merhaba, kaptan. Fidemi senin ödediğini söylediler. Bunun için sana teşekkür etmeliyim, gerçi sadece aracı olduğunu da biliyorum.";
				link.l1 = "Yeniden kazandığın özgürlüğünle pek mutlu görünmüyorsun. Bir şey mi kafanı kurcalıyor?";
				link.l1.go = "CaptainComission_202";
			}
		break;
		
		case "CaptainComission_201":
			dialog.text = "Lütfen, eğer planlarını çok bozmazsa, beni onun yanına götür. Ona şahsen teşekkür etmek istiyorum.";
			link.l1 = "Elbette, götüreceğim. Gel, seni gemiye götüreyim.";
			link.l1.go = "CaptainComission_201_1";
		break;
		
		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;
		
		case "CaptainComission_202":
			dialog.text = "Özgürlüğümden emin olmak için, bunun bedelini ödeyenlerin isimlerini bilmem gerekiyor.";
			link.l1 = "Yani, ödeyen bendim ama isteyerek yapmadım.";
			link.l1.go = "CaptainComission_202_1";
		break;
		
		case "CaptainComission_202_1":
			dialog.text = "Demek ki şüphelerimde haklıymışım. Bunu yapmaya zorlanmışsın "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "Evet, bu "+pchar.GenQuest.CaptainComission.Name+" from "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_202_2";
		break;
		
		case "CaptainComission_202_2":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta 
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Anladım. Sana ne vaat ettiklerini bilmiyorum ama anlaşma şu: beni şu meyhaneye götür "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", orada gerçekten güvende olacağım. Karşılığında, sahip olduğum bazı bilgileri seninle paylaşacağım.";
			link.l1 = "Bu sorun değil, özellikle de şimdiye kadar hiçbir şey vaat etmedikleri için. Benimle gel, seni gemime götüreyim.";
			link.l1.go = "CaptainComission_202_3";
			link.l2 = "Şüpheli bir bilgi yüzünden başıma bela almak istemem.";
			link.l2.go = "CaptainComission_203";
		break;
		
		
		
		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", "");			
			rChar.lifeDay = 0; 
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			LAi_SetActorType(NPChar);
			LAi_ActorFollow(NPChar, PChar, "OpenTheDoors", -1.0); //лесник  идем за ГГ
			DialogExit();
		break;
		
		case "CaptainComission_203":
			dialog.text = "Ne yazık ki, bunu sana henüz açıklayamam. Bu ikimiz için de sorun yaratabilir.";
			link.l1 = "Hele şimdi... Peşimden gel, ama saçmalık istemiyorum. Kendini tekrar tutuklu say.";
			link.l1.go = "CaptainComission_203_1";
		break;
		
		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0); //лесник - провожаем на корабль типа..
			DialogExit();
		break;
		
		case "CaptainComission_50":
			dialog.text = "Ne?! Korsanlar yine anlaşmayı değiştirmiş mi? Ama işten daha fazla para çıkaramam! Bu gidişle yakında iflas edeceğim!";
			link.l1 = "Hayır... Akraban Barbados'taki plantasyonlarda başarısız bir kaçış girişimi sırasında hayatını kaybetti.";
			link.l1.go = "CaptainComission_51";
		break;
		
		case "CaptainComission_51":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			dialog.text = "Ah... Tam anlamıyla yıkıldım... Bu nasıl oldu?";
			link.l1 = "Haydutlar fidyeyi beklemeden onu köleliğe sattılar. Onun peşinden Barbados'a gittim, ama onu kurtaramadım...";
			link.l1.go = "CaptainComission_52";
		break;
		
		case "CaptainComission_52":
			dialog.text = "Tanrım! Neler oluyor?\nPekâlâ, kaptan, katılımınız için teşekkürler. Ve lütfen, size verdiğim parayı geri verin.";
			link.l1 = "Masraflarım tüm beklentilerimi aştı, bu yüzden paranı kendime saklayacağım... Elveda.";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "Tabii, al... Sana yardım edemediğim için üzgünüm... Hoşça kal.";
				link.l2.go = "CaptainComission_54";
			}
		break;
		
		case "CaptainComission_53":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			OfficersReaction("bad");			
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_60":
			dialog.text = "Bu çok kötü. Gerçekten ne kadar kötü olduğunu bilmiyorsun...";
			link.l1 = "Bu konuda yapabileceğim bir şey yok. Hatta her şeyin böyle olmasına bile sevindim. Elveda.";
			link.l1.go = "CaptainComission_61";
		break;
		
		case "CaptainComission_61":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");			
			DialogExit();
		break;
		
		// диалог с рабом в колодках
		case "CaptainComission_70":
			dialog.text = "İç... Kaptan, biraz su getir...";
			link.l1 = "Hey, dostum, sen değil misin "+pchar.GenQuest.CaptainComission.SlaveName+"?";
			link.l1.go = "CaptainComission_71";
		break;
		
		case "CaptainComission_71":
			dialog.text = "Evet... Benim...";
			link.l1 = "Dinle! Eğer burada bir dil balığı gibi sığda can vermek istemiyorsan, kendine gel ve beni iyi dinle. Barbados Feneri'nin nerede olduğunu biliyor musun?";
			link.l1.go = "CaptainComission_72";
		break;
		
		case "CaptainComission_72":
			dialog.text = "Ben de...";
			link.l1 = "Fırsatını bulur bulmaz oraya kaç. Sana böyle bir fırsat ayarlamaya çalışacağım.";
			link.l1.go = "CaptainComission_73";			
		break;
		
		case "CaptainComission_73":	
			LAi_SetPlayerType(pchar); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);			
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);			
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}
						
			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);			
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		// диалог охранников раба
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("Sor bakalım kaptan, ama çabuk ol, görev başındayım.","Söyle, ama çabuk ol ve beni önemsiz şeylerle oyalama.");
			link.l1 = RandPhraseSimple("Bana belirli bir köleyi nasıl bulabileceğimi söyleyebilir misin? Adı "+pchar.GenQuest.CaptainComission.SlaveName+".","Bu plantasyonda bir yerde adı   olan bir köle olmalı"+pchar.GenQuest.CaptainComission.SlaveName+". Onunla nasıl konuşabileceğimi söyleyebilir misin?");
			link.l1.go = "CaptainComission_81";			
		break;
		
		case "CaptainComission_81":
			dialog.text = "Bugün ceza alıyor ve gözetim altında.";
			link.l1 = "Teşekkürler.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_85":
			dialog.text = "Teşekkür ederim... Kaptan, hayatımı kurtardınız...";
			link.l1 = "Barbados'taki deniz fenerine koş ve orada beni bekle.";
			link.l1.go = "CaptainComission_86";
		break;
		
		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;
		
		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Kaptan, size nasıl teşekkür edebilirim? Bu işkencenin sonunda bittiğine hâlâ inanamıyorum.";
				link.l1 = "Zaten akrabanız tarafından teşekkür edildim "+pchar.GenQuest.CaptainComission.Name+" from "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+". Onun talimatlarına göre hareket ediyorum.";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "Teşekkür ederim, kaptan. Kimin adına hareket ettiğinizi bilmiyorum ama kötü de olsa özgürlük, iyi bir kölelikten iyidir.";
				link.l1 = "Ne demek istiyorsun?";
				link.l1.go = "CaptainComission_92";
			}
		break;
		
		case "CaptainComission_91":
			dialog.text = "Eğer planlarını fazla bozmayacaksa, lütfen beni ona götür. Bütün bunlardan gerçekten çok yoruldum.";
			link.l1 = "Tabii ki yapacağım... eğer buradan sağ çıkarsak.";
			link.l1.go = "CaptainComission_91End";
		break;
		
		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_92":
			dialog.text = "Ve özgürlüğüm için para ödeyenlerin isimlerini öğrenebilir miyim?";
			link.l1 = "Aslında, bana ödeme yapmadılar. Bana başka seçenek bırakmadılar.";
			link.l1.go = "CaptainComission_93";
		break;
		
		case "CaptainComission_93":
			dialog.text = "Demek ki şüphelerimde haklıymışım. Bunu yapmaya seni zorlamışlar "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "Evet, öyle "+pchar.GenQuest.CaptainComission.Name+" den "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_94";
		break;		
		
		case "CaptainComission_94":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Sana ne vaat ettiklerini bilmiyorum, ama anlaşma şöyle: beni şu meyhaneye götür "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", orada gerçekten güvende olacağım. Karşılığında, sahip olduğum bazı bilgileri seninle paylaşacağım.";
			link.l1 = "Bu sorun değil, özellikle de şimdiye kadar hiçbir şey vaat etmedikleri için. Benimle gel, seni gemime götüreyim.";
			link.l1.go = "CaptainComission_95";
			link.l2 = "Kendimi şüpheli bir bilgi yüzünden belaya sokacak değilim.";
			link.l2.go = "CaptainComission_96";
		break;	
		
		case "CaptainComission_95":
		AddQuestRecord("CaptainComission1", "12"); // поставил запись в СЖ лесник
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_96":
			dialog.text = "Maalesef, bunu sana şu anda açıklayamam. Bu ikimiz için de sorun yaratabilir.";
			link.l1 = "Hele şimdi... Peşimden gel ve saçmalık etme, lütfen. Kendini bir kez daha tutuklu say.";
			link.l1.go = "CaptainComission_97";
		break;
		
		case "CaptainComission_97":	
            AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);		
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_100":		
			dialog.text = "Teşekkür ederim, kaptan. Artık nihayet güvendeyim. Sana para teklif etmiyorum, çünkü bilgi ve onu ustaca kullanmak, gelip geçici metallerden çok daha değerli.";
			link.l1 = "Bilgileri bekliyorum";
			link.l1.go = "CaptainComission_101";
		break;
		
		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "Şöyle ki, ben bir bilim insanıyım, uzmanlık alanım "+pchar.GenQuest.CaptainComission.SlaveSpeciality+" ve "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation))+" bana bir süredir işbirliği teklif ediyordu,"+"ama ben bir askeri mühendisim ve sadakat yeminlerime bağlı kalırım. Beni kaçırmaya kalktılar, ama asıl sorunlar korsanlar gerçek kimliğimi ve ne kadar önemli olduğumu öğrenince başladı\n"+"In the end, they managed to capture me, yet gold was all they wanted; they never needed my knowledge. My friends and enemies failed to ransom me in time, and I was sold to the plantations. You know the rest.";
			link.l1 = "Evet, akıllı olmanın da bir bedeli var, derler ya, gerçekten öyle.";	
			link.l1.go = "CaptainComission_102";
		break;
		
		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "protecting your ship and its crew during combat.";
				break;	
				case 1:
					sTemp = "quickly reloading your cannons and firing aimed shot under conditions of dusting. ";
				break;					
				case 2:
					sTemp = "quickly managing the sails and maneuvering in combat.";
				break;					
			}
			dialog.text = "Eh, öyle de denebilir. Yani, sana söylediklerime dikkat edersen, bu konuda çok daha yetkin olacaksın "+sTemp;
			link.l1 = "Teşekkür ederim, bu bilgi gerçekten çok faydalı oldu.";
			link.l1.go = "CaptainComission_103";
		break;
		
		case "CaptainComission_103":
			dialog.text = "Pekala, hoşça kal, her şey için teşekkürler.";
			link.l1 = "Ben de teşekkür ederim. Hoşça kal, bir dahaki sefere yakalanmamaya çalış.";
			link.l1.go = "CaptainComission_104";
		break;
		
		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// а теперь раздача слонов !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}					
				break;
				case 1:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}	
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Captain's request"
		
		// Генератор "Operation 'Galleon'"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //ПРАВКА
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));			
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();			
		break;
		
		// диалог с кэпом на палубе 
		case "CaptainComission_301":
		    if (!CheckAttribute(pchar,"GenQuest.pizdezh_uze_bil")) // проверка если разговор уже состоялся . чтобы не повторяться. лесник
			{
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("Selam, ben Kaptan "+GetFullName(NPChar)+", gemime neyin rüzgarı esti de güverteme çıktın '"+pchar.GenQuest.CaptainComission.ShipTypeName+"'?","Ah, gemimde misafir ağırlamaktan her zaman mutluluk duyarım. Kaptan "+GetFullName(NPChar)+" emrinizdeyim.");
			link.l1 = "Merhaba, ben kaptanım "+GetFullName(pchar)+", belli bir kaptanın adına hareket eden "+pchar.GenQuest.CaptainComission.CapName+".   Bana   seni   tutuklayacaklarını   söylememi   istedi   "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+". Yetkililer bundan haberdar "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+"."; // ПРАВКА + belamour gen
			link.l1.go = "CaptainComission_302";
			break;
			}
			dialog.text = "Ne halt ediyorsun burada? Her şeyi ayarladık! Gemiye geri dön!";
			link.l2 = "Uhh... Evet, tabii!";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_301"; // чтобы не было перехода на баг  - и т.д.  лесник 
			
		break;
		
		case "CaptainComission_302":
			dialog.text = "Ah, ne yazık! Bir düşüneyim\nPeki kaptan nerede "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "Öldü.";
			link.l1.go = "CaptainComission_303";
		break;
		
		case "CaptainComission_303":
			dialog.text = "Kahretsin! İşler daha da kötüye gidiyor... Dinle, "+GetFullName(pchar)+",   Böyle bir gelişmeyle yüzleşmeye hazır değilim, Kaptan "+pchar.GenQuest.CaptainComission.CapName+" ve ben  buluşmak için anlaştık "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+". Plan, gemiyi biraz yükleyecektik. Şimdi kaptan öldü, yerleşkeye gidemem\nGörünüşe göre senden bir iyilik istemekten başka çarem kalmadı.";
			link.l1 = "Onayım, ne tür bir yardıma ihtiyacın olduğuna bağlı.";
			link.l1.go = "CaptainComission_304";
		break;
		
		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Bana birkaç adam ve sandal bul. Yükün buradan götürülmesi gerekiyor "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+". Merhum kaptanın kargo payını kendine alabilirsin.";
			link.l1 = "Hmm... Görünüşe bakılırsa, boyundan büyük işlere kalkışmışsın. Daha fazla bilgiye ihtiyacım var.";
			link.l1.go = "CaptainComission_305";
			link.l2 = "Maalesef, bunun için zaman harcayacak durumda değilim.";
			link.l2.go = "CaptainComission_306";
		break;
		
		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Pekala, sana ayrıntıları vereceğim\n"+"Düzenli devriyelerimden birinde,   bayrağını taşıyan bir gemiyle karşılaştım "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+".   Emirlerimi teslim olmaları için görmezden geldiler."+"Kısa bir kovalamacadan sonra yetiştiğimizde "+sTemp+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"Ve böylece siyah bayrağı çektiler. Kale oldukça uzaktaydı, bu yüzden kendi başımıza savaşmak zorunda kaldık. Cib direğimizi parçaladılar, bu yüzden gemiye çıkmalarını engelleyemedik.\n"+"Az daha oluyordu, ama Kutsal Meryem’in yardımı ve bir grup misketçi sayesinde hepsini öldürmeyi başardık. Düşünsene, öğrendiğimizde nasıl sevindik "+sTemp+" ile doluydu. "+"Yaralarımız ve kaybettiğimiz yoldaşlarımız için bunun adil bir ödül olduğuna karar verdik\nHava çoktan kararmıştı, biz de aldık "+sTemp+" en yakın koya gidip yükü karaya sakladık. Sonra da patlattık "+sTemp+" ve batmış korsan gemisini bildirdim. Tabii ki, yükten hiç bahsetmedim.";
			link.l1 = "Görünüşe bakılırsa, birisi yine de ağzından kaçırmış...";	
			link.l1.go = "CaptainComission_307";
		break;
		
		case "CaptainComission_306":
			dialog.text = "Yazık kaptan... Yardım etmeye istekli olmamanız gerçekten üzücü.";
			link.l1 = "Bu benim isteğimle alakalı bir şey değil, canım. Anlamalısın. Elveda.";
			link.l1.go = "CaptainComission_306End";			
		break;
		
		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);			
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;
		
		case "CaptainComission_307":
			dialog.text = "Bence adamlarım değildi. Büyük ihtimalle, kargonun sahibi kaybının acısını hafifletmek istiyor\nEe? Yardımına güvenebilir miyim?";
			link.l1 = "Evet, kulağa iyi geliyor.";
			link.l1.go = "CaptainComission_308";
			link.l2 = "Hayır, dostum. Birincisi: Ne kadar yükün ambarıma gireceğini bilmiyorum. İkincisi: Yetkililerin onu bulup götürmediğine ve saklandığı yere pusu kurmadığına dair hiçbir garanti yok.";
			link.l2.go = "CaptainComission_309";
		break;
		
		case "CaptainComission_308":
			dialog.text = "Şurada buluşalım "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+" o zaman, tam gece yarısından sonra. Şu anki konumum gizlilik gerektiriyor. Devriyelerden uzak durmalıyız."; // belamour gen
			link.l1 = "Pekala, orada beni bekle.";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;
		
		case "CaptainComission_309":
			dialog.text = "Yazık, ama bana başka seçenek bırakmıyorsun. Tek bir gemi tüm yükü almak için yeterli değil. Bunun için hem kariyerimi hem de hayatımı riske attım. Eminim, mürettebatın da güzel bir pay karşılığında bana yardım etmekten memnuniyet duyar.";
			link.l1 = "Ve ne öneriyorsun?";
			link.l1.go = "CaptainComission_310";
		break;
		
		case "CaptainComission_310":
			dialog.text = "Gemini alıp seni burada bırakacağım "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+"."; // belamour gen
			link.l1 = "Başarılı olacağınızı pek sanmıyorum. Gerekirse tüm tayfanızı doğrasam da gemime dönerim.";
			link.l1.go = "CaptainComission_311";
			link.l2 = "Görünüşe bakılırsa başka seçeneğim yok. Pekâlâ, şiddete boyun eğeceğim...";
			link.l2.go = "CaptainComission_312";
		break;
		
		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //после резни на палубе - драка в море		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;
		
		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;
		
		case "CaptainComission_313": 		
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
		    pchar.GenQuest.pizdezh_uze_bil = "true"; // лесник временная запоминалка для диалога 
			DialogExit();			
		break;
		
		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "Kaptan, acele etmeliyiz. Bir devriyenin bizi fark etmesinden korkuyorum.";
			link.l1 = "Pekala, hadi acele edelim.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_315":
			dialog.text = "Kaptan, tüm filikaların denize indirilmesini emredin. Birkaç sefer yapmamız gerekecek, ve korkarım ki bir devriye koya gelebilir. ";
			link.l1 = "Endişelenme, her şey yolunda olacak. Sandallar zaten kıyıya yanaşıyor.";
			link.l1.go = "CaptainComission_316";
		break;
		
		case "CaptainComission_316":
			dialog.text = "Ah, kahretsin. Şimdi de misafirimiz var...";
			link.l1 = "Gerçekten, bir aptaldan bahsedersen hemen ortaya çıkar...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.pizdezh_uze_bil"); // удаление проверки на повтор диалога лесник
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;
		
		// диалог с патрулем на берегу
		case "CaptainComission_317":
			dialog.text = "Kaptan, bir savaş suçlusunu arıyoruz "+pchar.GenQuest.CaptainComission.Name+", yetkililerden değerli bir yükü gizlemiş olan. Belgelerinizi lütfen.";
			link.l1 = "Hangi belgeler, memur? Taze su stoğumuzu yenilemek için karaya çıktık.";
			link.l1.go = "CaptainComission_318";
		break;
		
		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004"; 
			dialog.text = "Ve işte burada, "+pchar.GenQuest.CaptainComission.Name+" kendin. Silahlarını teslim et ve ikiniz de beni takip edin!";
			link.l1 = "Bu gerçekten çok kötü bir zamandı, memur...";
			link.l1.go = "CaptainComission_319";
		break;
		
		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetHearRadius("CoastalGuards", 100.0);			
		    sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);		
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
				
		break;
		
		case "CaptainComission_320":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие если жив.
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));	
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "Takviye kuvvetler gelmeden acele etmeliyiz. Yükleme neredeyse bitti, ve senin payın "+pchar.GenQuest.CaptainComission.GoodsQty+" birim "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+".";
			link.l1 = "Mükemmel. Artık gitme zamanı. Seninle iş yapmak bir zevkti.";
			link.l1.go = "CaptainComission_321";
		break;
		
		case "CaptainComission_321":		
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "Ve sadece bir ricam daha var. Yetkililer peşimize düşecek, gemime eşlik edebilir misin lütfen "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+", şu anda "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+"?"; // belamour gen
			link.l1 = "Hayır dostum, bundan sonra herkes kendi başının çaresine bakacak. Elveda...";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "Elbette, iyi bir ödül karşılığında bunu yapabilirim.";
				link.l2.go = "CaptainComission_323";
			}				
		break;
		
		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0; 	
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;
		
		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + hRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Elbette. Eşlik etmeniz için size ödemeye hazırım  "+pchar.GenQuest.CaptainComission.ConvoyMoney+" peso. Ama bir şartım daha var: bu iş en fazla "+pchar.GenQuest.CaptainComission.iDay+" gün. Bu önemli.";	
			link.l1 = "Anlaştık. Hemen yola çıkalım.";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));		
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter"; 
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;
		
		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("Kaptan, zaman kaybediyoruz. Bizi her an bulabilirler.","Kaptan, zamana karşı yarışıyoruz. Beni aradıklarını unutma.","Kaptan, oyalanmamalıyız. Gemim devriyenin dikkatini çekmeyecek kadar küçük değil.");
			link.l1 = LinkRandPhrase("Evet, haklısın. Acele etmeliyiz.","O halde daha fazla oyalanmadan sandallara binin.","Bu kadar... Adamlarını topla. Gidiyoruz.");
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_326_0":
			dialog.text = "Kaptan, adamlarımla konuşmam gerek.";
			link.l1 = "Devam et.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "Sizi selamlıyorum, Kaptan "+pchar.CaptainComission.Name+" . Peki, tüm yükü getirdin mi? Peki kaptan nerede "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" öldü. Sormak zorunda kaldım "+NPCharSexPhrase(sld,"bu beyefendi","bu hanım")+" yardım için. Seni tanıştıracağım. Bu Kaptan "+pchar.CaptainComission.FullName+".";
			link.l1.go = "CaptainComission_327";
		break;
		
		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "Ve "+NPCharSexPhrase(sld,"Kim o? O mu","O kim? O mu")+" işlerimizden haberdar mı? ";
			link.l1 = "Genellikle evet. Ama bir sorun var -"+NPCharSexPhrase(sld,"emin","emin")+", yükün yarısının ona ait olduğunu "+NPCharSexPhrase(sld,"onu","onu")+". İkna etmeliyiz "+NPCharSexPhrase(sld,"onu","onu")+", bunun tam olarak böyle olmadığını.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;
		
		case "CaptainComission_328":
			dialog.text = "Arkadaşım "+GetFullName(pchar)+", zaten bilmen gereken her şeyi duydun. Ambarına girmemiz gerekiyor.";
			link.l1 = "Ve sen gerçekten adamlarımın, bir avuç serserinin ambarlarını boşaltmasını öylece izleyeceğini mi sanıyorsun?";
			link.l1.go = "CaptainComission_329";
		break;
		
		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "Doğru söylüyorsun. Diyelim ki, şu kadar nakit para: "+pchar.GenQuest.CaptainComission.GoodsSum+" peso, bize senin tayfanla çatışmaya girmemize gerek bırakmaz. Unutma, bu miktar yükümüzün yarısını kapsıyor, yani her şey adil. Eğer kabul edersen, kimse zarar görmez.";
			link.l1 = "Ya reddedersem ne olacak?";
			link.l1.go = "CaptainComission_330";
		break;
		
		case "CaptainComission_330":
			dialog.text = "Öyleyse, şiddet kaçınılmaz. İlk kurban sen olacaksın ve huzuru bu tenha koyda bulacaksın, tayfan ise sana yardım edemeyecek... Bu hoşuna gider miydi?";
			link.l1 = "Bana başka seçenek bırakmıyorsun. Peki, o zaman hepinizi öldüreceğim.";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "Sanırım başka seçeneğim yok. Peki, al paranı.";
				link.l2.go = "CaptainComission_332";
			}	
		break;
		
		case "CaptainComission_331":
			dialog.text = "Pekala, bu karar tam da sana göre olmuş "+GetSexPhrase("asil bir beyefendi","cesur bir hanımefendi")+".";
			link.l1 = "Felsefe yapmayı bırak! Hadi işe koyulalım!";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;
		
		case "CaptainComission_332":
			dialog.text = "Akıllıca bir karar. Sana bol şans diliyorum.";
			link.l1 = "Boğazında kalsın...";
			link.l1.go = "CaptainComission_333";
		break;
		
		case "CaptainComission_333":
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// лесник - разрешить снова драться после сдачи денег. но после драки кулаками не машут ..как говориться))
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;

		case "CaptainComission_340":
			dialog.text = "Kaptan "+GetFullName(pchar)+", geç kaldık. Artık ödül almaya hak kazanmadığını umarım anlıyorsun.";
			link.l1 = "Elbette biliyorum. Senin sayende iyi para kazandım zaten. Hoşça kal...";
			link.l1.go = "CaptainComission_341";
		break;
		
		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");			
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");					
			DialogExit();
		break;
		
		case "CaptainComission_Canoneer":
			dialog.text = "Taç'ın şanı uğruna savaşlarda çok acı çekmiş yaşlı bir askere biraz rom alır mıydın?";
			link.l1 = "Barmen! Bize biraz rom doldur!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;
		
		case "CaptainComission_Canoneer1":
			dialog.text = "Oh, teşekkür ederim, "+GetAddress_Form(pchar)+", hafızasını tamamen kaybetmiş bir sakata yardım etmen gerçekten çok nazikçe...";
			link.l1 = "Tamamen mi diyorsun?";
			link.l1.go = "CaptainComission_Canoneer2";
		break;
		
		case "CaptainComission_Canoneer2":
			dialog.text = "Elbette, hanımefendi"+GetSexPhrase("ter","s")+" kaptan... tamamen. Kafama doğru uçan bir kartuş mermisinden başka hiçbir şey hatırlamıyorum. Bak ne delik açmış, sanırım bütün hafızam oradan dışarı akıp gitmiş.";
			link.l1 = "Dostum, zavallı hikayelerini ev kadınlarına sakla. Üzüm mermisiyle doğrudan vurulanları gördüm, anıları kafalarıyla birlikte silinip gitmişti... Ve sen burada, hayali bir zincir gülle anlatıyorsun. Gel kaptandan konuşalım "+pchar.GenQuest.CaptainComission.Name+". ";
			link.l1.go = "CaptainComission_Canoneer3";
		break;
		
		case "CaptainComission_Canoneer3":
			dialog.text = "Eh, işte, biliyorsun. Bir şekilde geçimimi sağlamam lazım. Kaptana gelince "+pchar.GenQuest.CaptainComission.Name+", onun hakkında konuşmak bana bir kazanç getirmez... Eğer her soru için yüz altın alsaydım, şimdiye kadar valinin bir yılda topladığından daha fazla altınım olurdu... ";
			link.l1 = "O kaptanın sakladığı yükü satmayı denedin mi?";
			link.l1.go = "CaptainComission_Canoneer4";
		break;
		
		case "CaptainComission_Canoneer4":
			dialog.text = "Ne? Yine mi bir dedektif? Sana bir kez daha söylüyorum, hiçbir kaptanı hatırlamıyorum "+pchar.GenQuest.CaptainComission.Name+"! Kafam karışık, hem de doktor raporum var! Daha ne istiyorsun?!";
			link.l1 = "Hey, bu kadar heyecanlanma. Biliyorsun... Çok geç kalmıştı. Kaptan "+pchar.GenQuest.CaptainComission.CapName+"   bana söylememi istedi   "+pchar.GenQuest.CaptainComission.Name+" o yerleşimde yüzünü göstermemeli, yetkililer   yıkımın koşullarını biliyorlar "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Acc"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+", ve tutuklanacak.";
			link.l1.go = "CaptainComission_Canoneer5";
		break;
		
		case "CaptainComission_Canoneer5":
			dialog.text = "Of, bunu baştan söyleseydin ya, lafı dolandıracağına. Kaptana soran bendim "+pchar.GenQuest.CaptainComission.CapName+" gemimizi dönüşünde pusuya düşürmek için. "+"O kanlı dövüşten hemen sonra mallar iskeleye taşındı. O lanet korsan orada mallarıyla ne yapıyordu ki?! Onun yüzünden kaç adam öldü.";
			link.l1 = "Peki nasıl hayatta kalmayı başardın?";
			link.l1.go = "CaptainComission_Canoneer6";	
		break;
		
		case "CaptainComission_Canoneer6":
			dialog.text = "Yanlışlıkla. Açıkçası, kendi aptal hatam yüzünden. Yeterince hızlı olamadım, bu yüzden sandalımız tehlikeli bölgeden çıkamadı. Yalnızca ben zarar gördüm. Enkazdan biri bana çarptı ve suya fırladım. Kıyıya nasıl ulaştığımı bile hatırlamıyorum.";
			link.l1 = "Soruşturmadan nasıl sıyrılmayı başardın?";
			link.l1.go = "CaptainComission_Canoneer7";
		break;
		
		case "CaptainComission_Canoneer7":
			dialog.text = "Onlara, gemiye çıkarken yaralandığımı ve yük hakkında hiçbir şey bilmediğimi söyledim. Bir de aklım başımda değilmiş gibi davrandım, hani daha yeni toparlanmıştım ya, tam onların gelişi öncesinde "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+". Doğru düzgün hareket edemedim, bütün dengem bozulmuştu.";
			link.l1 = "Hey, ama kargo hakkındaki sırrı kim ortaya çıkardı, ha?";
			link.l1.go = "CaptainComission_Canoneer8";
		break;
		
		case "CaptainComission_Canoneer8":
			dialog.text = "Korsanlar, yaralanan tüccarın adına sözde valiğe bir mektup göndermişler. Kaptanın inatçılığı yüzünden ona kin güttüler. Bizi bu belanın içine sokan onun suçu, lanet olası dikbaşlılığıydı.";
			link.l1 = "Ama o korsanla ilk başta nasıl karşılaştın?";
			link.l1.go = "CaptainComission_Canoneer9";
		break;
		
		case "CaptainComission_Canoneer9":
			dialog.text = "Bilmiyorum. Sıradan bir devriye göreviydi, ve sıradan bir gemi   bayrağı altında seyrediyordu "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". Kaptanın neden onu incelemeye karar verdiği hakkında hiçbir fikrim yok, ama uyarı atışına aldırış etmediler ve onlara yetiştiğimizde, 'Jolly Roger' bayrağını çektiler. "+"Kalenin desteği yoktu, bu yüzden savaş kolay olmadı. Sonra gemiye çıktılar. Hâlâ onları nasıl yendiğimizi bilmiyorum.\n"+"Pekâlâ, o değerli yükün hepsini gördük. Bunu bize bizzat şeytan vermiş olmalı. Yükü karaya gizlemek ve ele geçirdiğimiz gemiyi havaya uçurmak zorunda kaldık. Geminin hasarı çok fazlaydı.";
			link.l1 = "Valinin adamları gizli yeri bulursa, bunca çaban ve fedakârlığın boşa gideceğinden korkmuyor musun?";	
			link.l1.go = "CaptainComission_Canoneer10";
		break;
		
		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;			
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "They won't find it. I blasted the cave's entrance well; after all, I was the best explosives expert in the whole squadron. Only smugglers can find my stash, they know every inch of this place.\n"+"Look, I myself have no clue what to do with the booty. I can't sell it or move it away on my own. Besides, no one will do business with a cracked skull. I don't want to profit from the deaths of my crew mates, but I can tell you the location of the stash for "+pchar.GenQuest.CaptainComission.Sum+"  pesos if you take me to "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.CanoneerCity)+".";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				link.l1 = "Katılıyorum. Al paranı. Şimdi konuş.";	
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "Lanet olsun! Tamam, burada bekle, parayı getireceğim.";
				link.l1.go = "CaptainComission_Canoneer12";				
			}	
			link.l2 = "Bu fazla, dostum. Ayrıca, uygun bir gemim de yok. Neyse, sana bol şans ve hoşça kal...";
			link.l2.go = "CaptainComission_Canoneer13";
		break;
		
		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Pekâlâ, bu gece yarısından sonra benimle burada buluş. "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+". Ve ambarında yer olduğundan emin ol "+pchar.GenQuest.CaptainComission.GoodsQty+" pcs. "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Bunu çöpe atmak yazık olurdu..."; // belamour gen
			link.l1 = "Onunla ben ilgilenirim. Koyda görüşürüz...";
			link.l1.go = "CaptainComission_Canoneer14";
		break;
		
		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //Gen лесник
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));	// belamour gen
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				dialog.text = "Ve işte sonunda geldin. Başlamıştım endişelenmeye. Beni yetkililere teslim edeceksin sanmıştım.";
				link.l1 = "Henüz delirmedim. Al paranı. Şimdi sıra sende.";
				pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";// лесник . снят таймер ожилания бабла
				link.l1.go = "CaptainComission_Canoneer11";
			}	
			else
			{
				dialog.text = "Peki, para nerede?";	
				link.l1 = "Lanet olsun! Tamam, burada bekle, onu getireceğim.";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;
		
		case "CaptainComission_350":
			dialog.text = "Kaptan, galiba geç kaldık. Kaçakçılar zaten gizli yeri bulmuşlar.";
			link.l1 = "Ganimetimi vermeyeceğim, şeytan bile elimden alamaz.";
			link.l1.go = "CaptainComission_351";
			link.l2 = "Bırakıyorum, rakiplerinle kendin uğraş.";	
			link.l2.go = "CaptainComission_352";
		break;
		
		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;
		
		case "CaptainComission_352":
			DialogExit();
			//SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
			 AddDialogExitQuestFunction("CaptainComission_NoGangDialog");   // лесник - исправлено . предыдцщий код не работал
		break;
		
		case "CaptainComission_360":
			dialog.text = "Kaptan, burada ciddi bir mesele var. Size tavsiyem, filonuzu bizim gemilerimiz gelmeden önce buradan götürmeniz.";
			link.l1 = "Beyler, galiba size ait olmayan bir şeyi almaya çalışıyorsunuz.";
			link.l1.go = "CaptainComission_361";
		break;
		
		case "CaptainComission_361":
			dialog.text = "Gerçekten mi?! Kiminle konuştuğunun farkında mısın?";
			link.l1 = "Seninle konuşuyorum, dostum. O yükün haklı bir sahibi var ve ben onu temsil ediyorum.";
			link.l1.go = "CaptainComission_362";
		break;
		
		case "CaptainComission_362":
			dialog.text = "İşlerimize karışmana izin vermeyiz, Tanrı'nın Mesihi olsan bile! Canını düşünüyorsan yolumuzu aç!";
			link.l1 = "Ben kendimi yeterince açık ifade etmedim mi? O yük benim, ve onsuz buradan ayrılmam!";
			link.l1.go = "CaptainComission_363";
		break;
		
		case "CaptainComission_363":
			dialog.text = "Ne hali varsa görsün! Eğer o kadar istiyorsan, burada sonsuza kadar bekleyeceksin!";
			link.l1 = "Kader, burada sonsuza dek kimin kalacağına karar verecek.";
			link.l1.go = "CaptainComission_364";
		break;
				
		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);						
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				//LAi_SetWarriorType(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);			
			}	
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_365":
			dialog.text = "Kaptan, adamlarınıza acele etmelerini söyleyin, devriye her an gelebilir. Ayrıca, kaçakçılar da belli ki kendi nakliyelerini bekliyorlardı.";
			link.l1 = "Evet, acele etmemiz lazım... Yükü ambarlara taşıyın, sonra buradan defolup gidelim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_366":
			dialog.text = "Teşekkür ederim, kaptan "+GetFullName(pchar)+". Eğer sen olmasaydın, kaçakçılar yükümüzü alırdı ve onu savunurken düşen adamlar boşuna ölmüş olurdu...";
			link.l1 = "Ve bana güvendiğin için teşekkür ederim.";
			link.l1.go = "CaptainComission_367";
		break;
		
		case "CaptainComission_367":
			dialog.text = "Burada bir tılsımım var, ona hayatımı borçluyum. Lütfen, bunu kabul et, belki sana da uğur getirir. Ve tekrar teşekkür ederim, dostum. Rüzgarlar hep arkanda olsun.";
			link.l1 = "Hediye için teşekkür ederim, beklemiyordum. Ve cebinde hâlâ birkaç kuruşun varken sağlığına dikkat etsen iyi edersin.";
			link.l1.go = "CaptainComission_368";
		break;
		
		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}	
			dialog.text = "Anlaşılan bugün ziyaret günüm. Bana ihtiyacın var mı?";
			link.l1 = "Eğer kaptan sensen "+pchar.GenQuest.CaptainComission.Name+", o zaman evet.";
			link.l1.go = "CaptainComission_371";
		break;
		
		case "CaptainComission_371":
			dialog.text = "...eski kaptan"+pchar.GenQuest.CaptainComission.Name+"...";
			link.l1 = "Ben "+GetFullName(pchar)+", ve sana birkaç sorum var.";
			link.l1.go = "CaptainComission_372";
		break;
		
		case "CaptainComission_372":
			dialog.text = "Peki, neden onlara cevap vereceğimi düşünüyorsun?";
			link.l1 = "Kaptan "+pchar.GenQuest.CaptainComission.CapName+"  bana   söyledi,   seni   uyarayım   diye:   yok oluşun   etrafındaki   koşullar   hakkında  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Acc"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+" yetkililerin kulağına gitti, "+"ama yolculuk sırasında gemini görmedim "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+".";
			link.l1.go = "CaptainComission_373";	
		break;
		
		case "CaptainComission_373":
			dialog.text = "Ve kaptan nerede "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "Öldü.";
			link.l1.go = "CaptainComission_374";
		break;
		
		case "CaptainComission_374":
			dialog.text = "Demek öyle... Yani mesele buymuş, ha? Şimdi birçok şey yerli yerine oturuyor. Demek birisi bizim yağma yaptığımızı ağzından kaçırmış "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+". "+"Er ya da geç, yükü bulacaklar ve beni asacaklar. Kaptan "+pchar.GenQuest.CaptainComission.CapName+" öldü, demek ki bana kimse yardım edemez\nSenden başka\n "+GetFullName(pchar)+", beni buradan çıkar, sana karşılığını fazlasıyla veririm.";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "Valinin eline yükün sahibinden bir mesaj ulaştı. Ve içindeki rakamlar oldukça etkileyici, biliyor musun.";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "Ama herhalde sana gözlerim kapalı yardım edeceğimi düşünmüyorsun, değil mi?";
					link.l1.go = "CaptainComission_375";
				}
			}			
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "Vali, yükün sahibinden bir mesaj aldı. Ve içindeki rakamlar oldukça etkileyici, biliyor musun.";
					link.l1.go = "CaptainComission_375";				
				}
				else
				{
					link.l1 = "Sömürgede kaçakçılarla iş birliği yaptığınıza dair söylentiler dolaşıyor...";
					link.l1.go = "CaptainComission_375";				
				}
			}
		break;
		
		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Sana bütün hikayeyi anlatmam gerekecek gibi görünüyor.\n"+"Düzenli devriyelerimden birinde, bayrağını taşıyan bir gemiyle karşılaştım "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". Teslim olmaları için verdiğim emirleri umursamadılar. "+"Varmıştık "+sTemp+" '"+pchar.GenQuest.CaptainComission.VictimShipName+" Kısa bir kovalamacadan sonra siyah bayrağı çektiler. Kale oldukça uzaktaydı, bu yüzden kendi başımıza savaşmak zorunda kaldık. Cib bumumuzu parçaladılar, bu yüzden aborda olmaktan kaçamadık.\n"+"Az kalsın kaybediyorduk, ama Kutsal Meryem'in yardımı ve bir grup tüfekçi sayesinde hepsini öldürmeyi başardık. Bir de öğrendiğimizdeki sevincimizi düşün, "+sTemp+" değerli eşyalarla doluydu. "+"Yaralarımız ve adamlarımızın ölümü için bunun adil bir ödül olduğuna karar verdik\nHava çoktan kararmıştı, ama almayı başardık "+sTemp+" en yakın koyda karaya çıkarıp yükü sakladık. Sonra da yaktık "+sTemp+" ve batmış bir korsan gemisi bildirdim. Tabii ki yükten bahsetmedim.";		
			link.l1 = "Bence beni kandırmanın bir anlamı yok. Bu yüzden bir anlaşma öneriyorum: bana gizli yeri göster, ben de seni takımadada istediğin yere götüreyim.";
			link.l1.go = "CaptainComission_376";
		break;
		
		case "CaptainComission_376":
			dialog.text = "Ha-ha-ha... Hayır kaptan, payımı almadan buradan ayrılmam, gerekirse darağacında sallanırım.";
			link.l1 = "Pekala. Payının yarısını alacaksın.";
			link.l1.go = "CaptainComission_377";
			link.l2 = "Hmm... Biliyor musun, senin iyiliğin için boynumu riske atmaya niyetim yok. Hoşça kal...";
			link.l2.go = "CaptainComission_378";
		break;
		
		case "CaptainComission_377":
			dialog.text = "İşte şimdi konuşuyorsun. Hazırım\nÖnce beni gemine saklamalısın. Saklanmış ganimetin olduğu körfezi sana göstereceğim.";
			link.l1 = "O zaman hızlı ve uyum içinde hareket edelim. Hücreni açacağım, sen de beni takip et. Geri kalma ve kaleden çıkana kadar soru sorma.";
			link.l1.go = "CaptainComission_379";
		break;
		
		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(npchar);// лесник - запрет диалога
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood") 
			{
				chrDisableReloadToLocation = true;	
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");	
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}	
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison"; 
			DialogExit();
		break;		
		
		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Kurtardığın için sağ ol. Hadi devam edelim "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Dat")+", sana malın yerini göstereceğim. Vahşiler bulmadan önce acele etmeliyiz.";	// belamour gen	
			link.l1 = "Tüm yükü alabileceğimizden emin misin?";
			link.l1.go = "CaptainComission_381";
		break;
		
		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Haklısın, yeterince yerin olduğundan emin ol "+pchar.GenQuest.CaptainComission.GoodsQty+" parça "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+".   Bu kadar kan dökülmüş değerli ganimeti kaybetmek yazık olurdu.   Bize ikinci bir şans vermeyecekler.";
			link.l1 = "Onunla ben ilgilenirim.";
			link.l1.go = "CaptainComission_382";
		break;
		
		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false); 
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // Откроем выход
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "CaptainComission_383":
			dialog.text = "Kaptan, şahitlere ihtiyacımız yok. Lütfen, bu insanları koydan ayrılmaya ikna etmeye çalış.";
			link.l1 = "Pekâlâ, öyle yapalım.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;
		
		case "CaptainComission_384":
			dialog.text = "Kaptan, üzgünüm ama burası alıştırmalarınız için en uygun yer değil. O iskele zaten dolu.";
			link.l1 = "Beyler, buraya gezmeye gelmedim. Burada işim var.";
			link.l1.go = "CaptainComission_385";
		break;
		
		case "CaptainComission_385":
			dialog.text = "Pekâlâ, burada da denizanası avlamıyoruz, o yüzden gemilerinizi çevirin ve defolup gidin buradan.";
			link.l1 = "Zamanımı seni gitmeye ikna etmekle harcamak istemiyorum. Ya isteyerek gidersin ve yaşarsın, ya da burada kalırsın sonsuza dek.";
			link.l1.go = "CaptainComission_386";
		break;
		
		case "CaptainComission_386":
			dialog.text = "Sözlerimi anlamakta zorlandığını görüyorum. Peki, bu senin sonun olur...";
			link.l1 = "Bu daha iyi!";
			link.l1.go = "CaptainComission_364";
		break;
		
		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "Buradayız. Kasa o kayalıktaki bir oyukta. Girişi kayalar kapatıyor. Kasanın içinde ise "+pchar.GenQuest.CaptainComission.GoodsQty+" birim "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+" . Unutma, bunun yarısı benim, değil mi?";
			link.l1 = "Elbette biliyorum. Adamlarım malları yüklerken biraz vaktimiz var. Sizi ve yükünüzü nereye götürmemiz gerektiğini konuşalım.";
			link.l1.go = "CaptainComission_388";
			if (!CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{	
			link.l2 = "Çok güzel. Şimdi söyle bakalım, bunu paylaşmam için bir sebep var mı?";
			link.l2.go = "CaptainComission_389";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = "Kaptan "+pchar.GenQuest.CaptainComission.Name+", Sana söylemem gereken tatsız bir şey var. Vali için çalışıyorum. Ve sakladığın tüm yükü ona teslim etmeye niyetliyim. Hapishaneye dönüp orada kaderini beklemelisin.";
				link.l3.go = "CaptainComission_389";
				link.l2 = "Çok iyi. Ama işin aslı şu... Başta seni yetkililere teslim etmek istiyordum, ama şimdi neden böyle bir şey yapayım? Ve neden seninle paylaşayım?";
			    link.l2.go = "CaptainComission_3899"; // // лесник . отдельный диалог в случае обмана всех.
			}	
		break;
		
		case "CaptainComission_388":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;			
			pchar.GenQuest.CaptainComission.iDay  = 20 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Gitmem gerekiyor "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+", at "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+" için "+pchar.GenQuest.CaptainComission.iDay+" gün. Oradaki adamlarım muhtemelen yükü satmaya hazırlamış olmalı."; // belamour gen
			link.l1 = "Pekala. O zaman gitme vakti geldi.";
			link.l1.go = "CaptainComission_391";
		break;
		case "CaptainComission_3899": // лесник . отдельный диалог в случае обмана всех.
		    DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Doğru. Her zaman kalpten ziyade akla güvenmeli. Yaşa ve öğren.\nBunu beklememiş olsam da, her zaman bir kavgaya hazırım. İhanetinin bedelini ödeyeceksin.";
			link.l1 = "Eh, şansın varsa...";
			link.l1.go = "CaptainComission_390";
			SetFunctionTimerConditionParam("CaptainComission_NaebalGubera", 0, 0, 1, MakeInt(24 - GetHour()), false);
		break;
		
		case "CaptainComission_389":
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Doğru. Her zaman kalbe değil, akla güvenmek gerekir. Yaşa ve öğren\nHer ne kadar bunu beklemesem de, her zaman bir kavgaya hazırım. İhanetinin hesabını vereceksin.";
			link.l1 = "Emrinizdeyim...";
			link.l1.go = "CaptainComission_390";
		break;
		
		
		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_SetImmortal(rChar, false);// лесник.  
			LAi_group_MoveCharacter(rChar, "EnemyFight");		
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 			
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))AddQuestRecord("CaptainComission2", "53");// лесник. выбор записи в СЖ
			else AddQuestRecord("CaptainComission2", "26");// смотря по какому пути пошел 
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Gen")); // belamour gen
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");	
			DialogExit();
		break;
		
		case "CaptainComission_392":
			dialog.text = "Görünüşe bakılırsa, geç kaldık... Müşteriler beklemedi ve yükün depolanmasıyla satışıyla kendim ilgilenmemin bir yolu yok...";
			link.l1 = "Bu konuda özel bir önerin var mı?";
			link.l1.go = "CaptainComission_393";
		break;
		
		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Kaptan "+GetFullName(pchar)+", biliyorum biraz garip olacak ama... payıma düşen parayı nakit olarak alabilir miyim? Sanırım, "+pchar.GenQuest.CaptainComission.GoodsPrice+" peso iyi bir uzlaşma olabilir.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "Evet, bu adil bir fiyat. Sorun değil. Al paranı, hoşça kal.";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "Ah, hayır dostum, bu böyle olmaz. Seni sonsuza kadar kollayamam. Eğer yükünü almak istemiyorsan, onu kendime saklarım. Merak etme, bir yolunu bulur, depolar ve sonunda satarım.";
			link.l2.go = "CaptainComission_3951";
		break;
		
		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "Bir dakika, kaptan. Beni kurtardığın için sana teşekkür etmek istiyorum. Biliyor musun, neredeyse umudumu kaybetmiştim... Al, eminim bu küçük eşyayı birçok zor durumda faydalı bulacaksın... Şimdi hoşça kal.";
			link.l1 = "Teşekkürler. Bunu beklemiyordum. Seninle iş yapmak güzeldi.";
			link.l1.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_3951": // лесник . верное назначение диалога
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes";
			dialog.text = "Bunu senden beklemezdim... Görünen o ki, seni düelloya davet etmekten başka çarem yok.";
			link.l1 = "Emrinizdeyim...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;
		
		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");	
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "Kaptan, adamlarımla konuşmam gerek.";
			link.l1 = "Devam et.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "Sizi selamlıyorum, Kaptan "+GetFullName(pchar)+" . Peki, tüm yükü getirdin mi? Peki kaptan nerede "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" öldü, ben ise bir ihbar yüzünden tutuklandım. Ve eğer kaptan "+pchar.CaptainComission.FullName+" bana yardım etmeseydin, beni de yükü de göremezdin.";
			link.l1.go = "CaptainComission_397";
		break;
		
		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "Ve "+NPCharSexPhrase(sld,"O kim? O mu","Kim o? O mu")+" işlerimizden haberdar mısın?";
			link.l1 = "Elbette. "+NPCharSexPhrase(sld,"O çıkardı","O çıkardı")+" me from the jail and undertook to deliver half of the cargo here; the other half I promised "+ NPCharSexPhrase(sld, "him","her") +" as a compensation.";
			link.l1.go = "CaptainComission_398";
		break;
		
		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "Eh, kaptan, yok artık. Bu senin derdin! Gemiyi alıp gitmeyi önerdim, ama sen lanet kariyerini fazla önemsiyordun. Ve işte buradasın, o çok sevdiğin vali seni zindana tıktı."+" Payımız yarıdan çok daha azdı! Biz canımızı misket topu altında tehlikeye atmadık ki sen yarısını kendine alasın!";
			link.l1 = "Dinle, lostromos, geminin tamamen mahvolduğunu hatırlamıyor musun? Neredeyse suya gömülmüştü. Anlamıyor musun, eğer bu adama yarısını vermeseydim, sen o yükten bir parça bile göremezdin bir daha?";	
			link.l1.go = "CaptainComission_399";
		break;
		
		case "CaptainComission_399":
			dialog.text = "Beni kandıramazsın! Senin onlarla işbirliği yapmadığını nereden bilebiliriz? Ya aslında hiç tutuklama olmadıysa? Ya sadece fazla açgözlü olup eşyalarımızı çalmaya karar verdiysen? Yoksa kılıç kullanmayı unuttuğumuzu mu sanıyorsun?!";
			link.l1 = "Sen delirmişsin. Kulaklarında sadece paraların şıngırtısını duyuyorsun.";
			link.l1.go = "CaptainComission_400";
		break;
		
		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "Oğlanlar! Kaptanımızın şimdi nasıl konuştuğuna bakın! Açgözlülük onu tamamen ele geçirmiş! Payımızı sattı "+NPCharSexPhrase(sld,"bir serseri","bir maceraperest kadın")+"!!";
			link.l1 = "Şimdi o pis ağzını kapa, yoksa sonsuza kadar sustururum seni!";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;
		
		case "CaptainComission_401":
			dialog.text = "Üzgünüm kaptan, bu saçma sahneye tanık olmak ve hatta katılmak zorunda kaldığınız için. Bundan sadece bir ay önce birleşmiş bir tayfa olduğumuza ve her birimizin bir arkadaşını kurtarmak için seve seve canını vereceğine inanmak zor.";
			link.l1 = "İtiraf etmeliyim ki, bunu hayal edemiyorum, alınma lütfen.";
			link.l1.go = "CaptainComission_402";
		break;
		
		case "CaptainComission_402":
			dialog.text = "Ne yazık ki, yükün depolanmasını ve satışını kendi başıma organize etme imkanım yok...";
			link.l1 = "Bu konuda özel bir önerin var mı?";
			link.l1.go = "CaptainComission_403";
		break;
		
		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Kaptan "+GetFullName(pchar)+",   biliyorum biraz garip olacak ama... payıma düşenin parasal karşılığını verebilir misin? Sanırım, "+pchar.GenQuest.CaptainComission.GoodsPrice+" peso iyi bir uzlaşma olabilir.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на всякий случай .лесник
				pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник
				link.l1 = "Pekâlâ, bana uyar. Al paranı, hoşça kal.";
				link.l1.go = "CaptainComission_404";
			}	
			link.l2 = "Hayır, bu işe yaramaz. Yükünü alabilir ya da ambarında bırakabilirsin, ama sana tek bir kuruş vermem.";
			link.l2.go = "CaptainComission_405";
		break;
		
		case "CaptainComission_404":
			bTemp = false;
			if(hrand(1) == 0)
			{
			    NPChar.reputation = 60 + rand(20); 
				NPChar.alignment = "good"; 
			}	
			else
			{
			    NPChar.reputation = 10 + rand(20); 
				NPChar.alignment = "bad"; 			
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation.nobility) > 50) bTemp = true; 
			if (NPChar.alignment == "bad" && sti(pchar.reputation.nobility) <= 50) bTemp = true;
			
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			
			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "Bir dakika, kaptan. Beni kurtardığın için sana teşekkür etmek istiyorum. Biliyor musun, neredeyse umudumu kaybetmiştim... Al, eminim bu küçük takı birçok zor durumda işine yarayacaktır... Şimdi hoşça kal.";
				link.l1 = "Teşekkür ederim. Bunu beklemiyordum. Seninle iş yapmak keyifti.";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "Dur bir dakika... Şimdi aklıma geldi... Artık kariyerim bitti, mürettebatım yok ve kendi memleketimde sürgünüm. Eminim ki güvenilir, eli sağlam ve sır tutmasını bilen adamlara ihtiyacın vardır. Lütfen beni de mürettebatına al, söz veriyorum pişman olmayacaksın.";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "Açıkçası, bir süredir senin kabulünü bekliyordum. Tabii. Gemide görüşürüz.";
					link.l1.go = "CaptainComission_407";
				}	
				link.l2 = "Hmm... biliyor musun, bana kalırsa sen başkasının emrinde çalışamayacak kadar zekisin. Hoşça kal...";
				link.l2.go = "CaptainComission_408";
			}
		break;
		
		case "CaptainComission_405":
			dialog.text = "Anlaşılan bugün kesinlikle şanslı günüm değil... Peki kaptan, hadi kılıçlarımızı çekelim ve her şeyi bir kerede bitirelim...";
			link.l1 = "Hizmetinizdeyim...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;
		
		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
	
		
		case "CaptainComission_407":	
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");		
			npchar.CaptainComission = true;
			SetCharacterRemovable(Npchar, true);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer"; 			
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;	
			NPChar.loyality = MAX_LOYALITY;
			DeleteAttribute(NPChar, "LifeDay");
			NPChar.id = "GenChar_" + NPChar.index;// лесник . смена ИД при взятии в оффы. 
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(NPChar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired"); 
			NPChar.quest.meeting = true; 
			DialogExit();
		break;		
		
		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);						
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;		
		// Генератор "Operation 'Galleon'"
		
		// Квест "meeting in the cove" -->
		// Офицер
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "Bu seni ilgilendirmez. Şimdi söyle bakalım, burada neyin peşindesin? Az önce tutuklanan adamı aramıyor musun?!";
				link.l1 = "Bir adam mı?! Hayır...";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;
			
		case "ContraMeetManQuest_Sold_2":
			dialog.text = "Aferin sana. Yoksa sen de onunla birlikte hapse girerdin. O yüzden burada oyalanma, denizci. Kaybol!";
				link.l1 = "Evet, en iyisi ben gideyim...";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;
			
		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Время больше не роляет
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			ContraMeetManQuest_DeletePatrolFromShore(); // По выходу потрем всех из локации
			break;
			
		// Сам чел
		case "ContraMeetManQuest_1":
			dialog.text = "Harika! Şimdi o kaçakçıyı bulmak için meyhaneye gitmeliyiz. Burada daha fazla oyalanmak istemem!";
				link.l1 = "Bu konuda sorun yok. Hadi gidelim...";
				link.l1.go = "ContraMeetManQuest_2";
			break;
			
		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			break;
		
		// Контрики в комнате таверны	
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_5":
			dialog.text = "He-he... Görünüşe göre, "+GetSexPhrase("dostum","kız")+", sen de yakında ona cehennemde katılacaksın... Hey, dostum - ikisini de gebertelim!";
				link.l1 = "Pislik domuz! Kendini savun!";
				link.l1.go = "ContraMeetManQuest_6";
			break;
			
		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;
			
		case "ContraMeetManQuest_7":
			dialog.text = "Bir kez daha teşekkür ederim, "+PChar.name+". Elveda...";
				link.l1 = "...";
				link.l1.go = "ContraMeetManQuest_9";
			break;
			
		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "Ödül mü?! Tabii, al – buyur "+FindRussianMoneyString(iMoney)+" ve elveda...";
				link.l1 = "Hoşça kal...";
				link.l1.go = "ContraMeetManQuest_10";
			break;
			
		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// <-- Квест "meeting in the cove"
			
		// Квест на доставку письма контрику -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "Heh! Bunu yutacağımızı mı sandın?! Hey millet, şu iki cellat kuşunu yakalayın!";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // Попытка отмазаться
			//{
				link.l1 = "Memur bey, iki masum insanı tutuklamaya kalkarak büyük bir hata yapıyorsunuz. İnanın bana, o adamı tanımıyorum ve onunla en ufak bir ilgim yok."+" Komutanınızın iki kanunlara uyan vatandaşı alıkoyarsanız bundan hiç memnun kalmayacağından eminim...";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // Тюрьма
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "Hmm... Evet, belki de haklısın. Komutan bundan kesinlikle memnun kalmayacak. Biliyor musun - hadi bu küçük olayı unutalım.";
				link.l1 = "Thank you, officer, you've saved us time. I'd like to ask you to be more careful next time; surely you wouldn't want to be demoted, would you?";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "Hayır, asla. O halde lütfen dağılın. Görüşürüz...";
				link.l1 = "Bu daha iyi!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;
		
		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // Денег не даёт
			{
				dialog.text = "Harika! Ve şimdi kaybolabilirsin!";
					link.l1 = "Ne?!   Peki ya para?   Anlaşmamız vardı...";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // Деньги или патруль
			{
				if(rand(2) == 1) // Патруль
				{
					dialog.text = "Teslimat için sağ ol. Şimdi defolup gidebili... bekle, biri geliyor...";
						link.l1 = "Ne?!";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // Просто отдает деньги
				{
					dialog.text = "Harika. Teslimat için teşekkürler. Al, buyur "+FindRussianMoneyString(iMoney)". Ve unutma, kaçakçılar iyi insanları her zaman hatırlar...";
					link.l1 = "Umarım öyle olur. Hoşça kal.";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}
			
			ChangeContrabandRelation(PChar, 5); // Письмо доставили - повышаем отношение у контриков
			ChangeCharacterComplexReputation(pchar,"nobility", -5); // Помогли контрикам - репу понижаем
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;
			
		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // Чтоб не поубивали кого-нить
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;
			
		case "ContraDeliverQuest_NoMon":
			dialog.text = "Dinle... seninle aramızda hiçbir anlaşma yoktu. Paranı o anlaşmayı kim yaptıysa ondan iste.";
				link.l1 = "Eh, bugün de şansım pek yaver gitmedi, ne diyeyim ki?! Neyse, görüşürüz...";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear()+"Bunun hesabını vereceksin! Ölümüne hazırlan!";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;
			
		case "ContraDeliverQuest_GoWithoutMoney": // Уходим без денег
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
			
		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "Bana meydan okumaya cüret ettin, "+GetSexPhrase("velet","pislik")+"?   Demek   sen   kendin   için   neyin   iyi   olduğunu   hiç   bilmiyorsun.   Karnını   deşerim!";
				link.l1 = "...";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;
			
		case "ContraDeliverQuest_Fight": // Бой
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;
			
		case "ContraDeliverQuest_GoWithMoney": // Уходим с деньгами
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // Квест пройден - атрибуды потрем
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// <-- Квест на доставку письма контрику
			
		// Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Если ждёт в таверне
				{
					dialog.text = RandPhraseSimple("Beş yüz adam! Ve bir ölü adamın sandığı! Hık!","İç! Hik! Ve şeytan gerisini halletti - Hik! - hepsini!");
						link.l1 = "Ah... Pekâlâ. Merhaba, bayım "+GetFullname(NPChar)+".";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // на палубе своего шипа
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "Pekala, şimdi bakalım... Üç parça yelken bezi, geminin gövdesi için tahtalar, kemerler ve halatların yenilenmesi...";
							link.l1 = "Merhaba, efendim "+GetFullName(NPChar)+". Ben kaptanım "+PChar.name+".";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("Gemimden hemen defol, sensiz de yapacak çok işim var!","Kitaplarını aldın, daha ne istiyorsun?!","Senden istediğin her şeyi yaptım, daha ne istiyorsun benden?!");
							link.l1 = "Bu kadar heyecanlanma, yoksa kalp krizi geçireceksin!";
							link.l1.go = "exit";
					}					
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("Rom, rom! Bana rom ver... Hık!","Uzun zaman oldu... hık... en son böyle sarhoş olalı...");
					link.l1 = "Evet, ambarın dolmuş... belki de bir koya yanaşmanın zamanı gelmiştir?";
					link.l1.go = "exit";
			}			
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("Lütfen oturun, ka-hıç-kaptan! Ne içersiniz?","Otur bakalım, Kaptan! Ne içmek istersin? Hık...");
					link.l1 = "Teşekkür ederim, ama düzgün bir adamla hoş bir sohbeti tercih ederim.";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "Beni aşağılamaya mı çalışıyorsun - hık! - ?.. O meyhanede düzgün bir adam yok! Hık! Hepsi haydut, hepsi katil! Hepsi de haracı kesiyor, bir de o var ya... hepsinin en kötüsü! O çetenin başı, boğazında müren balığıyla!";
				link.l1 = "Seninle konuşmak istiyorum. Sözüm sana. Peki, haydutların lideri kim ve neden o...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = "Mis"+GetSexPhrase("ter","s")+"! Sevgili dostum! Adın neydi, bir daha söyler misin? Sana saygım sonsuz! Şimdiye kadar kimse yaşlı bir deniz kurduna adam gibi adam demedi! Senin için her şeyi yaparım! Son kuruşuma kadar bütün paramı verirdim!.. Ah, unuttum. Param kalmadı. Bir tek reale bile yok elimde. O alçak, o tefeci son paramı da aldı, cehennemde şeytanlar onun bağırsaklarıyla toplarını doldursun!";
				link.l1 = "Kaptan bey? İyi misiniz? Farkında mısınız, sayıklıyorsunuz? Hangi parşömenler?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "Hayır, hayır! Bu yaşlı kaptan sarhoş olabilir ama aklı hâlâ yerinde. Kitapları ve parşömenleri bana Rahip verdi "+PChar.GenQuest.ChurchQuest_1.ToName+", onları   götürüyordum "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Acc")+". Sabah olunca yerel kiliseye gittim ve bu kitaplardan yerel papaza bahsettim. Tabii ki, görmek istedi — bilirsin onları, azizlerin hayatlarına falan bayılırlar. Ben de bir kamarot çocuğunu sandığı getirmesi için gönderdim. Beklerken de biraz kumar oynamaya karar verdim... ve nasıl olduysa tüm paramı kaybettim. Her şeyimi! İçkiyi ödeyecek bir kuruşum bile kalmadı! Böylece meyhaneci kitapları teminat olarak aldı, sonra da parşömenleri de ona verdim...";
				link.l1 = "Demek, rahibin sana emanet ettiği kutsal kitapları sattın  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+"?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "Biliyorum, biliyorum... Sonsuza dek Cehennem'de yanacağım. Şimdi ne bana o görevi veren Babaya, ne de evrakları teslim eden kişiye, ne de buradaki yerlilere yüz gösterebilirim... Kim şimdi ruhum için dua edecek? Ya beni aforoz ederlerse? Ah, vay halime... Bir içkiye ihtiyacım var... ";
				link.l1 = "Hey, sakin ol, o kadar da kötü değil. Yaptıkların berbattı ve hiç de saygılı değildin, ama yine de sana yardım etmeye hazırım. Borcunu ödeyeceğim ve bu el yazmalarını satın alacağım. Ayrıca, adı geçen iki rahibi de zaten tanıdığım için, doğrudan yelken açacağım  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Acc")+" oraya belgeleri teslim etmek için. Anlaştık mı?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "Kurtarıcım! Tanrı'nın meleği... Tabii ki kabul ediyorum! Sana her şeyimi veririm... her şeyimi! Yeter ki bir yudum daha içebileyim...";
				link.l1 = "Sanırım zaten yeterince içtin... Neyse. Sana barmenden biraz daha rom alırım.";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "...ve çarşaflar! Çarşafları da değiştirmemiz lazım!.. Ah, merhaba. Lütfen alınmayın, hanımefendi"+GetSexPhrase("ter","s")+" her-neysen-adın, ama şu anda gördüğün gibi oldukça meşgulüm, bu yüzden bana bir işin varsa, lütfen çabuk ol.";
				link.l1 = "Bildiğim kadarıyla, Baba "+PChar.GenQuest.ChurchQuest_1.ToName+"sana bazı kutsal belgeler verdim "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Voc")+". Onları teslim edeceğine söz vermiştin "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Acc")+" çünkü zaten o yöne gidiyordun."; // belamour gen
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;
			
		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "O tarafa gidiyordum ki, şu lanet fırtına eski tekni neredeyse paramparça etti, ben de kim bilir ne kadar süre burada mahsur kaldım! Limandaki şu üçkağıtçılar geminin gövdesi için bana gelgitin kıyıya attığı çürük tahtaları, yelkenler içinse büyükannelerinin gençken üzerinde uyuduğu eski çuvalları satmaya çalışıp duruyorlar.";
				link.l1 = "Efendim, bir dahaki sefere memnuniyetle muhteşem hikayelerinizi dinlerim, ama şimdi elinize geçen kitaplar ve el yazmaları hakkında daha fazla bilgi almak isterim "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Dat")+".";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;
			
		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "Kimse, beni duyuyor musun? Kimse bu lanet olası belgelerin teslimindeki gecikmeden dolayı beni suçlamaya cesaret edemez!";
				link.l1 = "Ah, hayır, kesinlikle öyle demek istemedim. Sadece yükünü hafifletmek istedim. Mesele şu ki, "+PChar.GenQuest.ChurchQuest_1.ToName+"  kitaplar ve belgelerin teslim edilmesi konusunda oldukça endişeli "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Acc")+" . Aslında, oraya şimdi yelken açacağım.";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;
			
		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "Bana öyle geliyor ki, hanımefendi"+GetSexPhrase("ter","s")+", her limanda bir ruhani danışmanın varmış. Gerçi bu beni hiç ilgilendirmez. Eğer o saçmalıklara değer veriyorsan, kitaplarını topla ve defol! İyi ki gidiyorsun!";
				link.l1 = "Teşekkür ederim, Kaptan. Onarımlarınızda bol şans.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // Свитки не отдает
		{
			dialog.text = "Bunun için endişelenmeyin, hanımefendi"+GetSexPhrase("ter","s")+", ve  şuraya git "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Acc")+" hafifçe, çünkü o belgeleri teslim etmeyi üstlenen bendim ve ne pahasına olursa olsun bunu yapacak olan da yine ben olacağım, böylece kimse her köşe başında kaptan diye bağırmayacak "+NPChar.name+" sözünde durmadı!";
				link.l1 = "Ama Kaptan, aslında mesele şu ki...";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;
			
		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "Aslında, mesele şu ki, seninle hiçbir işim yok. Kutsal Baba bana bir görev verdi, kitapları teslim etmemi istedi "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Acc")+" ve onları yerel rahibe teslim et. Ama seni orada göremiyorum. Hiçbir şekilde! Bol şans.";
//				link.l1 = "Pekâlâ, o zaman. Çok sorumlu bir adamsın, gerçi tek meziyetin bu. Sana bol şans, kaba dostum";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // Сваливаем, поверили ему
				link.l2 = "Senin küstah tavırlarından bıktım. Aptalca lafların bir meleği bile öfkelendirebilir. Kutsal babamın iradesini yerine getirmeliyim ve gerekirse silahımı kullanırım!";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // Квест выполнен без манускриптов
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "Sessiz ol, sessiz ol, Kaptan "+PChar.name+" ! Sana ne oldu? Neyse, bakıyorum ki bu belgeleri getirmezsen, o kutsal babaların hepsi sana çok kızacak, gökteki Babamızdan bahsetmiyorum bile. Peki, al şu kutsal evraklarını ve Tanrı'nın bereketiyle git.";
				link.l1 = "Durumumu sadece anladığın için değil, adımı da hatırladığın için memnunum. Aptalca bir şey yapmaya kalkıştığında adımı tekrar hatırlamanı öneririm.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // Сваливаем, поверили ему
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		// <-- Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем
			
		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("Defol...","Beni rahatsız etme!");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;
			
		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear()+"Bunu söylememeliydin! Şimdi seni Tanrı'ya göndermek zorundayım ki, günahlarımın affı için dua edesin!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear()+"Bunu söylememeliydin! Şimdi seni Rabbimizin huzuruna göndermem gerekecek ki günahlarımızın affı için dua edesin!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear()+"Bunu söylememeliydin! Şimdi seni Tanrı'nın huzuruna yollayıp, hepimizin günahları için af dilemeni sağlayacağım!";
			}
			
				link.l1 = "Pek sayılmaz, dostum. Herkes kendi hesabını Tanrı'ya verecek!";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "Hey, neden küfür ediyorsun? Ya seninle bir işim varsa.";
				link.l1 = "Bu gerçekten haber! Biliyor musun, senin gibi biriyle boş muhabbet edecek vaktim yok!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "Pekâlâ, ben de seninle uzun uzun konuşacak değilim. Ama belki birkaç ufak tefek şeyi iyi bir fiyata almak ilgini çeker?";
				link.l1 = "Ben sana hırsız malı mı satıyorum sandın?!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "Sakin ol, sakin ol, aramızda hırsız yok! Bu vazo bize dürüst çalışmamız karşılığında verildi! Bak hele... saf altın, incilerle süslenmiş. Ama mesele şu ki, bizim buna ihtiyacımız yok. Sadece satıp parasını paylaşmak istiyoruz.";
					link.l1 = "Bir bakayım... Aman Tanrım! Bu, ayin kadehi!!! Demek kiliseyi yağmalayan o kafirler sizsiniz "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"?! İşte buradasın!";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}
		
			dialog.text = "Sessiz ol, hanımefendi"+GetSexPhrase("ter","s")+" İkiyüzlü! Biliyor musun, paramız biraz azaldı, o yüzden bir şey satmaya karar verdik. Şu vazoya bir bak... saf altın, incilerle süslenmiş. Sana özel fiyat, diyelim ki bin sikke.";
				link.l1 = "Biraz daha yakından bakayım... Aman Tanrım! Bu, ayin kadehi!!! Demek kiliseyi yağmalayan o kafirler sizsiniz "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"?! İşte buradasın!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "Sakin ol, hanımefendi"+GetSexPhrase("ter","s")+"!.. Kahretsin, o ahmağa zamanı gelene kadar ortalığı karıştırmamasını söylemiştim...";
				link.l1 = "Ne saçmalıyorsun sen? Tamam, seçimini yap: ya çaldığın ganimeti güzelce verirsin, ya da muhafızları çağırıyorum.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "Dinle, "+GetSexPhrase("iyi adam","genç hanım")+", kavga etmeye gerek yok, bu meseleyi sakin bir şekilde çözelim. Bize inanmalısınız, aslında o kiliseyi soymadık, elimizde de para yok. Evet, soygunu yapıyormuş gibi davranmamız için birkaç peso ve şu altın süsü aldık. Ve bu altın kupa, kaçakçılara ödedikten sonra elimizde kalan tek şeydi...";
				link.l1 = "Yani, demek istiyorsun ki...";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "O lanetli rahip bizi tuttu, diyorum sana! Ama neden seni bizim başımıza sardı ki?.. Neyse, artık hesabımız kapandı. Al şu vazoyu, o iki yüzlüye göster, kendi gözlerinle göreceksin, suda çırpınan bir ahtapot gibi kıvranacak!";
				link.l1 = "Bardağı ver ve defol, yoksa fikrimi değiştiririm.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "İyi konuşuyorsun, ama beni kandırmak o kadar kolay değil. Beni ikna etmek istiyorsan, önce kılıcımı ikna et.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// Тут давать чашу, если будет
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			
			// Разрешим генерацию энкаунтеров, откроем выходы
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear()+"Şu serserilere demedim mi: ellerinizi kendinize saklayın ve papazdan sadece para alın!";
			}
			else
			{
				dialog.text = RandSwear()+"Şu açgözlü heriflere demedim mi: ellerinizi kendinize saklayın, papazdan sadece para alın!";
			}
			
					link.l1 = "Ne saçmalıyorsun? Tamam, seçimini yap: Ya çaldığın ganimeti güzelce verirsin, ya da muhafızları çağırırım.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "Ben farklı bir seçim yapıyorum, o yüzden çeneni kapa ve keseni ver, hayatını bağışlayacağım.";
				link.l1 = "Sana şimdi efendimizle görüşme ayarlayacağım!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "Pekâlâ, sana biraz para vereceğim, ama bunu tamamen kendi isteğimle yapıyorum, böylece sen ve arkadaşların dürüst bir hayat sürebilirsiniz ve kendinizi soygunla küçük düşürmek zorunda kalmazsınız.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "Ehh... Peki, anlaşmazlıklarımızı bir kenara bırakalım ve konuşmamızın başına dönelim. O şey için ne kadar istiyordun?";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// Не забыть чашу!
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money)/2); // Забираем половину денег
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // Полностью проигрышный вариант. Остаемся ни с чем
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}
			
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "Ben de hiçbir bela istemem, "+GetAddress_Form(pchar)+", ama şimdi fiyat arttı. O değerli kupa için yanında ne varsa hepsini isteyeceğim.";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "Sen açgözlü pislik! Bende sadece "+FindRussianMoneyString(iMoney)+" benimle. Al şunu ve defol!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "Yanlış seçim, açgözlü sıçan. Benim üzerimden sana hayır gelmez!"+GetSexPhrase(" I am as free as the wind - here today, gone tomorrow; today I am poor - tomorrow I shall be rich...","")+"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// Даем чашу
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // Диалог не забыть поменять.
			}
			
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "Bugün özellikle bunu söylemeye çalışmıyor musun "+GetSexPhrase("sen fakirsin","paran yok")+"?!";
				link.l1 = "Aynen öyle, açgözlü dostum, senin büyük hayal kırıklığına. Şimdi ise müsaadenle, yapacak çok işim var.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";	
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "Dur! Bunu kontrol edeceğiz, ve eğer doğruyu söylemediysen, o yalancı dilini karınca yuvasına sokarım!";
				link.l1 = "Bunu söyledikten sonra işin bitti!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;
			
		// Можно этот кэйс - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// ГГ как-бы может обыскать трупики и забрать все барахло...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("As a real gentleman, I am honest","I am honest"));
			break;
			
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕНЕР "PIRATES ON AN UNINHABITED ISLAND"
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PiratesOnUninhabited_1":
			dialog.text = "Ah, karar verilecek bir şey yok. Her şeyi kendimiz halledebiliriz. Ama senin gemini alıp buradan gideceğiz.";
			link.l1 = "Bir şartım var: önce kılıcımı elimden alman gerekecek...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_2":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				LAi_SetImmortal(CharacterFromID("PirateOnUninhabited_" + i), false);
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
			
				i = PiratesOnUninhabited_GenerateShipType();
				PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;
			
			if(hrand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;
				
				dialog.text = "Merhaba, kaptan! Görünüşe göre kaderin kendisi sizi kurtarmak için gönderdi "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+" ve adamları. Burada gerçekten zor durumdayız."+"Bizim "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name))+" fırtınada buradaki resiflerde karaya oturdu, ve sağ kalan mürettebatı dalgalar kıyıya vurdu."+"İçin "+(5+hrand(7))+"Haftalarca ufka bakıp, bizi kurtaracak bir geminin yelkenini görmeyi umduk.";
				link.l1 = RandPhraseSimple(RandPhraseSimple("Evet, bu hiç de imrenilecek bir kader değil. Ama denizcinin hayatı böyle, herkes senin durumuna düşebilir.","Anlıyorum... Tanrı her canı elinde tutar, sadece herkesi hatırlayacak kadar vakti yoktur."),RandPhraseSimple("Gerçekten de. İnsan plan yapar, ama takdir Allah’ındır.","Evet, bu gerçekten de talihsizlikti."));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = "Çok ciddiydi! O alçak herif "+PChar.GenQuest.PiratesOnUninhabited.BadPirateName+" ayrılmaktan başka bir ceza düşünemedim "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+" ıssız bir adada, sanki uyuz bir köpek gibi! "+"Güneşin ve susuzluğun bizi balıkçının tezgâhında kuruyan uskumru gibi kavurmasını ummuştu! Ama yanıldı, çünkü kader bizzat bizim yanımızdaydı; seni buraya, bizi kurtarmaya gönderdi...";
				link.l1 = RandPhraseSimple("O kadar da acele etme, dostum. Gördüğüm kadarıyla, siz özgür bir mesleğin adamlarısınız ve buraya da tesadüfen gelmediniz.","Şimdiden kurtuluştan mı bahsediyorsun? Anladığım kadarıyla, burada olmanın sebebi bazı özel başarıların.");
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;
		
		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + hrand(5);
			
			dialog.text = RandPhraseSimple("Kaptan, lütfen iyi yürekli olun ve yardım edin "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" sefil adamlar. Bizim tek umudumuz sensin, en yüce Rabbimiz dışında.","Kaptan, geminizde boş bir sandık var mı "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" sefalet içindeki adamlar mı?");
			
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = "Ah... peki, seni nereye götürmemi istersin?";
				link.l1.go = "PiratesOnUninhabited_5";
			}
			
			link.l2 = RandPhraseSimple(RandPhraseSimple("I am truly sorry, but there isn't a single free hammock, let alone a cabin. The sailors are sleeping on deck; they can't even get a proper night's rest after their watch...","I would really hate to disappoint you, but the ship is overloaded, and people have to sleep in bad weather. Should there be an outbreak of disease, I will lose half the crew."),RandPhraseSimple("I am truly sorry, but there is absolutely no spare crew space on my ship. I cannot take on any more passengers.","I have to disappoint you, but my ship is overloaded with crewmen. I fear the epidemic..."));
			link.l2.go = "PiratesOnUninhabited_21";
			
			if(stf(PChar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Sen deneyimli bir denizcisin ve bir gemi kazasından sağ çıkan birinin varlığının çok kötü bir işaret olduğunu bilmelisin. Benim tayfam sizi hiç düşünmeden denize atar.";
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;
		
		case "PiratesOnUninhabited_5":
			dialog.text = "Hmm... Biliyor musun, çeşitli sebeplerden dolayı yetkililerden mümkün olduğunca uzak durmak istiyoruz... Lütfen bizi herhangi bir yerleşim olan adadaki bir koya ya da ana karaya bırak, gerisini biz hallederiz.";
			link.l1 = "Pekala, yeterince boş ranza ve hamak var. Kendini sandala at.";
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = "Hmm... kötü şans... Önümüzde savaşlar var ve senin için daha güvenli yerin neresi olacağını bilmiyorum, gemimde mi yoksa bu rahat koyda mı.";
			link.l2.go = "PiratesOnUninhabited_6";
		break;
		
		case "PiratesOnUninhabited_6":
			dialog.text = "Ah kaptan! Şu zamanlarda insan karısıyla aynı yatakta bile kendini güvende hissedemiyor, ha-ha, denizde olmayı hiç söylemiyorum bile... Şu serserilere bak, her biri çıplak elle topa karşı dövüşmeye hazır. Güvenlik ya da rahatlık umurlarında bile değil, yüzlerinden okunuyor!";
			link.l1 = "Yüzlerinde sadece aptal iyilikseverlerini arkadan bıçaklama isteğini görebiliyorum.";
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = "Hmm... Aslında bu iyi bir fikir. Söylesene dostum, adamların benim tayfamda hizmet etmeye razı mı?";
			link.l2.go = "PiratesOnUninhabited_8";
		break;
		
		case "PiratesOnUninhabited_7":
			dialog.text = "Yazık kaptan... Görüyorum ki bunu dostça çözemeyeceğiz. Sanırım sana deniz kanununu hatırlatmam gerekecek. Ve unutma, gemiye çıkma konusunda kimse elimize su dökemez...";
			link.l1 = "Şimdi nihayet kim olduğunu gerçekten görebiliyorum...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", -3.0);
		break;
		
		// Берем их в команду
		case "PiratesOnUninhabited_8":
			dialog.text = "Elbette! Senin mürettebatına katılmaktan büyük mutluluk duyarlar! Onları dövüşte kimse alt edemez, belki sadece Davy Jones'un kendisi! Ha-ha-ha!";
			link.l1 = "Pekâlâ, o zaman. Hadi, sandallara binin...";
			link.l1.go = "PiratesOnUninhabited_9";
		break;
		
		case "PiratesOnUninhabited_9":
			bTemp = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				
				if(bTemp)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			OfficersReaction("bad");
			
			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_10":
			dialog.text = "Teşekkürler, kaptan! Yükleme fazla zaman almaz. Tanrım, bu anın gelmesi için ne çok dua ettik!";
			link.l1 = "Pekâlâ, o zaman.";
			link.l1.go = "PiratesOnUninhabited_11";
		break;
		
		// Берем их в пассажирами - держать курс на населенный остров
		case "PiratesOnUninhabited_11":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			
			if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
					// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
					if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					else
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					// <-- belamour gen
				}
				else
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
				// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				else
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				// <-- belamour gen
			}
			
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";
			
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
			
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_11_Again":
			dialog.text = LinkRandPhrase("Neden oyalanıyorsun, kaptan? Demir almamız için emir ver.","Üzgünüz kaptan, ama yelken açmaya hazırlanmalıyız.","Buraya gelmeye karar verdiğin için çok şanslıyız!");
			link.l1 = "Acele et. Gemi kimseyi beklemez.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове
		case "PiratesOnUninhabited_12":
			if(hrand(1) == 0)
			{
				// Успешное завершение квеста - даст награду
				dialog.text = "Thank you, captain. Indeed, we were right to believe in our luck... Please, accept this gem; I found it at that ill-fated cove. I hope it brings you luck.";
				link.l1 = "Böyle bir hediye beklemiyordum.";
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// Требуют денег
				dialog.text = "Kaptan, lütfen, haddimizi aşıyoruz sanmayın ama gerçekten çok parasız kaldık. Biliyorsunuz, elimizde ne varsa kaybettik. Bize birkaç avuç peso borç verir misiniz? Fırsatını bulduğumuzda mutlaka geri ödeyeceğiz...";
				link.l1 = "Vay canına! Gerçekten de, küstahlığın sınırı yok. Şimdiye kadar senin için yaptıklarımdan sonra, artık yapabileceğim tek şey, yetkililere senden bahsetmemek olurdu.";
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = "Yok artık... Peki, ne kadar istiyorsun?";
				link.l2.go = "PiratesOnUninhabited_17";
			}
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				
				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_14":
			dialog.text = LinkRandPhrase("Teşekkür ederim, kaptan.","Kaptan, size minnettarız.","Sizin için dua edeceğiz, Kaptan "+PChar.name+"!");
			link.l1 = "Bol şans. Elveda...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;
		
		case "PiratesOnUninhabited_15":
			dialog.text = "Heh, kaptan... Biliyor musun, aslında iyi anlaştık... Seni öldürmek gerçekten yazık olurdu...";
			link.l1 = "Deneyebilirsin!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
		break;
		
		case "PiratesOnUninhabited_16":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			dialog.text = "Peki, söyle bakalım, "+iMoney+" her birimiz için şu kadar peso gayet iyi olurdu... Tabii, tüm acı ve sıkıntılarımızın karşılığı olarak bu miktarın az olduğunu düşünmüyorsan, he-he...";
			link.l1 = RandPhraseSimple("Aksine, bunun fazlasıyla fazla olduğundan eminim... Her birinizin boynuna bir ilmek geçirmek en iyisi olurdu.","Böyle bir para için seni kendi ellerimle palmiye ağaçlarına maymun gibi asarım!");
			link.l1.go = "PiratesOnUninhabited_18";
			
			if(sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = "Pekala, al bakalım. Umarım sana başka bir borcum yoktur?";
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;
		
		case "PiratesOnUninhabited_18":
			dialog.text = "Ne cömertlik! Açıkçası, bizim her zaman istediğimizi aldığımızı çoktan fark ettiğini sanmıştım. Ve bu sefer de geri adım atmayacağız...";
			link.l1 = "Deneyebilirsin!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_19":
			dialog.text = "Aman kaptan, ne diyorsun sen?! Bir gün kiliseye yolumuz düşerse, adını anıp mum yakarız... hah!";
			link.l1 = "Umarım öyle...";
			link.l1.go = "PiratesOnUninhabited_20";
			
			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);
			
			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;
		
		case "PiratesOnUninhabited_20":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
			OfficersReaction("good");
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			NPChar.SaveItemsForDead = true; // сохранять на трупе вещи
			NPChar.DontClearDead = true;  // не убирать труп через 200с
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_21":
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// Игрок врет - свободное место есть
				dialog.text = "Aman kaptan, ne diyorsun sen?! Bir gün kiliseye yolumuz düşerse, adını anıp mutlaka bir mum yakarız... hah!";
				link.l1 = "Umarım öyledir...";
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = "Heh, kaptan, biliyor musun, bu pek de büyük bir sorun değil. Benim adamlarım ve ben, şu an onları dolduranlardan bir düzine hamak boşaltmaya hazırız...";
				link.l1 = "Hmm... bu bir tehdit gibi geliyor...";
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;
		
		case "PiratesOnUninhabited_22":
			dialog.text = "Aslında, bu bir tehdit. Gemine ihtiyacım var ve buradan senin iznin olsun ya da olmasın çıkacağım!";
			link.l1 = "Şimdi nihayet seni gerçekten ne olduğunu görebiliyorum...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_23":
			dialog.text = "Sizi anlıyorum, kaptan. Sizi gayet iyi anlıyorum... Kim darağacını bekleyen zavallı korsanlara bakmak ister ki?.. Ama... size bir teklifim olsa? Bizi yerleşimli bir adada ya da ana karada herhangi bir koya bırakırsanız, karşılığında size bir hazine haritası veririm. Anlaştık mı?";
			link.l1 = "Hmm... Peki bu haritanın sahte olmadığını nasıl garanti edebilirsin?";
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = "Ha, haritanın değeri, üstüne çizildiği kağıttan fazla değildir bence...";
			link.l2.go = "PiratesOnUninhabited_24";
		break;
		
		case "PiratesOnUninhabited_24":
			dialog.text = "Pekâlâ... Bize başka seçenek bırakmıyorsun... Yine de, senin iznin olsun ya da olmasın, buradan çıkacağız!";
			link.l1 = "Şimdi nihayet kim olduğunu gerçekten görebiliyorum...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_25":
			dialog.text = "Peki, bize en yakın limanda yetkililere teslim etmeyeceğinin garantisini nasıl vereceksin? İkimiz de birbirimizin kartlarını görmeden oynuyoruz...";
			link.l1 = "Pekâlâ, anlaştık.";
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове. Вариант, когда нам обещали карту сокровищ
		case "PiratesOnUninhabited_26":
			// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - имя в родительном падеже
			
			dialog.text = "Teşekkür ederim, kaptan "+PChar.name+". Yerine getirdin"+GetSexPhrase("","")+" sözünü tutma zamanı geldi "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_DAT)+" benimkini yerine getirmek için. Harita yanımda değil, ama sana hazinenin nerede olduğunu söyleyeceğim. Koy'a git...";
			link.l1 = "Ha, demek şimdi böyle söylüyorsun! En başından beri beni kandırmayı planladığını anlıyorum...";
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = "Sana hemen güvenilemeyeceğini anladım...";
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = "Bir korsana güvendiğinde olan budur. Ne biçim insanlarsınız siz? Sizin için hiçbir şey kutsal değil!";
			link.l3.go = "PiratesOnUninhabited_33";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_27":
			dialog.text = "Ortaya sorun çıkarma... Aziz değilim, ama sözümü tutarım!";
			link.l1 = "Ve yine sana inanmamı mı bekliyorsun? Yarın bütün takımada bana gülecek, öyle mi?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		case "PiratesOnUninhabited_28":
			dialog.text = "Hmm... Görünen o ki, barışçıl bir çözüm olmayacak. Ama Tanrı şahidimdir ki, bunu istememiştim...";
			link.l1 = "Kılıcını çek, yoksa seni olduğun fare gibi ezerim!";
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_29":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "Başka ne yapabilirdim ki? O pislik içinde adamlarımla birlikte çürüyüp ölmeyi mi bekleyecektim? Beni dinlesen iyi edersin..."+XI_ConvertString(sTitle+"Gen")+" kaptan "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" bir yerde ganimetini sakladığı bir gizli depo var. Ama dikkatli ol"+GetSexPhrase("","")+", oraya sık sık uğrar. Akıllı davranırsan, gizli yeri bulmak zor olmayacak..."; // belamour gen
			link.l1 = "Ve yine sana inanmamı mı bekliyorsun? Yarın tüm takımada benimle dalga geçsin diye mi?";
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = "Pekâlâ. Ama beni bir kez daha aptal yerine koyarsan, seni bulurum.";
			link.l2.go = "PiratesOnUninhabited_31";
		break;
		
		case "PiratesOnUninhabited_31":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Gen"))); // belamour gen
			
			// Таймер для клада. По прошествии 10 дней в кладе будут всякие бакланы и т.д.
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.function = "PiratesOnUninhabited_TreasureLose"; // belamour gen
			
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";
			
			DialogExit();
			
			// Курс в бухту, которую назвал пират. У нас сроку 10 дней, котом клад пропадёт
		break;
		
		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);
			
			dialog.text = LinkRandPhrase("Dinle "+sTemp+", mantıklı konuşuyor.","Bana kızma "+sTemp+", başka seçeneği yoktu.","Teşekkür ederim, kaptan.");
			link.l1 = "Bol şanslar...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;
		
		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "Başka ne yapabilirdim ki? O pislik içinde adamlarımla birlikte çürüyüp ölmemi mi isterdin? Beni dinlesen iyi edersin..."+XI_ConvertString(sTitle+"Gen")+" kaptan "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" orada ganimetlerini sakladığı bir gizli yer var. Ama dikkatli ol, oraya sık sık uğrar. Akıllı davranırsan o yeri bulmak zor olmayacak..."; // belamour gen
			link.l1 = "Ve yine sana inanmamı mı bekliyorsun? Yarın bütün takımada benimle alay etsin diye mi?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		// Пираты в бухте с сокровищем
		case "PiratesOnUninhabited_34":
			dialog.text = "Sen kimsin?"+GetSexPhrase(" dostum"," kız ")+"? Ve seni bu ıssız yere ne getirdi?";
			link.l1 = "Taze su stoğumu yenilemek için durdum.";
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = "  adına buradayım "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+".";
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;
		
		case "PiratesOnUninhabited_35":
			dialog.text = "Bunu yapmak için kötü bir yer seçtin... Peki, acele etme.";
			link.l1 = "A-ha...";
			link.l1.go = "exit";
			link.l2 = "Sen kim oluyorsun da bana ne yapmam gerektiğini söylüyorsun?";
			link.l2.go = "PiratesOnUninhabited_36";
		break;
		
		case "PiratesOnUninhabited_36":
			dialog.text = "Ne yapılacağını herkese ben söylüyorum. Kendini fazla akıllı sananlar ise palmiye ağacından sallanacak.";
			link.l1 = "Dilini koparırım, köpek.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PiratesOnUninhabited_38":
			dialog.text = "Ve neden kendisi gelmedi?";
			link.l1 = "O istemedi, burada kaldı "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+" ve beni bekliyor."; // belamour gen
			link.l1.go = "PiratesOnUninhabited_39";
		break;
		
		case "PiratesOnUninhabited_39":
			dialog.text = "O yaşlı düzenbaz! Bizi yine kandırmaya çalışıyor, değil mi? Bu iş böyle olmaz. Ona söyle, parayı ancak biz yanındayken alabilir!";
			link.l1 = "Bana para olmadan geri dönmememi ve kimseyi gemiye almamamı söyledi...";
			link.l1.go = "PiratesOnUninhabited_40";
		break;
		
		case "PiratesOnUninhabited_40":
			dialog.text = "Pekala, ona bu kadar güveniyorsan burada kalabilirsin. Ama biz gemini, paranı alıp yolumuza devam edeceğiz "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+".   [[[VAR1]]]’in yüzünü görmeye can atıyoruz "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+"."; // belamour gen
			link.l1 = "Eğer onu bu kadar özlüyorsan, yüzerek gidebilirsin... ya da burada ölebilirsin.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;
		
		// Ветка из PiratesOnUninhabited_3
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + hrand(5);
			iMoney = GetFreeCrewQuantity(PChar);
			
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;
			
			dialog.text = "Sen kurnaz bir insansın. Ama sana şunu temin edeyim ki, Kaptan ile olan çatışmamız "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_ABL)+" tamamen ideolojik bir mesele. Ona kirli işlerinin bir gün cezasını bulacağını söylemiştim, şimdi ise benim  "+iBanditsCount+" dostlarımız Tanrı'ya ve adalete olan sevgimiz yüzünden acı çekiyor.";
			link.l1 = "Nasıl yani... Bahse girerim isyanın asıl kışkırtıcıları sizdiniz ve hak ettiğinizi buldunuz.";
			link.l1.go = "PiratesOnUninhabited_42";
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = "Elbette... Yine de kaptanın fikrini duymak güzel olurdu "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" kendisi sizin anlaşmazlıklarınız hakkında.";
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;
		
		case "PiratesOnUninhabited_42":
			dialog.text = "Kaptan, neden dürüst insanları güvensizliğinizle incitiyorsunuz? Yüzlerine bir bakın... gerçekten isyancı olduklarını mı düşünüyorsunuz? Onlar olabildiğince mütevazı insanlar... Ama iyi bir komutanın emrinde, haklı bir dava için dövüşte kimse ellerine su dökemez! Her birine bizzat kefilim.";
			link.l1 = "Peki, şimdi seninle ne yapacağım?";
			link.l1.go = "PiratesOnUninhabited_43";
		break;
		
		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);
			
			dialog.text = "Ne istersen yapabilirsin. Bizi bir yerleşime götür ya da tayfana kat, bana göre iyi bir kaptana benziyorsun.";
			
			if(iMoney >= iBanditsCount)
			{
				link.l1 = "Pekala, seni tayfama alacağım. Ama sakın saçmalık yapma! Gemimde disiplin esastır!";
				link.l1.go = "PiratesOnUninhabited_9"; // Берем в команду
			}
			
			link.l2 = "Seni hiçbir yere götürmüyorum. Mürettebatımda zaten yeterince haydut var.";
			link.l2.go = "PiratesOnUninhabited_24"; // Рубилово и конец квеста
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = "Pekala, kayığa bin, seni bir yere götüreceğim.";
				link.l3.go = "PiratesOnUninhabited_11"; // В пассажиры и на остров
			}
		break;
		
		case "PiratesOnUninhabited_43_again":
			dialog.text = LinkRandPhrase("Yemin ederim, kaptan, pişman olmayacaksınız.","Doğru kararı verdiniz, kaptan.","Kaptan, emin olun ki siz de bizim kadar şanslıydınız!");
			link.l1 = RandPhraseSimple("Umarım öyle.","Acele et. Gemi kimseyi beklemez.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;
		
		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;
			
			dialog.text = "Bunu kolayca ayarlayabilirim. O,  ile yelken açıyor "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name+"Voc"))+" '"+sTitle+" ve köle ticaretiyle uğraşıyor... Şöyle yapalım: Onu bulursak, yük senin olsun, gemi bizim. Ha, bir de ona şunu sorabilirsin: "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+". Umarım o ismi duyunca altına kaçırmaz, çünkü o benim gemim..."; // belamour gen
			link.l1 = "Pekâlâ, anlaştık.";
			link.l1.go = "PiratesOnUninhabited_45";
		break;
		
		case "PiratesOnUninhabited_45":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				rChar.location = "none"; // Убираем из локации при выходе   исправлено с NPChar на rChar - лесник
				rChar.location.locator = ""; // лесник  - так же исправлено .  тогда бага не будет.
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1)
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			//NPChar.FaceId = 101; // лесник потом подобрать аву бандиту.   
			
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			// --> belamour окончание по количеству персон
			if(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) >= 5)
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors");
			}
			else
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailor");
			}
			// <-- belamour
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Voc")) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PiratesOnUninhabited_SetCapToMap(); // Ставим корабль на карту
			
			DialogExit();
		break;
		
		// Диалог с кэпом в каюте
		case "PiratesOnUninhabited_46":
			dialog.text = "Benden ne istiyorsun, Allah aşkına?";
			link.l1 = "   Selam vermek için geldim,   "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+"Onu tanıdığını varsayıyorum?";
			link.l1.go = "PiratesOnUninhabited_47";
			
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
		break;
		
		case "PiratesOnUninhabited_47":
			dialog.text = "Keşke o alçağı daha önce boğsaydım. Neyse, sanırım iyiliğimin bedelini ödeme zamanı geldi...";
			link.l1 = "Gerçekten de... Ve zaman şimdi doldu...";
			link.l1.go = "PiratesOnUninhabited_48";
		break;
		
		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);
			
			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // важный метод
			
			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_49":
			dialog.text = "Harika iş çıkardın, kaptan! Her şey anlaştığımız gibi mi o zaman? Biz gemiyi alıyoruz, sen de yükü?";
			link.l1 = "Tabii. Gemiyi al ve iyi kullan.";
			link.l1.go = "PiratesOnUninhabited_50";
		break;
		
		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // Убираем из каюты
			NPChar.location.locator = "";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();
			
		break;
		
		// На палубе, когда корабль с нашим пиратом отпустили
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = "Sizi selamlıyorum, Kaptan "+PChar.name+".";
			link.l1 = "Peki, gemini nasıl buluyorsun?";
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;
		
		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = "Heh... gıcırdıyor ve inliyor, tıpkı benim gibi. Sanırım ikimizin de açık denizlerde geçirecek fazla zamanı kalmadı...";
			link.l1 = "Öyleyse iyi şanslar...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;
		
		// В бухте, вариант, когда корабль, который нужно было захватить, утопили
		case "PiratesOnUninhabited_51":
			dialog.text = "Neden gemimi batırdın?! Anlaşmamızı hatırlıyor musun?";
			link.l1 = "Ne? Onun beni batırmasını istemedim tabii. Zar zor kurtulduğumu görmüyor musun?";
			link.l1.go = "PiratesOnUninhabited_52";
		break;
		
		case "PiratesOnUninhabited_52":
			if(hrand(1) == 1)
			{
				dialog.text = "Böyle mi dövüşülür? Ne biçim gemi kaybettin sen! Ne halt ediyorsun! Senin gibi bir çocuk burada ne arıyor?";
				link.l1 = "Dilini koparırım, köpek.";
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + hrand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = "Böyle mi dövüşülür? Ne biçim gemi kaybettin! O geminin bana kaça patladığını biliyor musun? "+FindRussianMoneyString(iMoney)+"! Artık bana borçlusun...";
				link.l1 = "Senin için fazla olmaz mı? Unutma, sana zaten bir iyilik yaptım.";
				link.l1.go = "PiratesOnUninhabited_54";
				
				if(sti(PChar.money) >= iMoney)
				{
					link.l2 = "Lanet olsun sana ve o uğursuz gemine! Al paranı ve bir daha gözüme görünme!";
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;
		
		case "PiratesOnUninhabited_53":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_54":
			dialog.text = "Ve şimdi o iyiliğin bana ne faydası var?! Eğer kaptan "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_NOM)+" şimdi gemimle birlikte denizin dibinde! Artık ne payımı alabiliyorum, ne de gemimi geri alabiliyorum! Ne talih, bir serseri gibi lağımda ölmek!!!";
			link.l1 = "Ama neden? Senin için burada, hemen şimdi, görkemli bir cenaze ayarlayabilirim. Uygunsa tabii...";
			link.l1.go = "PiratesOnUninhabited_53";
		break;
		
		case "PiratesOnUninhabited_55":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// КОНЕЦ
		
		// Warship, 15.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Belki de... bir anlaşmaya varabiliriz, ne dersin? Eğer bize bir iyilik yaparsan, biz de karşılığını veririz, he-he.";
			link.l1 = "Bir iyilik mi? Peki mesele ne, karşılığında ne teklif ediyorsun?";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_2":
			LAi_Group_SetRelation("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, true);
			
			DialogExit();
			LAi_SetFightMode(PChar, true);
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Kaptanımız "+PChar.GenQuest.JusticeOnSale.SmugglerName+"   yerel devriye tarafından yakalandı  "+XI_ConvertString("Colony"+PChar.GenQuest.JusticeOnSale.CityId+"Gen")+". Onu hapiste tutuyorlar, ama asacak kadar delilleri yok. Onu kendimiz zorla çıkaramayız\n"+"Saygın bir adamsınız. Sizi herkes tanıyor. Belki pazarlık edebilir, kefaletle çıkarabilir ya da onu doğrudan satın alabilirsiniz? Bize güvenin, adamımızı aldığımız gibi adadan ayrılacağız, itibarınız da zarar görmeyecek!"; // belamour gen
			link.l1 = "Diyelim ki sana yardım edebilirim. Ama benim ödemem ne olacak?";
			link.l1.go = "JusticeOnSale_4";
			link.l2 = "Cehenneme git, şeytanın dölü! Seninle hiçbir işim olmaz!";
			link.l2.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Biraz Hint süsü ve tılsımı ister misin? Oldukça nadirdirler... Yoksa peşin para mı istersin? Birkaç bin peso, ne dersin?";
			link.l1 = "Cehenneme git, şeytanın tohumu! Seninle hiçbir işim olmaz!";
			link.l1.go = "JusticeOnSale_5";
			link.l2 = "Hindistan süslerine ilgim var. Sanırım kabul edeceğim.";
			link.l2.go = "JusticeOnSale_6";
			link.l3 = "Nakit bir denizcinin en iyi dostudur. Paranın kokusu olmaz, hepimiz biliyoruz. Katılıyorum.";
			link.l3.go = "JusticeOnSale_7";
		break;
		
		case "JusticeOnSale_5":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			DialogExit();
		break;
		
		case "JusticeOnSale_6":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 0; // Подрякушки.
			dialog.text = "Teşekkürler, Kaptan. Kefalet bedelini de ödülünüze ek olarak size ödeyeceğiz. Sanırım kaptanımız hakkında komutanla konuşmalısınız. Belki onu ikna edebilirsiniz. Onu çıkardıktan sonra, bize gelin "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", işte gemimiz oraya demir attı - "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" '"+PChar.GenQuest.JusticeOnSale.ShipName+"'. Seni kıyıda bekliyor olacağız."; // belamour gen
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_7":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 1; // Монеты.
			
			dialog.text = "Teşekkürler, Kaptan. Kefalet bedelini ödülünüze ek olarak size ödeyeceğiz. Sanırım kaptanımız hakkında komutanla konuşmalısınız. Belki onu ikna edebilirsiniz. Onu çıkardıktan sonra, bize gelin "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", işte gemimizin demir attığı yer orası - "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" '"+PChar.GenQuest.JusticeOnSale.ShipName+". Sizi kıyıda bekliyor olacağız."; // belamour gen
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			ReOpenQuestHeader("JusticeOnSale");
			AddQuestRecord("JusticeOnSale", "1");
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen")); // belamour gen
			PChar.GenQuest.JusticeOnSale.MayorWait = true;
			PChar.GenQuest.JusticeOnSale.PrisonWait = true;
			
			DialogExit();
		break;
		
		case "JusticeOnSale_9":
			if(hrand(1) == 0)
			{
				if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
				{
					// Награда побрякушками.
					dialog.text = "Buradayız, kaptan! O göbekli bürokratları kandırmakta harika iş çıkardın! İşte ödülün. Çocuklar, getirin şu ıvır zıvırları!";
				}
				else
				{
					// Награда золотом.
					dialog.text = "Buradayız, kaptan! O göbekli memurları kandırmakta harika bir iş çıkardın! İşte ödülün. Çocuklar, sandığı getirin!";
				}
				
				link.l1 = "Hakkımı ver ve defol!";
				link.l1.go = "JusticeOnSale_10";
			}
			else
			{
				// Массакра.
				dialog.text = "Buradayız, kaptan! Her şeyi güzelce ayarlamışsın görüyorum. Ama bak... şahitlere ihtiyacımız yok, o yüzden... Kaptana teşekkür edelim, çocuklar!";
				link.l1 = RandSwear()+"Seni ilk gördüğümde vurmalıydım!";
				link.l1.go = "JusticeOnSale_11";
			}
			chrDisableReloadToLocation = false;
		break;
		
		case "JusticeOnSale_10":
			DialogExit();
			if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddItems(PChar, "indian_"+(1+hrand(10)), 1);
				}
				else
				{
					AddItems(PChar, "obereg_"+(1+hrand(10)), 1);
				}
			}
			else
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 700 + hrand(2000));
				}
				else
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 500 + hrand(1000));
				}
			}
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_ActorGoToLocation(rChar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "none", "", "", "", 3.0);
			}
			AddQuestRecord("JusticeOnSale", "3");
			CloseQuestHeader("JusticeOnSale");
		break;
		
		case "JusticeOnSale_11":
			AddQuestRecord("JusticeOnSale", "4");
			CloseQuestHeader("JusticeOnSale");
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_Group_MoveCharacter(rChar, "JusticeOnSale_ShoreGroup");
			}
			
			LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		
		// belamour постоялец-->
		case "Unwantedpostor_room":
			dialog.text = ""+GetSexPhrase("Sen kimsin? Ve neden odama böyle dalıyorsun?","Vay canına. Sen de kimsin? Burası benim odam tabii ki, ama böyle bir misafire itirazım yok. Bu bir aşk mesajı mı?")+"";
			link.l1 = ""+GetSexPhrase("Artık senin değil. Han sahibi odayı bana kiraladı, sen de artık parasını ödemediğine göre buradan çıkmak üzeresin. Bunu kolay yoldan da halledebiliriz, zor yoldan da. Seçim senin.","Hayal görüyorsun. Bizim durumumuzda ise temizlik var. O yüzden toparlan ve buradan defol. Burası artık benim odam, çünkü senin aksine ben her zaman han sahiplerine paramı öderim.")+"";
			link.l1.go = "Unwantedpostor_room_1";
		break;
		
		case "Unwantedpostor_room_1":
			If(sti(pchar.reputation.fame) > 60)
			{
				dialog.text = ""+GetSexPhrase("Sanırım senin hakkında bir şeyler duydum. Tamam, kazandın, gidiyorum, hâlâ yaşamak istiyorum...","Hmm, senin hakkında çok şey duydum. Sanırım sadece dilin değil, zekân da keskin. Peki, kızma, oda senin.")+"";
				link.l1 = ""+GetSexPhrase("Doğru bir karar verdin.","Aferin oğlum.")+"";
				link.l1.go = "Unwantedpostor_peace";
				break;
			}
			dialog.text = ""+GetSexPhrase("Demek öyle, ha? Peki, ben zoru seçiyorum.","Seni kahpe! Sana iyi davranmak istemiştim...")+"";
			link.l1 = ""+GetSexPhrase("Dediğiniz gibi...","Ve sen buna 'nazikçe' mi diyorsun? Sana acıyorum. Gerçi, belki de acımıyorum.")+"";
			link.l1.go = "Unwantedpostor_fight";
		break;
		
		case "Unwantedpostor_peace":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			DeleteAttribute(PChar, "GenQuest.Unwantedpostor");
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 180, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "Fortune", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Sneak", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Leadership", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetFightMode(pchar, true);
			sld = characterFromId("Berglar_Unwantedpostor"); 
			LAi_SetWarriorType(sld);
			LAi_Group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_SetCheckMinHP(sld, 10, true, "Unwantedpostor_Win");
			LAi_SetCheckMinHP(pchar, 10, true, "Unwantedpostor_Lose");	
		break;
		
		case "Unwantedpostor_Win":
			dialog.text = ""+GetSexPhrase("Peki, tamam, dur! Beni öldürme. Gidiyorum.","Dur! Şimdi ne yapacağız, bu oda için birbirimizi mi öldüreceğiz?! Al başına çal, hepsi senin olsun. Pislik...")+"";
			link.l1 = ""+GetSexPhrase("Doğru karar. Bir dahaki sefere aklını kullan: herkes benim kadar iyi değildir, bazıları seni istemeden öldürebilir.","Adamlar.")+"";
			link.l1.go = "Unwantedpostor_Win_1";
		break;
		
		case "Unwantedpostor_Win_1":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) DeleteAttribute(PChar, "GenQuest.Unwantedpostor"); // полуночная драка
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 170+rand(20), false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "FencingL", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingS", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingH", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_Lose":
			dialog.text = ""+GetSexPhrase("Peki, beni kovdun mu? Defol git buradan, yoksa seni doğrarım.","Demek tek bildiğin şey gevezelik etmek. Hâlâ iyi bir ruh halinde olduğuma şükret, yoksa sana çok daha beterini yapardım. Şimdi defol git buradan!")+"";
			link.l1 = ""+GetSexPhrase("Lanet olsun...","Lanet olsun, seni hafife almışım... Tamam, tamam, şimdi gidiyorum.")+"";
			link.l1.go = "Unwantedpostor_Lose_1";
		break;
		
		case "Unwantedpostor_Lose_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sld = CharacterFromID("Berglar_Unwantedpostor");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) pchar.GenQuest.Unwantedpostor = "Lose"; // если драка за полночь перевалит
			DoQuestReloadToLocation(Locations[FindLocation(pchar.location)].fastreload+"_tavern", "reload", "reload2_back", "");	
		break;
		// <-- belamour постоялец
		
		// belamour пьяный матрос -->
		case "GuiltySailor":
			dialog.text = "Ha?.. Defol buradan, acemi, ben... hık!.. her önüne gelenle içmem.";
			link.l1 = "Sana öyle bir vuracağım ki, bir hafta boyunca içki içemeyeceksin.";
			link.l1.go = "GuiltySailor_1";
		break;
		
		case "GuiltySailor_1":
			dialog.text = "Ne?! Kiminle konuştuğunun farkında mısın? Ben, ' gemisinin tayfasıyım."+pchar.ship.name+"! Sadece kaptana haber vermem yeterli, şehri terk etmeye bile vaktin kalmaz! Hâlâ sağ salimken defol buradan."; 
			link.l1 = "...";
			link.l1.go = "GuiltySailor_2";
		break;
		
		case "GuiltySailor_2":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "GuiltySailor_3";
		break;
		
		case "GuiltySailor_3":
			dialog.text = "Kaptan?..";
			link.l1 = "Bir ay boyunca güverteyi temizleyeceksin.";
			link.l1.go = "GuiltySailor_4";
		break;
		
		case "GuiltySailor_4":
			NPChar.Dialog.currentnode = "GuiltySailor_Again";
			SetFunctionTimerCondition("GuiltySailor_NextQ", 0, 0, 45+rand(45), false);
			DialogExit();
		break;
		
		case "GuiltySailor_Again":
			dialog.text = "Üzgünüm, kaptan!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "GuiltySailor_Again";
		break;
		// <-- пьяный матрос
		
		// belamour хороший специалист -->
		case "ExpertSailor":
			int ExpertSailorVar = 1 + hrand(2);
			dialog.text = "Selam, kaptan! Senin kaptan olduğunu biliyorum, evet.";
			link.l1 = "Selam. Kaptan olduğumu nereden biliyorsun?";
			link.l1.go = "ExpertSailor_"+ExpertSailorVar;
		break;
		
		case "ExpertSailor_1": // матрос
			dialog.text = "Ha, I am a seasoned sea wolf, I've been sailing the seas for more than a decade. I was mainly engaged in sailing: sailed in calm, in storms, on a lugger, and even on a battleship. True, last month I was wounded after a hard battle; there was a fierce storm and no one dared climb the sail, so I did, but I paid the price for it. Luckily, I only twisted my ankle and couldn't walk for a few weeks. So they sent me ashore. Now I'm better and I'm sitting here, waiting for an opportunity.";
			link.l1 = "İlginç. Bu konuda uzman biri ekibimde olsa fena olmazdı. Mürettebatıma katılmak ister misin?";
			link.l1.go = "ExpertSailor_1_1";
		break;
		
		case "ExpertSailor_1_1":
			dialog.text = "Neden olmasın? Şimdiden geminin güvertesini ve taze rüzgarla dolan yelkenlerin sesini özledim. Gerekirse ekibini de çalıştırabilirim. Ama baştan söyleyeyim, hemen bin peso isterim, yoksa ceplerim zaten boş. Gerçi, takımın geri kalanı da öyle. Dürüst biriyimdir.";
			link.l1 = "Hayır, muhtemelen reddedeceğim. Her denizciye gemiye katılması için bin peso ödersem, iflas ederim. Beni suçlama.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Anlaştık. İyi bir uzman için bin peso gözümde yok. Dur... al. Ve seni gemide bekliyor olacağım.";
				link.l2.go = "ExpertSailor_payS";
			}
		break;
		
		case "ExpertSailor_nomoney":
			DialogExit();
			NPChar.Dialog.currentnode = "ExpertSailor_Again";
		break;
		
		case "ExpertSailor_payS":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Sailors", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_2": // канонир
			dialog.text = "Ha, ben denizlerde yıllarını geçirmiş bir deniz kurduyum, on yılı aşkın süredir denizlerdeyim. Çoğunlukla topların başında durdum: falconetlerden, carronadelardan, culverinlerden, sakerlerden ateş ettim... bir luggerde, hatta bir savaş gemisinde bile görev yaptım. Doğrusu, geçen ay ağır bir çarpışmadan sonra yaralandım, misket güllelerinden birinin sekmesi bacağıma geldi, ciddi bir şey değil, sadece bir çizik, bu yüzden beni karaya çıkardılar. Şimdi iyiyim ve burada oturmuş, bir fırsat bekliyorum.";
			link.l1 = "İlginç. Bu konuda uzman birini ekibimde görmek isterim. Ekibime katılmak ister misin?";
			link.l1.go = "ExpertSailor_2_1";
		break;
		
		case "ExpertSailor_2_1":
			dialog.text = "Neden olmasın? Şimdiden top güvertesini, barutun kokusunu ve topların gürültüsünü özledim. Gerekirse ekibini de eğitebilirim. Ama baştan söyleyeyim, bin peso isterim, yoksa cebim boş kalır. Ve diğerleri gibi ben de dürüst bir adamım.";
			link.l1 = "Hayır, muhtemelen reddedeceğim. Her denizciye gemiye katılması için bin peso ödersem iflas ederim. Beni suçlama.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Anlaştık. İyi bir uzmana bin peso vermek umurumda değil. Dur bir... al bakalım. Ve seni gemide bekliyor olacağım.";
				link.l2.go = "ExpertSailor_payС";
			}
		break;
		
		case "ExpertSailor_payС":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Cannoners", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_3": // солдат
			dialog.text = "Ha, ben denizlerde yıllarını geçirmiş bir deniz kurduyum, on yıldan fazla zamandır denizlerdeyim. Genellikle gemi baskınlarında savaştım: korsanlarla ve düzenli ordularla çarpıştım, her türlü silahı kullanmayı bilirim, bir luggerda ve hatta bir savaş gemisinde görev yaptım. Doğru, geçen ay zorlu bir dövüşten sonra yaralandım, sadece sırtımda küçük bir pala çizği—korkak yüzüme bakamadı ama ben onu öldürdüm. Ah, o çizği gördüklerinde yüzlerini görmeliydin, ha-ha. Sonra beni karaya gönderdiler. Şimdi iyileştim ve burada bir fırsat bekliyorum.";
			link.l1 = "İlginç. Bu konuda bir uzmana sahip olmak fena olmazdı. Mürettebatıma katılmak ister misin?";
			link.l1.go = "ExpertSailor_3_1";
		break;
		
		case "ExpertSailor_3_1":
			dialog.text = "Neden olmasın? Zaten kılıçların şakırtısını, gemilerin birbirine yaklaşırken çıkardığı gürültüyü ve savaşın adrenalinini özledim. Gerekirse ekibini de eğitebilirim. Ama peşin olarak bin peso istemek zorundayım, çünkü ceplerim zaten bomboş. Ve ekibin geri kalanı gibi, ben de dürüst bir adamım.";
			link.l1 = "Hayır, muhtemelen reddedeceğim. Her denizciye katılması için bin peso ödersem iflas ederim. Beni suçlama.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Anlaştık. İyi bir uzmana bin peso ödemek umurumda değil. Dur... al. Ve seni gemide bekliyor olacağım.";
				link.l2.go = "ExpertSailor_payA";
			}
		break;
		
		case "ExpertSailor_payA":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Soldiers", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_Again":
			dialog.text = "Denizde bol şanslar, kaptan!";
			link.l1 = "Sen de.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ExpertSailor_Again";
		break;
		// <-- хороший специалист
		
		//belamour ночной приключенец -->
		// матрос -->
		case "NightAdventure_Sailor":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Se-sen kimsin?";
			link.l1 = "Ben kaptanım "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Üzgünüm dostum, acelem var.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_SailorTavern":          link.l1.go = "NightAdventure_Sailor_1_1"; break; // до таверны
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1"; break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1"; break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorBoat":      		 link.l1.go = "NightAdventure_Sailor_3_1"; break; // до пирса
				case "NightAdventure_SailorShip":            link.l1.go = "NightAdventure_Sailor_3_1"; break;
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";       break; // наезд
			}
		break;
		// до таверны 
		case "NightAdventure_Sailor_1_1":
			dialog.text = "Kaptan?.. hıçk! K-kaptan... beni meyhaneye götür... hıçk!.. ha? Lütfen. Sanırım... bu k-koloni de kayboldum, evet... hıçk!..";
			link.l1 = "Bırak beni, vaktim yok!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Pekâlâ, gidelim. Oraya tek başına gidebilecek gibi görünmüyorsun.";
			link.l2.go = "NightAdventure_Sailor_1_2";
		break;
		
		case "NightAdventure_Sailor_1_2":
			dialog.text = "Sadece... hık!.. y-yavaşça, lütfen. Ben... hık!.. ayakta... duramıyorum...";
			link.l1 = "Pekâlâ, hadi gidelim, yavaşça.";
			link.l1.go = "NightAdventure_Sailor_tavern";
		break;
		
		case "NightAdventure_Sailor_tavern":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorTavern"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// шулер
		case "NightAdventure_Sailor_2_1":
			dialog.text = "Kaptan?.. hıç!.. K-kaptan... yardım et bana!";
			link.l1 = "Bırak beni, vaktim yok!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Senin neyin var?";
			link.l2.go = "NightAdventure_Sailor_2_2";
		break;
		
		case "NightAdventure_Sailor_2_2":
			dialog.text = "Orada... meyhanede... hık!.. Kartçı!";
			link.l1 = "Peki, bunda ne var ki? Herhangi bir kolonideki herhangi bir meyhanede, yerlerdeki toprak kadar kart hilesi yapanlar var.";
			link.l1.go = "NightAdventure_Sailor_2_3";
		break;
		
		case "NightAdventure_Sailor_2_3":
			dialog.text = "K-kaptan, siz... anlamıyorsunuz... hık!... Beni bir kuruşsuz bıraktı! Hık!.. Sonra da... kovdu beni... hık!..";
			link.l1 = "Şimdi benden ne istiyorsun?";
			link.l1.go = "NightAdventure_Sailor_2_4";
		break;
		
		case "NightAdventure_Sailor_2_4":
			dialog.text = "Benimle g-gel... hık!... Onunla ilgilen! B-beni... hık!... paramı geri vermeye zorl-a! hık!..";
			link.l1 = "Masada bir sarhoşu yenmek için kart ustası olman gerekmez. Bir dahaki sefere daha az iç.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Peki, buna neden ihtiyacım var, ha? .. Tamam, hadi gidelim, bakalım şu kart ustanı görelim.";
			link.l2.go = "NightAdventure_Sailor_2_5";
		break;
		
		case "NightAdventure_Sailor_2_5":
			dialog.text = "Sadece... hık!.. y-yavaşça, lütfen. Ben... hık!.. ayakta... duramıyorum...";
			link.l1 = "Pekâlâ, yavaşça gidelim.";
			link.l1.go = "NightAdventure_Sailor_gambler";
		break;
		
		case "NightAdventure_Sailor_gambler":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorGambler"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// диалог в таверне с матросом
		case "NA_SailorTavern":
			dialog.text = "K-kaptan... hık!.. çok teşekkür ederim... bana gerçekten yardım ettiniz! B-ben... buyurun... hık!.. Bu sizin için.";
			link.l1 = "Hadi, boşver... Artık böyle içme. Ya da en azından, bela arama.";
			link.l1.go = "NA_SailorTavern_1";
		break;
		
		case "NA_SailorTavern_1":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор про  шулера
		case "NA_SailorGambler":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShuler0")
			{
				dialog.text = "K-kaptan!.. Şey... Hık!.. Kartçı!..";
				link.l1 = "Kim, ben mi? Kart hilesi mi?";
				link.l1.go = "NA_SailorGamblerBelka";
			}
			else	
			{
				dialog.text = "İşte orada, kaptan! Hık!.. M-masada oturuyor...";
				link.l1 = "Hadi...";
				link.l1.go = "NA_SailorGamblerCards"; 
			}
					
		break;
		// шулер сбежал
		case "NA_SailorGamblerBelka": 
			dialog.text = "Hayır... hık!... Sharper!... Kayboldu!...";
			link.l1 = "Pekâlâ, gitti, yani seni beklemedi.";
			link.l1.go = "NA_SailorGamblerBelka_1";
		break;
		
		case "NA_SailorGamblerBelka_1":
			dialog.text = "Ve sonra... n-ne olacak? Hık!..";
			link.l1 = "Artık yapabileceğin bir şey yok. Gece gece koloninin her yerinde onu arayacak değilim. Bir daha böyle içme. Ya da en azından sarhoşken kumar oynama.";
			link.l1.go = "NA_SailorGamblerBelka_2";
		break;
		
		case "NA_SailorGamblerBelka_2":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		// шулер остался таверне
		case "NA_SailorGamblerCards":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			iNation = npchar.nation
			iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank);
			iScl = 15 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("NightAdventure_CardProf", "citiz_"+(rand(9)+11), "man", "man", iRank, iNation, 1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
			sld.dialog.filename    = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "NightAdventure_CardProf";
			sld.greeting = "player";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			AddMoneyToCharacter(sld, sti(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(sld, "totem_13");
			FreeSitLocator(pchar.location, "sit_front4");
			ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit_front4");
			LAi_SetSitType(sld);
			chrDisableReloadToLocation = false;
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор с самим шулером
		case "NightAdventure_CardProf":
			dialog.text = "Bir zar oyunu öneriyorum. Var mısın?";
			link.l1 = "Olmaz. Bu geminin kaptanıyım ve üçkağıtçılarla oyun oynamam. Ama eğer şu iyi adama parasını geri vermezsen kaburgalarını kolayca kırabilirim.";
			link.l1.go = "NightAdventure_CardProf_1";
		break;
		
		case "NightAdventure_CardProf_1":
			dialog.text = "Kartçılarla mı?! Ben kartçı mıyım? Parayı kime iade edeceğim, o sarhoşa mı?! Beni kırıyorsun kaptan...";
			link.l1 = "Daha da saldırgan olabilirim. Parayı geri ver.";
			link.l1.go = "NightAdventure_CardProf_2";
		break;
		
		case "NightAdventure_CardProf_2":
			dialog.text = "Evet, ben bir kart hilesi değilim! Dürüst bir oyuncuyum. Şans kazanır, ve arkadaşın sadece şanssızdı, hepsi bu.";
			link.l1 = "Şans, ha? Zarlarını ver, bakalım ne kadar şanslı düşecekler.";
			link.l1.go = "NightAdventure_CardProf_3";
		break;
		
		case "NightAdventure_CardProf_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveMoney") // отдал деньги
			{
				AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money));
				dialog.text = "Pekala, pekala, sakin ol kaptan. Sarhoşu yendim, biraz da hile yaptım ama herkes böyle oynuyor zaten. Al, işte onun parası.";
				link.l1 = "İşte bu daha iyi. Ve umarım anlıyorsun, eğer arkadaşım şimdi bunun tam miktar olmadığını söylerse, tekrar sana geleceğim?";
				link.l1.go = "NightAdventure_CardProf_GiveMoney";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveOk") // играл честно
			{
				dialog.text = "Evet, lütfen, işte zarlarım. İki set de burada. Kontrol et. Saklayacak hiçbir şeyim yok.";
				link.l1 = "Yani... Çift... Hiçbir şey... Çift... Full... Hiçbir şey... Hiçbir şey... İki Çift... Üçlü... Hiçbir şey... Çift...";
				link.l1.go = "NightAdventure_CardProf_Ok";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerFight") // драка
			{
				dialog.text = "Evet, lütfen, işte zarlarım. İki set de burada. Kontrol et. Saklayacak hiçbir şeyim yok.";
				link.l1 = "Yani... Kare... Kare... Full house... Full house... Kare... Poker... Full house... Poker... Kare... Full house... Hm, bunu bana nasıl açıklayacaksın?";
				link.l1.go = "NightAdventure_CardProf_Fight";
			}
		break;
		// разошлись миром
		case "NightAdventure_CardProf_GiveMoney":
			dialog.text = "Her şeyi anladım, işte tam tutar. Sana ve arkadaşına bol şans.";
			link.l1 = "Sen de.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_1";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_GiveMoney_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// матрос забирает свои деньги
		case "NightAdventure_CardProf_GiveMoney_2":
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			dialog.text = "Ama... o bunu kabul etmek istemedi! Hık!..";
			link.l1 = "Evet, kaçmaya çalıştım. Al, paranı tut.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_3";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_3":
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
			dialog.text = "K-kaptan... hık!.. çok teşekkür ederim... bana gerçekten yardım ettin! Ben... 'yan tarafa kusar'... al bakalım... hık!.. Bu senin için.";
			link.l1 = "Hadi ama, ugh... boşver... Bir daha böyle içme. Ya da en azından sarhoşken kumar oynama.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_4";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// играл честно
		case "NightAdventure_CardProf_Ok":
			dialog.text = "Peki? İkna oldun mu?";
			link.l1 = "Hmm, gerçekten de sıradan zarlar gibi görünüyorlar ...";
			link.l1.go = "NightAdventure_CardProf_Ok_1";
		break;
		
		case "NightAdventure_CardProf_Ok_1":
			dialog.text = "Sana söyledim. Arkadaşın da sadece sarhoş. Yenildiğini kabul edemediği için seni de buraya getirdi.";
			link.l1 = "Pekala, yaşananlar için üzgünüm. İyi şanslar.";
			link.l1.go = "NightAdventure_CardProf_Ok_2";
		break;
		
		case "NightAdventure_CardProf_Ok_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_Ok_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// подходит матрос
		case "NightAdventure_CardProf_Ok_3":
			dialog.text = "Yani... hık!.. ne oldu?.. O... hık!.. bir üçkağıtçı değil miymiş?..";
			link.l1 = "Pekâlâ, dürüstçe oynamış gibi görünüyor.";
			link.l1.go = "NightAdventure_CardProf_Ok_4";
		break;
		
		case "NightAdventure_CardProf_Ok_4":
			dialog.text = "Ve sonra... n-ne olacak? Hık!..";
			link.l1 = "Artık yapabileceğin bir şey yok. Adam seni gerçekten yendi. Bir daha böyle içme. Ya da en azından sarhoşken kumar oynama.";
			link.l1.go = "NightAdventure_CardProf_Ok_5";
		break;
		
		case "NightAdventure_CardProf_Ok_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// драка 
		case "NightAdventure_CardProf_Fight":
			dialog.text = "Şans. Sadece şanslıydın, hepsi bu. Şans, kaprisli bir hanımdır.";
			link.l1 = "Hmm, gerçekten öyle mi. O halde seninle oynayalım, ama unutma, ben bu zarlarla oynarım!";
			link.l1.go = "NightAdventure_CardProf_Fight_1";
		break;
		
		case "NightAdventure_CardProf_Fight_1":
			dialog.text = "Bunlar mı?.. Yani... Hayır, seninle oynamak istemiyorum! Beni aşağıladın. Hem zaten, beş kuruşum yok...";
			link.l1 = "Belki de bu meyhanedeki herkese zarlarını anlatmamı istersin? Ya da onlara göstereyim mi? Sonra da onlara şanstan bahsedersin. Ne dersin?";
			link.l1.go = "NightAdventure_CardProf_Fight_2";
		break;
		
		case "NightAdventure_CardProf_Fight_2":
			dialog.text = "Ne?! Sen kendini ne sanıyorsun?! Beni tehdit mi ediyorsun?! Şimdi defolup gitmezsen, üstünde birkaç delik açarım!";
			link.l1 = "Ben burada kalıp herkesin senin zarlarını görmesini tercih ederim.";
			link.l1.go = "NightAdventure_CardProf_Fight_3";
		break;
		
		case "NightAdventure_CardProf_Fight_3":
			dialog.text = "Pekâlâ, buraya gel, leş kargası!";
			link.l1 = "Pantolonunu kaybetme.";
			link.l1.go = "NightAdventure_CardProf_Fight_4";
		break;
		
		case "NightAdventure_CardProf_Fight_4":
			LAi_LocationDisableOfficersGen(pchar.location, true); // офицеров не  пускать
			SetFunctionLocationCondition("NightAdventure_Duel", Locations[FindLocation(pchar.location)].fastreload+"_town", false);
			pchar.quest.NightAdventure_KillPhant.over = "yes";
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// матрос на выходе
		case "NightAdventure_CardProf_Fight_5":
			dialog.text = "K-kaptan?.. Sen... hık!.. kavga mı ettin?.. Ve bu... hık!.. d-daha mı keskin?";
			link.l1 = "Kendisi yumruk yedi. Artık kimseyle oynamayacak.";
			link.l1.go = "NightAdventure_CardProf_Fight_6";
		break;
		
		case "NightAdventure_CardProf_Fight_6":
			dialog.text = "Ama... o bunu kabul etmek istemedi! Hık!..";
			link.l1 = "Evet, bundan kaçmaya çalıştı. Sende olan parası yoktu. Muhtemelen harcamıştır.";
			link.l1.go = "NightAdventure_CardProf_Fight_7NM";
			link.l2 = "Evet, kaçmaya çalıştı. Al, paran burada.";
			link.l2.go = "NightAdventure_CardProf_Fight_7";
		break;
		
		case "NightAdventure_CardProf_Fight_7NM": // скажем, что нет денег
			ChangeCharacterComplexReputation(pchar,"nobility", -5); 
			ChangeOfficersLoyality("bad", 2); 
			dialog.text = "Ve şimdi... s-sonra ne olacak? Hık!..";
			link.l1 = "Artık yapabileceğin bir şey yok. Dürüstçe seni yendi. Bir daha böyle içme. Ya da en azından sarhoşken kumar oynama.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
		break;
		
		case "NightAdventure_CardProf_Fight_7": // деньги есть
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			ChangeCharacterComplexReputation(pchar,"nobility", 3); 
			ChangeOfficersLoyality("good", 1); 
			dialog.text = "K-kaptan... hık!.. çok teşekkür ederim... bana gerçekten yardım ettin! Ben... 'yan tarafa kusar'... al bakalım... hık!.. Bu senin için.";
			link.l1 = "Hadi ama, ugh... boşver... Bir daha böyle içme. Ya da en azından sarhoşken kumar oynama.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
		break;
		
		case "NightAdventure_CardProf_Fight_End": 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DialogExit();
			
		break;
		// проводить до пирса
		case "NightAdventure_Sailor_3_1":
			dialog.text = "Kaptan?.. hık!.. K-kaptan... beni i-i-skeleye götür... hık!.. ha? Lütfen. B-ben... hık!.. g-gemeye gitmem lazım... Usta Gemici... k-küfredecek... hık!.. eğer g-geç kalırsam...";
			link.l1 = "Çekil önümden, vaktim yok!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Pekala, gidelim. Oraya tek başına gidebilecek gibi görünmüyorsun";
			link.l2.go = "NightAdventure_Sailor_3_2";
		break;
		
		case "NightAdventure_Sailor_3_2":
			dialog.text = "Sadece... hık!.. y-a-vaşça, lütfen. Ben... hık!.. dayanamıyorum...";
			link.l1 = "Peki, yavaşça gidelim.";
			link.l1.go = "NightAdventure_Sailor_3_3";
		break;
		
		case "NightAdventure_Sailor_3_3":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorBoat")
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorBoat"; 
			}
			else
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorShip"; 
			}
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocatorCondition("NightAdventure_ToBoat",  npchar.City+"_town", "quest", "quest1", false)
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		// вариант просто проводить
		case "NA_SailorBoat":
			dialog.text = "K-kaptan... hık!.. çok teşekkür ederim... bana gerçekten yardım ettin! Ben... 'yan tarafa kusar'... al bakalım... hık!.. Bu senin için.";
			link.l1 = "Hadi ama, ugh... boşver... Artık böyle içme. Ya da en azından macera aramaya çıkma.";
			link.l1.go = "NA_SailorBoat_1";
		break;
		
		case "NA_SailorBoat_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13)  {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19)  {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25)  {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", -1); 
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// просится на корабль
		case "NA_SailorShip":
			dialog.text = "K-kaptan!.. Gemi!";
			link.l1 = "Hangi 'gemi'?";
			link.l1.go = "NA_SailorShip_1";
		break;
		
		case "NA_SailorShip_1":
			dialog.text = "G-gemi!.. Nerede o?.. hık!..";
			link.l1 = "Belli ki gitti. Meyhanelerde daha az içmelisin. Koca gemi bir sarhoş denizciyi bekleyecek değil ya.";
			link.l1.go = "NA_SailorShip_2";
		break;
		
		case "NA_SailorShip_2":
			dialog.text = "Ama ben... hık!... sarhoş değilim... neredeyse... belki...";
			link.l1 = "Ah, evet, gerçekten. İyi şanslar.";
			link.l1.go = "NA_SailorShip_3";
		break;
		
		case "NA_SailorShip_3":
			dialog.text = "Bekle, k-kaptan! B-beni... hık!.. gemine götür! Bir daha... hık!.. i-içmeyeceğim...";
			if(GetFreeCrewQuantity(pchar) > 0)
			{
				link.l1 = "Peki, ne yapabilirsin ki. Ama doğruca gemiye git. Sakın bir yerde sarhoş yakalanayım deme, bir sonraki limana kadar güverteyi temizlersin.";
				link.l1.go = "NA_SailorShip_4";
			}
			link.l2 = "Yani maaşımla sarhoş olup sonra seni kolonideki her meyhanede ve kapı önünde aramak zorunda mı kalacağım? Hayır, böyle bir mutluluğa ihtiyacım yok.";
			link.l2.go = "NA_SailorShip_6";
			
		break; 
		
		case "NA_SailorShip_4": 
			AddCharacterCrew(pchar, 1);
			dialog.text = "Evet, k-kaptan!.. hık!..";
			link.l1 = "...";
			link.l1.go = "NA_SailorShip_5";
		break;
		
		case "NA_SailorShip_5": 
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", 5.0); // побежит вдохновленный 
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NA_SailorShip_6": 
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload4_back");
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NightAdventure_OpenLoc", -1);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// пьяные наезды
		case "NightAdventure_Bull":
			switch (rand(5))
			{
				case 0:
				dialog.text = "Kaptan?.. hık!.. Sen... kara faresi... hık!.. kaptan falan değilsin!..";
				link.l1 = "Senin gibi yüzlercesini gemi baskınlarında biçtim, o yüzden defol git, sarhoş.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 1:
				dialog.text = "Kaptan... hık!.. B-baskının o teknesinin kaptanı mı?.. hık!..";
				link.l1 = "Eğer denizdeyken bu tekneyi ufukta görürsen, doğrudan suya atlamak en iyisi: köpekbalıklarıyla hayatta kalma şansın, gemimle karşılaşmaktan daha yüksek. Şimdi defol git!";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 2:
				dialog.text = "Kaptan mı?.. hık!.. Sen kaptan değil, süt içicisin!.. A-annen daha bir kız çocuğuydu... hık!.. ben denizlerde çoktan yol alırken...";
				link.l1 = "Ama annen, benim gibi bir oğlanın kaptan olduğunu, seninse hâlâ güverteleri ovmaktan başka bir işe yaramayan sarhoş bir denizci olarak kaldığını duysa muhtemelen sevinirdi.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 3:
				dialog.text = "Kaptan?.. Dikkat et... hık!.. Kaptan... Dişlerini dökerim... hık!.. Gözünü bile açamadan işini bitiririm!..";
				link.l1 = "Geri tepme öldürür. Çık dışarı! Cesaretin varsa dişlerimi kır...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 4:
				dialog.text = "Kaptan?.. Görünüşe bakılırsa... hık!.. b-bir çeşit serseri...";
				link.l1 = "Galiba henüz kendine aynada bakmadın...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 5:
				dialog.text = "K-kaptan?.. Ben... hic!.. senin geminde hizmet etmeye... hic!.. asla razı olmazdım... hic!..";
				link.l1 = "Ve kimse seni gemime davet etmedi, bu yüzden kabul etmek için bir sebebin yoktu. Çekil önümden.";
				link.l1.go = "NightAdventure_End";
				break;
			}
		break;
		
		case "NightAdventure_End":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_Again";
		break;
		
		case "NightAdventure_Again":
			NextDiag.TempNode = "NightAdventure_Again";
			dialog.text = "Hik!..";
			link.l1 = "Uyu.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_SailorAgain":
			dialog.text = "Hıç!.. Evet... hâlâ uzak mı?.. ";
			link.l1 = "Yaklaştık, sabırlı ol.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- матрос
		// горожанин -->
		case "NightAdventure_Citizen":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "S-sen... hık!.. kimsin?..";
			link.l1 = "Ben Kaptanım "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Üzgünüm dostum, acelem var.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_CitizenHomie":          link.l1.go = "NightAdventure_Citizen_1_1"; break; // выручить приятеля
				case "NightAdventure_CitizenHomieSolderNM":  link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_CitizenHomieSolderGM":  link.l1.go = "NightAdventure_Citizen_1_1"; break;
				case "NightAdventure_CitizenHomieOfficer":   link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1";  break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1";  break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";        break;// наезд
			}
		break;
		
		// дружок
		case "NightAdventure_Citizen_1_1":
			dialog.text = "Kaptan?.. hık!.. K-kaptan... yardım et bana! B-ben... yani... hık!.. arkadaşım... gerçekten senin y-yardımına ihtiyacı var! Lütfen.";
			link.l1 = "Gece yarısı karşılaştığım her sarhoşun derdini çözecek değilim.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Pekala, oradaki arkadaşına ne olduğunu anlat bakalım.";
			link.l2.go = "NightAdventure_Citizen_1_2";
		break;
		
		case "NightAdventure_Citizen_1_2":
			dialog.text = "Arkadaşım ... yani, aslında ... sarhoş oldu. Yani genel olarak ... hık! .. sarhoş oldu ...";
			link.l1 = "Elbette, görev başında içki içen tayfaları ayıltmayı başardım, ama bunu oldukça sert yöntemlerle yaptım. Sanırım arkadaşınızın buna ihtiyacı yok.";
			link.l1.go = "NightAdventure_Citizen_1_3";
		break;
		
		case "NightAdventure_Citizen_1_3":
			dialog.text = "Hayır! O... o muhafızlarla birlikte! Onlarla tartıştı... Sonra kavga çıktı. Ve o... hık!.. hapse atıldı... sadece sarhoş!";
			link.l1 = "Şimdi benden ne istiyorsun? Kendi suçu: daha az içmeliydi. Ya da en azından başına iş açmaya kalkışmamalıydı...";
			link.l1.go = "NightAdventure_Citizen_1_4";
		break;
		
		case "NightAdventure_Citizen_1_4":
			dialog.text = "Gardiyanla konuş, kaptan... hık! .. kaptan! O bırakır... onu bırakır! Hmm... işte burada... hık!.. ne şanslısın... Arkadaşım az önce... tartıştı... yani... ve yüzüme yumruk atmak istedi... ama... hık!.. silah bulamadı...";
			link.l1 = "Şimdi geceleri gardiyanlarla kavga eden sarhoşları hapisten çıkarmaktan başka işim kalmadı. Yok, bırak orada birkaç gün otursun. Belki bir dahaki sefere iki kere düşünürsün.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Pekâlâ, cehenneme kadar yolun var. Tamam, gardiyanla konuşacağım.";
			link.l2.go = "NightAdventure_Citizen_1_5";
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && !CheckNationLicence(HOLLAND))
			{
				link.l2 = "Gardiyanın aksanımı beğeneceğinden pek emin değilim. Sonra valiye rapor eder zaten. O yüzden bensiz devam et.";
				link.l2.go = "NightAdventure_Citizen_RE";
			}
			if(ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
			{
				link.l2 = "Korkarım dostum, buranın zindanlarına giden yol bana kapalı. Gardiyan portremi bir ikon gibi saklıyor ve onların o misafirperver odalarına yerleşmeye hiç niyetim yok. Üzgünüm, sana yardımcı olamam.";
				link.l2.go = "NightAdventure_Citizen_NR";
			}
		break;
		
		case "NightAdventure_Citizen_1_5":
			DialogExit();
			pchar.GenQuest.NightAdventureToJail = true;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			chrDisableReloadToLocation = true; //закрыть локацию пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_CitizenHomiePresent":
			dialog.text = "S-sağ olun... Kaptan. Arkadaşım için de. B-bu... sizin için.";
			link.l1 = "Bir dahaki sefere, arkadaşın sarhoş olup muhafızlarla kavga etmeye kalkışınca gözünü üzerinde tut. Her gece kaptanlar sokaklarda dolaşıp, birkaç ayyaş için gardiyanla pazarlık yapmaya hazır olmuyor. İyi şanslar.";
			link.l1.go = "NightAdventure_CitizenHomiePresent_1";
		break;
		
		case "NightAdventure_CitizenHomiePresent_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5.0);
			sld = characterFromId("NightAdventure_Homie");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			if(GetDataDay() < 7) 						{GiveItem2Character(pchar, "indian_2");  Log_Info("You've received amulet 'Gunpowder tester'");}
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "obereg_5");  Log_Info("You've received amulet 'Jade turtle'");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "obereg_6");  Log_Info("You've received amulet 'Monkey's fist'");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "obereg_8");  Log_Info("You've received amulet 'Merchant's beads'");}
			if(GetDataDay() == 25) 		    			{GiveItem2Character(pchar, "indian_9");  Log_Info("You've received amulet 'Baldo'");}
			if(GetDataDay() == 26) 	    				{GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			if(GetDataDay() >= 27 && GetDataDay() < 31) {GiveItem2Character(pchar, "obereg_4");  Log_Info("You've received amulet 'Gypsy's fan'");}
			if(GetDataDay() == 31) 	    				{GiveItem2Character(pchar, "amulet_11"); Log_Info("You've received amulet 'Cimaruta'");}
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_Citizen_RE":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)  < (rand(100)+rand(100)))
			{
				dialog.text = "Ah!.. Demek biliyorum nasıl... hık!.. arkadaşımı kurtaracağımı... h-hapiste... hık!.. Muhafızlar! Şehirde bir c-asus var!.. hık!..";
				link.l1 = "Arkadaşını kurtarmak için çok kötü bir yol seçmişsin.";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Ah, y-yabancı ... hık! .. Sen... sen başını belaya sokacaksın ... hık! .. Tamam... burada ... hık! .. her şey kontrol altında.";
				link.l1 = "Elbette. Bir şey olursa hemen sana gelirim.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Citizen_NR":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE) < (rand(100)+rand(100)))
			{
				dialog.text = "Ah ... demek sen ... hık! .. Sen bir suçlusun! Muhafızlar!";
				link.l1 = "Demek artık böyle konuşuyorsun!";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Ah, nasıl... hık! .. pardon. Ya eğer... sen bana izin versen... gardiyanla senin için... hık!.. pazarlık yapayım, ve sen de... hık!.. b-benim arkadaşım için?..";
				link.l1 = "Hayır, benim için pazarlık etmene gerek yok, sağ ol. İyi şanslar.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Fight":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			LAi_group_Attack(NPChar, Pchar);
		break;
		// контрабандист 
		case "NightAdventure_Pirate": 
			LAi_RemoveLoginTime(npchar);
			dialog.text = "S-sen... hık!.. kimsin?...";
			link.l1 = "Ben Kaptan "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Üzgünüm dostum, acelem var.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_Bull":          		 link.l1.go = "NightAdventure_Bull";       break; // пьяные наезды
				case "NightAdventure_PiratePeace":           link.l1.go = "NightAdventure_PirateCave"; break; // до пещеры
				case "NightAdventure_PirateBad":             link.l1.go = "NightAdventure_PirateCave"; break;
			}
		break;
		
		case "NightAdventure_PirateCave":
			dialog.text = "Kaptan?.. hık!.. K-kaptan... dinle, beni şehrin yakınındaki mağaraya götür... hık!.. ha? L-lütfen.";
			link.l1 = "Mağaraya mı? Anlamadım. Neden mağaraya gidiyorsun? Ve neden bana ihtiyacın var?";
			link.l1.go = "NightAdventure_PirateCave_1";
		break;
		
		case "NightAdventure_PirateCave_1":
			dialog.text = "Bakın... k-kaptan... hık!.. İçki için param bitti... Ve... hık!.. bir mağarada... bir zula var, yani... hık!.. Ama ben... şey... gece... o o... ormanda tek başıma gitmeye... hık!.. korkuyorum... Yani...";
			link.l1 = "Çekil önümden, vaktim yok!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Pekâlâ, hadi gidelim. Oraya tek başına gidebilecek gibi görünmüyorsun";
			link.l2.go = "NightAdventure_PirateCave_2";
		break;
		
		case "NightAdventure_PirateCave_2":
			dialog.text = "Sadece... hık!.. y-a-vaşça, lütfen. Ben... hık!.. dayanamıyorum...";
			link.l1 = "Pekala, yavaşça gidelim.";
			link.l1.go = "NightAdventure_PirateCave_3";
		break;
		
		case "NightAdventure_PirateCave_3":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = true; // что взяли квест
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			string NAIsland = GetIslandByCityName(npchar.city);
			string NACave = "absent. Tell belamour that you are";
			// найти пещеру на острове
			i = Findlocation(NAIsland+"_Grot");
			if(i != -1) NACave = NAIsland+"_Grot";
			i = Findlocation(NAIsland+"_Cave");
			if(i != -1) NACave = NAIsland+"_Cave";
			// для мейна и капстервиля
			i = Findlocation(npchar.city+"_Cave");
			if(i != -1) NACave = npchar.city+"_Cave";
			i = Findlocation(npchar.city+"_Grot");
			if(i != -1) NACave = npchar.city+"_Grot";
			
			log_testinfo("Cave "+NACave+" on the island " +NAIsland);
			SetFunctionLocationCondition("NightAdventure_InCave", NACave, false);
			SetFunctionLocationCondition("NightAdventure_InFort", npchar.city+"_ammo", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_PirateCave_4": // диалог в пищере
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PiratePeace")
			{
				AddMoneyToCharacter(pchar, 1000);
				TakeNItems(pchar, "potionrum", 1);   
				TakeNItems(pchar, "potionwine", 1);
				PlaySound("interface\important_item.wav");
				Log_Info("You've received an alcohol")
				dialog.text = "K-kaptan... hık!.. çok teşekkür ederim... bana gerçekten yardım ettiniz! B-ben... al bakalım... hık!.. Bu senin için.";
				link.l1 = "Hadi ama, ıh... boşver... Bir daha böyle içme.";
				link.l1.go = "NightAdventure_PirateCave_4_1";
				break;
			} 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PirateBad")
			{
				dialog.text = "Harika, kaptan! Kabul ettiğine sevindim.";
				link.l1 = "Peki, hazine nerde? Bir dakika, galiba sarhoş değilsin.";
				link.l1.go = "NightAdventure_PirateCave_5";
				break;
			} 
		break;
		
		case "NightAdventure_PirateCave_4_1": // мирный исход
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
		break;
		
		case "NightAdventure_PirateCave_5": // драка
			dialog.text = "Evet, fazla içmedim, benim için endişelenme. Ve o saklama yeri hakkında ... Arkadaşlar!";
			link.l1 = "...";
			link.l1.go = "NightAdventure_PirateCave_6";
		break;
		
		case "NightAdventure_PirateCave_6": 
			DialogExit();
			AddDialogExitQuestFunction("NightAdventure_PiratesInCave");
		break;
		
		case "NightAdventure_PirateCave_7": 
			dialog.text = "Arkadaşlar, buraya bir ganimet getirdim. Bunu açmanız gerekiyor. Tabii, bu ganimet kendiliğinden, güzel bir şekilde açılmazsa. Kaptan, siz ne dersiniz?";
			link.l1 = LinkRandPhrase("Bence kendini içkiye vurup hafızanı kaybetsen daha iyi olurdu. En azından hayatta kalırdın. Ve şimdi geriye tek bir yol kaldı ... "," Savaş gemisinin kaptanını soymaya kalkıştığına göre pek akıllı biri olduğunu sanmıyorum ... "," Sanırım yaşamak sana fazla geldi, çünkü bunu denemeye kalkıştın...");
			link.l1.go = "NightAdventure_PirateCave_8F";
			link.l2 = "Pekala, sanırım iyi ayrılmak en iyisi. Peki, ne kadarına ihtiyacın var?";
			link.l2.go = "NightAdventure_PirateCave_8A";
		break;
		
		case "NightAdventure_PirateCave_8F": 
			dialog.text = "Yani, kolay yoldan gizli yeri açmayacak mıyız?";
			link.l1 = "Korkarım bu, hayatındaki son ganimetti.";
			link.l1.go = "NightAdventure_PirateCave_9F";
		break;
		
		case "NightAdventure_PirateCave_9F": 
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			sld = CharacterFromID(pchar.GenQuest.NightAdventureId);
			sld.SaveItemsForDead   = true; // сохранять на трупе вещи
			sld.DontClearDead = true;  // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetFightMode(pchar, true);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_PirateCave_8A": // испугался
			iMoney = sti(pchar.money)/3;
			dialog.text = "Ah, biz açgözlü değiliz. Sadece "+FindRussianMoneyString(iMoney)+"."; 
			link.l1 = "Korkarım bu, hayatındaki son ganimetti.";
			link.l1.go = "NightAdventure_PirateCave_9F";
			link.l2 = "Pekâlâ, nasıl istersen. Bir daha asla sarhoş birine yardım etmeyeceğim...";
			link.l2.go = "NightAdventure_PirateCave_9A";
		break;
		
		case "NightAdventure_PirateCave_9A": 
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_PirateCaveAgain";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false); 
			iMoney = sti(pchar.money)/3;
			AddMoneyToCharacter(pchar, -iMoney);
			AddMoneyToCharacter(npchar, iMoney);
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				sld.dialog.currentnode = "NightAdventure_PirateCaveAgain";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_Group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "NightAdventure_PirateCaveAgain": 
			dialog.text = "Kaptan, cömertliğinizle beni şaşırttınız. Bizimle biraz daha paylaşmak ister misiniz?";
			link.l1 = "Sana zaten her şeyi verdim. Gidiyorum...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_PirateCaveAgain";
		break;
		
		// дворянин -->
		case "NightAdventure_Noble":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "S-sen... hık!.. kimsin?...";
			link.l1 = "Ben Kaptanım "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Üzgünüm dostum, acelem var.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_NobleGame":             link.l1.go = "NightAdventure_NobleGame";  break; // карты
				case "NightAdventure_NobleGameDuel":         link.l1.go = "NightAdventure_NobleGame";  break; 
				case "NightAdventure_NobleWhore": 			 link.l1.go = "NightAdventure_NobleWhore"; break; // жрица
			}
		break;
		// карты
		case "NightAdventure_NobleGame": 
			dialog.text = "Kaptan?.. hık!.. ah, "+GetAddress_Form(NPChar)+" ... Çok özür... dilerim... hık!.. bu h-halime kusura bakmayın. Bana k-katılmak ister misiniz? hık!.. N-ne olur."; 
			link.l1 = "Üzgünüm, "+GetAddress_Form(NPChar)+", ama meşgulüm."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Katılmak mı? Üzgünüm, ama bugün içmeyeceğim.."; 
			link.l2.go = "NightAdventure_NobleGame_1";
		break;
		
		case "NightAdventure_NobleGame_1":
			dialog.text = "Ah, senin... hic!.. içmene gerek yok! Şey... Arkadaşımla bir kadeh içtim... Yani... zaten biraz çakırkeyfim... anlıyor musun?";
			link.l1 = "Pekala. Ayılmana yardım etmemi ister misin?";
			link.l1.go = "NightAdventure_NobleGame_2";
		break;
		
		case "NightAdventure_NobleGame_2": 
			dialog.text = "Pek sayılmaz! İyiyim. Şimdi oynamak istiyorum... kart, genel olarak oynamak istiyorum... hık!.. A-ama bu sefil... p-paralar için... bu çapulcularla... hık!.. m-meyhanede... değil! Gerçek bir soyluyla! hık!.. Gerçek bahislerle!.."; 
			link.l1 = "Üzgünüm, "+GetAddress_Form(NPChar)+", ne diyeyim... Kumar bana göre değil. Denizcilere maaş ödemek, gemiyi idare etmek lazım, biliyorsun..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Hmm, peki, oynayalım. Meyhaneye gidelim mi?"; 
			link.l2.go = "NightAdventure_NobleGame_3";
		break;
		
		case "NightAdventure_NobleGame_3": 
			dialog.text = "Pekâlâ! Sadece... hık!.. y-a-vaşça, lütfen. Ben... hık!.. ayakta... duramıyorum..."; 
			link.l1 = "Pekala, yavaşça gidelim."; 
			link.l1.go = "NightAdventure_NobleGame_4";
		break;
		
		case "NightAdventure_NobleGame_4":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleGame_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleGame_5": 
			pchar.quest.NightAdventure_Intavern.over = "yes";
			FreeSitLocator(pchar.location, "sit_front4");
			FreeSitLocator(pchar.location, "sit_base4");
			dialog.text = "O masa için... hık!.. hadi gidelim!"; 
			link.l1 = "Pekâlâ, gidelim."; 
			link.l1.go = "NightAdventure_NobleGame_6";
		break;
		
		case "NightAdventure_NobleGame_6": 
			DialogExit();
			//if(CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LAi_Fade("NightAdventure_NobleGameDialogPrep", "NightAdventure_NobleGameDialog");
		break;
		
		case "NightAdventure_NobleGame_7": 
			dialog.text = "Senin... hiçbir fikrin yok, k-kaptan, ben... hık!.. gerçek bir soyluyla tanıştığım için ne kadar mutlu olduğumu! hık!.. Bu vahşi yerde... genelde sadece... hık!.. ç-çöpler..."; 
			link.l1 = "Evet, yerel kolonilerde bunun gibi çok var. Ee, oynayalım mı?"; 
			link.l1.go = "NightAdventure_NobleGame_8";
		break;
		
		case "NightAdventure_NobleGame_8": 
			dialog.text = "Evet, oynayalım! Hık!.. Ne üzerine oynuyoruz?.."; 
			if(sti(pchar.money) > 10000)
			{
				link.l1 = "1000 peso için oynuyoruz."; 
				link.l1.go = "NightAdventure_NobleGame_9_1";
			}
			if(sti(pchar.money) > 20000)
			{
				link.l2 = "2.000 peso için oynuyoruz."; 
				link.l2.go = "NightAdventure_NobleGame_9_2";
			}
			link.l3 = "Hmm, üzgünüm, galiba şu an cebim boş..."; 
			link.l3.go = "NightAdventure_NobleGame_Голодранец";
		break;
		
		case "NightAdventure_NobleGame_Голодранец": 
			dialog.text = "N-ne?.. Senin... hık!.. benimle oynamak için... paran yok mu?.. "; 
			link.l1 = "Pekala, olur böyle şeyler. Bir dahaki sefere oynarız, merak etme."; 
			link.l1.go = "NightAdventure_NobleGame_Голодранец_1";
		break;
		
		case "NightAdventure_NobleGame_Голодранец_1": 
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_9_1": 
			DialogExit();
			npchar.money = 15000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 1000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_9_2": 
			DialogExit();
			npchar.money = 30000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 2000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_Win": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Win");
			dialog.text = "Hık!.. Harika vakit geçirdim, k-kaptan! Hık!.."; 
			link.l1 = "Sana katılıyorum. En azından işten biraz uzaklaş."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd";
		break;
		
		case "NightAdventure_NobleGame_Lose": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Fail");
			dialog.text = "Hik!.. Harika vakit geçirdim, k-kaptan! Hik!.."; 
			link.l1 = "Sana katılıyorum. En azından işten biraz uzaklaş."; 
			link.l1.go = "NightAdventure_NobleGame_Lose_1";
		break;
		
		case "NightAdventure_NobleGame_Lose_1": 
			dialog.text = "Bazen insanın... hık!.. b-biraz iyi bir... hık!.. dostluğa ihtiyacı olur. Çok teşekkür ederim... hık!.. bana eşlik ettiğin için!"; 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleGameDuel")
			{		
				link.l1 = "Evet, az önce paramparça oldum. Ve nasıl oldu da kazanma şansım varken bile sen kazandın?"; 
				link.l1.go = "NightAdventure_NobleGame_Duel";
				break;
			}	
			link.l1 = "Aynı şekilde, oyun ve sohbet için teşekkür ederim."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd": 
			dialog.text = "Bazen insanın... hık!.. biraz hoş... hık!.. birileriyle vakit geçirmesi gerekir. Çok teşekkür ederim... hık!.. bana eşlik ettiğin için!"; 
			link.l1 = "Aynı şekilde, oyun ve sohbet için teşekkür ederim."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_Duel": 
			dialog.text = "Sadece şans, k-kaptan... hık!.."; 
			link.l1 = "Bu sadece şans gibi durmuyor...."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_1";
		break;
		
		case "NightAdventure_NobleGame_Duel_1": 
			dialog.text = "Ne demek istiyorsun? Hile mi yaptığımı ima ediyorsun? Her şeyi kendin gördün, aynı desteden kart çektik!"; 
			link.l1 = "Evet, gördüm. Ayrıca bir dakika önce dilin neredeyse kıpırdamıyordu, şimdi ise sarhoş değilmişsin gibi konuşuyorsun."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_2";
		break;
		
		case "NightAdventure_NobleGame_Duel_2": 
			dialog.text = "Ah, kahretsin! Hem de beni fena yakaladın! Tamam, kabul ediyorum, saklamayacağım. Sarhoş değildim. Ama bilirsin, şu sözde zengin ve sarhoş adamlarla kart oynamak isteyenlere insanlar nasıl da kolay kanıyor! Bahse girecek bir şeyi olan herkes, kesinlikle zengin ama sarhoş bir soyludan güzel bir kazanç koparırım umuduyla ilk iş meyhaneye koşuyor. Şunu da söyleyeyim, içimi bu kadar çabuk gören ilk kişi sensin."; 
			link.l1 = "Peki, şimdi ne olacak? Paramı kolay yoldan geri verecek misin?"; 
			link.l1.go = "NightAdventure_NobleGame_Duel_3";
		break;
		
		case "NightAdventure_NobleGame_Duel_3": 
			dialog.text = "Ha ha ha, güldürme beni kaptan. Tabii ki sana hiçbir şey geri vermeyeceğim! Ve sakın beni buna zorlayabileceğini düşünme. Rahatlıkla, başıboş bir kaptan tarafından aşağılanan saygın bir soylu rolünü oynayabilirim. O yüzden sana tavsiyem şu: yenilgini kabul et ve yoluna devam et."; 
			link.l1 = "Umarım bir gün daha kötü bir durumda karşılaşmayız, çünkü o zaman böyle gülemezsin. Hoşça kal."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
			link.l2 = "Ve sana tavsiyem, kendine bir kılıç almak için vakit bulmaya çalış."; 
			link.l2.go = "NightAdventure_NobleGame_Duel_4";
		break;
		
		case "NightAdventure_NobleGame_Duel_4": 
			dialog.text = "Buna cesaret edemezsin... Burası bir meyhane, insanlarla dolu..."; 
			link.l1 = "Ben sadece başıboş bir kaptanım, neden nezaket kurallarını umursayayım ki? Hem liman meyhanesinde gece vakti ne olabilir ki... Kılıcı senden her bakımdan daha iyi kullanırım."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_5";
		break;
		
		case "NightAdventure_NobleGame_Duel_5": 
			dialog.text = "Demek mesele böyle ha?! Şimdi kimin gerçekten sahibi olduğunu göreceğiz!"; 
			link.l1 = "Emrinizdeyim..."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_6";
		break;
		
		case "NightAdventure_NobleGame_Duel_6": 
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionLocationCondition("NightAdventure_KillPhant", NPChar.City+"_town", false);
			npchar.money = 0;
			AddMoneyToCharacter(npchar, makeint(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(npchar, "totem_13");
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			chrDisableReloadToLocation = false; // открыть локацию
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// жрица
		case "NightAdventure_NobleWhore": 
			dialog.text = "Kaptan?.. hık!.. ah, "+GetAddress_Form(NPChar)+" ... Üzgünüm... hık!.. bu h-halime... Yardım edebilir misin? hık!.. N-ne olur."; 
			link.l1 = "Üzgünüm, "+GetAddress_Form(NPChar)+", ama meşgulüm."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Ah... dinliyorum."; 
			link.l2.go = "NightAdventure_NobleWhore_1";
		break;
		
		case "NightAdventure_NobleWhore_1": 
			dialog.text = "Sadece... Yani... Zaten biraz çakırkeyfim... Görüyorsun... hık!.. değil mi?"; 
			link.l1 = "Dürüst olmak gerekirse, evet. Ayılmana yardım etmemi ister misin?"; 
			link.l1.go = "NightAdventure_NobleWhore_2";
		break;
		
		case "NightAdventure_NobleWhore_2": 
			dialog.text = "Pek sayılmaz! Ben i-iyiyim. Bir kadın istiyorum. Ama çok s-sarhoşum... hık!.. H-hanımefendi beni kovacak, yani. Acaba... hık!... b-benim için konuşur musun? Sana para veririm."; 
			link.l1 = "Üzgünüm, "+GetAddress_Form(NPChar)+", ama sana nasıl söyleyeyim... Geneleve gitmem ben. Onur, itibar... anlıyorsun ya ..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Peki, tamam, sana yardım edeceğim."; 
			link.l2.go = "NightAdventure_NobleWhore_3";
		break;
		
		case "NightAdventure_NobleWhore_3": 
			dialog.text = "Sadece... hık!.. y-a-vaşça, lütfen. Ben... hık!.. dayanamıyorum..."; 
			link.l1 = "Pekala, yavaşça gidelim."; 
			link.l1.go = "NightAdventure_NobleWhore_4";
		break;
		
		case "NightAdventure_NobleWhore_4":
			DialogExit();
			if(npchar.city != "Charles" || npchar.city != "Tortuga") // вход только с парадного
			{
				LocatorReloadEnterDisable(npchar.city+"_town", "reload91", true);
			}
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventure_money = 3000+(rand(4)*500);
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleWhore_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_InBrothel", npchar.City+"_Brothel", false);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleWhore_5": 
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhoreMoney";
			AddMoneyToCharacter(pchar, 5000);
			dialog.text = "İşte para... hık!... Seni b-burada bekleyeceğim."; 
			link.l1 = "Tamam, yakında döneceğim."; 
			link.l1.go = "NightAdventure_NobleWhore_6";
		break;
		
		case "NightAdventure_NobleWhore_6": 
			LAi_SetCitizenType(npchar);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload1_back", true); 
			LocatorReloadEnterDisable(npchar.city + "_SecBrRoom", "reload2", true); 
			NPChar.Dialog.currentnode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "S-sadece... bana getir... hık!.. en iyisini!.. Evet..."; 
			link.l1 = "Pekâlâ, tamam, anladım."; 
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleWhore_7": // заказ исполнен
			dialog.text = "Hıç!.. Daha ne kadar bekleyeceğiz?"; 
			link.l1 = "Bu kolonideki en güzel kız yukarıda seni bekliyor."; 
			link.l1.go = "NightAdventure_NobleWhore_8";
		break;
		
		case "NightAdventure_NobleWhore_8": 
			dialog.text = "Evet!.. Bu akşam... harika... T-teşekkür ederim, "+GetAddress_Form(NPChar)+". Paranın kalanı... hık!... al onu. Ve ben batıyorum... içine... benim..... güzeeel... ha-hanımefendim...";
			link.l1 = "Pekala, iyi eğlenceler."; 
			link.l1.go = "NightAdventure_NobleWhore_9";
		break;
		
		case "NightAdventure_NobleWhore_9": 
			DialogExit();
			chrDisableReloadToLocation = true; // закрыть пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "", "", "", "NightAdventure_OpenBrothel", -1);
		break;
		
		case "NightAdventure_NobleBrothelAgain":
			NextDiag.TempNode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "Hic!.. Daha ne kadar bekleyeceğiz?";
			link.l1 = "Yakında pazarlık yapacağım, sabırlı ol.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleEnd":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_NobleEndAgain";
		break;
		
		case "NightAdventure_NobleEndAgain":
			NextDiag.TempNode = "NightAdventure_NobleEndAgain";
			dialog.text = "Hik!..";
			link.l1 = "Uyuman gerekiyor.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleTownAgain":
			dialog.text = "Hıç!.. Evet... hâlâ uzak mı?..";
			link.l1 = "Neredeyse geldik, sabırlı ol.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- ночной приключенец
		
		// belamour квест на получение фонаря Xenon -->
		case "CemeteryMan":
			dialog.text = "Ha? Sen kimsin? Burada ne yapıyorsun?";
			link.l1 = "Ben de sana aynı şeyi sorabilirim.";
			link.l1.go = "CemeteryMan_1";
		break;
		
		case "CemeteryMan_1":
			dialog.text = "Biz mi? Ah, biz... ııı... Burada çiçek topluyoruz...";
			link.l1 = "Mezar çiçekleri mi? Peki, herbaryumun nasıl gidiyor?";
			link.l1.go = "CemeteryMan_2";
		break;
		
		case "CemeteryMan_2":
			dialog.text = "Ot... Bitkilerle mi ilgili?";
			link.l1 = "Yani... sanırım burada neler döndüğünü anladım.";
			link.l1.go = "CemeteryMan_3";
		break;
		
		case "CemeteryMan_3":
			dialog.text = "Biz yağmacı değiliz! Bizim hakkımızda böyle konuşma! Biz sadece...";
			link.l1 = "Sadece ne?";
			link.l1.go = "CemeteryMan_4";
		break;
		
		case "CemeteryMan_4":
			dialog.text = "Şey, biz... Babam birbirimizi görmemizi yasakladı! Onun babası da öyle! Yani biz... biz de kimsenin olmadığı bir yer arıyorduk. Yalnız kalmak için. Zaten kapının kilidi de bozuk, buraya girmek çok kolay...";
			link.l1 = "Şimdi o huzursuz ruhun tüyler ürpertici inlemelerinin ne olduğunu anlıyorum...";
			link.l1.go = "CemeteryMan_5";
		break;
		
		case "CemeteryMan_5":
			DialogExit();
			sld = characterFromId("CemeteryCouple_2");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "CemeteryMan_6":
			dialog.text = "Pekâlâ, madem her şeyi çözdün, belki artık bizi rahat bırakırsın?";
			link.l1 = "Randevularını bir mezar odasında ayarlamaktan korkmuyor musun? Pek iyi bir yer sayılmaz...";
			link.l1.go = "CemeteryMan_7";
		break;
		
		case "CemeteryMan_7":
			dialog.text = "Biz batıl inançlı değiliz! Hem korkutucu olsa bile - başka seçeneğimiz var mı? Şehirde olsak, ailelerimiz hemen öğrenirdi. Ama burada, kimse bizi ispiyonlamaz. Şimdilik, en iyi seçenek bu.";
			link.l1 = "Gerçekten üzgünüm, ama başka bir yer bakabilir misin? Yanlış anlama, her şeyi anlıyorum - gençlik falan - ama mezarlık bekçisini neredeyse ödü kopmuş, her gece mahzenden gelen sesler ve inlemeler yüzünden.";
			link.l1.go = "CemeteryMan_8";
		break;
		
		case "CemeteryMan_8":
			dialog.text = "Pekala... Muhafızı korkutmak planımızda yoktu. Ama başka nerede buluşabiliriz ki? Yoksa buluşmalarımızı açık havada mı yapmamızı öneriyorsun?";
			link.l1 = "Aşkın sınırları yoktur. Kimseyi rahatsız etmeyeceğiniz başka bir yer bulun. O zaman sizi de kimse rahatsız etmez. Muhtemelen. Bir de ailenizle aranızdaki meseleleri çözseniz iyi olur - sonsuza dek saklanmayı düşünmüyorsunuz herhalde, değil mi?";
			link.l1.go = "CemeteryMan_9";
		break;
		
		case "CemeteryMan_9":
			dialog.text = "Fine, we'll think of something... We won't be scaring the guard anymore; you have my word.";
			link.l1 = "Harika. Sana bol şans!";
			link.l1.go = "CemeteryMan_10";
		break;
		
		case "CemeteryMan_10":
			sld = characterFromId("CemeteryCouple_1");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("CemeteryCouple_2");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			pchar.questTemp.Lantern = "ToKeeper";
			DeleteAttribute(pchar,"questTemp.Lantern.nation");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("NoiseCemetery", "2");
			DialogExit();
		break;
		
		case "CemeteryGirl":
			dialog.text = "Ne?!";
			link.l1 = "Ah, hiçbir şey...";
			link.l1.go = "CemeteryGirl_1";
		break;
		
		case "CemeteryGirl_1":
			DialogExit();
			sld = characterFromId("CemeteryCouple_1");
			sld.dialog.currentnode = "CemeteryMan_6";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		// <-- квест на получение фонаря 

		//замечание по обнажённому оружию от персонажей типа citizen // лесник вставил в ген.квесты чтобы не было пустого диалога .
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını indirmeni rica ediyorum.","Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını indirmeni rica ediyorum.");
			link.l1 = LinkRandPhrase("Pekala.","Nasıl istersen...","Dediğin gibi...");
			link.l1.go = "exit";
		break;																																																				  
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 13; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_31"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}

// Для генера "Пираты на необитаемом острове"
String PiratesOnUninhabited_GetStringNum(int _num)
{
	String retValue = "";
	
	switch(_num)
	{
		case 5: retValue = "five"; break;
		case 6: retValue = "six"; break;
		case 7: retValue = "seven"; break;
		case 8: retValue = "eight"; break;
		case 9: retValue = "nine"; break;
		case 10: retValue = "ten"; break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		switch(hrand(1))
		{
			case 0: retShipType = SHIP_LUGGER; break;
			case 1: retShipType = SHIP_SLOOP; break;
		}
	}
	
	if(rank >= 5 && rank < 20)
	{
		switch(hrand(3))
		{
			case 0: retShipType = SHIP_SLOOP; break;
			case 1: retShipType = SHIP_BRIGANTINE; break;
			case 2: retShipType = SHIP_SCHOONER_W; break;
			case 3: retShipType = SHIP_BRIG; break;
		}
	}
	
	if(rank >= 20)
	{
		switch(hrand(2))
		{
			case 0: retShipType = SHIP_CORVETTE; break;
			case 1: retShipType = SHIP_GALEON_H; break;
			case 2: retShipType = SHIP_FRIGATE; break;
		}
	}
	
	return retShipType;
}

String PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	String retShoreId;
	
	switch(hrand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	String group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "soldier"));		
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	character.Ship.Mode = "pirate";	
	SetCaptanModelByEncType(character, "pirate");

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	character.DontRansackCaptain = true; //не сдаваться
	
	SetAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придёт
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // Сколько влезет рабов
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + hrand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("Pirates on an uninhabited island: cap left " + character.fromCity + " and went to: " + character.toShore);
}
// belamour gen количество каторжан прописью -->
String Convict_GetStringNum(int iCQTY)
{
	String ConvictStr = "";
	
	switch(iCQTY)
	{
		case 2: ConvictStr = "two"; break;
		case 3: ConvictStr = "three"; break;
		case 4: ConvictStr = "four"; break;
		case 5: ConvictStr = "five"; break;
		case 6: ConvictStr = "six"; break;
		case 7: ConvictStr = "seven"; break;
	}
	
	return ConvictStr;
}
// <-- gen
