// Абигайль Шнеур
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
				if (pchar.questTemp.HWIC.Holl == "AbbyInHouse")
				{
					dialog.text = "Günaydın, efendim. Sizi evimize getiren nedir?";
					link.l1 = "İyi günler, Abigail. Benim adım "+GetFullName(pchar)+". Ben Cumhuriyet'in ve Hollanda Batı Hint Şirketi'nin çıkarlarına hizmet eden bir kaptanım.";
					link.l1.go = "AbbyAndLucas";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "Aman Tanrım, babamın parasını buldun mu? Gerçek mi bu? Ah, çok sevindim! Çabuk, babama git, seninle konuşmak istiyor. Hadi, onunla görüş!";
					link.l1 = "Yoldayım, madam.";
					link.l1.go = "exit";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyLeavesMarried")
				{
					dialog.text = "Bizi tam bir umutsuzluktan kurtardınız, kaptan! Size minnettarım! Artık Shneur ailesinin iyi adı geri kazanılabilir!";
					link.l1 = "Bir centilmen olarak sadece görevimi yapıyorum, madam. Umarım artık sizi hamimle evlenmekten alıkoyacak hiçbir şey kalmamıştır.";
					link.l1.go = "AbbyAndLucas_8";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Bir şey mi istiyorsunuz, kaptan?";
				link.l1 = "Şu anda değil, hanımefendi.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "AbigileInChurch")
				{
					dialog.text = "Selam, Kutsal Kraliçe, hayatımız, tatlılığımız ve umudumuz. Sana yakarıyoruz, Havva'nın sürgün edilmiş yoksul çocukları olarak. Sana iç çekişlerimizi gönderiyoruz, bu gözyaşı vadisinde yas tutup ağlıyoruz... ah efendim, beni korkuttunuz! Sizi buraya getiren nedir?";
					link.l1 = "Affedersiniz, Abigail, değil mi? Beni Richard Fleetwood gönderdi...";
					link.l1.go = "Seek_Island";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Bir şey mi istiyorsunuz, kaptan?";
				link.l1 = "Şu anda değil, hanımefendi.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Burada neler oluyor? Bu gürültü de ne? Baba, bu tuhaf adam kim?";
					link.l1 = "İyi günler, madam. Abigail Schneur, sanırım? Sizi gördüğüme memnun oldum. Küstahlığımı mazur görün, fakat size acil bir mektup getirdim... Aslında göndereni söylemek isterdim, ama sevgili babanız bırakın evinize girmemi, bu mesajı size ulaştırmama bile izin vermiyor.";
					link.l1.go = "Abigile_kidnapping";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDay")
				{
					dialog.text = "Ah, işte buradasın Charles. Seninle her yere gelmeye hazırım!";
					link.l1 = "Hadi gidelim o zaman.";
					link.l1.go = "Abigile_kidnapping_7";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInCabin")
				{
					dialog.text = "St. John's'a vardık mı, Charles? Richard'ı yakında görecek miyim?";
					link.l1 = "Yes, madam, we are in St. John's. Unfortunately, Richard is not in town at the moment; he was ordered to patrol near Barbados two days ago. Don't worry, he should return in a week.";
					link.l1.go = "Abigile_kidnapping_8";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileLie")
				{
					dialog.text = "Charles! Seni gördüğüme çok sevindim! Richard'dan bir haber var mı?";
					link.l1 = "Alas, my dear madame. Richard had to stay in Bridgetown for a while on a secret and important mission; it has something to do with the Dutch. I take it Richard has told you what he does for a living, right?";
					link.l1.go = "Abigile_kidnapping_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHome")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Charles! Sen misin! Sonunda geri döndün!";
					link.l1 = "Selamlar, hanımefendi. Sizi gördüğüme memnun oldum.";
					link.l1.go = "Abigile_return";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHomeGo")
				{
					dialog.text = "Ah, sonunda evimdeyim! Babamı tekrar görmek ne büyük mutluluk! Charles, benim için yaptığın her şey için sana minnettarım!";
					link.l1 = "Lütfen, böyle konuşmanıza gerek yok hanımefendi. Sadece zor durumda olan bir hanımefendiye karşı bir centilmen olarak görevimi yapıyorum.";
					link.l1.go = "Abigile_return_6";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryNext")
				{
					dialog.text = "Baba, eğer bir şey hatırlarsan, lütfen söyle! Charles, o... ona güvenebilirsin. Hatta diyebilirim ki, bize yardım edebilecek tek kişi o!";
					link.l1 = "";
					link.l1.go = "Abigile_return_12";
					pchar.questTemp.HWIC.Self = "SolomonHistoryAfter";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryEnd")
				{
					dialog.text = "Senin için gece gündüz dua edeceğim! Söyle bana... bana söyle ki bunu yapacaksın! Adayı bulacaksın, değil mi!";
					link.l1 = "Elimden geleni yapacağım, madam.";
					link.l1.go = "Abigile_return_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "final" || pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Ah, Charles! Geri döndün! Çabuk söyle, adayı buldun mu? Daha fazla beklemeye dayanamıyorum!";
					if (makeint(Pchar.money) >= 200000)
					{
						link.l1 = "Evet, Abi. Adayı ve babanın parasını buldum. Onu sana geri getirmek için buradayım.";
						link.l1.go = "Abigile_GiveMoney";
					}
					link.l2 = "Ne yazık ki, hanımefendi. Ne Kaptan Keller'ı ne de adanızı bulabildim. Elimden geleni yaptım, ama...";
					link.l2.go = "Abigile_NoMoney";
				break;
				}
				dialog.text = "Ah, sen misin Charles! Bir şeye ihtiyacın var mı? Sana bir kahve ikram edeyim mi?";
				link.l1 = "Hayır, hiçbir şey yok. Lütfen kendinizi yormayın.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "İyi günler, efendim. Ne istemiştiniz?";
			link.l1 = "Hiçbir şey, madam. Affınıza sığınıyorum. Hoşça kalın.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

//-------------------------------------------------за Голландию-----------------------------------------------
		case "AbbyAndLucas":
			dialog.text = "Sizinle tanışmak benim için bir onur, Kaptan "+GetFullName(pchar)+". Şehirdeki diğer hanımlardan seninle ilgili her türlü hikayeyi duydum. Korsan hayalet gemisini ele geçirip Willemstad'a ödül olarak getiren adam sensin. Söylesene kaptan... Bu geminin komutasında gerçekten... Richard Fleetwood mu vardı?";
			link.l1 = "Duyduğunuz her şey doğru, madam. Gerçeği öğrendiğimde en az sizin kadar şaşırdım. Bu tam bir skandal! İngiliz Milletler Topluluğu'nun bir deniz subayı, kendi ulusunun tüccarlarını sıradan bir korsan gibi yağmalıyor! O alçak, Hollanda Batı Hint Şirketi'nin desteğiyle bir 'hayalet gemi' gibi davranarak rezil işlerini gizlemeye çalıştı. Bu bahaneyle hem Şirketi suçladı hem de Hollanda gemilerine saldırdı.";
			link.l1.go = "AbbyAndLucas_1";
		break;
		
		case "AbbyAndLucas_1":
			dialog.text = "Başım dönüyor... Böyle korkunç şeyler duymak çok zor, kaptan. Richard Fleetwood'u şahsen tanırdım, asla onun böyle bir şey yapacağını düşünmezdim...";
			link.l1 = "Madame, I have been informed by my patron Lucas Rodenburg about your voyage to Curacao from Recife. Now it is clear. Fleetwood sank your ship and then returned to 'save' you and your father from being marooned on that lost island. I read the pirate's journal myself; he recorded every detail in his logbook.";
			link.l1.go = "AbbyAndLucas_2";
		break;
		
		case "AbbyAndLucas_2":
			dialog.text = "Ne kabus ama... Demek ki babam haklıymış. Sürekli Richard’ın bütün felaketlerimizin arkasındaki korsan olduğunu söylerdi. Gerçeğin ortaya çıkmasına sevinmem gerek sanırım... ah, özür dilerim kaptan. Zavallı kafam bunların hepsini kaldıramıyor... Sizin gibi önemli bir adam, benim gibi sıradan bir kızdan ne isteyebilir ki?";
			link.l1 = "Abigail, çok karmaşık ve hassas bir mesele için buradayım. Beni dinler misin?";
			link.l1.go = "AbbyAndLucas_3";
		break;
		
		case "AbbyAndLucas_3":
			dialog.text = "Elbette, efendim. Sizi dikkatle dinliyorum.";
			link.l1 = "Dediğim gibi, Şirkete hizmet ediyorum. Lucas Rodenburg sadece askeri komutanım değil, aynı zamanda iyi bir dostumdur. Beni size bir mesajla gönderdi. Evlilik teklifini kabul etmeniz, ona büyük bir mutluluk getirecektir. Sizden ricam, koruyucumla evlenmenizdir. Sizin mutluluğunuz için dünyadaki her şeyi yapmaya hazır.";
			link.l1.go = "AbbyAndLucas_4";
		break;
		
		case "AbbyAndLucas_4":
			dialog.text = "Ah, kaptan! Şimdi anlıyorum neden Bay Rodenburg bunu kendi yapmak istememiş... Zavallı babacığım çok sevinirdi, ama ben...";
			link.l1 = "Madam, bir şeyin sizi üzdüğünü görebiliyorum. Mynheer Rodenburg'un samimiyetinden mi şüphe ediyorsunuz? Belki fikrinizi değiştirmenize yardımcı olabilirim?";
			link.l1.go = "AbbyAndLucas_5";
		break;
		
		case "AbbyAndLucas_5":
			dialog.text = "Ah kaptan, hayır, Mynheer Rodenburg'un samimiyetinden hiç şüphem yok. Lucas hem bana hem de babama o kadar çok iyilik yaptı ki, o olmasaydı başımıza neler gelirdi düşünmek bile istemiyorum. Ama lütfen, benim durumumu anlamalısınız!\nAilem Rothschildler kadar zengin değil belki, ama hiçbir zaman yoksul olmadık. Shneur ailesi, Avrupa'nın bankacılık çevrelerinde servetimizle tanınır... ama şimdi bu korkunç korsan bizi mahvetti! Arkadan dönen bu çirkin dedikodulara artık katlanamıyorum. Bu kasabadaki her geveze ev kadını ve hizmetçi kız, Mynheer Rodenburg'un peşinde sadece parası için olduğumu düşünüyor. 'Tam bir Yahudi kadını gibi,' diyorlar. Ne acımasız insanlar! Keşke babam adanın yerini hatırlayabilseydi! Aile servetimizin kalanını, kız kardeşlerimi ve erkek kardeşimi öldüren o zalim korsanların elinden kurtarmak için oraya saklamıştı!\nAma zavallı babam denizci değil ki, adanın ve paramızın nerede olduğunu bir türlü hatırlayamıyor! Lütfen babamla konuşun kaptan! Belki sizin tecrübeli sezgilerinizle işine yarayacak bir şey hatırlayabilir. Lütfen o adayı ve servetimizi bulun! Böylece yoksul bir kızı utançtan ve rezillikten kurtarmış olacaksınız!";
			link.l1 = "Pekâlâ, Abigail. Babanla konuşacağım. Güven bana kızım, elimden geleni yapacağım.";
			link.l1.go = "AbbyAndLucas_6";
		break;
		
		case "AbbyAndLucas_6":
			dialog.text = "Teşekkür ederim, efendim. Sizin için gece gündüz dua edeceğim. Atalarımızın Tanrısı yanınızda olsun!";
			link.l1 = "Elveda, Abigail. Söz veriyorum, iyi haberlerle döneceğim.";
			link.l1.go = "AbbyAndLucas_7";
		break;
		
		case "AbbyAndLucas_7":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-27");
			pchar.questTemp.HWIC.Holl = "AbbyFather";
			AddLandQuestMark(characterFromId("Solomon"), "questmarkmain");
		break;
		
		case "AbbyAndLucas_8":
			dialog.text = "Ah, evet! Bay Rodenburg onurlu ve iyi kalpli bir adam. Hiç tereddüt etmeden ona rızamı vereceğim ve onu kocam olarak anmaktan mutluluk duyacağım.";
			link.l1 = "O halde görevimi tamamladım sayıyorum. Şimdi gidip Bay Rodenburg'a bu güzel haberi vermeliyim. Size içtenlikle mutluluklar dilerim, hanımefendi.";
			link.l1.go = "AbbyAndLucas_9";
		break;
		
		case "AbbyAndLucas_9":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-33");
			pchar.questTemp.HWIC.Holl = "AbbyAgreeMarried";//теперь к Лукасу
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		break;
		
//-------------------------------------------------за Англию-----------------------------------------
		case "Seek_Island":
			dialog.text = "Richard seni mi gönderdi?! Kutsal Meryem, şükürler olsun! Ah, efendim! Zavallı Richard'ın yaralandığını ve ölüm döşeğinde olduğunu duydum. Doğru mu? Söyle bana, hayatta mı?! İyi mi?!";
			link.l1 = "Richard hayatta ve... çoğunlukla sağlıklı. Önce kötü haber: biraz yıpranmış ve geçici olarak kör olmuş, ama iyileşiyor. Şimdi iyi haber: Richard seninle birlikte İngiltere'ye yelken açmak ve orada evlenmek istiyor. Karayipler'deki zamanı sona erdi ve cevabını bekliyor.";
			link.l1.go = "Seek_Island_1";
		break;
		
		case "Seek_Island_1":
			dialog.text = "Ah, sevgili haberci, Richard'a söyle, mutluluğumuz için onunla istediği her yere gitmeye hazırım. Ama kaçışımızın zavallı babamı öldüreceğinden korkuyorum... Efendim, çaresizim ve ne yapacağımı bilmiyorum. Keşke Richard o lanetli adayı ve ailemizin altınlarının olduğu sandığı bulabilseydi... Belki yokluğumda babamı bir nebze olsun teselli ederdi.";
			link.l1 = "Anladım... Görevim seni Antigua'ya götürmekti ama bu işleri biraz karıştırıyor. Eğer adayı ve sandığı bulup sana getirirsem, o zaman benimle St. John's'a ve Richard'ın yanına gelir misin?";
			link.l1.go = "Seek_Island_2";
		break;
		
		case "Seek_Island_2":
			dialog.text = "Ah evet efendim, aile dualarımızda sizi anacağım! İlk oğlumuza sizin adınızı vereceğim! Çok teşekkür ederim, kaptan! Sizin için dua edeceğim! Gidin, Tanrı ve Kutsal Meryem sizinle olsun!";
			link.l1 = "Sizi fazla bekletmeyeceğim, madam. Yakında döneceğim.";
			link.l1.go = "Seek_Island_3";
		break;
		
		case "Seek_Island_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-18");
			pchar.questTemp.HWIC.Eng = "SeekIsland";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Villemstad_houseSp2_bedroom", "goto", "goto1", "", -1);//Аби домой
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DelMapQuestMarkCity("Villemstad");
		break;
		
//--------------------------------------------против всех------------------------------------------------
		case "Abigile_kidnapping":
			dialog.text = "Oh... Ondan bir mektubunuz mu var? Ah baba, lütfen misafirlerimize bu kadar sert davranma! Beni bu takıntılı kuruntularınla utandırıyorsun! Bayım, lütfen, beni takip edin, sizinle konuşmak istiyorum.";
			link.l1 = "Teşekkür ederim, hanımefendi. Bu evde aklı başında biriyle karşılaşmak güzel.";
			link.l1.go = "Abigile_kidnapping_1";
		break;
		
		case "Abigile_kidnapping_1":
			DialogExit();
			npchar.greeting = "abigile_3";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "Abigile_Stay", -1);
			NextDiag.CurrentNode = "Abigile_kidnapping_2";
			pchar.questTemp.HWIC.Self = "AbigileTalk";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Abigile_kidnapping_2":
			DelLandQuestMark(npchar);
			dialog.text = "Babamı bağışlayın, efendim. O aslında iyi ve nazik bir insandır, ama bizim... talihsizliklerimiz onu yıktı.";
			link.l1 = "It is all right, mistress, I understand. Let me introduce myself, I am Charlie the... Knippel. I am here on the orders of Richard Fleetwood; he wants me to bring you to him. Here, please, read the letter.";
			link.l1.go = "Abigile_kidnapping_3";
		break;
		
		case "Abigile_kidnapping_3":
			RemoveItems(PChar, "NPC_Letter", 1);
			dialog.text = "Ah Richard...(okuyor). Aman Tanrım! Babamın kaybettiği tüm parayı geri vermeye karar vermiş! Ne büyük cömertlik! Sevgili, tatlı Richard! Efendim, adeta Gabriel gibi güzel haberler getiriyorsunuz! Richard nerede? Curacao’da mı?";
			link.l1 = "Hayır, hanımefendi. Ona suikast düzenlendi ve ağır yaralandı. Şu anda Antigua'da... mektubu bitirmediniz.";
			link.l1.go = "Abigile_kidnapping_4";
		break;
		
		case "Abigile_kidnapping_4":
			dialog.text = "Kutsal Meryem, günahsız doğan, bize aracılık et! Söyle bana, o güvende mi? Yarası kötü mü?";
			link.l1 = "Bu kadar endişelenmeyin, hanımefendi! Richard öyle kolayca bir avuç herifin eline düşecek adam değildir. Şu anda dinlenip iyileşiyor. Sizi yanına götürmemi istedi. Sonra ikiniz birlikte Londra'ya gideceksiniz... lütfen, mektubu bitirin, hanımefendi, acele etmeyin.";
			link.l1.go = "Abigile_kidnapping_5";
		break;
		
		case "Abigile_kidnapping_5":
			dialog.text = "Ah, evet... Üzgünüm (okuyor). Bay Knippel, sizinle yelken açmaya hazırım. Eşyalarımı toplamak ve babamla konuşmak için bir güne ihtiyacım var. Yarın tekrar gelin, sizinle geleceğim.";
			link.l1 = "Pekala, hanımefendi. Yarın burada olacağım. Merak etmeyin, ben ve tayfam yolculuğumuz boyunca sizi her türlü tehlikeden koruyacağız.";
			link.l1.go = "Abigile_kidnapping_6";
		break;
		
		case "Abigile_kidnapping_6":
			DialogExit();
			npchar.greeting = "abigile_2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Holl_Gambit", "3-22");
			pchar.quest.Abigile_Kidnap.win_condition.l1 = "Timer";
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.hour  = 7.0;
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l2 = "location";
			pchar.quest.Abigile_Kidnap.win_condition.l2.location = "Villemstad_houseSp2";
			pchar.quest.Abigile_Kidnap.function = "AbigileGoToShip";
			pchar.questTemp.HWIC.Self = "AbigileWaitNextDay";
			SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false);//таймер 3 дня, ибо нефиг
		break;
		
		case "Abigile_kidnapping_7":
			DialogExit();
			chrDisableReloadToLocation = true;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SetAbigileToCabin", -1);//Аби в каюту к ГГ поставим
			AddQuestRecord("Holl_Gambit", "3-23");
			pchar.questTemp.HWIC.Self = "AbigileOnShip";
			pchar.quest.AbigileGoToShipOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false);//таймер на 1 месяц, ибо нефиг
			pchar.quest.Abigile_died.win_condition.l1 = "NPC_Death";
			pchar.quest.Abigile_died.win_condition.l1.character = "Abigile";
			pchar.quest.Abigile_died.function = "AbigileDied";//специально для особо упоротых
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_8":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, ne yazık. Ama daha önce beklediğim gibi, bir hafta daha bekleyebilirim sanırım...";
			link.l1 = "Güzel söylediniz, hanımefendi. Bekleyişinizi biraz hafifletmek için, bu sade kamarayı arkadaşımın evine değişmeyi öneriyorum. Sizi orada yumuşak bir yatak ve özenle hazırlanmış güzel yemekler bekliyor olacak.";
			link.l1.go = "Abigile_kidnapping_9";
		break;
		
		case "Abigile_kidnapping_9":
			dialog.text = "Çok naziksin, Charlie. Teşekkür ederim. Ayaklarımın altında toprak olması iyi gelecek... Bunca dalgada savrulduktan sonra kendimi epey halsiz hissediyorum.";
			link.l1 = "Lütfen beni takip edin, hanımefendi.";
			link.l1.go = "Abigile_kidnapping_10";
		break;
		
		case "Abigile_kidnapping_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.questTemp.HWIC.Self = "AbigileInHouse";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_11":
			dialog.text = "Sizinle tanıştığıma memnun oldum, John. Nazik misafirperverliğiniz için teşekkür ederim, beyler!";
			link.l1 = "...";
			link.l1.go = "Abigile_kidnapping_12";
		break;
		
		case "Abigile_kidnapping_12":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "SentJons_HouseF3_Room2", "barmen", "bar1", "ContinueWithMerdok", -1);
			pchar.questTemp.HWIC.Self = "AbigileInRoom";
			NextDiag.CurrentNode = "First time";
			RemovePassenger(Pchar, npchar);
			pchar.quest.RemoveAbigileOver.over = "yes";//снять таймер
			sld = characterFromId("Merdok");
			LAi_SetActorType(sld);//чтобы геймер сам с ним не заговорил
		break;
		
		case "Abigile_kidnapping_13":
			DelLandQuestMark(npchar);
			dialog.text = "Ah Charlie, Richard'ı sadece birkaç kez gördüm ve ne yaptığı hakkında pek bir şey anlatmadı.";
			link.l1 = "Onun sevdiği kadından böyle büyük bir sırrı saklamasına gerçekten şaşırdım... Hanımefendi, Richard sıradan bir kaptan değil. Aynı zamanda İngiliz Gizli Konseyi'nin özel bir ajanı. Lord Protector'un bizzat verdiği hassas görevlerle ilgilenen çok önemli bir adam. Şu anda görevi, Karayipler'de Hollanda Batı Hindistan Şirketi'nin ticari gücünü yok etmekle ilgili.";
			link.l1.go = "Abigile_kidnapping_14"
		break;
		
		case "Abigile_kidnapping_14":
			dialog.text = "Beyefendi, ne diyorsunuz?";
			link.l1 = "Evet, hanımefendi. Sevgiliniz Richard - benim de dostum - çok önemli bir adam. Onun arkadaşı olmaktan her zaman gurur duydum, ama son zamanlarda bana bile çok ketum davranıyor. Belli ki gizli bir görevde. Sizi görememesine sebep olan bu görev için üzgünüm.";
			link.l1.go = "Abigile_kidnapping_15";
		break;
		
		case "Abigile_kidnapping_15":
			dialog.text = "Charlie, beni korkutuyorsun. Emin misin, iyi olduğuna?";
			link.l1 = "Bundan eminim. Sadece... Şu anda sana nasıl davrandığını onaylamıyorum. Görevinin ne kadar önemli olduğunu ve seni bile olsa, sorumluluğunu hiçe sayamayacağını anlıyorum.";
			link.l1.go = "Abigile_kidnapping_16";
		break;
		
		case "Abigile_kidnapping_16":
			dialog.text = "Ah, sevgili Charlie... Gerekirse Richard'ı İkinci Geliş'e kadar beklerim. Belki meyhanenin üst katında kalabilirim... John'un misafirperverliğinden bu kadar uzun süre yararlanamam.";
			link.l1 = "Saçmalamayı bırakın, hanımefendi! Varlığınız bize onur verir ve ben, sevgili dostum Richard Fleetwood'un nişanlısını evinden kovarsam, adım Charlie Knippel olmasın!";
			link.l1.go = "Abigile_kidnapping_17";
		break;
		
		case "Abigile_kidnapping_17":
			dialog.text = "Charlie... Duyguların beni gerçekten çok etkiledi. Ben sıradan bir kızım, üstelik Yahudi biriyim...";
			link.l1 = "Hanımefendi! Bunun pervasızca bir laf olduğunu biliyorum, siz iyi bir Hristiyan genç hanımsınız! Sakın meyhaneleri aklınızdan bile geçirmeyin! Richard'a hizmetimde size karşı görevimi yerine getiremezsem kendimi asla affetmem.";
			link.l1.go = "Abigile_kidnapping_18";
		break;
		
		case "Abigile_kidnapping_18":
			dialog.text = "Teşekkür ederim, Charlie. Senin böyle... iyi bir adam olmandan memnunum.";
			link.l1 = "It is my duty, miss. Now, I am sorry, but I have to go. You are free to walk around the town now; you must feel quite lonely confined in this house, am I right?";
			link.l1.go = "Abigile_kidnapping_19";
		break;
		
		case "Abigile_kidnapping_19":
			dialog.text = "Şey... John gerçekten ilginç bir sohbet arkadaşı. Tozları, karışımları ve türlü türlü... hastalıklar hakkında saatlerce konuşabilir. Aynı zamanda nazik ve kibar bir adam. Ayrıca, düzenli olarak kiliseye gidiyorum, buradaki rahip oldukça iyi biri... ama tabii ki, Richard'ı gerçekten çok özlüyorum.";
			link.l1 = "Bence yakında döner. Bir şeye ihtiyacınız olursa Charlie Knippel hizmetinizde.";
			link.l1.go = "Abigile_kidnapping_20";
		break;
		
		case "Abigile_kidnapping_20":
			DialogExit();
			pchar.questTemp.HWIC.Self = "MeetTonzag";
			pchar.quest.Meet_Tonzag.win_condition.l1 = "location";
			pchar.quest.Meet_Tonzag.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Meet_Tonzag.function = "TonzagMeetingInDange";
		break;
		
		case "Abigile_return":
			dialog.text = "Richard hakkında söylentiler duydum... ortadan kaybolmuş diyorlar. Bu konuda bir bilgin var mı, Charlie?";
			link.l1 = "Biliyorum, Abigail. Üzgünüm... Richard Fleetwood İngiltere'ye gitti ve geri dönmeyecek. Terfi aldı ya da başka bir yere atandı, öyle bir şey... neyse, sana yaptıklarından sonra onu tanımak bile istemiyorum.";
			link.l1.go = "Abigile_return_1";
		break;
		
		case "Abigile_return_1":
			dialog.text = "Ah, sonunun böyle olacağını biliyordum....(ağlar) Neden babamı dinlemedim ki! En azından, Lucas Rodenburg'la evlenseydim babam mutlu olurdu.";
			link.l1 = "Beni tekrar affedin, hanımefendi...";
			link.l1.go = "Abigile_return_2";
		break;
		
		case "Abigile_return_2":
			dialog.text = "Ne için, Charlie? Hiçbir suçun yok ki. Bana karşı hep iyi davrandın!";
			link.l1 = "For me to tell you even more bad news. I've just returned from Curacao; Lucas Rodenburg has been arrested for sedition and treason against the Republic. He is being sent back to Amsterdam in chains to stand trial. He tried to murder Peter Stuyvesant, director of the Company. On top of that, he attempted to overthrow the governor of Willemstad and is suspected of the murder of at least one other person, so I doubt the Stadtholder is going to let him off with a slap on the wrist.";
			link.l1.go = "Abigile_return_3";
		break;
		
		case "Abigile_return_3":
			dialog.text = "Aman Tanrım! Ne kabus ama! Bayılacağım galiba! Charles, bu doğru mu? Hayır, lütfen doğru olmadığını söyle!";
			link.l1 = "Üzgünüm, hanımefendi, işler daha da kötüleşiyor. Rodenburg'un eylemlerinin soruşturulması sırasında ortaya çıktı ki, fırkatanızı batıran korsan Lucas Rodenburg'un emriyle hareket ediyormuş. Kendi başına İngiliz gemilerine karşı gizli bir savaş yürütüyormuş. Çok üzgünüm, Abigail. Karayipler'de karşılaştığınız tüm adamlar yalancı, hırsız ve katildi.";
			link.l1.go = "Abigile_return_4";
		break;
		
		case "Abigile_return_4":
			dialog.text = "Oh... Mahvoldum. Charles... lütfen... beni Willemstad'daki evimize götür. Babama ihtiyacım var...";
			link.l1 = "Elbette, sevgili hanımefendi. Ne yazık ki burada, St. John's'ta sizin için hiçbir şey yok. Gidin, eşyalarınızı toplayın, John'a veda edin, hemen yola çıkıyoruz.";
			link.l1.go = "Abigile_return_5";
		break;
		
		case "Abigile_return_5":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-57");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);//откроем комнату Аби
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.HWIC.Self = "AbiReturnHomeGo";
			pchar.quest.AbiReturn_Home.win_condition.l1 = "location";
			pchar.quest.AbiReturn_Home.win_condition.l1.location = "Villemstad_town";
			pchar.quest.AbiReturn_Home.function = "AbiGoInVillemstad";
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "Abigile_return_6":
			dialog.text = "Hayır Charlie, asıl ben sana teşekkür etmeliyim. Sen ve John olmasaydınız başıma ne gelirdi, bilmiyorum. Takımadada tanıdığım tek dürüst adamlarsınız.";
			link.l1 = "Hm... Beni utandırıyorsun, Abigail. Sana yardım ettiğim için memnunum. Ve tüm bu karmaşa için gerçekten üzgünüm.";
			link.l1.go = "Abigile_return_7";
		break;
		
		case "Abigile_return_7":
			dialog.text = "Biliyor musun Charlie, Curacao'ya yolculuğumuz sırasında çok düşündüm. Artık her şey net - Richard Fleetwood, Bay Rodenburg - hepsi sonunda biten korkunç bir kabus gibiydi. Babamla yeniden bir aradayım ve normal bir hayata dönebiliriz\nAma kolay olmayacak - hiç paramız yok. Yine de üstesinden geleceğiz, her şey yoluna girecek. Kutsal Meryem Ana bize göz kulak olacak, O çocuklarını asla unutmaz, hatta Oğlu'nu inkâr eden inatçı yaşlı babamı bile.";
			link.l1 = "Abigail Hanım, size yardım edeceğim.";
			link.l1.go = "Abigile_return_8";
		break;
		
		case "Abigile_return_8":
			dialog.text = "Bize yardım mı edeceksin? Ama nasıl, Charlie?";
			link.l1 = "Richard bana geminin batışını ve nasıl kurtarıldığını anlattı. Ayrıca, babanın eşyalarını haritada olmayan bir adada saklamayı başardığını da biliyorum. O adayı bulup paranı geri getireceğim.";
			link.l1.go = "Abigile_return_9";
		break;
		
		case "Abigile_return_9":
			dialog.text = "Oh Charlie... Neither my father nor I can tell you where that ill-fated island is... We are not sailors. On top of that, I was terrified for my life during the attack; I don't remember a thing besides blood and the smell of death.";
			link.l1 = "Abigail, hatırlamaya çalış. Lütfen, en küçük ayrıntı bile bana yardımcı olabilir. Saldırıdan önce herhangi bir şey oldu mu? Bu ada nasıl bir yer?";
			link.l1.go = "Abigile_return_10";
		break;
		
		case "Abigile_return_10":
			dialog.text = "Ada... Bir ada gibi miydi? Bir koy, ormanlar. Bana pek bir şey ilginç gelmedi. Ah, hatırladım! Belki bu işinize yarar. Korsan saldırısından kısa bir süre önce bir fluytla karşılaştık ve kaptanını selamladık. Onu gemimize davet ettiler ve kaptanımızla akşam yemeği yediler. Biz de oradaydık. Belki o bu adayı biliyordur.";
			link.l1 = "Bu gerçekten ilginç! Fluyt'ın ve kaptanının adları neydi?";
			link.l1.go = "Abigile_return_11";
		break;
		
		case "Abigile_return_11":
			dialog.text = "Hatırlamıyorum, Charlie. Gerçekten hatırlamıyorum...";
			link.l1 = "Hatırlamaya çalış, Abi!";
			link.l1.go = "Abigile_return_12";
			pchar.questTemp.HWIC.Self = "SolomonHistory";
		break;
		
		case "Abigile_return_12":
			DialogExit();
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_return_13":
			dialog.text = "Seni bekliyor olacağız. Yardım et bana, Charlie the Knippel. Tek umudumuz sensin... Senin için dua edeceğim! Yolun açık olsun!";
			link.l1 = "Yoldayım. Elveda, Abi. Elveda, Solomon.";
			link.l1.go = "Abigile_return_14";
		break;
		
		case "Abigile_return_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "ReturnAbiNormal", -1);
			pchar.questTemp.HWIC.Self = "SeekFleut";
			AddQuestRecord("Holl_Gambit", "3-58");
			AddLandQuestMark(characterFromId("Villemstad_PortMan"), "questmarkmain");
		break;
		
		case "Abigile_NoMoney":
			dialog.text = "Ah, ah... ne yazık. Umut etmiştik ama... yine de teşekkür ederim Charlie, kimse yardım etmeye yanaşmazken sen denedin. Görünen o ki, Tanrı bana böyle bir kader biçmiş.";
			link.l1 = "Elveda, Abigail. Umarım iyi olursun.";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Abigile_Poor";
		break;
		
		case "Abigile_GiveMoney":
			dialog.text = "Bu... bu doğru mu? Gerçekten kayıp paramızı geri mi getirdin? Ah, Charlie!";
			link.l1 = "Evet, doğru. Bende. Al, senin olsun. Hepsi senin.";
			link.l1.go = "Abigile_GiveMoney_1";
		break;
		
		case "Abigile_GiveMoney_1":
			AddMoneyToCharacter(pchar, -200000);
			pchar.quest.MakeAbiPoor.over = "yes"; //снять прерывание
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			dialog.text = "Sana nasıl teşekkür edebilirim ki?! Nasıl?!";
			link.l1 = "Sana teşekkür etmene gerek yok, Abi. Senin için yapabileceğimin en azı buydu. Artık hayatına yeniden başlayabilirsin, ne Rodenburglar, ne Fleetwoodlar, ne de başka tuhaf adamlar seni kullanmaya çalışacak. Eminim baban bu parayı değerlendirecek bir yol bulur... galiba bu aileden gelen bir özellik.";
			link.l1.go = "Abigile_GiveMoney_2";
		break;
		
		case "Abigile_GiveMoney_2":
			dialog.text = "Charlie, bu kadar şımarık olma! Benim için, babam için, bizim için yaptıkların saymakla bitmez. Senin varlığına öyle alıştım ki... Her gün senin ve tayfanın selameti için yorulmadan dua ettim, etmeye de devam edeceğim, Kutsal Meryem'e emanet olasınız diye! Sen bizim koruyucu meleğimizsin. İnan ya da inanma, Tanrı seni ailemize gönderdi\nGitmeden önce bilmeni isterim ki, evimizin kapıları sana her zaman açık olacak. Ve... lütfen, sevgili Charlie, bana izin ver, seni öpeyim...";
			link.l1 = "Pekâlâ... evet, tabii ki, Abi... madem ısrar ediyorsun.";
			link.l1.go = "Abigile_GiveMoney_3";
		break;
		
		case "Abigile_GiveMoney_3":
			DialogExit();
			npchar.greeting = "abigile_1";
			npchar.dialog.currentnode = "Abigile_AllRight";
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("AbiKiss", "");
		break;
		
		case "Abigile_Poor":
			dialog.text = "Tanrı seni korusun, Charles. Bizim için hiçbir şey değişmedi... Kilisenin dışında artık yiyecek dileniyorum.";
			link.l1 = "Güçlü olun, hanımefendi. Tanrı sizinle olsun.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_Poor";
		break;
		
		case "Abigile_AllRight":
			dialog.text = "Charles, sen misin! Seni gördüğüme çok sevindim! Lütfen, otur! Hemen kahve yapayım!";
			link.l1 = "Seni görmek de beni mutlu etti, Abi. Ve iyi olmana da sevindim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_AllRight";
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Woman_FackYou":
			dialog.text = "Demek mesele buymuş?! Seni misafirim olarak ağırladım, sen ise beni soymaya kalktın?! Muhafızlar!!!";
			link.l1 = "Çeneni kapa, aptal kız.";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
