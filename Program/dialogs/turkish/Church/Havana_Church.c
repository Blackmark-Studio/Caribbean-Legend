// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular, "+GetSexPhrase("evladım","kızım")+"?","Sor, dinliyorum..."),"Dinliyorum, şimdi konuş. "+GetSexPhrase("evladım","kızım")+"...","Üçüncü kez, "+GetSexPhrase("evladım","kızım")+", neye ihtiyacın varsa söyle.","Bir din adamının çok işi var ve sen beni oyalıyorsun, "+GetSexPhrase("evladım","kızım")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda değil, padre..."),"Söyleyecek bir şeyim yok, özür dilerim.","Soracağım, ama sonra. Beni affedin, baba.","Affedersiniz, kutsal baba...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
			{
				ref sld = characterFromId("Villemstad_Priest");
				link.l1 = "Selamlar, Peder. Başrahip "+sld.name+" Willemstad kilisesinden beni gönderdiler. Ona Küba'daki bir mağarada gördüğünüz tuhaf şeylerden bahsetmişsiniz.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
			{
				link.l1 = "Ormandaki mağarayı ziyaret ettim, baba.";
				link.l1.go = "caleuche_4";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "caleuche":
			dialog.text = "Tanrı'ya şükür ki kulak verdi! Yaşayan ölülerle ilgili dedikodular kulağıma gelir gelmez, hemen Santiago'nun engizitörü Saygıdeğer Vincento Baba'ya haber verdim. Konuyu inceleyeceğine söz verdi, ama şu ana kadar hiçbir şey yapılmadı! Korkarım Saygıdeğer Baba'nın ilgilenmesi gereken daha önemli meseleleri var...";
			link.l1 = "Bunu kendim araştıracağım. Ayrıca, bu söylentilerin hepsi sarhoş avcıların zırvalarından ibaret - bu yüzden Engizisyon onları ciddiye almamış. Kendi gözlerimle görmek için ormana gideceğim.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Sana temin ederim evladım, bu çok önemli. Bana yürüyen ölülerden bahseden adama hayatımı emanet edebilirim.";
			link.l1 = "Pekâlâ, o zaman savaşa hazırlanacağım. Eğer o lanetli yaratıklar gerçekten mağarada yuvalandıysa, onları bu dünyadan temizleyeceğim.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Tanrı'nın kutsamasıyla git, evladım! Al, bu kutsanmış muskayı da yanında götür. Görevinde sana yardımcı olacak. Şimdi git, kötülüğün tohumlarını yok et!";
			link.l1 = "O zamana kadar, Baba "+npchar.name+". İşim biter bitmez hemen sana döneceğim.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "27");
			pchar.questTemp.Caleuche = "cave";
			Log_Info("You have received a church amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7"); 
			if (GetCharacterIndex("cavehunter") != -1)
			{
				sld = characterFromId("cavehunter");
				sld.dialog.currentnode = "cavehunter_5";
				LAi_SetGuardianType(sld);
				sld.protector = true;
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				AddLandQuestMark(sld, "questmarkmain");
			}
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
			pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
		break;
		
		case "caleuche_4":
			dialog.text = "Ne gördün, evladım? Korkularımız yersiz miydi?";
			link.l1 = "Korkarım hayır, Peder "+npchar.name+". Mağara ölülerle doluydu, ama Tanrı'nın yardımıyla galip geldim. Artık kimseye zarar veremeyecekler.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Tanrı'ya şükürler olsun! Gerçekten de O'nun cezalandırıcı kılıcısın, evladım! Lütfen tüm Havana cemaati adına en derin şükranlarımı kabul et. Lütfen, bu kutsanmış muskaları minnettarlığımızın bir nişanesi olarak al. Tehlikeli yolculuklarında sana mutlaka faydalı olacaklardır.";
			link.l1 = "Teşekkür ederim, Peder "+npchar.name+".";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_3"); 
			GiveItem2Character(pchar, "amulet_9"); 
			GiveItem2Character(pchar, "obereg_7"); 
			GiveItem2Character(pchar, "obereg_11"); 
			dialog.text = "Ayrıca, hem sıradan insanlar hem de soylular kahramanca davranışınızı öğrensin diye elimden geleni yapacağım ve gece gündüz sizin için yorulmadan dua edeceğim.";
			link.l1 = "Teşekkür ederim, Peder. Ayrıca size bir sorum daha olacak.";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Sor, evladım.";
			link.l1 = "Söyle bana, Peder "+npchar.name+", yakın zamanda Joachim Merriman adında bir adam şehrinize geldi mi? Orta yaşlı bir beyefendi, bıyıklı, imparator sakallı ve delici bakışlara sahip bir Portekizli?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Ne adı ne de tarifi bana bir şey hatırlatıyor, üzgünüm. Kim bu adam?";
			link.l1 = "Merriman bir büyücü. Engizisyon onu çok uzun zamandır avlıyor. Baba "+sld.name+" ve Küba'da yaşayan ölülerin ortaya çıkmasının onun işi olduğundan şüpheleniyorum. Kısa bir süre önce Willemstad'da yaşıyordu, sonra aniden ortadan kayboldu. Çok geçmeden, ona ev sahipliği yapan kadın yürüyen bir iskelete dönüştü.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Ne kabus ama! Hemen engizisyonculara, bizzat Peder Vincento'ya haber vereceğim! Burada neler olduğunu mutlaka öğrenmeli! Söyle bana, evladım, sence ormanda kaybolan insanlar...?";
			link.l1 = "Gerçekten de, mağaradaki o yaşayan ölülerin senin eski vatandaşların olduğundan neredeyse eminim. Bu Portekizliyi Küba'da bulup haddini bildirmek istiyorum! O alçak, eski bir putperest kalıntısını - Yum Cimil'in yeşim kafatasını - ele geçirmiş. Korkarım ki, bu eser ve Hint büyücülüğüyle, Merriman'ı kimse durdurmazsa başımıza daha da büyük dertler açacak.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Ölülerin yeniden dirileceğine inanıyor musun?";
			link.l1 = "Büyük ihtimalle. Onu neyin motive ettiğinden emin değilim, ama emellerinin erdemli olmaktan çok uzak olduğuna şüphe yok.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "Yüce Rabbimiz bize merhamet etsin! Onu bul, evladım! Kutsal Kilisemiz adına ona karşı her türlü önlemi alman için sana izin veriyorum! Hemen Santiago'ya bir haberci gönderip Peder Vincento'ya rapor ileteceğim.";
			link.l1 = "Bunu yapın. Hoşça kalın, Peder "+npchar.name+".";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			DialogExit();
			AddQuestRecord("Caleuche", "29");
			pchar.questTemp.Caleuche = "graveyard";
			AddCharacterMaxHealth(pchar, 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddLandQuestMark(characterFromId("Havana_CemeteryMan"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
