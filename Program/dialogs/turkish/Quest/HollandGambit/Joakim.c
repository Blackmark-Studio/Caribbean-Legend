// Жоаким Мерриман - португальский сумрачный гений
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbySeekIsland" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "İyi günler, efendim! Ben Doktor Joachim Merriman. Kaptan   ile konuşma şerefine mi nail oldum?"+GetFullName(pchar)+"?";
					link.l1 = "Evet, o benim. Adımı nereden bildin sen? Daha önce tanıştığımızı hatırlamıyorum.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					dialog.text = "Sizi gördüğüme sevindim, kaptan. Adımlarınızdaki canlılıktan, beni çok mutlu edecek bir haberle geldiğinizi anlıyorum. Yum Cimil'in kafatası elinizde mi?";
					link.l1 = "Bahsettiğin kafatası bende. Adeta bir fırın gibi enerjiyle dolup taşıyor.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Başka söylemek istediğiniz bir şey var mı, kaptan?";
				link.l1 = "Hayır, señor Merriman. Gidiyorum..";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "JoakimMeeting" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "İyi günler, efendim! Ben Doktor Joachim Merriman. Kaptan   ile mi konuşma şerefine nail oldum?"+GetFullName(pchar)+"?";
					link.l1 = "Evet, o benim. Adımı nasıl bildin? Daha önce seninle tanıştığımı hatırlamıyorum.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("Villemstad");
					dialog.text = "Sizi görmekten memnun oldum, kaptan. Adımlarınızdaki hafiflikten bana güzel bir haber getirdiğinizi anlıyorum. Yum Cimil’in kafatası elinizde mi?";
					link.l1 = "Bahsettiğin kafatası bende. Adeta bir fırın gibi enerjiyle dolup taşıyor, içinden kıvılcımlar fışkırıyor.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Başka eklemek istediğiniz bir şey var mı, kaptan?";
				link.l1 = "Hayır, Doktor Merriman. Ben gidiyorum.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "İyi günler. Benden bir şey ister misiniz?";
			link.l1 = "Hayır, üzgünüm.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Landlady"://хозяйка дома
			dialog.text = "Eğer Doktor Merriman'ı görmek için geldiyseniz, burada değil. Artık burada yaşamıyor.";
			link.l1 = "Anladım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady";
		break;
		
		case "Landlady_1"://хозяйка дома
			dialog.text = "Eğer Doktor Merriman'ı görmeye geldiyseniz, size söylemeliyim ki şu anda evde değil. Şu an seyahatte ve ne zaman döneceğini bilmiyorum.";
			link.l1 = "Anladım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_1";
		break;
		
		case "Landlady_2"://хозяйка дома
			dialog.text = "Eğer Doktor Merriman'ı görmeye geldiyseniz, burada değil. Artık burada yaşamıyor.";
			link.l1 = "Anladım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_2";
		break;
		
		case "JoakimSeekSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "İşleriniz sandığınız kadar gizli değil, kaptan! Ama endişelenmeyin, size bir teklifim var! Ben bir bilim insanıyım, bir nevi tabiat filozofuyum; İspanyol Ana Karası ve Batı Hint Adaları'ndaki Hintli paganların büyüleyici kültürünü inceliyorum. Lütfen benimle evime kadar yürüyüp oturma odamda muhtemelen çok kârlı olabilecek ayrıntıları konuşur musunuz?";
			link.l1 = "Merakımı ve ilgimi çektiniz. Yolu siz gösterin.";
			link.l1.go = "JoakimSeekSkull_1";
		break;
		
		case "JoakimSeekSkull_1":
			dialog.text = "Bunu reddetmeyeceksiniz, efendim! Evim buradan çok uzakta değil. Beni takip edin!";
			link.l1 = "...";
			link.l1.go = "JoakimSeekSkull_2";
		break;
		
		case "JoakimSeekSkull_2":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Villemstad_houseSp1_room", "goto", "goto1", "JoakimInRoom", -1);
		break;
		
		case "JoakimSeekSkull_3":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "Burada başkalarının kulak misafiri olmasından korkmadan konuşabiliriz. Yakın zamanda komşum Solomon Shneur'u ziyaret ettiniz. Ben de oradan geçiyordum ve, lütfen kusuruma bakmayın Kaptan, istemeden de olsa Solomon'la yaptığınız konuşmanın bazı detaylarını duydum. O kadar ilginçti ki, tüm konuşmayı dinlemek zorunda kaldım!";
			link.l1 = "Diğer kulak misafirlerinden korkan bir kulak misafiri, öyle mi?";
			link.l1.go = "JoakimSeekSkull_4";
		break;
		
		case "JoakimSeekSkull_4":
			dialog.text = "Şimdi, şimdi, kaptan! Hiç de öyle değil! Solomon benim komşum, sık sık bana gelir. Dini farklılıklarımıza rağmen iyi arkadaşız! Onun başına gelenleri biliyorum... tıpkı Willemstad’daki herkes gibi! Solomon dertlerini sabah akşam, kim dinlerse anlatır. Ama bu kadar yeter. O yaşlı Yahudi sana mutlaka, altınlarıyla birlikte bilinmeyen bir adada sakladığı eski yeşim kafatasından da söz etmiştir. Ondan bahsetti mi?";
			link.l1 = "Bana bir kafatasından bahsetmişti, ama onun yeşimden yapıldığını söylememişti. Ayrıca bunun dedesinin kafatası olduğunu da söyledi. Doğrusunu istersen, ya bir tür Kabala korkusu sandım, ya da yaşlı bunak kafayı sıyırmış diye düşündüm.";
			link.l1.go = "JoakimSeekSkull_5";
		break;
		
		case "JoakimSeekSkull_5":
			dialog.text = "Hayır, kaptan, Solomon tamamen aklı başında, sadece biraz tuhaf. Kafatası gerçekten var. Bu, eski bir Kızılderili hazinesi, Yum Cimil’in yeşimden yapılmış kafatası! O yaşlı Yahudinin onu nasıl ele geçirdiğine dair hiçbir fikrim yok. Hayatımın yarısını onu arayarak geçirdim\nSolomon’un aile servetini sakladığı o adayı bul. Kafatası mutlaka sandığında olmalı. O yeşim kafatasını bana getir, sana yarım milyon peso ödeyeceğim.";
			link.l1 = "Beş yüz mü? Bu kadarı zamanımı harcamaya değmez ki- bir dakika... yarım milyon sekizlik mi dedin?! Şaka mı yapıyorsun? Hayatımda hiç bu kadar parayı bir arada görmedim!";
			link.l1.go = "JoakimSeekSkull_6";
		break;
		
		case "JoakimSeekSkull_6":
			dialog.text = "Hâlâ genç bir adamsın, kaptan... Peki, var mısın? Bana yeşim kafatasını veriyorsun, ben de sana karşılığında beş yüz bin sekizlik veriyorum. Anlaştık mı?";
			link.l1 = "Ha, eski bir kafatası için servet mi? Tabii ki varım.";
			link.l1.go = "JoakimSeekSkull_7";
		break;
		
		case "JoakimSeekSkull_7":
			dialog.text = "Harika. Kârı bilen biriyle çalışmak her zaman zevktir. Bana tekrar ihtiyacın olursa burada, evimde bulabilirsin. Bol şans!";
			link.l1 = "Teşekkür ederim, Doktor Merriman. Sizi fazla bekletmeyeceğim.";
			link.l1.go = "exit";
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			AddDialogExitQuestFunction("CheckIslandCoordinates");//вот тут-то мы и проверим, есть ли у нас координаты острова, и далее будем исходить из результата.
		break;
		
		case "JoakimFindSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-02.wav");
			dialog.text = "Ah, evet! Gücünden tamamen haklısınız... Ama artık yeter, gösterin bana, sabırsızlıktan titriyorum.";
			link.l1 = "Buyurun, lütfen, alın. Umarım yanılmamışımdır?";
			link.l1.go = "JoakimFindSkull_1";
			DelLandQuestMark(npchar);
		break;
		
		case "JoakimFindSkull_1":
			RemoveItems(PChar, "SkullAztec", 1);
			dialog.text = "Ah, inanılmaz! Evet, işte bu. Mükemmel, kaptan, gerçekten mükemmel! Sonunda! Nihayet bu benimle! Yıllardır bu anı bekliyordum!";
			link.l1 = "Peki ya söz verdiğiniz para ne olacak, Doktor Merriman?";
			link.l1.go = "JoakimFindSkull_2";
		break;
		
		case "JoakimFindSkull_2":
			AddMoneyToCharacter(pchar, 500000);
			dialog.text = "Ah, evet, tabii ki! Yarım milyon sekizlik. Alın, hak ettiniz.";
			link.l1 = "Seninle iş yapmak zevkti. Bu kadar küçük bir şeyin bu kadar değerli olacağına inanmak zor...";
			link.l1.go = "JoakimFindSkull_3";
		break;
		
		case "JoakimFindSkull_3":
			dialog.text = "Küçük bir şey mi? Neden bahsettiğini bilmiyorsun. Bu... ah, senin cahil zihnin bu değerli kafatasının ardındaki muazzam gücü kavrayamaz bile. Doğrusunu söylemek gerekirse, zaten ayıracak vaktim yok\nYaptıkların için teşekkür ederim, kaptan. Artık veda etme vakti geldi. Gitmeliyim.";
			link.l1 = "Elveda, Doktor Merriman. Belki yine karşılaşırız.";
			link.l1.go = "JoakimFindSkull_4";
		break;
		
		case "JoakimFindSkull_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Landlady");
			sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
			sld.dialog.currentnode = "Landlady_2";
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
		break;
		
		case "JoakimSeekSkull_8":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			DelLandQuestMark(npchar);
			dialog.text = "Burada konuşabiliriz, kaptan. Komşum Solomon'un kızı Abigail Shneur ile yakın bir dost olduğunuzu biliyorum. Geminizle sevgilisine doğru yelken açtı... ama bu pek de önemli değil.";
			link.l1 = "Ne demek istiyorsunuz, Doktor?";
			link.l1.go = "JoakimSeekSkull_9";
		break;
		
		case "JoakimSeekSkull_9":
			dialog.text = "Eğer Solomon'u tanıyorsan, o zaman onun gemi kazası ve bilinmeyen bir adada sakladığı kayıp hazinelerle ilgili hikayesini de biliyor olmalısın. Bu hikayeyi Willemstad'daki herkese çoktan anlattı.";
			link.l1 = "Sence ben hem bu konuda bir şeyler duymuşumdur, hem de yaşlı Yahudinin talihsizliğiyle neden ilgileneyim ki?";
			link.l1.go = "JoakimSeekSkull_10";
		break;
		
		case "JoakimSeekSkull_10":
			dialog.text = "Solomon'u sevmiyor musun? Sana temin ederim, o sadece zararsız bir yaşlı tuhaf. Onu unut gitsin. Biz iş konuşalım\nSolomon'la birkaç uzun sohbetim oldu. Bu yaşlı Yahudinin yıllardır aradığım paha biçilmez bir antikaya sahip olduğunu keşfettiğimde neler hissettiğimi hayal bile edemezsin! Deli ihtiyar, o zavallı paralarıyla birlikte, bunu bir adada saklamış ve şimdi yerini bile hatırlamıyor\nBu antikaya ihtiyacım var. Onu bana getir, sana beş yüz bin sekizlik ödeyeceğim.";
			link.l1 = "Yarım milyon sekizlik mi? Şaka yapıyor olmalısınız, doktor. Hayatımda bir arada bu kadar parayı hiç görmedim!";
			link.l1.go = "JoakimSeekSkull_11";
		break;
		
		case "JoakimSeekSkull_11":
			dialog.text = "Hâlâ genç bir adamsın. Peki, var mısın? Kafatasını bana veriyorsun, ben de sana beş yüz bin sekizlik veriyorum. Üstelik, Süleyman'ın parasını da alabilirsin. Yaşlı adamın dediğine göre, orada yaklaşık iki yüz bin peso olmalı... Yani, toplamda yedi yüz bin sekizlik senin olacak. Anlaştık mı, kaptan?";
			link.l1 = "Beni çarpan çarpsın! Tabii ki bu bir anlaşma! Ama bu adayı nasıl bulacağım?";
			link.l1.go = "JoakimSeekSkull_12";
		break;
		
		case "JoakimSeekSkull_12":
			dialog.text = "Abigail ile konuş. Belki bir şeyler hatırlıyordur. Solomon'a sor. Bak, adanın nerede olduğunu bilseydim, zaten senden yardım istemezdim.";
			link.l1 = "Anladım. Aptalca bir soru sordum, kusura bakma. Şimdi, bu adayı bulmam gerek. Ödememi hazır beklemeni istiyorum.";
			link.l1.go = "JoakimSeekSkull_13";
		break;
		
		case "JoakimSeekSkull_13":
			dialog.text = "Kesinlikle. Birbirimizi anladığımıza sevindim, Kaptan. Arayışınızda bol şans. Beni her zaman burada, evimde bulabilirsiniz.";
			link.l1 = "Sizi fazla bekletmeyeceğim, Doktor Merriman. Hoşça kalın!";
			link.l1.go = "JoakimSeekSkull_14";
		break;
		
		case "JoakimSeekSkull_14":
			DialogExit();
			pchar.questTemp.HWIC.Self = "SeekAbiIsland";
			AddQuestRecord("Holl_Gambit", "3-55");
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", true);//закроем комнату Аби
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "First time";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		// калеуче
		case "caleuche":
			PlaySound("Voice\English\LSC\Chymiset-03.wav");
			dialog.text = "Evetttt. Kurban taşları düşmanlarımın kanıyla kıpkırmızı oldu! Yum Cimil bana ölüleri yönetme gücünü bahşetti! Bu güçle, yakında yaşayanlara hükmedeceğim!";
			link.l1 = "Çok melodramatik olmuş, Merriman. Yürüyen cesetlerden oluşan ordunla ne yapmayı düşünüyorsun? Sezar mı oynuyorsun, dünyayı fethetmeye mi çalışıyorsun?";
			link.l1.go = "caleuche_1";
			CreateLocationParticles("large_smoke", "goto", "goto37", 0.5, 0, 0, "");
		break;
		
		case "caleuche_1":
			dialog.text = "Sessiz ol, aptal! Gerçekten de gizli planımı uzun bir tiradla açıklayacağımı mı sandın?! Neyse, madem bu karşılaşmadan sağ çıkamayacaksın, anlatmamam için bir sebep yok! Önce ölümsüz lejyonlarım Karayipler’in tüm karanlık mağaralarını ve zindanlarını ele geçirecek. Karakollarım her köyde konuşlanacak ve işaretimi bekleyecek. Zamanı geldiğinde ise yürüyen cesetlerim ortaya çıkıp yaşayanların topraklarını istila edecek!\nNe yazık ki bunu görecek kadar yaşamayacaksın, zavallı küçük iyilik timsali, sözde kahraman! Tapınağıma girdin – ve buradan sağ çıkamayacaksın! Karanlık orduma ben önderlik edeceğim!";
			link.l1 = "Dinle dostum, sen hiçbir şeyi yönetmiyorsun, Jack ve boktan başka; üstelik Jack de çoktan şehirden gitti.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			PlaySound("Types\warrior04.wav");
			dialog.text = "Oh ho ho! Bana ve iskelet hizmetkârlarıma meydan mı okuyorsun?! O halde gerçek yüzümü gör ve korkudan titremeye hazır ol!";
			link.l1 = "Gel, alacağını al.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			npchar.model = "Meriman_2";
			Characters_RefreshModel(npchar);
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			dialog.text = "";
			link.l1 = "Ahhh! Tatlı İsa!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			PlaySound("Voice\English\hambit\Joakim Merriman-04.wav");
			dialog.text = "Şimdi karşında kimin durduğunu anladın mı, seni sümüklü kurtçuk?! Seninle bir hesabım var! Yum Cimil bizzat bana göz kulak oluyor! Ruhunu yutacağım!";
			link.l1 = "Pekâlâ, aptal kafa. Hadi kapışalım.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto37", "none", "", "", "Caleuche_MerrimanTeleport", -1);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto37");
			pchar.questTemp.Caleuche.Merriman_hide = "true";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Sen bir "+GetSexPhrase("Hırsız, beyim! Muhafızlar, yakalayın onu","Hırsız, kız! Muhafızlar, yakalayın onu")+"!!!","Şuna bak! Daha arkamı döner dönmez sandığımı karıştırmaya kalktın! Hırsız! Yakalayın şu hırsızı!!!","Gardiyanlar! Soygun! Hırsızı yakalayın!!!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
