// диалоги Уракана, Канека и прочих индейцев ица
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bir şeye ihtiyacın var mı?";
			link.l1 = "Hayır, hiçbir şey.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// ица-горожане
		case "itza_ctz":
			dialog.text = LinkRandPhrase("Bir başka solgun yüz... Büyük rahip kalbini oyacak diye çok mutlu...","Sarışın surat Tayasal'a nasıl gelineceğini biliyor, ama şehirden kimse çıkamaz!","Şaşırdım, solgun yüz: hâlâ ruhlar diyarına gitmemişsin... Yürüyebiliyorken yürü, yakında atalarını göreceksin.");
			link.l1 = LinkRandPhrase("Pekâlâ, göreceğiz...","Beni korkutmaya çalışma, kızıl tenli savaşçı. Bundan daha kötülerini gördüm.","Devam et, devam et. Hadi çocukları korkutmayı dene.");
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz";
		break;
		
		case "itza_ctz_1":
			dialog.text = LinkRandPhrase("Beni düşmanımla savaş için kutsa, ulu Cavil!","Büyük Cavil ve büyük Kukulcan bize şeref veriyorlar. Eski Maya zamanlarında bile böyle bir şey olmamıştı!","Kukulcan ile Cavil arasındaki büyük savaşın efsanesini çocuklarımıza aktarırız!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz_1";
		break;
		
		// Уракан - вождь ица
		case "urakan":
			dialog.text = "Sen büyük bir savaşçısın, solgun yüz. Kanını tanrılara sunuyoruz. Onurlu bir şekilde öleceksin.";
			link.l1 = "Sakin ol, kızıl derili savaşçı. Kanek'inin beni Kukulcan'a ya da başka birine kurban olarak sunmasına izin vermeyeceğim. Savaşçıların beni ele geçiremedi. Hepsi tek tek savaşta yere serildi.";
			link.l1.go = "urakan_1";
		break;
		
		case "urakan_1":
			dialog.text = "Evet, cömert savaşçı, solgun yüzlü. Ama yüzlerce Tayasal Itza savaşçısına karşı duramazsın. Yine de, ilginç bir kelime söyledin. Büyük Kanek ve Kukulcan hakkında nereden biliyorsun?";
			link.l1 = "Peki, tahmin edeyim... Kanek olmadığınıza göre, adınız Urakan olmalı ve rahip Kanek'in oğlu olmalısınız?";
			link.l1.go = "urakan_2";
		break;
		
		case "urakan_2":
			dialog.text = "Dudakların doğruyu söylüyor, solgun yüz. Ben Urakan'ım ve şaşırdım.";
			link.l1 = "Buna bir bakınca daha da şaşıracaksın... Bak.";
			link.l1.go = "urakan_3";
		break;
		
		case "urakan_3":
			dialog.text = "Tanrılar aşkına! Eğer soluk yüzlüde maske varsa, demek ki vakit geldi... Sen, Kukulkan'ın bahsettiği kişisin. Tayasal'a geldiğinde seni ona götürmemizi emretti. Geldiğini biliyor.";
			link.l1 = "Kukulcan mı?! O burada, Tayasal'da mı?";
			link.l1.go = "urakan_4";
		break;
		
		case "urakan_4":
			dialog.text = "Evet, beyaz savaşçı. Quetzalcoatl Tayasal'a geliyor. Yakında atalara ışık getirmek için ayrılacak, Maya'nın büyük şehrine.";
			link.l1 = "Kahretsin! Demek o zaten burada...(sesini alçaltarak) Urakan, her şeyi biliyorum. Ksatl Cha'yı Gerçeğin Muhafızı ile birlikte Ksocheatem'i ve Kukulcan'ın maskesini aramaya gönderenin sen olduğunu biliyorum...";
			link.l1.go = "urakan_5";
		break;
		
		case "urakan_5":
			dialog.text = "";
			link.l1 = "Gözlerinde şaşkınlık görüyorum, ama aynı zamanda şüphe de var, ulu şef Urakan. Kukulcan'dan memnun değilsin, değil mi?";
			link.l1.go = "urakan_6";
		break;
		
		case "urakan_6":
			dialog.text = "Her Itza savaşçısı, büyük Kukulcan'ın geldiğine seviniyor, beyaz savaşçı. Kukulcan'ın huzuruna çıkmalısın. Seni birçok gece bekledi. O büyük bir kahindir. Her şeyi önceden bilir. Uçan Yılan'a git, başka bir yolun yok. Tayasal'dan ayrılmana izin vermeyeceğiz.";
			link.l1 = "Kukulcan zamanın kapılarından geçtiği anda, sen de dahil olmak üzere hepinizin yok olacağını anlamıyor musun? Ve en güzeli, başka bir bedende, başka bir biçimde yeniden doğacaksın... Belki sıradan bir savaşçı, belki de bir sakat ya da dilenci olarak...";
			link.l1.go = "urakan_7";
		break;
		
		case "urakan_7":
			dialog.text = "Git, solgun tenli savaşçı. Kukulcan'ı Itza savaşçılarının Büyük Tapınağı'nda bulacaksın. Köprüyü dümdüz geç, büyük piramidi görene kadar devam et. Tapınağın alt kapısından gir ve kutsal alana yaklaş.";
			link.l1 = "Pekala. Kukulcan'a gideceğim, çünkü bu karşılaşmadan kaçamayacağımız belli oldu. Ama seni uyardım.";
			link.l1.go = "urakan_8";
		break;
		
		case "urakan_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_warrior_SetStay(npchar, true);
			LAi_warrior_DialogEnable(npchar, true);
			NextDiag.CurrentNode = "urakan_9";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			AddQuestRecord("Tieyasal", "25");
			pchar.quest.Tieyasal_Templegreat.win_condition.l1 = "location";
			pchar.quest.Tieyasal_Templegreat.win_condition.l1.location = "Temple_great";
			pchar.quest.Tieyasal_Templegreat.function = "Tieyasal_InGreatTemple";
			// экспа за бой
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "urakan_9":
			dialog.text = "Git, beyaz savaşçı. Kukulcan seni bekliyor.";
			link.l1 = "Yoldayım...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_9";
		break;
		
		case "urakan_10":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "Gerçek oldu! Kukulcan’la nasıl savaştığını gördüğümde, senin bizzat Cavil olduğunu anladım. Tayasal’a, babam ve Kukulcan yüzünden ölümle karşı karşıya kalan Itza halkını kurtarmak için geldin. Babam, büyük rahip Kanek, çoktan ölmüş Maya atalarının adına Itza halkını felakete sürükledi.\nBen, yıllardır Itza halkını koruyan savaş reisi Urakan’ım. Tayasal’dan tek bir solgun yüz bile sağ çıkmadı. Savaşçılarım ve ben, Itza halkının daha nice yıllar boyunca güvende ve hayatta kalmasını sağladık. Tüm halkımı feda etmek istemiyorum.";
			link.l1 = "Bunu biliyordum, Urakan. Ve senden köprüde bana yardım etmeni istedim.";
			link.l1.go = "urakan_11";
		break;
		
		case "urakan_11":
			dialog.text = "Büyük Cavil’in gözünden hiçbir şey kaçmaz. Urakan’ın kim olduğunuzu tam olarak anlayamamasını bağışlayın.";
			link.l1 = "Merak etme, şef. Kukulcan’ın ölümlü bedenini yendim, ama önümüzde başka önemli bir görev var – geçmişe açılan kapıları kapatmak. Zamandaki bu doğaüstü yarık mutlaka mühürlenmeli. Bana yardım edecek misin?";
			link.l1.go = "urakan_12";
		break;
		
		case "urakan_12":
			dialog.text = "Urakan sana nasıl yardımcı olabilir, ey Cavil?";
			link.l1 = "Ksatl Cha'yı Gerçeğin Muhafızı ile birlikte Ksocheatem ve Kukulcan'ın maskesini aramaya gönderdin. Demek, bunun zamanın kapılarını kapatmak için kullanılabileceğini biliyorsun. Bunu sana baban mı anlattı?";
			link.l1.go = "urakan_13";
		break;
		
		case "urakan_13":
			dialog.text = "Babam konuşmaz. Bilgelik ve Bilgi Tapınağı'ndaki yazıları inceliyorum. Ama Urakan için çoğu şey belirsiz. Belki Cavil anlayabilir?";
			link.l1 = "Tam olarak ne öğrendin?";
			link.l1.go = "urakan_14";
		break;
		
		case "urakan_14":
			dialog.text = "Bunu ezberledim. Yazı şöyle diyor: 'Güneş yağmura karşı doğduğunda ve ateş aralarında bir üçgen oluşturduğunda, Tohil'in bacağını bacağına vur ve zaman sunağında Kukulcan'ın maskesini yak. Ve Itzamna'nın zaman kapılarını günlerin sonuna dek mühürle.'";
			link.l1 = "Ne.";
			link.l1.go = "urakan_15";
		break;
		
		case "urakan_15":
			dialog.text = "Evet.";
			link.l1 = "Tanrım... Kapıları göster bana.";
			link.l1.go = "urakan_16";
		break;
		
		case "urakan_16":
			dialog.text = "Kukulcan tapınağındalar. Ama oranın kapısı kilitli. Onu sadece babam kilitleyip açabilir. Kukulcan tapınağının kapısını açarken şöyle der: 'Güneş doğar ve batar, su yükselir ve çekilir, ateş yanar ve söner, savaş ve barış yer değiştirir, ama yalnızca gökyüzü sonsuzdur. Zamanın üstünde yalnızca gökyüzü vardır.'";
			link.l1 = "İlginç... Bunu aklımızda tutalım ve neler yapabileceğimize bakalım...";
			link.l1.go = "urakan_17";
		break;
		
		case "urakan_17":
			dialog.text = "Ben burada kalıyorum, aşağıda, zamanın sunağının yanında. Taysal’daki her piramidi ve binayı içeriden gördüm. Anahtarları bul. Ben burada kalıyorum.";
			link.l1 = "Eğer önemli bir sorum olursa, mutlaka sana gelirim.";
			link.l1.go = "urakan_18";
		break;
		
		case "urakan_18":
			DialogExit();
			NextDiag.CurrentNode = "urakan_adv";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1 = "location";
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Tieyasal_UrakanTemple.function = "Tieyasal_UrakanInTemple";
			AddQuestRecord("Tieyasal", "26");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "quest", "urakan", "", -1);
			// экспа за бой
			AddComplexSelfExpToScill(1000, 1000, 1000, 1000);
			AddCharacterExpToSkill(pchar, "Leadership", 3000);
			AddCharacterExpToSkill(pchar, "Fortune", 1500);
		break;
		
		case "urakan_adv":
			dialog.text = "Urakan, büyük Cavil’e akıl ya da yardım edebilir mi?";
			if (Tieyasal_CheckTablets() && !CheckAttribute(npchar, "quest.tablets"))
			{
				link.l1 = "Şu bulduğum tablete bir bak. Bulduğum yere bakılırsa, bunun babanla bir ilgisi olmalı, üstelik sıradan bir eşya olmadığı da belli...";
				link.l1.go = "tablets";
			}
			if (CheckAttribute(npchar, "quest.treasureentrance"))
			{
				link.l1 = "Büyük Tapınak'ın tepesinde başka bir giriş buldum, ama kapalı. İçeri nasıl girebilirim? Belki aradığım şey oradadır.";
				link.l1.go = "treasure";
			}
			link.l9 = "Şu anda bir şey yok, Urakan. Kendi başıma hallederim...";
			link.l9.go = "exit";
			NextDiag.TempNode = "urakan_adv";
		break;
		
		case "tablets":
			dialog.text = "Tanrı'nın taş levhası. Babamın elinde birkaç farklı parçası var ve onlar onun için çok değerli. Eski Tayasal ustaları bu levhayı gizli mekanizmaları çalıştırmak, kapıları açıp kapatmak, hatta büyü ritüelleri yapmak için kullanmışlar.\nDoğru yere koyarsan çalışıyorlar - babam da böyle yapıyor. Ama ben de senin gibi bir savaşçıyım, onları doğru kullanmayı bilmiyorum. Belki Cavil biliyordur?";
			link.l1 = "Bunun köküne kadar ineceğiz...";
			link.l1.go = "exit";
			npchar.quest.tablets = "true";
			NextDiag.TempNode = "urakan_adv";
			AddQuestRecord("Tieyasal", "31");
		break;
		
		case "treasure":
			dialog.text = "Bu, Tayasal hazinelerinin kapısı. Orada Itza yerlilerinin zenginlikleri yatıyor. Kapıyı içeriden sadece babam açıp kapatabilir. O olmadan hazine odasına kimse girmeye cesaret edemez. Ben bile.";
			link.l1 = "Baban girişi nasıl açtı?";
			link.l1.go = "treasure_1";
		break;
		
		case "treasure_1":
			dialog.text = "Babam der ki: 'Her servetin iki yüzü vardır. Ancak bu iki yüzü bilen Tayasal'ın hazinelerine girebilir.' Bunun ne anlama geldiğini bilmiyorum. Belki Cavil tahmin edebilir?";
			link.l1 = "Bunu da çözeceğiz...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_adv";
			DeleteAttribute(npchar, "quest.treasureentrance");
			AddQuestRecord("Tieyasal", "32");
		break;
		
		case "urakan_19":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "Bunu başardın, yüce Cavil! Itza halkı artık güvende. Ben, Kanek’in oğlu Urakan, bana bahşettiğin onuru asla lekelemeyeceğime ve Tayasal’ı senin adına namussuz beyaz yüzlülerin her türlü istilasından koruyacağıma söz veriyorum.";
			link.l1 = "Buna inanabilirim, şef. Şimdi kutlayabiliriz: Kukulcan'ın haince planlarını durdurduk. Bir daha asla bir zaman devrimi başlatamayacak.";
			link.l1.go = "urakan_20";
		break;
		
		case "urakan_20":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Büyük Cavil'e şan olsun! Benim ve neslim için Tayasal'da iki tanrı görmüş olmak büyük bir onur. Bu tarihi çocuklarımız için yazıyoruz. Onlar Tayasal'daki tanrıların savaşını bilecekler! Cavil'e şan olsun! Şan olsun!";
			link.l1 = "Bir içkiye ihtiyacım var...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_Win_IndianBead");
		break;
		
		// Канек - жрец ица
		case "kanek":
			dialog.text = "Kanatlı Yılan'ın huzurundasın, soluk yüzlü. Kudretli Kukulkan'ın ruhu, insan bedeninde. Onun bedeninin babası sayesinde kardeşi olman senin için bir şans, tıpkı onun annesinin babası olmamın benim için bir şans olduğu gibi; o kadının, ona hayat verenin. Bu büyük bir onur. Belki de bu yüzden güçlü bir savaşçı oldun ve hâlâ hayattasın. Ama vaktin dolacak, soluk yüzlü. Yeni bir çağ başlatacağız, büyük Maya'nın zamanı. Kendi gücümüzü kuracağız ve soluk yüzlülerin dünyamıza gelmesine asla izin vermeyeceğiz. Çok yakında. Ben, rahip Kanek, gidecek ve ritüeli başlatacağım!";
			link.l1 = "Harika...";
			link.l1.go = "kanek_1";
		break;
		
		case "kanek_1":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kanek_2":
			dialog.text = "Urakan, efendimizin ne dediğini duydun. Şimdi teslim ol!";
			link.l1 = "Büyüklerin savaşı başladığında, bizim gibi sıradan ölümlüler için en iyisi kenarda durup uzaktan izlemek, baba...";
			link.l1.go = "kanek_3";
		break;
		
		case "kanek_3":
			dialog.text = "Ne?! Kendine gel, oğlum!";
			link.l1 = "Bu adam Kukulcan'ın kardeşi ve büyük bir savaşçı. Onda bizzat Cavil'in vücut bulmuş halini görüyorum! Böylesi bir tanrıya ancak o dayanabilirdi. Tanrıların düellosunda oyalanmak yok, baba! Eğer Kukulcan'a adaklar sunarsan, savaşçılarım kanlarını Cavil'e verecekler!";
			link.l1.go = "kanek_4";
		break;
		
		case "kanek_4":
			dialog.text = "Akıl sağlığın yerinde mi, Urakan?";
			link.l1 = "Yıllar boyunca, Hurakan'ın adını taşıyan ben, topraklarımızı Cavil'in adına yabancıların istilasından başarıyla korudum. Yüzlercesi sopalarımızın altında can verdi ve hiçbiri Tayasal'dan sağ çıkamadı. Fakat hayatımda bu kadar güçlü ve çevik bir savaşçıya, bu solgun yüze rastlamadım. Eğer Kukulcan'ı alt edebilirse, Cavil'in ruhunun ta kendisi demektir!";
			link.l1.go = "kanek_5";
		break;
		
		case "kanek_5":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
