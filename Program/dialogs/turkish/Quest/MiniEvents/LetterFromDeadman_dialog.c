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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;
		
		case "Sailor_1":
			dialog.text = "Ne istiyorsun, "+GetSexPhrase("dostum","kız")+"? Eğer bana biraz rom ikram ediyorsan, hayır demem. Şu lanet kasabanın etrafında o kadar çok tur attım ki, bacaklarım neredeyse birbirine dolanacak. Peki, senin adın ne?";
			link.l1 = "Kaptan "+GetFullName(pchar)+". Sen 'Kartal'dan değilsin, değil mi?";
			link.l1.go = "Sailor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Sailor_2":
			if (pchar.sex == "man")
			{
				dialog.text = "Ve ben - "+GetFullName(npchar)+". Evet, ben 'Kartal'danım. Gemimizi beğendiniz mi, kaptan?";
			}
			else
			{
				dialog.text = "Kaptan? Vay canına... Hımm... Ben Antonio Velenta. Evet, 'Kartal'danım. Gemimiz gözünüze mi çarptı, Kaptan?";
			}
			link.l1 = "Bir gemi gemidir. Şehirde oyalanmak yerine bir an önce gemiye binsen iyi olur—kaptanın zaten öfkesinden köpürüyor. Akıntı çekilmeden limandan ayrılmak istiyor ve bana sorarsan, delikanlı, seni beklemeye hiç niyeti yok.";
			link.l1.go = "Sailor_3";
		break;
		
		case "Sailor_3":
			dialog.text = "Lanet olsun... Biliyorum, biliyorum... Ama bu şehirde hâlâ halletmem gereken işlerim var. Birkaç dublon kazanmak ister misin, Kaptan?";
			link.l1 = "Altın her zaman hoş karşılanır. Ama kazanmak başka, başını belaya sokmak başka. Neymiş iş? Söyle bakalım.";
			link.l1.go = "Sailor_4";
		break;
		
		case "Sailor_4":
			dialog.text = "Bakın, ambarı boşaltırken bir mektuba rastladım. Bilinçli olarak saklanmış gibi değildi, sadece eski fıçılar arasında öylece duruyordu. Fluyt'umuz birden fazla kez baskına uğradı, bu yüzden nereden geldiğini kestirmek zor.";
			link.l1 = "Mektubu buldun, peki ne olmuş yani?";
			link.l1.go = "Sailor_5";
		break;
		
		case "Sailor_5":
			dialog.text = "Bu mektup Porto Bello'dan Marisa Caldera adında birine gönderilmiş. Balmumu ile mühürlenmiş... İçimde bir his var – bu sıradan bir mesele değil. Belki bir kaptandan, belki bir tüccardan... ama kesinlikle benim gibi sıradan bir denizciden değil! Yalnız, alıcıyı bulacak vaktim yok – bizim kaptan şaka kaldırmaz.   Bunu benden almak istemez misin? Bin peso'ya bırakırım. Sen kaptansın, bu señorita'yı bulmak senin için zor olmaz. Kim bilir, belki seni altınla ya da başka bir şeyle ödüllendirir... ne demek istediğimi anladın mı?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Pekala, belki Marisa'nı ben bulurum.  Her halükarda, kaybedecek bir şeyim yok. Bin peso dışında. Mektubu ver.";
				link.l1.go = "Sailor_6";
			}
			else
			{
				Notification_Money(false, 1000, "peso");
			}
			link.l2 = "Üzgünüm dostum, ama başkasını bulman gerekecek. Mektup taşımaktan daha önemli işlerim var.";
			link.l2.go = "Sailor_end";
		break;
		
		case "Sailor_end":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_end");
		break;
		
		case "Sailor_6":
			dialog.text = "Al bakalım. Kendine iyi bak, "+GetSexPhrase("dostum","kız")+", gitmeliyim – eşyalarımın 'Kartal' ile birlikte denize açılmasını istemem.";
			link.l1 = "...";
			link.l1.go = "Sailor_accept";
			GiveItem2Character(PChar, "LFD_letter");
			AddMoneyToCharacter(pchar, -1000);
		break;
		
		case "Sailor_accept":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_accept");
			AddQuestRecord("LFD", "2");
		break;
		
		case "Dolores_1":
			dialog.text = "Sen kimsin? Ne istiyorsun?";
			link.l1 = "Benim adım Kaptan "+GetFullName(pchar)+". Marisa Caldera'yı arıyorum.";
			link.l1.go = "Dolores_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Dolores_2":
			sld = CharacterFromID("PortoBello_priest");
			dialog.text = "Marisa'yı tanımıyorum. Yanlış kapıya geldiniz. Şimdi gidin, yoksa muhafızları çağırırım – sizi anında dışarı atarlar.";
			link.l1 = "Baba "+sld.name+" bana onun arkadaşı olduğunuzu söyledi. Ona hitaben yazılmış bir mektubum var. Görünüşüne bakılırsa, epey gecikmiş. Onu bizzat teslim etmek istiyorum.";
			link.l1.go = "Dolores_3";
		break;
		
		case "Dolores_3":
			dialog.text = "Ah, Baba... Herkese karşı çok naziktir, ama insanları nadiren yanlış değerlendirir. Mektubu bana bırakabilirsin. Onun eline ulaşmasını sağlarım.";
			link.l1 = "Beni affedin, señorita, ama bunu şahsen teslim etmeyi tercih ederim. Ona nasıl elde ettiğim ve neden bu kadar geç ulaştığıyla ilgili soruları olabilir.";
			link.l1.go = "Dolores_4";
		break;
		
		case "Dolores_4":
			dialog.text = "Ve senin iyi niyetlerine öylece inanmamı mı bekliyorsun? Dürüst yüzlü nice alçağı gördüm ben. Mektubu bırak ya da yoluna devam et.";
			link.l1 = "Sana bir kaptan olarak söz veriyorum, ne sana ne de Marisa'ya zarar vermeyeceğim. Ayrıca, ister korumayı ister silah kullanmayı bilen başka birini toplantımıza davet edebilirsin. Tek amacım bu mektubu Marisa'ya şahsen teslim etmek.";
			link.l1.go = "Dolores_5";
		break;
		
		case "Dolores_5":
			dialog.text = "Pekâlâ. Yarın gece saat on birden sonra uğra. Onun seninle görüşmeyi kabul edeceğine söz veremem, ama söylediklerinin hepsini ileteceğim.";
			link.l1 = "Orada olacağım. Yakında görüşürüz.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Dolores_1");
		break;
		
		case "Marisa_1":
			dialog.text = "Merhaba, "+GetAddress_Form(NPChar)+" "+pchar.lastname+". Beni arıyormuşsun, işte buradayım. Dolores bana bir mektubun olduğunu söyledi?";
			link.l1 = "İyi günler, Bayan Caldera. Doğru, işte buradasınız. Ne yazık ki, size ulaşmam epey zaman aldı gibi görünüyor.";
			link.l1.go = "Marisa_2";
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Given: Letter for Marisa Caldera", "None");
		break;
		
		case "Marisa_2":
			dialog.text = "Dolores... Bu onun el yazısı... Ramiro'nun el yazısı!";
			link.l1 = "...";
			link.l1.go = "Marisa_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
			sld = CharacterFromID("LFD_Dolores");
			LAi_CharacterEnableDialog(sld);
		break;
		case "Marisa_2_1":
			StartInstantDialog("LFD_Dolores", "Marisa_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_3":
			dialog.text = "Ama bu nasıl mümkün olabilir? İki yıl geçti!";
			link.l1 = "...";
			link.l1.go = "Marisa_3_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_3_1":
			StartInstantDialog("LFD_Marisa", "Marisa_4", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" Kaptan... Ona nasıl sahip oldunuz? Nerede buldunuz? Her şeyi bilmem gerek! Lütfen, bildiğiniz her şeyi anlatın.";
			link.l1 = "Bu mektup bana bir denizciden geldi. Karanlık bir ambar köşesinde bulmuş ve bizzat sana teslim etmek istemiş, ama aceleyle gemisine dönmek zorunda kalmış. Bu yüzden beni seni bulmam için görevlendirdi, işte buradayım. Bildiğim her şey bu...";
			link.l1.go = "Marisa_5";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_5":
			dialog.text = "Teşekkür ederim, "+GetAddress_Form(NPChar)+"! Çok teşekkür ederim! Lütfen gitme. Seninle biraz daha konuşmak istiyorum, ama önce... Bu mektubu okumam lazım.";
			link.l1 = "Elbette, Leydi Caldera. Burada olacağım.";
			link.l1.go = "Marisa_6";
		break;
		
		case "Marisa_6":
			DialogExit();
			SetLaunchFrameFormParam("Twenty minutes passed, Marisa read the letter...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("LFD_Dolores_3", 0.0);
			LaunchFrameForm();
		break;
		
		case "Marisa_11":
			dialog.text = "Dolores... Bu mektubu son seferinden önce yazmış. Belize'deki bir tüccardan büyük bir abanoz sevkiyatı alma fırsatı çıktığını, ama yeterli parası olmadığını söylemek istemiş. O zaman bu borcu almış... İki yüz dublon... Şimdi de bu yüzden huzur bulamıyorum.";
			link.l1 = "...";
			link.l1.go = "Marisa_11_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_11_1":
			StartInstantDialog("LFD_Dolores", "Marisa_12", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_12":
			dialog.text = "Bu her şeyi açıklıyor... Ama ne yazık ki, yükünü hafifletmeyecek. Güçlü ol, Marisa. Karanlık sonsuza dek sürmez ve bu borç seni daima takip etmeyecek.";
			link.l1 = "...";
			link.l1.go = "Marisa_12_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_12_1":
			StartInstantDialog("LFD_Marisa", "Marisa_13", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_13":
			dialog.text = "Hayır Dolores, olmayacak! Ramiro, bizim yerde birikmiş parası olduğunu yazdı... Eğer hâlâ dokunulmamışsa, belki borcu ödeyip sonunda bu kâbustan kurtulabilirim.";
			link.l1 = "...";
			link.l1.go = "Marisa_13_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_13_1":
			StartInstantDialog("LFD_Dolores", "Marisa_14", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_14":
			dialog.text = "Tanrı sana merhamet gösterdi! Dualarımızı işitti...";
			link.l1 = "...";
			link.l1.go = "Marisa_14_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_14_1":
			StartInstantDialog("LFD_Marisa", "Marisa_15", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_15":
			dialog.text = "Kaptan, bu mektubu bana getirdiğiniz için bir kez daha teşekkür ederim. Benim için çok değerli... Ama sizden bir iyilik daha isteyeceğim. Görüyorsunuz, kocam Ramiro benim her şeyimdi ve başka hiçbir adamdan koruma istemedim. Şimdi o yokken, sığınacak kimsem kalmadı, kendi ailem de yok\nOnun saklandığı yere gitmem gerek – şehir dışında. Ama tek başıma gitmeye korkuyorum, rahmetli kocamın alacaklıları peşimde. Mektubu bana ulaştırarak onurlu davrandınız... Lütfen, bana bir kez daha yardım edin.";
			link.l1 = "Elbette, Marisa, sana eşlik ederim. Ne zaman yola çıkmak istersin?";
			link.l1.go = "Marisa_16";
			link.l2 = "Üzgünüm, señora, ama şehrinizdeki kalışım zaten fazlasıyla uzadı. Kırsalda gezintiler planlarımda yok.";
			link.l2.go = "Marisa_end_1";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_end_1":
			dialog.text = "Anlıyorum... Benim için umduğumdan fazlasını yaptınız zaten. Teşekkür ederim, Kaptan, ve elveda.";
			link.l1 = "Hoşça kal.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_end");
		break;
		
		case "Marisa_16":
			dialog.text = "Teşekkür ederim, Kaptan. Yarın şafakta, saat yediye kadar gelin. Hazır olacağım.";
			link.l1 = "O zaman tekrar görüşene dek, señora.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_1");
		break;
		
		case "Marisa_21":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				if (pchar.sex == "man")
				{
					dialog.text = "Caballero, işte buradasınız... Gerçekten onurlu bir adamsınız! Hadi yola çıkalım. Yolumuz, Mosquitos Körfezi'nden çok uzakta olmayan mağaraya, ormandan geçiyor.";
				}
				else
				{
					dialog.text = "Kaptan, işte buradasınız... Geleceğinizi biliyordum. Biliyor musunuz, kendi gemisine komuta eden bir kadınla ilk kez karşılaşıyorum. Ve şimdiden görüyorum ki, hem onurda hem de soylulukta herhangi bir adamdan hiç de geri kalmıyorsunuz!";
				}
				link.l1 = "Harika, señora. O halde hiç vakit kaybetmeyelim. Yakında kal ve bir an bile ayrılma.";
				link.l1.go = "Marisa_go_cove";
				if (startHeroType == 4) // если ГГ Элен
				{
					link.l1 = "Teşekkür ederim, Marisa. Babam bir kaptandı ve onurlu bir adamdı – çocukluğumdan beri bana da aynı değerleri aşıladı.";
					link.l1.go = "Marisa_22";
				}
			}
			else
			{
				dialog.text = "Sabahın erken saatlerinde, yediye doğru gel. Hazır olacağım.";
				link.l1 = "O zaman görüşürüz, señora.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_21";
			}
		break;
		
		case "Marisa_22":
			dialog.text = "Öyle mi? O da benim Ramiro’mun başına gelenin aynısını mı yaşadı?";
			link.l1 = "Kesinlikle elinde kılıçla ya da bir fırtınanın ortasında sonunu karşılamayı tercih ederdi. Ama kaderin başka planları vardı – kimseye bahsetmediği bir hastalık onu bitirdi.";
			link.l1.go = "Marisa_23";
		break;
		
		case "Marisa_23":
			dialog.text = "Kayıbınız için üzgünüm, "+pchar.name+" Rab Tanrı en iyilerimizi yanına alır... Ve her zaman nedenini anlayamasak da, bu O'nun iradesidir. Yapabileceğimiz tek şey, onların ölümsüz ruhlarının huzur bulması için dua etmektir.";
			link.l1 = "...";
			link.l1.go = "Marisa_24";
		break;
		
		case "Marisa_24":
			dialog.text = "Hadi gidelim. Yolumuz, Mosquitos Körfezi'nden çok uzakta olmayan mağaraya, ormandan geçiyor.";
			link.l1 = "Elbette. Yakında kal ve bir an bile etrafta dolaşma.";
			link.l1.go = "Marisa_go_cove";
		break;
		
		case "Marisa_go_cove":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_2");
		break;
		
		case "Marisa_31":
			dialog.text = "İşte buradayız... Ramiro ve ben gençken, o daha kocam olmadan önce, bir keresinde yağmurdan burada saklanmıştık. O zaman bana, ne olursa olsun kalbimi kazanacağını söylemişti.";
			link.l1 = "Üzgünüm, buraya kocanız olmadan tek başınıza gelmek zorunda kaldınız, señora. Böyle yerler birçok anı barındırır. Hadi etrafa bakalım – belki anıların yanında, Ramiro'nun en zor zamanlar için sakladığı şeyi de buluruz.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_4");
		break;
		
		case "Marisa_32":
			dialog.text = ""+GetSexPhrase("Señor "+pchar.lastname+"",""+pchar.name+"")+"... Bir şey bulabildin mi? Ramiro'nun geride bıraktığı şey bu mu? Beni daha çok ne korkutuyor bilmiyorum – boş olması mı, yoksa borcu kapatmaya yetmeyecek olması mı...";
			if (PCharDublonsTotal() >= 400 && GetCharacterItem(pchar, "jewelry2") >= 10 && GetCharacterItem(pchar, "jewelry3") >= 10 && CheckCharacterItem(PChar, "mushket1"))
			{
				link.l1 = "(gösterir) İşte, sandığın içindeki her şey burada. Umarım bu, kaderini daha iyiye çevirmene yeter.";
				link.l1.go = "Marisa_33";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Hâlâ sandığın içinde arama yapıyorum.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_32";
			}
		break;
		
		case "Marisa_33":
			dialog.text = "Ah, Kaptan! Tabii ki! Bu yeterli olmalı! Ama yardımınızı karşılıksız bırakamam. Alın, yüz doblon. Siz olmasaydınız, bu gizli yeri asla öğrenemezdim ve hâlâ Ramiro'nun alacaklısının gönderdiği adamlardan saklanıyor olurdum...";
			link.l1 = "Çok cömertsiniz, señora, teşekkür ederim. Bizim işimizde altın asla boşa gitmez.";
			link.l1.go = "Marisa_34";
			link.l2 = "Hayır, señora. Bu paraya benden çok daha fazla ihtiyacınız var. Önemli olan artık dertlerinizi geride bırakıp huzur içinde yaşayabilmeniz. Bu benim için fazlasıyla yeterli.";
			link.l2.go = "Marisa_35";
			RemoveDublonsFromPCharTotal(400);
			RemoveItems(pchar, "jewelry2", 10);
			RemoveItems(pchar, "jewelry3", 10);
			TakeItemFromCharacter(pchar, "mushket1");
			TakeItemFromCharacter(pchar, "obereg_7");
			TakeItemFromCharacter(pchar, "amulet_11");
			notification("Given: Amulet 'Cimaruta'", "None");
			notification("Given: Amulet 'Fisherman'", "None");
			notification("Given: Matchlock Musket", "None");
			notification("Given: Diamond (10)", "None");
			notification("Given: Ruby (10)", "None");
		break;
		
		case "Marisa_34":
			dialog.text = "Pekala, "+GetSexPhrase("señor",""+pchar.name+"")+",   gitsek iyi olur. Eğer kasabada beni gördülerse, biri peşimize düşmüş olabilir. Burada oyalanmasak iyi olur.";
			link.l1 = "Haklısın, Marisa. Hadi gidelim.";
			link.l1.go = "Marisa_naemnik";
			TakeNItems(pchar, "gold_dublon", 100);
		break;
		
		case "Marisa_35":
			dialog.text = "Kaptan, lütfen... Kocam bu silahı ailemizi korumak için saklamıştı ve eminim ki—sizin ellerinizde adil bir amaç için hizmet edecek. Ramiro, umudun tükendiği anda beni kurtaran kişiye gittiğini bilse mutlu olurdu.";
			link.l1 = "Pekala, Marisa, teşekkür ederim. Sen iyi ve onurlu bir kadınsın, ve kaderin sana bu kadar zalim davranmasına gerçekten üzülüyorum.";
			link.l1.go = "Marisa_36";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Marisa_36":
			dialog.text = "Bazen Tanrı inancımızı sınamak için bize zor günler, hatta yıllar gönderir, ama doğru yolda yürüyenleri asla terk etmez. Sizi bana yardım etmeniz için gönderdi ve şimdi umuyorum ki en büyük sıkıntım yakında geride kalacak.\nAma şimdilik, artık dönme vakti. Burada yeterince kaldık, hâlâ beni aradıkları için tehlikeli olabilir.";
			link.l1 = "Elbette, señora, gidelim.";
			link.l1.go = "Marisa_naemnik";
			GiveItem2Character(pchar, "mushket1");
			GiveItem2Character(pchar, "obereg_7");
			GiveItem2Character(pchar, "amulet_11");
		break;
		
		case "Marisa_naemnik":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Ha! Demek kayıp olanımız buradaymış! Gerçekten de burada, bu delikte bir fare gibi saklanabileceğini ve seni bulamayacağımı mı sandın? Şehri defalarca altüst ettim, meğer sen hep buradaymışsın"+GetSexPhrase(", üstüne üstlük bir de o veletle buluşmaya gittin. Nerede benim param, küçük kaltak? Hemen vermezsen, bu mağara mezarın olur.",".")+"";
			link.l1 = "...";
			link.l1.go = "Naemnik_1_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_1_1":
			StartInstantDialog("LFD_Marisa", "Naemnik_2", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_2":
			dialog.text = "Sen...";
			link.l1 = "...";
			link.l1.go = "Naemnik_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_2_1":
			StartInstantDialog("LFD_Naemnik", "Naemnik_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_3":
			dialog.text = "...";
			link.l1 = "Demek kadınlardan borç tahsil ederek geçimini sağlıyorsun? Seçtiğin mesleğe bakılırsa, akıl hiçbir zaman güçlü yanın olmamış. Kendi başına buraya kadar gelmiş olman bile şaşırtıcı, daha akıllı birini takip etmek yerine... mesela kendi çizmelerini.";
			link.l1.go = "Naemnik_4";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Naemnik_4":
			if (pchar.sex == "man")
			{
				dialog.text = "Kapa çeneni, kahraman. Senin zamanın da gelecek, ama önce onunla işim var. Beş yüz yirmi beş doblon borcu var – faiziyle birlikte. Ya hepsini öder, ya da sonsuza dek burada kalır – solucanlara yem olur. Ama madem bu kadar adilsin, onun borcunu sen öde, ben de giderim.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Sen gerçekten içeri girip, bir kadına hakaret edip, beni görmezden gelip, üstüne üstlük doblonlarla buradan sağ salim çıkabileceğini mi sanıyorsun? Pek akıllı biri olmadığın belli. Ama bir kadının önünde kavga başlatmam. O yüzden sana bir teklifim var: Madam Caldera’dan özür dile, doblonlarını al ve defol buradan. Yoksa sana gerçek terbiyenin ne olduğunu göstermek zorunda kalacağım.";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			else
			{
				dialog.text = "Çeneni kapa ve sıranı bekle. Bu sefil ile işim bitince seninle ilgileneceğim. Beş yüz yirmi beş dublon borcu var – faiziyle birlikte. Madem bu kadar adilsin, onun borcunu sen öde, ben de çekip gideyim.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Pekâlâ, kaba tavırlarını ve bana karşı olan saygısızlığını affetmeye hazırım. Ama eğer dubloonlarını alıp buradan sağ çıkmak istiyorsan, Lady Caldera'dan özür dilemen gerekecek. Yoksa, bakalım silahı kim daha iyi kullanıyor, görürüz. Ve inan bana, silahımı sadece gösteriş olsun diye taşımıyorum.";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			link.l2 = "Belli ki, sıramı bekleyeceğimi sandıysan pek akıllı değilsin. Hele de senin ve senin gibilerin Lady Caldera’ya yaşattığı onca belaya göz yumacağımı düşündüysen, hiç değilsin.";
			link.l2.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_5":
			dialog.text = "Peki, öyle olsun. Eğer gereksiz bir riske girmeden parayı alabiliyorsak, kendimi tehlikeye atmam için bir sebep göremiyorum. Altınları ver – ve yoluna git.";
			link.l1 = "Önce hanımefendiden özür dile.";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Beni affedin, señora. Şeytan bana galip geldi.";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		
		case "Naemnik_7":
			dialog.text = "Mutlu"+GetSexPhrase("","")+" Altını ver ve yoluma devam edeyim. Yapacak çok işim var, seninle burada laflayacak vaktim yok.";
			link.l1 = "Al paranı al ve buradan defol.";
			link.l1.go = "Naemnik_7_1";
			CharacterTurnByChr(npchar, pchar);
			RemoveDublonsFromPCharTotal(525);
		break;
		
		case "Naemnik_7_1":
			StartInstantDialog("LFD_Marisa", "Marisa_37", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "Marisa_37":
			dialog.text = "Kaptan, gerçekten anlamıyorum... Bu ne anlama geliyor?";
			link.l1 = "Artık hiçbir borcun yok. Özgürsün.";
			link.l1.go = "Marisa_38";
			CharacterTurnByChr(npchar, pchar);
			
			sld = CharacterFromID("LFD_Naemnik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5);
			sld.lifeday = 0;
		break;
		
		case "Marisa_38":
			dialog.text = "Ama... Şu anda sana tüm borcumu ödeyecek param yok. Biraz bekleyebilirsen...";
			link.l1 = "Anlamıyorsun, Marisa. Bana hiçbir borcun yok. Artık kimseye de borcun kalmadı. Bulduğun para da sana çok faydalı olacak. Eski hayatına dön – kilise seni bekliyor.";
			link.l1.go = "Marisa_39";
		break;
		
		case "Marisa_39":
			dialog.text = "Ben... Ben buna inanamıyorum. Böyle şeyler olmaz, "+GetSexPhrase("caballero","senorita")+"! Bana bir servet ödedin... öylece mi? Ve şimdi her şey bitti mi? Ne borç kaldı, ne peşime düşen? Söylesene, bu gerçek mi?";
			link.l1 = "Doğru, señora. Her şey bitti. Artık kimseye borcunuz yok.";
			link.l1.go = "Marisa_40";
		break;
		
		case "Marisa_40":
			dialog.text = "Oh, Kaptan, ne kadar asil birisiniz! Sanki Tanrı sizi bana göndermiş gibi hissediyorum! Ama size nasıl teşekkür edeceğimi bile bilmiyorum. Siz... hayatımı tamamen değiştirdiniz ve ben... size ne verebilirim ki?";
			link.l1 = "Hiçbir şey yapmana gerek yok, Marisa. Sadece yaşa. Korkusuzca, geçmişin zincirlerinden kurtulmuş olarak. Eski hayatına dön ve orada mutluluğu bul – bana teşekkür etmenin en güzel yolu bu olur. Hadi, seni kasabaya kadar götüreyim.";
			link.l1.go = "Naemnik_mir";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_bitva");
		break;
		
		case "Naemnik_mir":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_mir");
		break;
		
		case "Marisa_41":
			dialog.text = "Ne yaptınız Kaptan, onu öldürdünüz!";
			link.l1 = "Evet, señora. Sizi ve onurunuzu korumak zorundaydım...";
			link.l1.go = "Marisa_42";
		break;
		
		case "Marisa_42":
			dialog.text = "Ah, Kaptan, bir can almak, hele ki onun gibi birinin bile olsa, korkunç ve ağır bir günahtır! Ölümsüz ruhundan bunun küçücük bir parçasını bile temizlemek için gece gündüz dua etmen gerekecek. Tanrı şahidimdir, elimde ne varsa ona verirdim, o da çekip giderdi... Ama şimdi... şimdi onun kanı senin ellerinde, ve artık affedilip affedilmeyeceğine yalnızca gökler karar verecek!";
			link.l1 = "Belki de bu Tanrı'nın isteğiydi. Ama buna takılıp kalmayalım. Bunun yerine bu mağaradan çıkalım.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Naemnik_bitva_3");
		break;
		
		case "Marisa_51":
			dialog.text = "Kaptan, size bir kez daha teşekkür etmeme izin verin! Sağlığınız ve esenliğiniz için dua edeceğim, "+pchar.name+". Lütfen kilisemize gelin – Rab tüm günahlarınızı affetsin ve size bereketini versin.";
			link.l1 = "Belki bir ara uğrarım. Ve unutma Marisa, orada o mutlu yüzünü görmezsem çok hayal kırıklığına uğrarım.";
			link.l1.go = "Marisa_52";
		break;
		
		case "Marisa_52":
			dialog.text = "Ah, "+GetAddress_Form(NPChar)+"... Bana karşı öyle naziksiniz ki. Sizi kasabamızda tekrar görmeyi gerçekten çok isterim. Ama şimdi, affedin beni, hayatımı düzene koymak ve güzel haberi Dolores'le paylaşmak için sabırsızlanıyorum.";
			link.l1 = "Elbette, Marisa. Hoşça kal. Kendine iyi bak.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
		break;
		
		case "Marisa_54":
			dialog.text = "Kaptan, size bir kez daha sonsuz minnettarlığımı sunmak isterim! Benim için imkânsızı başardınız! Bu iyiliğiniz ve asaletiniz karşısında, son iki yıldır paralı askerlerden nasıl kaçabildiğimi anlatmak istiyorum. Belki bir gün bu bilgi sizin de işinize yarar.";
			link.l1 = "Teşekkür ederim, señora. Böyle konularda bilgi altın kadar değerlidir. Dinliyorum.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Finish_In_Town_NaemnikAlive_2");
		break;
		
		case "Marisa_55":
			dialog.text = "İşte bu iki yılı böyle geçirdim. Gücün bu kadar önemli olduğu bir dünyada, gölgelerde kalmayı bilmek, başkalarının ancak hayalini kurabileceği fırsatların kapısını açar.";
			link.l1 = "Hikayeni paylaştığın için teşekkür ederim, Marisa. Çok şey yaşamışsın ve tecrübelerin gerçekten paha biçilemez.";
			link.l1.go = "Marisa_56";
			AddCharacterExpToSkill(pchar, "Sneak", 500);
		break;
		
		case "Marisa_56":
			dialog.text = "Sizi kasabamızda tekrar görmekten gerçekten memnun olacağım. Lütfen, kilisemize gelin—Rab tüm günahlarınızı affetsin ve size bereketini bahşetsin.";
			link.l1 = "Belki bir ara uğrarım. Ve unutma Marisa, eğer orada o mutlu yüzünü göremezsem, çok hayal kırıklığına uğrarım.";
			link.l1.go = "Marisa_57";
		break;
		
		case "Marisa_57":
			dialog.text = "Ah, Kaptan... Bana çok iyi davrandınız. Ama şimdi, affedin beni, hayatımı düzene sokmak ve güzel haberi Dolores'le paylaşmak için sabırsızlanıyorum.";
			link.l1 = "Elbette, Marisa. Hoşça kal. Kendine iyi bak.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
			
			//слухи
			AddSimpleRumourCity(""+GetSexPhrase("Did you hear? Captain "+GetFullName(pchar)+" paid off Calder's widow’s debt from his own pocket! Not many would part with that kind of money for a stranger. Seems Spain still has true caballeros left!","It warms the heart to see that Spain is home not only to worthy caballeros, but also to women whose honor and courage rival any man’s.")+"", "PortoBello", 7, 1, "");
			AddSimpleRumourCity("They say a certain captain paid his own money to free Calder’s widow from her late husband’s debts! Not everyone would act so nobly. A true person of honor, don’t you think?", "PortoBello", 7, 1, "");
		break;
		
		case "Marisa_61":
			if (CheckAttribute(pchar, "questTemp.LFD_NaemnikDead"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Kaptan, sizi tekrar görmek ne büyük mutluluk! Uğrayacağınızı umuyordum. Belki bugün biraz kalıp dua etmeye vaktiniz vardır?";
						link.l1 = "Memnun"+GetSexPhrase("","")+"  Marisa ile buluşmak güzel. Ama şu anda oyalanmaya vaktim yok, korkarım. Rabbime olan görevimi unutmam, ama dua etmek biraz bekleyecek.";
						link.l1.go = "Marisa_62";
					break;

					case 1:
						dialog.text = "Kaptan, yine siz! Sizi görmek her zaman bir zevk. Görünen o ki, Tanrı size kilisenin yolunu unutturmuyor... Belki sonunda dua etmek için bir vaktiniz olur?";
						link.l1 = "Marisa, seni görmek güzel. Ama kalamam – işlerim bekleyemez. İnanıyorum ki Tanrı, dualar olmadan da düşüncelerimi bilir.";
						link.l1.go = "Marisa_63";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Kaptan, sizi tekrar görmek ne büyük bir mutluluk! Her gün, bana gösterdiğiniz iyilik için Tanrı'ya şükrediyorum. Bana yardım ettiğinizde dünya daha aydınlık oldu.";
						link.l1 = "Memnun"+GetSexPhrase("","")+"   Seni sağlıklı görmek güzel, Marisa. Umarım hayat sana başka tatsız sürprizler getirmemiştir. Çok daha mutlu görünüyorsun.";
						link.l1.go = "Marisa_64";
					break;

					case 1:
						dialog.text = "Kaptan, sizi gördüğüme çok sevindim! Her kiliseye gelişinizde içim huzurla doluyor. Yanınızda iyiliklerin ışığını getiriyorsunuz.";
						link.l1 = "Ve ben de memnunum"+GetSexPhrase("","")+" Seni görmek güzel, Marisa. Sakin bir hayata alıştın mı, yoksa bazen hâlâ geçmişe mi dönüyorsun?";
						link.l1.go = "Marisa_65";
					break;
				}
			}
			SetTimerFunction("LFD_Marisa_HelloAgain", 0, 0, 1);
		break;
		
		case "Marisa_62":	
			dialog.text = ""+pchar.name+", eğer herkes dua etmeyi ertelemiş olsaydı, dünya çoktan karanlığa gömülürdü. Endişelerini bir kenara bırak – tövbe sana devam etme gücü verir.";
			link.l1 = "Anlıyorum Marisa, ama şu anda gerçekten yapamam. Kelimeler olmadan da Rabbimin beni duyacağına inanıyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_62_1":	
			dialog.text = ""+pchar.name+", fikrini değiştirdin mi? Günahlar kendiliğinden yok olmaz, ne kadar beklersen o kadar ağırlaşırlar.";
			link.l1 = "Ne yazık ki, gitmem gerek. Ama bir dahaki sefere söz, dua edeceğim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_63":	
			dialog.text = "İnanç sadece bilmekle ilgili değil, harekete geçmekle ilgilidir! Kurtuluş yolunu sonsuza dek erteleyemezsin. Günahın yükünü üzerinden atmanın getirdiği hafifliği hissetmek istemez misin?";
			link.l1 = "Belki, ama şimdi değil. Duam beklemek zorunda kalsa da, Rabbim beni duysun.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_63_1":	
			dialog.text = "Kaptan, tövbeyi ertelemek başlı başına bir günah değil mi? Bir gün çok geç olabilir.";
			link.l1 = "Belki, ama bugün hiç vaktim yok maalesef. İnancım yanımda, Rabbim tövbemi dualarım olmadan da görüyor.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_64":	
			dialog.text = "Evet, sayende artık rahatça nefes alabiliyorum. Tanrı seni ve yolculuğunu korusun. Belki benimle dua etmek istersin?";
			link.l1 = "Dualarınız zaten yeterince güçlü. En önemlisi, artık sadece iyilikle çevrilisiniz.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_64_1":	
			dialog.text = ""+pchar.name+", sonunda fikrini değiştirdin mi? Yaratıcımıza dua edelim mi?";
			link.l1 = "Ne yazık ki Marisa, şimdi gitmem gerekiyor, yapmam gereken işler var.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_65":	
			dialog.text = "Ben sadece ileriye bakmaya çalışıyorum. Artık bir geleceğim var ve bunu tamamen sana borçluyum. Belki de bunun için birlikte Tanrı'ya şükretmeliyiz?";
			link.l1 = "Bence sen benden daha iyi yaparsın. En önemlisi, duaların sana huzur getirsin.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_65_1":	
			dialog.text = ""+pchar.name+", belki en azından bir dua etmeni sağlayabilirim?";
			link.l1 = "Beni affet, Marisa, ama ne yazık ki şu anda vaktim yok. Benim için de dua et.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera":	
			dialog.text = "Kaptan, burası değil. Aradığımız mağara Mosquitos Körfezi'nin yanında.";
			link.l1 = "...";
			link.l1.go = "Marisa_Ne_Ta_Peshera_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera_1":	
			DialogExit();
			NextDiag.TempNode = "Marisa_31";
			DeleteQuestCondition("LFD_Ne_Ta_Peshera");
			
			sld = CharacterFromID("LFD_Marisa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
	}
}