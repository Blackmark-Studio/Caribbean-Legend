int iLoxlyPseudoGlobal;

// Альберт Локсли - адвокат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
    string sTemp, attrLoc;
	
    attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
	{
		i = findsubstr(attrLoc, "_" , 0);
		npchar.quest.relation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else Dialog.CurrentNode = "RelationAny_Done";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Benim adım Albert Loxley ve ben bir avukatım. Müvekkillerimin çıkarlarını davalarda savunurum. Hizmetlerim pahalıdır, ama inanın bana, her kuruşuna değer.";
				if(SandBoxMode)
				{					
					if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
					{
						link.l1 = "İngiliz yetkilileriyle başım dertte.";
						link.l1.go = "RelationTo_0";
					}
					
					if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
					{
						link.l2 = "Fransız yetkilileriyle başım dertte.";
						link.l2.go = "RelationTo_1";
					}
					if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
					{
						link.l3 = "İspanyol yetkililerle başım dertte.";
						link.l3.go = "RelationTo_2";
					}

					if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
					{
						link.l4 = "Hollanda yetkilileriyle başım dertte.";
						link.l4.go = "RelationTo_3";
					}
					if (ChangeContrabandRelation(pchar, 0) <= 5)
					{
						Link.l5 = "Kaçakçılarla kavga ettim.";
						Link.l5.go = "contraband";
					}
					Link.l7 = "Teşekkür ederim, ama neyse ki şimdiye kadar bir avukatın hizmetine ihtiyaç duymadım.";
					Link.l7.go = "exit";
					NextDiag.TempNode = "Loxly";
					npchar.quest.meeting = "1";
					break;
				}
				link.l1 = "Teşekkür ederim, ama neyse ki şimdiye kadar bir avukatın hizmetine ihtiyaç duymadım.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
				{
					link.l1 = "I need your services. I am an authorised delegate of a young lady named Helen McArthur; she is the granddaughter of the famous Nicolas Sharp. She is the only heir at law left after the death of her mother and uncle. She has every right to Isla Tesoro according to her uncle's testament. How much would you ask for helping Helen become the rightful mistress of the island?";
					link.l1.go = "saga";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga"))
				{
					if (pchar.questTemp.Saga == "loxly") // первое обращение по саге
					{
						dialog.text = "Hizmetlerime ihtiyacınız var mı, Efendim? Memnun kalacağınızdan emin olabilirsiniz.";
						link.l1 = "Yes, I need them. I am an authorised delegate of a young lady named Helen McArthur; she is the granddaughter of the famous Nicolas Sharp. She is the sole heir at law after the death of her mother and uncle. She holds all rights to Isla Tesoro according to her uncle's testament. How much would you ask for helping Helen become the rightful mistress of the island?";
						link.l1.go = "saga";
						break;
					}
					if (pchar.questTemp.Saga == "bakaut")
					{
						dialog.text = "Efendim, işinizin ayrıntılarını henüz bilmiyorum. Lütfen, daha sonra tekrar gelin, zaten size bunu söylemiştim.";
						link.l1 = "Pekâlâ.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
					{ // если не выполнил до конца квест по бакауту
						dialog.text = "Efendim, maalesef arşivlerden gerekli tüm belgeleri toplamak için daha fazla zamana ihtiyacım var. Henüz hazır değilim. Lütfen daha sonra uğrayın.";
						link.l1 = "Pekâlâ.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "removebakaut") // с бакаутом разобрались
					{
						// четвертая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							RemoveItems(pchar, "map_sharp_full", 1);
							dialog.text = "Beyefendi, neden bu kadar yavaş çalışıyorsunuz?! Artık işiniz bitti, müvekkiliniz için her şey sona erdi. Vasiyetnamenin geçerlilik süresi doldu ve Isla Tesoro artık İngiltere'ye ait. Yakında askeri üs olacak.";
							link.l1 ="Vay canına! Görünen o ki, tüm çabalarım boşa gitmiş...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Ah, işte buradasınız, efendim. Belgeleri inceledim, şimdi avans zamanı. Yanınızda doblonları getirdiniz mi?";
							if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) {n = 1000;}
							else {n = 450;}
							if (PCharDublonsTotal() >= n)
							{
								link.l1 = "Evet, verdim. İşte doblonların.";
								link.l1.go = "saga_5";
							}
							else
							{
								link.l1 = "Beni affedin, hafızam pek iyi değil, belgeleri gemimdeki sandıkta unuttum. Hemen getiririm.";
								link.l1.go = "exit";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "shadow")
					{
						// пятая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							dialog.text = "Beyefendi, neden bu kadar yavaş çalıştınız?! Artık iş işten geçti. Vasiyetnamenin geçerlilik süresi doldu ve Isla Tesoro artık İngiltere'ye ait. Yakında orası bir askeri üs olacak.";
							link.l1 ="Vay canına! Görünen o ki, tüm çabalarım boşa gitmiş...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Beyefendi, müvekkilinizin soyunu kanıtlayacak bir şey bulabildiniz mi?";
							if (!CheckCharacterItem(pchar, "Letter_beatriss"))
							{
								link.l1 = "Henüz değil. Ama bunun üzerinde çalışıyorum.";
								link.l1.go = "exit";
							}
							else
							{
								link.l1 = "Evet. Gerçekten de kesin kanıtlarım var.";
								link.l1.go = "saga_14";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
					{
						 // запрет сохранения чтобы ленку не заграбастали себе умники всякие с ГК-  лесник
						InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться																																			   
						dialog.text = "A-ah, işte buradasınız, efendim. Sizi görmek güzel. İtiraf etmeliyim ki, sizi bir süredir bekliyordum. Bu sizin başkanınız mı?";
						link.l1 = "Evet. Sizi Helen McArthur ile tanıştırayım.";
						link.l1.go = "saga_26";
						break;
					}
					dialog.text = "Hizmetlerime ihtiyacınız var mı, efendim? Memnun kalacağınızdan emin olabilirsiniz.";
					link.l1 = "Teşekkür ederim, ama şu anda onlara ihtiyacım yok.";
					link.l1.go = "exit";
				}
				if (CheckAttribute(npchar, "quest.waitgold"))
				{
					dialog.text = "İyi günler, efendim. Ücretimi getirdiğinizi varsayıyorum?";
					if (PCharDublonsTotal() >= 450)
					{
						link.l1 = "Evet, aldım. İşte doblonlarınız.";
						link.l1.go = "saga_36";
					}
					link.l2 = "Biliyor musunuz Bay Loxley, ben düşündüm de... Demek istediğim, 900 doblon işiniz için fazlasıyla yeterli.";
					link.l2.go = "saga_38";
					link.l3 = "Hatırlıyorum, Bay Loxley. Birazdan getireceğim...";
					link.l3.go = "exit";
					break;
				}
				dialog.text = "Hizmetlerime ihtiyacınız var mı, efendim? Memnun kalacağınızdan emin olabilirsiniz.";
				link.l1 = "Teşekkür ederim, ama şu anda onlara ihtiyacım yok.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "saga":
			// третья проверка времени. Отбираем Элен, чистим квестовый лут, даем флаг на Свенсона, вызываем перемены
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				RemoveItems(pchar, "map_sharp_full", 1);
				dialog.text = "Beyefendi, sanırım denizde fazla kaldınız. Isla Tesoro artık İngiliz Donanması'nın askeri üssü! Evet, Sharp'ın vasiyeti vardı, ama süresi doldu ve Isla Tesoro İngiliz tacının mülkü oldu. Ne yazık ki!";
				link.l1 ="Vay canına! Görünen o ki, tüm çabalarım boşa gitmiş...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "Hanımefendi bütün adanın sahibi olduğunu mu iddia ediyor? Hm... Görünen o ki bu iş kolay olmayacak. Isla Tesoro neredeyse İngiliz kolonisi olmuş bile...";
				link.l1 = "Henüz değil. Vasiyete göre, haritanın iki parçasını da sunan erkek ya da kadın Isla Tesoro'nun sahibi olacak. Bizde Sharp'ın haritasının iki parçası da var, bu da mirasın ana kanıtı.";
				link.l1.go = "saga_1";
			}
		break;
		
		case "saga_1":
			dialog.text = "Nicolas Sharp... Demek öyle. Arşive gidip Isla Tesoro ile ilgili belgeleri incelemem gerekiyor. Harita yanında mı?";
			link.l1 = "Var, ama sana ancak bir sözleşme imzaladıktan sonra vereceğim. Peki, hizmetlerinin bedeli ne olacak?";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			sTemp = "";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = " Your esteemed involvement won't go unnoticed either. Cartagena... There will be questions.";
			dialog.text = "Dediğim gibi - bu iş kolay olmayacak. Bütün bir adanın mülkiyet hakkını kanıtlaman gerekiyor, eski bir tekneye ya da kulübeye değil. Üstelik, Nicolas Sharp bir korsandı ve korsanlara ya da onların akrabalarına yardım etmek pahalıya patlar."+sTemp;
			link.l1 = "Bana gerçek bir miktar söyleyecek misin?";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "Efendim, nihai tutar dava sırasında belirlenecek. Hâlâ ne kadar sorunlu olacağını bilmiyorum. Ama bir avans tahmini yapmaya hazırım - "+sTemp+" dublon. Bu miktar altını işimizin nasıl gittiğine bağlı olarak bir ya da iki kez daha ödemek gerekecek.\nParayı bir hafta içinde getir, arşivleri kontrol edip hazırlanmak için zamana ihtiyacım var. Sonra bir anlaşma yaparız. Anlaştık mı?";
			link.l1 = "Seni takımadadaki en iyi avukat olarak tavsiye ettiler, o halde anlaştık. Bir hafta sonra görüşürüz!";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			DialogExit();
			pchar.questTemp.Saga = "bakaut"; // обновляем флаг
			AddQuestRecord("Testament", "2");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) AddQuestUserData("Testament", "sMoney", "1000");
			else AddQuestUserData("Testament", "sMoney", "450");
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				bDisableFastReload = true;
				SetFunctionLocationCondition("HelenDrinking_PortRoyalDialog", "PortRoyal_town", false);
			}
		break;
		
		case "saga_5":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
			{
				RemoveDublonsFromPCharTotal(1000);
				//Log_Info("You have given 1450 doubloons");
			}
			else
			{
				RemoveDublonsFromPCharTotal(450);
				//Log_Info("You have given 450 doubloons");
			}
			PlaySound("interface\important_item.wav");
			dialog.text = "Pekâlâ. Davanızı üstlenmeye ve mahkemede çıkarlarınızı savunmaya hazırım. Şimdi, lafı fazla uzatmayalım. Arşivlerde iyi iş çıkardım ve önemli insanlarla konuştum. Sharp'ın mirasıyla ilgili dava kolay olmayacak. Haritanın iki parçasını da elde etmiş olmanız iyi, ama bu yeterli olmayabilir.\nAlbay Doyle, Tortuga'nın kontrolünü ele geçiremeyince Isla Tesoro için büyük planlar yaptı. Doğal savunmaları var ve bu bölgedeki gelecekteki bir askeri üs olarak kullanılabilir.";
			link.l1 = "Ama Helen'in İngiliz yasalarına göre adada tam hakkı var!";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Belki bilmiyorsundur ama merhum Sharp vasiyetine bir ekleme yapmıştı. Mirasçı ya da mirasçılar onun soyadını taşımak zorunda. Ve bildiğim kadarıyla, senin kızın farklı bir soyadına sahip. McArthur demiştin, değil mi?";
			link.l1 = "Bu, onun üvey babasının soyadı, fakat Helen'ın Sharp soyadını taşıma hakkı var; çünkü o, merhum Beatrice Sharp'ın kızı, yani Nicolas'ın torunu.";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Harika! Ama bunu yemin ederek kim doğrulayabilir? Helen’in üvey ebeveynleri Beatrice Sharp’ı tanıyor muydu?";
			link.l1 = "Anladığım kadarıyla, öyle değildi. Bay McArthur onu Gladys'in kızı olarak görüyordu, oysa Gladys sadece kızın babasını tanıyordu.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Bu gerçekten üzücü. Görüyorsunuz, arşivlerde Beatrice Sharp'ın hiç çocuğu olduğuna dair bir kayıt bulamadım. Çocuğun doğumuna dair resmi bir kayıt hiç olmayabilir de. Herkes kendini Sharp'ın torunu ilan edip onun soyadını taşımaya hakkı olduğunu iddia edebilir.";
			link.l1 = "Ama haritanın tamamı sadece Helen'de var!";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Bu onun koz kartı, ve belki de yerel yetkililerin Isla Tesoro için kendi planları olmasaydı bu yeterli olurdu. Beatrice'in el yazısıyla yazılmış, imzasını taşıyan bir belge arşivde duruyor. Onun tarafından yazılmış, kızının doğumunu kanıtlayacak bir belge bulmamız gerekiyor—o kızı ki, o Gladys'e verilmişti... eh, soyadı neydi?";
			link.l1 = "Chandler. Belize'den Gladys Chandler.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Aynen öyle. Böyle bir şeyi bulma şansın var mı?";
			link.l1 = "Pek sanmıyorum. Çok yıl geçti üzerinden. Efsaneye göre, Helen’in babası bizzat Kaptan Butcher olabilir. Belki de St. John’un eski celladı bu konuda bize bir şeyler anlatabilir. Helen’in babasını hayatta gören son kişi oydu.";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "Hm. Gerçekten de eğlenceli bir adamdı. Yanılmıyorsam adı Raymond Baker’dı. Onunla bir kez sohbet etme şansım oldu. Akıllı ve iyi eğitimli bir adam. Neyse, sen Antigua’da bir şeyler bulmaya çalış, ben de arşivlerde araştırmaya devam edeceğim, belki işe yarar bir şey bulurum.";
			link.l1 = "Pekâlâ. Bana uyar.";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Bana Sharp'ın haritasını ver ve acele et, Baker'la konuş, belki onun yardımıyla bazı belgeler bulabilirsin. Hatta onun doğumuna dair bir kanıt bile bulabilirsin.";
			link.l1 = "Eh, keşke yapabilsem. Peki, görüşürüz Bay Loxley.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			DialogExit();
			RemoveItems(pchar, "map_sharp_full", 1);
			pchar.questTemp.Saga = "shadow";
			pchar.questTemp.Saga.Shadows = "sentjons";
			AddQuestRecord("Shadows", "1");
		break;
		
		case "saga_14":
			dialog.text = "Öyle mi? Hadi şu kanıtlara bir bakalım.";
			link.l1 = "Bu, Beatrice Sharp'ın kardeşine yazdığı özel bir mektup. Burada, bir kız çocuğu dünyaya getirdiğini ve çocuğun babasının aslında Lawrence Beltrope olduğunu yazıyor. Kız, Gladys Chandler adında genç bir dul kadına gönderilmiş. Lawrence Beltrope'un diğer adı ise Kaptan Butcher. Al, mektubu sana vereyim...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			RemoveItems(pchar, "Letter_beatriss", 1);
			dialog.text = "";
			link.l1 = "Gladys bunu yemin ederek doğrulamaya hazır. Ayrıca babasının kendini Kaptan Butcher olarak tanıttığını da doğrulamaya hazır.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // Белтроп убит
			{
				dialog.text = "Bir dakika! Kaptan Butcher, kötü şöhretli korsan ve İngiliz tebaasının katili, yirmi yıl önce St. John's kalesinde asıldı. Ve Lawrence Beltrope, Richard Doyle'un yakın dostu, kısa süre önce trajik bir şekilde hayatını kaybetti. Üstelik Doyle, onu Sharptown'un yeni valisi yapmak istiyordu!";
				link.l1 = "Ha! Tabii, kimse bunu bilmiyor... St. John's'un eski celladı Raymond Baker'ın yazılı bir ifadesi var; Butcher'ın idamını ölüm tehdidiyle sahte olarak gerçekleştirmeye zorlandığını söylüyor! Bak, işte burada...";
				link.l1.go = "saga_17";
			}
			else
			{
				dialog.text = "Bir dakika! İngiliz tebaasını katleden ünlü korsan Kaptan Butcher, yirmi yıl önce St. John's kalesinde asıldı. Lawrence Beltrope ise hayatta ve Port Royal'ın en görkemli malikanelerinden birinde yaşıyor. Üstelik Doyle onu Sharptown'ın yeni valisi yapmak istiyor!";
				link.l1 = "Ha! Tabii, kimse bunu bilmiyor... St. John's'un eski celladı Raymond Baker'ın yazılı bir ifadesi var bende; Butcher'ın idamını ölüm tehdidiyle sahte olarak gerçekleştirmeye zorlandığını söylüyor! Al, bak istersen...";
				link.l1.go = "saga_17";
			}
		break;
		
		case "saga_17":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "Hm. Bakalım, bakalım...";
			link.l1 = "Bu oldukça ustaca değil mi? Kaptan Butcher hayatta kalmayı başardı ve İngiltere'ye döndü. Adını tekrar Lawrence Beltrope olarak değiştirdi ve kimseye fark ettirmeden buraya geri geldi.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "saga_18";
			else link.l1.go = "saga_22";
		break;
		
		case "saga_18":
			dialog.text = "Ama bu... Bu her şeyi değiştirir! Beatrice'in mektubunu yayımlamak, askeri valinin bunca zamandır firari korsan Butcher'ı sakladığını gösterecek; oysa Butcher'ı görünce hemen tutuklayıp geçmişteki suçlarından dolayı mahkemeye çıkarmaları gerekirdi!\nVe Baker'ın tanıklığı, buna karşı öne sürülebilecek tüm itirazları tamamen çürütecek! Bu harika! Böyle bir koz elimizdeyken, Doyle'u adil bir şekilde alt edeceğiz!";
			link.l1 = "Memnun oldum. Bu sınavda sana güveniyorum. Ayrıca, söyle bakalım, Lawrence Beltrope nasıl öldü?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "Bu ürkütücü bir hikaye, efendim. Kendi yatak odasında, yüzü dehşetle buruşmuş halde bulundu. Böylesine korkusuz bir adamı neyin bu kadar dehşete düşürdüğünü hayal etmek bile zor. Diyorlar ki, vücudu kırağıyla kaplıymış. Bedeni korkunç, derin yaralarla doluydu ama yerde tek bir damla kan yoktu! Düşünebiliyor musunuz! Tek bir damla bile yok!";
			link.l1 = "Evet, bu tam bir kâbus gibi geliyor. Görünüşe göre öldürülmüş... Ama bunu kim yapmış olabilir?";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Bilinmiyor. Her şey çok karmaşık... Garnizonun hekimi, yaralarının ölümcül olmadığını söyledi. Beltrope korkudan, acıdan ya da başka bir şeyden öldü. Her halükarda, bu gizemli bir ölüm.";
			link.l1 = "Anlıyorum... Peki, duruşma ne zaman başlayacak?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Her şey size bağlı, efendim. Ücretimin ikinci kısmı olan 450 dublonu ödediğiniz anda tüm belgeleri mahkemeye sunacağım. Bundan bir hafta sonra Helen haklarına kavuşacak.";
			if (PCharDublonsTotal() >= 450)
			{
				link.l1 = "Pekâlâ. İşte doblonlarınız.";
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = "Evet, elbette. İhtiyacın olan parayı sana getireceğim.";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		break;
		
		case "saga_23":
			// шестая проверка времени
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				dialog.text = "Bayım, beni gerçekten şaşırttınız! O kadar çok şey yaptınız ki, ada neredeyse bizim olacaktı, ama şimdi her şey bitti çünkü ücretimi ödemekte geciktiniz! Vasiyetnamenin süresi doldu ve Isla Tesoro artık İngiliz tacına ait. Orası bir askeri üs olacak.";
				link.l1 ="Vay canına! Görünen o ki, tüm çabalarım boşa gitmiş...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "İkinci kısmı da getirdiniz mi, efendim?";
				if (PCharDublonsTotal() >= 450)
				{
					link.l1 = "Evet, tabii ki. İşte doblonlarınız.";
					link.l1.go = "saga_24";
				}
				else
				{
					link.l1 = "Affedersiniz, hafızam biraz zayıf, onları gemimdeki bir sandıkta unuttum. Hemen getiririm.";
					link.l1.go = "exit";
					NextDiag.TempNode = "saga_23";
				}
			}
		break;
		
		case "saga_22":
			dialog.text = "Ama bu... bu her şeyi değiştirir! Beatrice'in mektubunu yayımlamak demek, Lawrence Beltrope'un derhal tutuklanıp geçmişteki suçları için mahkemeye çıkarılması gerektiği anlamına geliyor!\nVe Baker'ın tanıklığı, buna karşı öne sürülebilecek tüm argümanları yerle bir edecek! Bu harika! Böyle bir kozumuz varken, Doyle'u açık açık yeneceğiz!";
			link.l1 = "Çok memnun oldum. Duruşma ne zaman başlayacak?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_24":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Mükemmel, efendim. Sizinle iş yapmak bir zevkti. Şimdi, anlaşma şöyle. Yarın tekrar buraya gelin. Evet, evet, doğru duydunuz – yarın! Sonuçta, ben takımadaların en iyi avukatıyım ve bağlantılarım var.\nMüvekkilinizi getirin, o olmadan duruşma olmaz. Geç kalmayın ve şehirden ayrılmayın. Ve eğer mümkünse ödemenin son kısmını da yanınızda getirin, zaferimizden tamamen eminim.";
			link.l1 = "Güzel. Yarın ofisinizde olacağız, Bay Loxley.";
			link.l1.go = "saga_25";
		break;
		
		case "saga_25":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "court_date");
			pchar.questTemp.Saga = "court"; // обновляем флаг
			AddQuestRecord("Testament", "10");
			NextDiag.CurrentNode = "First time";
			// закрываем выходы из города
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);// лесник там нет этого пирса
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
			// снимаем общий таймер Саги!
			pchar.quest.Saga_TimeOver.over = "yes";
		break;
		
		case "saga_26":
			dialog.text = "MacArthur mı? Hayır, Sharp! Hadi şimdi peşimden gel!";
			link.l1 = "...";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			LAi_ActorFollow(sld, npchar, "", -1);
			NextDiag.CurrentNode = "saga_28";
			// открываем выходы из города
			//LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник рано 
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
			//LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "saga_28":
			dialog.text = "Sizi ve hanımefendiyi tebrik etmek isterim, efendim. Artık Isla Tesoro'nun meşru hükümdarı o. Bunu kutlamak için bir kadeh şampanya içmeye değer!";
			link.l1 = "Kesinlikle, Bay Loxley. Konuşmanız gerçekten mükemmeldi. Mahkemede Lawrence Beltrop'un Kaptan Butcher olduğunu söylediğinizde Albay Doyle'un kalp krizi geçireceğini sandım.";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Evet, Bay Doyle Isla Tesoro'da askeri üs kurma hayaline veda etmek zorunda kalacak. Ne yapabilir ki? Kanun kanundur ve herkes için yazılmıştır, saygıdeğer albay için bile.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			{
				link.l1 = "Tüm belgeler tamam mı ve Helen'in ada üzerindeki hakkını doğruluyorlar mı?";
				link.l1.go = "saga_30";
			}
			else
			{
				link.l1 = "Hakimin Lawrence Beltrop'un tutuklanmasını emrettiğini duydum. Sanırım onu asacaklar?";
				link.l1.go = "saga_34";
			}
		break;
		
		case "saga_30":
			dialog.text = "Elbette, efendim. Üzerlerindeki her virgülü kontrol ettim. Doğru olduklarından emin olabilirsiniz.";
			link.l1 = "Pekâlâ...";
			link.l1.go = "saga_31";
		break;
		
		case "saga_31":
			dialog.text = "Well, my job is done. The case was tricky, but we have won it together. Now, Sir, you only have to pay me the final part of my fee. No pressure, I realise that you must be busy. But I trust you will find time to bring me the remaining 450 doubloons within a week.\nBesides, a client like you can always count on substantial discounts. I can be of great help to you; I have connections in every capital of the archipelago, even in the hostile ones, so any legal problem you encounter can be settled.";
			link.l1 = "Mükemmel. Artık kime soracağımı biliyorum.";
			link.l1.go = "saga_32";
		break;
		
		case "saga_32":
			dialog.text = "En zorlu durumlarda bile sana olumlu bir sonuç garanti ediyorum.";
			link.l1 = "Güzel. Şimdi gitmem lazım, Helen'le yapacak çok işimiz var.";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Hoşça kalın, efendim.";
			link.l1 = "Hoşça kal, Bay Loxley.";
			link.l1.go = "saga_35";
		break;
		
		case "saga_34":
			dialog.text = "Sanırım öyle, o Kaptan Butcher, bir korsan ve bir haydut. Ama şu anda Port Royal'de değil. Kaçmayı başardı, adanın içlerine doğru ilerledi. Ama av başladı ve kesinlikle yakalanacak.";
			link.l1 = "Anladım... Evraklar tamam mı?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_35":
			DialogExit();
			SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // таймер на оплату услуг
			DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
			npchar.quest.waitgold = "true";
			pchar.questTemp.Saga = "lastpages";
			NextDiag.CurrentNode = "First time";
		break;
		
		case "saga_36":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Harika! Sizinle iş yapmak büyük bir zevkti, efendim! Artık her konuda yardımımı isteyebilir ve indirim alabilirsiniz. Kanunla başınız dertteyse, başınıza ödül konduysa... Buyurun gelin. Sizi her zaman görmekten memnuniyet duyarım.";
			link.l1 = "Belaya hiç bulaşmasam daha iyi olurdu, ama... bazen işler yolunda gitmiyor. Teşekkür ederim ve hoşça kalın, Bay Loxley.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			DialogExit();
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			NextDiag.CurrentNode = "Loxly"; // услуги адвоката
		break;
		
		case "saga_38":
			dialog.text = "Ne demek istiyorsunuz, efendim? Anlaşmamızın şartlarını çiğnemeyi mi düşünüyorsunuz?";
			link.l1 = "Aynen öyle. İşin çoğunu ben yaptım. Kanıtları elde etmek için neler çektiğimi hayal bile edemezsin. Sen ise sadece o evrakları alıp mahkemeye gittin. Dokuz yüz doblon fazlasıyla yeterli, bundan eminim.";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = "Sen bir korsan gibi konuşuyorsun, Bayım! Dört yüz elli doblon kaybetmekten fakirleşmem ama sen de zenginleşmeyeceksin. Aslında, sen çok daha fazlasını kaybettin! Ve belki gelecekte de bir şeyler kaybedebilirsin... Hemen evimden çık ve bir daha asla burada görünme!";
			link.l1 = "Ve bunu yapacağım. Elveda, Bay Loxley.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // закроем вход к Локсли
			ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;
		
		case "saga_40":
			dialog.text = "Seninle konuşmak istemiyorum. Defol git yoksa muhafızları çağırırım!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
		break;
		
		// провалы Саги
		case "saga_l3":
			dialog.text = "Efendim, eğer daha önce bana gelmiş olsaydınız davanızı kazanabilirdik. Vasiyetnamenin süresi doldu. Üzgünüm.";
			link.l1 = "Eh, ben daha da üzgünüm! Neyse, hoşça kalın Bay Loxley.";
			link.l1.go = "saga_l3_1";
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l3";
		break;
		
		case "saga_l3_1":
			DialogExit();
			pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga = "late_l3"; // для Свенсона
		break;
		
	//-------------------------------------- адвокатские услуги ------------------------------------------------
		case "Loxly":
			dialog.text = TimeGreeting()+", Efendim. Sizi görmek güzel. Hizmetlerime ihtiyacınız var mı?";
			link.l1 = "Evet. Bu yüzden buradayım.";
			link.l1.go = "loxly_1";
			link.l2 = "Hayır, neyse ki şu anda onlara ihtiyacım yok. Sadece seni selamlamak istedim.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "loxly_1":
			dialog.text = "Seni dinlemeye hazırım. Ne tür bir yardıma ihtiyacın var?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l1 = "İngiliz yetkilileriyle başım dertte.";
				link.l1.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l2 = "Fransız yetkilileriyle başım dertte.";
				link.l2.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l3 = "İspanyol yetkilileriyle başım dertte.";
				link.l3.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "Hollanda makamlarıyla başım dertte.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Kaçakçılarla kavga ettim.";
				Link.l5.go = "contraband";
            }
			Link.l7 = "Üzgünüm, fikrimi değiştirdim...";
			Link.l7.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "RelationYet": // уже оплачено
			dialog.text = "Sizin işiniz üzerinde zaten çalışıyorum. Her şey yoluna girecek, size teminat verebilirim.";
			Link.l1 = "Teşekkür ederim. Bekliyor olacağım.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		// --> снятие НЗГ
		case "RelationAny_Done":
			i = sti(npchar.quest.relation);
			iLoxlyPseudoGlobal = CalculateRelationSum(i, true);
			int iRate = abs(ChangeCharacterNationReputation(pchar, i, 0));
			if (iRate <= 10) sTemp = "Well, I wouldn't call that trouble. Just a little problem. I will settle the affair at once";
			if (iRate > 10 && iRate <= 30) sTemp = "Yes, your reputation is slightly spoiled but I don't see anything critical. I will settle the affair at once";
			if (iRate > 30 && iRate <= 60) sTemp = "Yes, you went down the wrong path with the authorities. It won't be easy but I am sure that I will be able to settle your disagreements without a hitch";
			if (iRate > 60 && iRate <= 90) sTemp = "And how did you do that, Sir? Your troubles are not just serious, they are really serious. The authorities are very eager to get you. I will have to put a lot of effort into settling your disagreements";
			if (iRate > 90) sTemp = "Well... The situation is catastrophic - you are claimed to be the most bitter enemy. It will be tough but I am the best lawyer in the Caribbean after all, so I will settle your disagreements";
			dialog.text = ""+sTemp+" ile "+XI_ConvertString(Nations[i].Name+"Abl")+". Bunun sana bir bedeli olacak "+FindRussianMoneyString(iLoxlyPseudoGlobal)+".";
			if(sti(pchar.money) >= iLoxlyPseudoGlobal)
			{
				link.l1 = "Pekâlâ, Bay Loxley, kabul ediyorum. İşte paranız, işleri mümkün olduğunca çabuk halletmeye çalışın.";
				link.l1.go = "relation";
			}
			link.l2 = "Şu anda istediğin paraya sahip değilim. Sonra tekrar geleceğim!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;

		case "relation":
			i = sti(npchar.quest.relation);
			dialog.text = "Sizinle iş yapmak bir zevkti, efendim. Artık rahat bir nefes alabilirsiniz, sorununuz önümüzdeki iki hafta içinde çözülecek. Lütfen herhangi bir çatışmadan kaçının "+XI_ConvertString(Nations[i].Name+"Abl")+", ben ise tam da müzakerelerin ortasındayım.";
			link.l1 = "Pekala, uyarını dikkate alacağım. Teşekkür ederim ve hoşça kal!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -iLoxlyPseudoGlobal);
			ChangeNationRelationFromRelationAgent(i);
			attrLoc = "RelationAgent" + GetNationNameByType(i);
            Pchar.GenQuest.(attrLoc) = true;
			Pchar.GenQuest.(attrLoc).loyer = "true";
			NextDiag.TempNode = "Loxly";
		break;
		// <-- снятие НЗГ
		
		case "contraband":
			iLoxlyPseudoGlobal = CalculateRelationContraSum(true);
			dialog.Text = "Ve bunu neden yaptın? Kaçakçılar iyi adamlardır, kendilerine göre dürüsttürler. Hepimizin yaşaması ve karnını doyurması lazım... Neyse, o kadar da önemli değil ve sana sadece şu kadara mal olacak "+FindRussianMoneyString(iLoxlyPseudoGlobal)+".";
			if(sti(Pchar.money) >= iLoxlyPseudoGlobal)
			{
				Link.l1 = "Pekâlâ, Bay Loxley, kabul ediyorum. İşte paranız, işleri mümkün olduğunca çabuk halletmeye çalışın.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Şu anda istediğin miktar bende yok. Sonra tekrar geleceğim!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Harika, sorununuzu çözeceğim. Yakında tekrar sizinle iş yapmak isteyecekler.";
			Link.l1 = "Teşekkürler!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -iLoxlyPseudoGlobal);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
