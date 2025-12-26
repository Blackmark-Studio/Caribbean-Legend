void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
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
			dialog.text = "Ne istiyorsunuz?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;
		
		case "SKD_DomAnri":
			dialog.text = "Evime hoş geldiniz, beyler. Size nasıl yardımcı olabilirim?";
			link.l1 = "Levasseur selamlarını iletiyor, monsieur.";
			link.l1.go = "SKD_DomAnri_2";
			StartQuestMovie(true, false, true);
		break;
		
		case "SKD_DomAnri_2":
			dialog.text = "Demek öyle... Alicia! Bizi yalnız bırak, lütfen. Bu beyefendilerin benimle işi var.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_2_1";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		case "SKD_DomAnri_2_1":
			StartInstantDialog("SKD_Alisia", "SKD_DomAnri_3", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_3":
			dialog.text = "Ama...";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_3_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
		break;
		case "SKD_DomAnri_3_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_4", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_4":
			dialog.text = "Seni seviyorum, canım. Hadi bakalım!";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_5";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		
		case "SKD_DomAnri_5":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Anri_DlgExit_1");
		break;
		
		case "SKD_DomAnri_6":
			dialog.text = "Harika işler, Tanrım! Hayatının aşkını dünyanın öbür ucunda bulmak için her şeyi kaybetmeye değdi! Beyler, tamamen size aitim. Sanmıyorum ki bir anlaşma yapabileceğiz, değil mi?";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_6_1";
		break;
		case "SKD_DomAnri_6_1":
			StartInstantDialog("Duran", "SKD_DomAnri_7", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_7":
			dialog.text = "Hayır, ve merhamet istemeye de kalkışma.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_7_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
			locCameraFromToPos(-0.52, 1.47, 0.76, false, -2.52, 0.20, 0.99);
		break;
		case "SKD_DomAnri_7_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_8", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_8":
			dialog.text = "Bir Tarikat Şövalyesinin merhamet dilemesi yakışık almaz.";
			link.l1 = "Eskiden bir şövalyeydim, gerçi.";
			link.l1.go = "SKD_DomAnri_9";
		break;
		
		case "SKD_DomAnri_9":
			dialog.text = "Dünyadaki bütün mürekkep yetmezdi o unvanı elimden almalarına.";
			link.l1 = "Öyleyse, kanıtla.  Ama önce, merakımı gider: Tahta ihanet mi ettin? Yoksa, Levasseur'un senin canını bu kadar istemesinin sebebini anlamıyorum.";
			link.l1.go = "SKD_DomAnri_10";
		break;
		
		case "SKD_DomAnri_10":
			dialog.text = "Yeminime sadığım, monsieur, bu yüzden bana kızmayın. Sadece şunu söyleyebilirim ki, Taht’a ihanet eden biri beni başka bir hainin işini bitirmem için gönderdi. Ve bunu, benden daha yetenekli bir Kardeş başarılı olana kadar tekrar tekrar yapacak. Yeterince konuştuk. Beyler, savaşa!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_11";
		break;
		
		case "SKD_DomAnri_11":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Anri_DlgExit_2");
		break;
		
		case "SKD_DomAnri_12":
			dialog.text = "Ah-ah! Oh, sağ ol, Kaptan. Zorlu bir herifti. Onu tek başıma alt edemezdim.";
			link.l1 = "Her nedense bu zafer beni pek mutlu etmedi. Sanırım işimiz burada bitti?";
			link.l1.go = "SKD_DomAnri_13";
		break;
		
		case "SKD_DomAnri_13":
			dialog.text = "Tam olarak değil, önce yukarıya, ikinci kata kaçan kızı bulup ortadan kaldırmamız gerekiyor.";
			link.l1 = "Ne?! Geri çekil! Aklını mı kaçırdın, Claude? Ben cellat değilim!";
			link.l1.go = "SKD_DomAnri_14";
		break;
		
		case "SKD_DomAnri_14":
			dialog.text = "Hiçbir şey yapmak zorunda değilsiniz, Kaptan. Hem, bütün suç sizde: Ona Levasseur'dan bahsetmemeliydiniz.";
			link.l1 = "Bu saçmalık ve sen de bunun farkındasın. Bir daha bana anlamsız bir azarlama yapmaya kalkarsan, bununla paçayı sıyıramazsın.";
			link.l1.go = "SKD_DomAnri_15";
		break;
		
		case "SKD_DomAnri_15":
			dialog.text = "Heh! Benim hatam, Kaptan. Doğru, Levasseur'un emirlerinde yalnızca şövalyeyi değil, yanındaki herkesi ortadan kaldırmam gerektiği açıkça yazıyordu. Hepsini, anlıyor musun? Bu insanlarla oyun olmaz ve istekleri ciddiye alınmalı. İşimi yapmama engel olma, Kaptan. Son bir pis iş, sonra sonsuza dek yanındayım, yemin ederim!";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				Notification_Reputation(true, 71, "low");
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(Güvenilir) (Onur) Bir zamanlar bana yükseklere uçmamın kaderimde olduğunu söylemiştiniz ve buna katkıda bulunmaktan memnun olduğunuzu belirtmiştiniz.";
				link.l1.go = "SKD_DomAnri_VD";
			}
			else
			{
				if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
			}
			link.l2 = "Cehenneme kadar yolun var! Pis işini yap. Yeminini kabul ediyorum ve bunu ölümüne ciddiye alsan iyi edersin. Anlaştık mı?";
			link.l2.go = "SKD_DomAnri_DuranDruzhba";
			link.l3 = "Bu fiyata olmaz, Claude. O kızı öldürmene izin vermem.";
			link.l3.go = "SKD_DomAnri_DuranDraka";
		break;
		
		case "SKD_DomAnri_DuranDraka":
			dialog.text = "Heh! Sanırım birbirimizi öldürmek kaderimizde varmış, ha, Kaptan?";
			link.l1 = "Sanırım öyle. Tortuga'da kaldığımız yerden devam edelim, ne dersin?";
			link.l1.go = "SKD_DomAnri_DuranDraka_2";
		break;
		
		case "SKD_DomAnri_DuranDraka_2":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_3");
		break;
		
		case "SKD_DomAnri_DuranDruzhba":
			dialog.text = "Başüstüne, Kaptan!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_2";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_2":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_4");
		break;
		
		case "SKD_DomAnri_DuranDruzhba_3":
			dialog.text = "Bitti, Kaptan. Beni gerçekten şaşırttı...";
			link.l1 = "Bunu duymak istemiyorum. Sözümü tuttum. Şimdi sıra sende.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_4";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_4":
			dialog.text = "Altın bir yana, ama sıradan bir paralı asker için kendi canını ortaya koymak çok daha değerli. Sonuna kadar yanınızdayım, Kaptan.";
			link.l1 = "O zaman burada işimiz bitti.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_5";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_5":
			dialog.text = "Aynen öyle.";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_6";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_6":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_5");
		break;
		
		case "SKD_DomAnri_VD":
			dialog.text = "Yaptım. Ne demek istiyorsun, Kaptan?";
			link.l1 = "Bana o sözlerin boş laf olmadığını kanıtla. Ekibimde yer almak mı istiyorsun? Gelecekteki ganimetten pay mı? O zaman emirlerime uy. Kıza dokunma. Neden mi? Çünkü dokunursan sonsuza dek bir cellat olarak kalırsın, ve ben yanımda öyle insanlara yer vermem.";
			link.l1.go = "SKD_DomAnri_VD_2";
		break;
		
		case "SKD_DomAnri_VD_2":
			dialog.text = "Bu, seninle ölümüne dövüşmek üzere olduğumuz ikinci sefer, Kaptan\nVe yine, dilini kullanma yeteneğin sayesinde kazanıyorsun! Ha ha! Haklısın! Eh, kız da cehenneme gitsin. Sonuçta ben bir hayvanım. Mürettebata katılmama izin var mı?";
			link.l1 = "Hoş geldin, Claude. Bu sefer gerçekten.";
			link.l1.go = "SKD_DomAnri_VD_3";
		break;
		
		case "SKD_DomAnri_VD_3":
			dialog.text = "Emredersiniz, Kaptan!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_VD_4";
		break;
		
		case "SKD_DomAnri_VD_4":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_6");
		break;
		
		case "SKD_KlodDuran":
			dialog.text = "Bir şey çıktı, Kaptan.";
			Link.l1 = "Dur tahmin edeyim: yine istifa etmekle tehdit edip zam mı isteyeceksin?";
			Link.l1.go = "SKD_KlodDuran_1";
		break;
		
		case "SKD_KlodDuran_1":
			dialog.text = "Heh! Bu sefer değil... Merak etmeyin, Kaptan, paranızı verdiğiniz sürece, tamamen hizmetinizdeyim... tabii makul ölçülerde. Biz paralı askerlerin hayatta kalmasının tek yolu bu. Hem en iyilerimize bile üç kuruş ödeniyor.";
			link.l1 = "Neden doğrudan işe koyulmuyoruz?";
			link.l1.go = "SKD_KlodDuran_2";
		break;
		
		case "SKD_KlodDuran_2":
			dialog.text = "Tortuga'daki o kaltak'ı hatırlıyor musun?";
			link.l1 = "Marceline mi? Valinin karısı mı? Öyle bir kadını unutamazsın.";
			link.l1.go = "SKD_KlodDuran_3";
		break;
		
		case "SKD_KlodDuran_3":
			dialog.text = "Levasseur'un evine tesadüfen gelmedim. O alçak ve kafirle işlerim vardı.";
			link.l1 = "Güçlüler hakkında bu kadar küçümseyici konuşman biraz garip, Claude.";
			link.l1.go = "SKD_KlodDuran_4";
		break;
		
		case "SKD_KlodDuran_4":
			dialog.text = "Ha? Heh! Levasseur tam bir şeytan! O, ondan beslenen korsanlardan bile çok daha beter!";
			link.l1 = "Sen demin onunla iş yaptığını söyledin. Bu biraz ikiyüzlülük olmuyor mu?";
			link.l1.go = "SKD_KlodDuran_5";
		break;
		
		case "SKD_KlodDuran_5":
			dialog.text = "Ben melek değilim, Kaptan, geçimimi bana söyleneni öldürerek sağlıyorum. Bu yüzden beni bu kadar değerli buluyorsun, değil mi? Ama benim gibiler bile, Levasseur'un Tortuga'daki inlerinde kadınlara neler yaptıklarına dair söylentileri duyunca tüyleri diken diken oluyor!";
			link.l1 = "Söylentiler beni ilgilendirmez. Bu adam bir soylu ve Kral'ın hizmetkârı, saygıyı hak ediyor.";
			link.l1.go = "SKD_KlodDuran_6";
		break;
		
		case "SKD_KlodDuran_6":
			dialog.text = "Yani, Kral'ın adamını soydun ve karısıyla yattın ha? Heh! Sen bilirsin, Kaptan. Lafı uzatmayalım. Ekselansları bana bir adamı bulup öldürmemi emretti. Oldukça sıradan bir iş, gerçi bu kadar yüksek bir makamdan ve üstelik bizzat nadiren gelir.";
			link.l1 = "Ne istiyorsun? Seni serbest bırakıp sözünü tutmanı ve bu adamı öldürmeni mi?";
			link.l1.go = "SKD_KlodDuran_7";
		break;
		
		case "SKD_KlodDuran_7":
			dialog.text = "Bu işi birlikte halletmemizi istiyorum, Kaptan. Tortuga’da işler kötüye gidince hizmetinize katılmayı kabul ettim, ama bu işi bitirmeden içim rahat etmeyecek. Levasseur bunu öğrenirse beni öldürür. Ayrıca, işi yarım bırakmak profesyonelliğe yakışmaz.";
			link.l1 = "Bir müşterinin karısıyla ilişki yaşamak profesyonelliğe sığar mı? Böyle bir isteği sizden duymak oldukça tuhaf, özellikle de sohbetimizin başında ilişkimizin özünü gayet yerinde tarif ettiğinizi hatırlarsak. Altın için kan, öyle mi?";
			link.l1.go = "SKD_KlodDuran_8";
		break;
		
		case "SKD_KlodDuran_8":
			dialog.text = "Eğer bana yardım ederseniz, sadece kılıcımı değil, sadakatimi de kazanırsınız. Sizin yükseleceğiniz daha ilk bakışta belli, Kaptan. Bunu başarmanıza yardımcı olmaktan memnuniyet duyarım.";
			link.l1 = "Kabul etmeliyim, senin gibi yetenekli birinin arkamı kollamasını tercih ederim. Bu hedefini nerede bulabiliriz?";
			link.l1.go = "SKD_KlodDuran_10";
			link.l2 = "Kılıcın şimdilik yeterli olacak. Ben bir suikastçı değilim. Rahat ol, subay!";
			link.l2.go = "SKD_KlodDuran_9";
		break;
		
		case "SKD_KlodDuran_9":
			dialog.text = "Peki kaptan. Sormaya değerdi yine de.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_9_1";
		break;
		
		case "SKD_KlodDuran_9_1":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_1");
		break;
		
		case "SKD_KlodDuran_10":
			dialog.text = "Heh! İşte sorun bu, Kaptan. Bildiğim tek şey, Malta Şövalyeleri'nden eski bir şövalye olduğu ve şu anda İngiliz topraklarında bir yerlerde saklandığı. Soylu biri, yani bir harabede yaşamıyordur.";
			link.l1 = "Tarikat Şövalyesi mi?";
			link.l1.go = "SKD_KlodDuran_11";
		break;
		
		case "SKD_KlodDuran_11":
			dialog.text = "Eski bir şövalye. Evet, ve bu işi aldığım için şimdiden bin kez pişman oldum. Şövalyeler şeytan gibi dövüşür, bu yüzden kılıç kullanma becerilerin için ciddi bir sınav olacağına garanti veriyorum.";
			link.l1 = "Hoşuma gitmiyor ama deneyelim bakalım. Yani: fakir değil, soylu biri ve İngilizlerle saklanıyor? Levasseur, neden onunla ilgilenmemiz gerektiğini söylemedi mi?";
			link.l1.go = "SKD_KlodDuran_12";
		break;
		
		case "SKD_KlodDuran_12":
			dialog.text = "Tabii ki yapmaz! Ama bu işin içinde siyaset var, yoksa asker gönderirdi.";
			link.l1 = "Deneyeceğim, ama hiçbir şey vaat edemem.";
			link.l1.go = "SKD_KlodDuran_13";
		break;
		
		case "SKD_KlodDuran_13":
			dialog.text = "Sağ ol, Kaptan.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_14";
		break;
		
		case "SKD_KlodDuran_14":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_2");
		break;
		
	}
} 
