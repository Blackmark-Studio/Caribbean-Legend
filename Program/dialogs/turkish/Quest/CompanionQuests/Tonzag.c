void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;
		
		case "startoff":
			dialog.text = "Kaptan de Mor! Tortuga'ya hoş geldiniz!";
			link.l1 = "Günaydın, Teğmen. Arkadaşlarınla deniz manzarasının tadını mı çıkarıyorsun?";
			link.l1.go = "startoff_joke";
			link.l2 = "Çekil, Teğmen.";
			link.l2.go = "startoff_silence";
			
			AddDialogExitQuestFunction("Tonzag_Arrested");
		break;
		
		case "startoff_joke":
			dialog.text = "Kaptan, şöhretiniz sizden önce geliyor ve üsttekiler, güzel Tortuga Adamızın cazibelerini size biraz gezdirmeye karar verdiler. Hemen başlıyoruz—şehrin zindanlarıyla. Subaylarınız da davetli.";
			link.l1 = "Teğmen, ben sahilde yakaladığın sıradan bir kaçakçı değilim. Lütfen şaka yapma. Durumu düzgünce açıkla.";
			link.l1.go = "startoff_joke_1";
			link.l2 = "O halde vakit kaybetmeyelim! Yolu sen göster, Teğmen!";
			link.l2.go = "startoff_joke_2";
		break;
		
		case "startoff_silence":
			dialog.text = "Sizinle, denizcilerle uğraşmak için farklı bir yol gerektiğini görüyorum. Askerler, savaşa hazırlanın! Kaptan de Maure, siz ve subaylarınız tutuklusunuz. Silahlarınızı teslim edin!";
			link.l1 = "Sana bir kurşun verebilirim - nereye istersin, Teğmen? Sizin gibi kara fareleriyle başka türlü olmuyor zaten.";
			link.l1.go = "startoff_silence_1";
			link.l2 = "Hangi yasaya göre? Silahlı bir grubu kan dökmeden tutuklamak istiyorsan, Teğmen, daha çok çabalamalısın.";
			link.l2.go = "startoff_silence_2";
		break;
		
		case "startoff_joke_1":
			dialog.text = "Bana göre, hepiniz aynısınız... Üzgünüm ama açıklama yok, Kaptan. Yukarıdan gelen emirler. Silahlarınızı teslim edin, lütfen.";
			link.l1 = "Şimdi başıma iş almak istemiyorum... Şimdi değil. Dediklerini yap.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", +5);
		break;
		
		case "startoff_joke_2":
			dialog.text = "Uh... Sanırım beni tam olarak anlamadınız. Kaptan, siz ve subaylarınız tutuklusunuz! Silahlarınızı bırakın ve bizimle gelin!";
			link.l1 = "Şimdi başıma dert almak istemiyorum... Şu dediklerini yap.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "startoff_silence_1":
			dialog.text = "Bir kelime daha edersen, Kaptan, seni burada gömeriz. Silahları hemen yere bırakın!";
			link.l1 = "Şu anda başıma iş almak istemiyorum...   Ne derlerse yap.";
			link.l1.go = "exit";
			
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "startoff_silence_2":
			dialog.text = "Kandan korkmam, Kaptan. Mucizevi bir şekilde hayatta kalsan bile, bir daha asla Tortuga'ya adım atamazsın. Üstelik askeri istihbaratımız, bu adaya erişimini fazlasıyla önemsediğini düşünüyor.";
			link.l1 = "Şimdi başıma iş almak istemiyorum... Şimdi değil. Dediklerini yap.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Kaptan, işler berbat! Düşman bizi fena kıstırdı, korkarım ki ölene kadar bırakmayacaklar! Adamlarımız gerçekten zor durumda, topçuların çoğu da saf dışı kaldı!";
			link.l1 = "Onlara yardım edeceğim. Komutayı devral ve bizi buradan çıkar!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Evet, efendim!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Zafer, Kaptan! Çıkarma birliği yok edildi, düşman geri çekilmeyi seçti ve güneye yöneldi. Geminin durumu kabul edilebilir. Hayatta kalan mürettebat: "+GetCrewQuantity(pchar)+" insanlar. Rapor tamamlandı!";
			link.l1 = "Teşekkürler! Limana varana kadar herkese rom ve nöbeti sıkı tutun!";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Yaşasın! Baş üstüne!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
		
		case "killer":
			dialog.text = "Ve işte adamın kendisi! Dışarıdaki kanlı katliamı gördün mü? Hepsi senin işin, hain! Ama her şeyin hesabını vereceksin: Porto Bello için, Gruoh için ve bu maden için!";
			link.l1 = "Bekle, bu da ne demek oluyor...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_FightInMine");
		break;
		
		case "mine_head":
			dialog.text = "";
			link.l1 = "Ah! Bu iyiye işaret değil...";
			link.l1.go = "mine_head_1";
		break;
		
		case "mine_head_1":
			dialog.text = "San Santiago, beni koru! Alçaklık! Kim böyle bir canavarlığı yapabilir? Cevap ver, senyor!";
			link.l1 = "Sakin ol, señor! Önce kendini tanıt! Evet, burada korkunç bir katliam yaşandı, ama bunu yapanlar çoktan öldü. Onların kalıntılarıyla madenleri bizzat ben 'süsledim'...";
			link.l1.go = "mine_head_2";
		break;
		
		case "mine_head_2":
			dialog.text = "Ben "+GetFullName(npchar)+", kraliyet Los Teques madeninin baş mühendisi. Aylar süren bir görevden yeni döndüm ve... ne görüyorum! Burada olanlar Tanrı'ya ve insanlığa karşı bir suç, bu yüzden sizden silahlarınızı derhal teslim etmenizi istiyorum. Caracas yetkilileri bu alçaklığı araştıracak!";
			link.l1 = " Uygun göremem, senyor, ve yemin ederim ki bu katliamla hiçbir ilgim yok! Ama ısrar ederseniz, kendi bedeniniz de bu yığına eklenecek.";
			link.l1.go = "mine_head_3";
		break;
		
		case "mine_head_3":
			dialog.text = "Ölümden korkmam, ama ne zaman geri çekileceğimi bilirim. Git, ama unutma, burada olanları rapor edeceğim ve tek bir detayı bile atlamayacağım!";
			link.l1 = "Buna razı olamam, señor. Üzgünüm, iş buraya kadar geldi. Savaşa!";
			link.l1.go = "mine_head_fight";
			link.l2 = "Ölümü arıyor gibisin, señor. Ama bugün, başka kimse ölmeyecek. Gidiyoruz ve umarım bu ayrıntı da raporuna girer!";
			link.l2.go = "mine_head_peace";
		break;
		
		case "mine_head_peace":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_LetMineHeadGo");
		break;
		
		case "mine_head_fight":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_FightMineHead");
		break;
		
		case "alonso":
			dialog.text = "Esiri ne yapalım, Kaptan?";
			link.l1 = "Özel bir şey yok, sadece onun ölmesine ya da kaçmasına izin verme.";
			link.l1.go = "alonso_1";
		break;
		
		case "alonso_1":
			dialog.text = "Emredersiniz! Anladığım kadarıyla, bugünkü sorguya katılmam gerekmeyecek, Kaptan?";
			link.l1 = "Neden olmasın? Mesleğini değiştirmeye mi karar verdin, Alonso?";
			link.l1.go = "alonso_2";
		break;
		
		case "alonso_2":
			dialog.text = "Ha-ha, hayır, Kaptan. Bu işi seviyorum ama görünen o ki artık gemide yeni bir usta var!";
			link.l1 = "Hercule? Bu fikri nereden aldın?";
			link.l1.go = "alonso_3";
		break;
		
		case "alonso_3":
			dialog.text = "Pekâlâ, Kaptan, yaşlı adam bu iş için alet çantasını getirmiş ve hemen kullanmaya başlamış. Benimkini çıkarmama bile gerek kalmayacak. Ha!";
			link.l1 = "Anladım... Devam et!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_DrinkAgain");
		break;
		
		case "captive":
			dialog.text = "Ah... Charles de Maure. Tüm Birlik adına özürlerimi sunmama izin verin. Sizi rahat bırakma emri bize çok geç ulaştı. Örgütümüzün size karşı hiçbir talebi yok, Kaptan. Ama şu kel hayvan... Iyy! Sizin tasmanızdayken güvende, ama size tavsiyem, onu tutmamanız ve ait olduğu yerde, lağımda çürümeye bırakmanız!";
			link.l1 = "Tavsiyen için sağ ol, ama beni paralı askerlerinden kim koruyor, asıl onu merak ediyorum.";
			link.l1.go = "captive_1";
		break;
		
		case "captive_1":
			dialog.text = "Bilemem, Kaptan. Sanırım talimatlar yeni hamimizden geldi. Duymuşsundur, hain? Birlik artık yeniden zirvede!";
			link.l1 = "Ve o kim?";
			link.l1.go = "captive_2";
		break;
		
		case "captive_2":
			dialog.text = "Bilemem, Kaptan, bilsem bile böyle şeyleri açıklamayız.";
			link.l1 = "Öyleyse, bana başka bir şey söyle, sonra nereye istersen gidebilirsin. Söz veriyorum.";
			link.l1.go = "captive_3";
		break;
		
		case "captive_3":
			dialog.text = "Bu kadar mı? Peki, Kaptan, sorularını sor ve bırak gideyim. Söz veriyorum, dönebilecek olsam bile Birliğe bir daha asla dönmem.";
			link.l1 = "Neden bu kadar takıldın Hercule'e? Sırf bir firari için fazla dert ediyorsun.";
			link.l1.go = "captive_4";
		break;
		
		case "captive_4":
			dialog.text = "Ne söyledin ona, köpek herif? Her şey göründüğü gibi değil, Kaptan! Birlik sürekli yer değiştirir, şifreler değişir, işverenler farklıdır. Ayrılmak mı istiyorsun? Tabii! Çıkış sadece üst düzey subaylara kapalıdır, bu pislik asla onlardan biri olmadı. Karısı, evet, ama Madame Tonzag’a fazlasıyla saygı duyardık, onun için istisna yaptık.";
			link.l1 = "O halde neden?";
			link.l1.go = "captive_5";
		break;
		
		case "captive_5":
			dialog.text = "Porto Bello'da bir olay vardı... Büyüktü. Bak, arkadaşın sadece gitmedi, sadece sözleşmeyi bozmadı, işini bitirmeye gelen grubu da öldürmekle kalmadı. Sokaklarda tam anlamıyla bir katliama yol açtı, bu da bizim Kastilyalılarla ilişkilerimizi epeyce zorlaştırdı. O gün iyi Katoliklerin yaşadığı korkuyu, nadiren bir korsan baskını yaratır. Cehennem olsun, bunu başkası yapmış olsaydı belki etkilenirdim bile.";
			link.l1 = "Bir başka katliam mı? Ne ilginç. Devam et.";
			link.l1.go = "captive_6";
		break;
		
		case "captive_6":
			dialog.text = "O zamanlar Şirket’in Başkan Yardımcısı olan Rodenburg araya girdi. Bir şekilde bütün olayı örtbas etmeyi başardı, ama bu, en iyi adamlarımızdan birçoğunu İspanyol cezalandırma operasyonlarında kaybetmemizden önce olmadı. Bir süre geçtikten sonra ise, onlarla yeniden iş yapmaya başladık... Ah! Ama hiçbir şeyi unutmadık ve fırsat doğar doğmaz intikam almaya çalıştık. Bütün bu işin kışkırtıcısı Tonzag öldürülmeliydi.";
			link.l1 = "Bunda başarılı olamadın. Peki ya maden?";
			link.l1.go = "captive_7";
		break;
		
		case "captive_7":
			dialog.text = "We were forced to do it. Getting rid of that scum required too much expense; we needed gold. All because of him... But the attempted assassination failed, and I returned to Los Teques to tidy up a bit... How did you figure out where to look?";
			link.l1 = "Önemli değil. Liderinizle görüşmem gerek. Yanlış anlaşılmayı bizzat çözmek istiyorum, çünkü o gizemli haminizin verdiği güvenceler her an geçerliliğini yitirebilir.";
			link.l1.go = "captive_8";
		break;
		
		case "captive_8":
			dialog.text = "Eminim Caracas'ta seni zaten bekliyorlar, Kaptan. Bak, senden hiçbir şey gizlemiyorum.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog");
		break;
		
		case "captive_9":
			dialog.text = "Komutan Arno öldü, şimdi Austin sorumlu.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog2");
		break;
		
		case "captive_10":
			dialog.text = "Tüm sorularını yanıtladım, Kaptan. Sözünü tut.";
			link.l1 = "Seni serbest bırakıyorum. Gemimden in, ve Caracas'ta bana pusu kurulmamış olması için dua et.";
			link.l1.go = "captive_spare";
			link.l2 = "İlginç sohbet için sağ ol. Madende gördüklerimden sonra, Hercule'ü katliamla suçlamak biraz fazla oldu. Cehenneme git, ait olduğun yere.";
			link.l2.go = "captive_execute";
		break;
		
		case "captive_execute":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ExecuteCaptive");
		break;
		
		case "captive_spare":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin2");
		break;
		
		case "cureer":
			dialog.text = "Beyler, bir toplantıya davetlisiniz. Sizi kilisede bekliyorlar, bu yüzden güvenlik garanti altında.";
			link.l1 = "Bu çabuk oldu...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CureerGoAway");
		break;
		
		case "ostin":
			StartQuestMovie(true, false, true);
			PlaySound("VOICE\" + LanguageGetLanguage() + "\OliverTrast02.wav");
			dialog.text = "Charles de Maure. Hercule. Buradan sağ çıkamayacaksın.";
			link.l1 = "Her zaman bir sohbeti başlatmak için güzel bir yol. Gerçekten hepsine ihtiyacın var mı?";
			link.l1.go = "ostin_1";
		break;
		
		case "ostin_1":
			dialog.text = "Seninle işler pek de basit değil, Kaptan. Bak, yeni patronumuz seni rahat bırakmamız için ısrar etti... ama o isteğini nereye sokacağını biliyor! Sizin gibilerden nefret ederim! O güzelim beyaz yelkenlerinizle dolaşırsınız, ağzınızdan süt dökülse yere düşmez sanırsınız. Ama kılıcımın çeliği içinize girdi mi, hepiniz kızlar gibi çığlık atarsınız. İşte buna bayılıyorum, Charles, sana söyleyeyim! Uzun zamandır yapmamıştım... ve şimdi tam karşımda duruyorsun, yakışıklı.";
			link.l1 = "Hasta olmuşsun, dostum.";
			link.l1.go = "ostin_2";
		break;
		
		case "ostin_2":
			dialog.text = "Hayır, gitmene izin veremem. Ama arkadaşın için işim çok daha basit – adamlarımın ona ihtiyacı yok, fakat hâlâ Lig'den eski birkaç tanıdığı var, yöntemlerimin ne kadar etkili olduğuna tam ikna olmuş değiller... Temiz işlere, temiz dublonlara, temiz Şirket'e fazla alışmışlar. Ama onların fikrini değiştirecek şeyi biliyorum – cesur bir günahkârın kafası bir tepside, ha-ha!";
			link.l1 = "Yanlış yeri seçtin, deli herif. Gerçekten bir kilisede kavga mı başlatacaksın?";
			link.l1.go = "ostin_3";
		break;
		
		case "ostin_3":
			dialog.text = "Tabii, neden olmasın? İnsanlara acıyor musun? Los Teques'teki kadar kazançlı olmayabilir, ama yine de iyi vakit geçireceğiz. Tanrı'nın evinin duvarlarını boyayacağız, ha-ha! Kaptan, sen bolca boya sağlayacaksın.";
			link.l1 = "Anladım. Bize imreniyorsun, değil mi, seni deli sıçan? Özgürlüğümüze mi özeniyorsun? Kızların bizi görünce sevindiğine, ceplerimizde paraların şıngırdadığına mı? Kendine bak: seni hangi patronların mezarından çıkardı, domuz? Seni kiliseye kim aldı?";
			link.l1.go = "ostin_4";
		break;
		
		case "ostin_4":
			dialog.text = "Yere yat, pis velet!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchVystrel");
		break;
		
	}
} 
