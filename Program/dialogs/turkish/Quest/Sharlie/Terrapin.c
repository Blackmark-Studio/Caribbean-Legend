// НПС по квесту Суп из черепахи
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hayır, hiçbir şey.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// денщик Фокса - Бенджамин Джонс
		case "BenjaminJons":
			if (CheckAttribute(PChar, "questTemp.Terrapin.Benjamin") && pchar.questTemp.Terrapin == "baster")
			{
				dialog.text = "Albay şu anda arazide askeri tatbikatta. Ondan ne istiyorsunuz, kaptan?";
				link.l1 = "Bu sefer, Ben, sana ihtiyacım var. Kız kardeşin Molly hakkında kötü haberlerim var. O güzel kız belli ki bir belaya bulaşmış. Tortuga korsanları tarafından kaçırılmış. Yardıma ihtiyacı var ve seni uyarmamı istedi. Mesajı getirmeye çalışan adam öldürüldü, ama ölmeden önce bana kız kardeşinden bahsetmeyi başardı.";
				link.l1.go = "sister";
				break;
			}
			sld = characterFromId("Fox");
			if (sld.location == pchar.location)
			{
				dialog.text = "Eğer Albay Fox'u görmek için geldiyseniz, buyurun içeri — sizi kabul edecek..";
				link.l1 = "Pekâlâ o zaman.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Albay burada değil. Daha sonra uğrayın.";
				link.l1 = "Pekâlâ...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "BenjaminJons";
		break;
		
		case "sister":
			dialog.text = "Ha! Kız kardeşime 'güzel' diyen ilk adamsın. Tanrı ona bir grenadyerin vücudunu ve ses yerine de Eriha borusunu verdi. Bizim Molly kendini savunmayı bilir. Ama Yüce Rabbimizin yaratıcılığı çenesinin altıyla bitmedi tabii. Hayır, hayır, yaptığı en güzel şey, merhum babamızın kıllı, çiçekbozuğu suratını göğüslerinin üstüne yapıştırmak oldu. Ve şunu söylemeliyim ki, efendim, babamın yüzü atları bayıltırdı.";
			link.l1 = "Pek de üzgün görünmüyorsun...";
			link.l1.go = "sister_1";
		break;
		
		case "sister_1":
			dialog.text = "Ve neden Tortuga'da ortaya çıksın ki? Molly, cesur albayımızın kızı Catherine Fox'un hizmetçisi. Catherine, babasının doğum gününü kutlamak için Avrupa'dan geliyordu. Ama gemisinin içinde olduğu filo gecikti\nEğer gerçek Molly Jones'u ve bu arada gerçekten çok güzel olan hanımını görmek istiyorsan, bir ay sonra buraya gel. Bir gün bile önce değil.";
			link.l1 = "Anlaşılan kız kardeşin Molly Jones, Bayan Fox'a hizmet etmiş ve şu anda Atlantik'in öte yakasında yaşıyor?";
			link.l1.go = "sister_2";
		break;
		
		case "sister_2":
			dialog.text = "Exactly so! The last courier informed us that a navy squadron dispatched by Lord Protector Cromwell himself was supposed to leave London only a month ago. The brig 'Albatross', with Catherine aboard, was to accompany them. We shall learn if this is truly the case from the next mail packet boat. Although the ships haven't arrived yet, and the colonel had strictly forbidden the 'Albatross' to sail alone.\nDid you know that his beloved wife died during an attack by French corsairs? It was not easy for the colonel, and he still dreads the dangers of the high seas... So I can't help you with Molly Jones, captain! There are a lot of colonist girls named Molly! Besides, having the surname Jones in Britain is as good as having no surname at all!\nEvery sea dog at Antigua knows me and my commander. I'm not surprised that some poor girl who got into trouble wants my help. I'd like to, but I haven't the coin for a ransom. The colonel owes me three months' wages; my salary, along with everyone else's, arrives with the 'Albatross'.";
			link.l1 = "Görünüşe göre o zaman yanılmışım. Yine de açıklaman için teşekkürler.";
			link.l1.go = "sister_3";
		break;
		
		case "sister_3":
			dialog.text = "Hiç de değil, kaptan.";
			link.l1 = "...";
			link.l1.go = "sister_4";
		break;
		
		case "sister_4":
			DialogExit();
			AddQuestRecord("Terrapin", "3");
			pchar.questTemp.Terrapin.Catherina = "take"; // возможен вариант с Кати
			DeleteAttribute(pchar, "questTemp.Terrapin.Benjamin");
		break;
		
		// Робер Мартэн
		case "Rober":
			PlaySound("Voice\English\sharlie\Rober Marten-01.wav");
			dialog.text = "Ne istiyorsun?! Konuşmak istemiyorum.";
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "rober")
			{
				link.l1 = "Sana bir işim var, kaptan. Keyfin pek yerinde değil gibi görünüyor, belki teklifim moralini biraz yükseltir.";
				link.l1.go = "rober_1";
			}
			else
			{
				link.l1 = "Sessiz ol, biraz rom iç. Benim hatam, affedersin.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rober";
		break;
		
		case "rober_1":
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Terrapin_LateBaster.over = "yes"; //снять таймер
			dialog.text = "Bu kulağa oldukça hoş geliyor! Ve yüzün sanki bir yerden tanıdık geliyor... Sadece seni nerede gördüğümü hatırlayamıyorum. Devam et, anlat bakalım!";
			link.l1 = "Thibaut ile işlerini biliyorum... Sakin ol dostum! Benden korkmana gerek yok. Sana bir teklifim var.";
			link.l1.go = "rober_2";
		break;
		
		case "rober_2":
			dialog.text = "Lanet olsun! Kahrolası ayyaş domuz!... Başaramadım...";
			link.l1 = "Doğru söyledin. Denizcin çok konuşkandı, ama onun dedikoduları benden öteye gitmedi. Ve artık daha da yayılmayacak, çünkü bu işi sen hallettin, değil mi?";
			link.l1.go = "rober_3";
		break;
		
		case "rober_3":
			dialog.text = "Caramba! Şimdi seni tanıdım! Sen Albay Doiley'i rezil eden ve bütün adasını ele geçiren adamsın! Hollanda Batı Hindistan Şirketi'yle büyük işlere bulaştın, Batı Hintler'den bir baronla yakınsın... Adın... "+GetFullName(pchar)+", değil mi?";
			link.l1 = "Elinde doğru bilgiler var. Evet, benim. Ama biraz sakin olabilir misin, Robert?";
			link.l1.go = "rober_4";
		break;
		
		case "rober_4":
			PlaySound("Voice\English\sharlie\Rober Marten-02.wav");
			dialog.text = "Ah! Yani, nasıl sakin olabilirim ki, takımadaların en ünlü denizcilerinden biri benimle ilgileniyor, üstelik işlerimi de öğrenmiş! O brige saldırmak aklıma nereden geldi, bilmiyorum! Benden ne istiyorsun?";
			link.l1 = "Çeneni kapa ve beni dinle. Görüyorum ki ikimiz de Levasseur’un kellesini istiyoruz. O kendini beğenmiş palavracı haddini fazlasıyla aştı ve tehlikeli insanları kızdırdı. Adadaki güç dengesini değiştirmeye ve de Poincy’yi yerine oturtmaya niyetliyim, ama memleketimden daha fazla adamın kanını dökmek istemiyorum, hele ki pis bir hırsız yüzünden hiç istemem. Bana yardım edebilirsin. Ben de sana ve Thibaut’ya ayrıcalıklarınızı korumanızda yardımcı olabilirim.";
			link.l1.go = "rober_5";
		break;
		
		case "rober_5":
			dialog.text = "Bekle, bekle! Kulaklarıma inanamıyorum! Şans bugün bana gülüyor. Haklısın, aynı amaçları paylaşıyoruz. Seninle işler çok daha ilginç hale gelebilir... Thibaut iyi bir düellocu, ama amcasının boğazını kesecek cesareti yok... Ama senin gibi kurnaz bir köpekbalığı bunu yapabilir. Ünün zaten dilden dile dolaşıyor\nSenin garantilerine ihtiyacım yok, ama karşılığında kızı bana vereceksin. Onu Karayipler'deki işlerim bitene kadar rehin olarak tutmam gerek. Yakında İngiliz firkateynleri peşime düşecek. Şeytan aklımı başımdan aldı da o brigantini neden saldırdım! Filodan ayrılmış, kolay bir av gibi görünüyordu...";
			link.l1 = "Onda ne vardı? Levasseur’dan sakladığın o kızda ne özeldi?";
			link.l1.go = "rober_6";
		break;
		
		case "rober_6":
			dialog.text = "Evet. Thibaut’yu o kızdan ayrılmaya ikna etmelisin. Kim olduğunu öğrenene kadar ona göz kulak olmasını istemiştim, ama bu ‘Miss Jones’ ya da her kimse, Thibaut’nun aklını başından aldı ve şimdi Henry onu benden bile saklıyor! O büyüleyici kadını bana getir, ben de Levasseur’la şehir dışında buluşmanı ayarlayacağım. O zaman ona pusu kurma fırsatın olacak. Fisheye Plajı’nda seni bekliyor olacağım.";
			link.l1 = "Anlaştık. Şimdi bana Thibaut'u nasıl yakalayacağımı söyle.";
			link.l1.go = "rober_7";
		break;
		
		case "rober_7":
			dialog.text = "Meyhanedeki insanlar sana onun evinin yolunu gösterebilir. Henri oldukça dikkat çekici biridir. Onu ifşa etmekle tehdit et ve kızı bana getirmesini sağla. Aynı gün Levasseur'a yeğeninin şehir zindanında nadir bir güzelliği sakladığını haber vereceğim\nBenim ulak seni meyhanede bulacak. Henri'yi bulamayınca vali küçük bir birlikle zindana gidecek ve sen de onunla güzelce konuşma fırsatı yakalayacaksın.";
			link.l1 = "Kızı nereye götürmemi istersiniz?";
			link.l1.go = "rober_8";
		break;
		
		case "rober_8":
			dialog.text = "Ona söyle, kızı kendisi sahile getirsin. Ben de hazır oradayken onunla iki çift laf edeceğim...";
			link.l1 = "Pekâlâ. Anlaştık. Tortuga'da görüşürüz!";
			link.l1.go = "rober_9";
		break;
		
		case "rober_9":
			dialog.text = "Her şey planladığımız gibi giderse, bir daha asla karşılaşmayacağız. En azından umarım öyle olur. Elveda!";
			link.l1 = "...";
			link.l1.go = "rober_10";
		break;
		
		case "rober_10":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Baster_tavern", "goto", "goto2");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina")) AddQuestRecord("Terrapin", "6");
			else AddQuestRecord("Terrapin", "5");
			pchar.questTemp.Terrapin = "tortuga";
			// создаем Тибо
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Tibo", "Tibo", "man", "man", 35, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_18", "pistol4", "bullet", 250);
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.name = "Henry";
			sld.lastname = "Thibaut";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "tibo";
			sld.greeting = "Tibo";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			TakeNItems(sld, "potion2", 8);
			TakeNItems(sld, "potion3", 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 40, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 20, false); // таймер
			SetFunctionLocationCondition("Tonzag_AtTortuga", "Tortuga_town", false);
		break;
		
		case "rober_abordage":
			dialog.text = "Ah! Bunu hiç beklemiyordum... Ruhum için geldin, değil mi? Her şeyi anlaştığımız gibi yaptım! Ne oluyor böyle?!";
			link.l1 = "Senin hakkında bir hüküm var, Robert. Bu hükmü yerine getirmek bana verildi. Şimdi görevimi yerine getiriyorum.";
			link.l1.go = "rober_abordage_1";
		break;
		
		case "rober_abordage_1":
			dialog.text = "Sen şeytan! Bu imkânsız! Her şeyi bu kadar çabuk nasıl öğrenmiş olabilir?! Hem nasıl öğrendi ki?!";
			link.l1 = "Tilki'yi mi kastediyorsun? Hayır. Beni o göndermedi. Albay hâlâ kızını senin kurtardığından bile habersiz. Seni öldürmek isteyen eski dostun Henry Thibaut. Beni o tuttu.";
			link.l1.go = "rober_abordage_2";
		break;
		
		case "rober_abordage_2":
			dialog.text = "Şu lanet olası oğlancı! 'Voltigeur'dayken onu yengeçlere yem etmeliydim... O alçak sana ne kadar söz verdi?";
			link.l1 = "Bir adamın başına konan ödülü öğrenmesi her gün olmaz, değil mi Robert? Thibaut senin için çeyrek milyon biçmişti ama ona daha değerli olduğunu söyledim. Senin değerin üç yüz bin gümüş peso, dostum. Sevindin mi şimdi?";
			link.l1.go = "rober_abordage_3";
		break;
		
		case "rober_abordage_3":
			dialog.text = "Bir saniye... Anlaşalım! Sana daha fazla ödeyeyim!";
			link.l1 = "Hangi parayla, Robert? Yalan söylediğinden adım gibi eminim. Henry'nin bana vaat ettiği kadar paran yok. Hem bu, asıl mesele de değil. Bir gerçek olmasaydı, seni avlaması ve Thibaut'yla çevirdiğin pis işleri bitirmesi için onun teklifini çoktan reddederdim.";
			link.l1.go = "rober_abordage_4";
		break;
		
		case "rober_abordage_4":
			dialog.text = "Hangi gerçek bu?";
			link.l1 = "Catherine Fox'u öldürdün. O zavallı kızın tek suçu Albay Fox'un kızı olarak doğmaktı. Savunmasız kadınları öldüren senin gibi alçak korkaklardan nefret ediyorum! Seninle hiçbir anlaşma yapmayacağım. Bunu düşünmeye bile niyetim yok. Boşuna konuşma.";
			link.l1.go = "rober_abordage_5";
		break;
		
		case "rober_abordage_5":
			PlaySound("Voice\English\sharlie\Rober Marten-03.wav");
			dialog.text = "Lanet olsun! Başka ne yapabilirdim ki?! Onu yaşatıp sonsuza dek teknede saklayamazdım! Ve sen kimsin... seni serseri, seni alçak, seni katil, bana ahlak dersi verecek! Kendine bak! Senin 'yöntemlerine'! Benden hiç de iyi değilsin!";
			link.l1 = "Yeter. Martene, kılıcını çek! Artık bu işi bitirelim.";
			link.l1.go = "rober_abordage_6";
		break;
		
		case "rober_abordage_6":
			dialog.text = "Seni cehennemde göreceğim!";
			link.l1 = "...";
			link.l1.go = "rober_abordage_7";
		break;
		
		case "rober_abordage_7":
			DialogExit();
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Тибо, вариант без Кати
		case "tibo":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "Evimde ne işiniz var, beyefendi?";
			link.l1 = TimeGreeting()+", Bay Thibaut. Sizi tanıyan birinin, Kaptan Robert Martene'in adına buradayım.";
			link.l1.go = "tibo_1";
		break;
		
		case "tibo_1":
			dialog.text = "Hm. Ee? Sonra?";
			link.l1 = "Kaptan Martene şu anda Fisheye Plajı'nda sizinle görüşmek istiyor. Ama yalnız değil. Sizinle birlikte Molly Jones'u da görmekten memnuniyet duyar. Ne demek istediğimi anladınız mı?";
			link.l1.go = "tibo_2";
		break;
		
		case "tibo_2":
			PlaySound("Voice\English\sharlie\Henry Thibault-01.wav");
			dialog.text = "Ne yazık ki, efendim, hayır. Molly Jones adını hiç duymadım, ayrıca Robert'in bana hiç tanımadığım bir... tam yetkili göndermesi için de hiçbir sebebi olmadı. Bilginize, monsieur, bu adada valinin ardından ikinci adam benim, yani...";
			link.l1 = "Hayat öngörülemez bir canavar, Henry... Şu anda adadaki en önemli ikinci adamsın, ama birkaç saat sonra zindanda zincire vurulabilirsin... Hem de sana bir kuruşunu bile vermeyecek biri için. Amcanın emrine karşı geldin, değil mi, Mösyö Thibaut? Senin için ne daha önemli: başıboş bir kız mı, yoksa kendi hayatın mı?";
			link.l1.go = "tibo_3";
		break;
		
		case "tibo_3":
			dialog.text = "Sen... Yalan söylüyorsun! Saçmalıyorsun!";
			link.l1 = "Sen de herkes gibi amcanın ne kadar öfkeli olabileceğini bilirsin. Levasseur, güneş batmadan önce kızı sakladığını öğrenecek. Robert'ın bunu nasıl öğrendiğini sorma, sadece söylediklerime kulak ver: ödü kopmuş durumda ve hemen demir almak istiyor. Şehre girmeye bile cesaret edemedi ve bu mesajı sana iletmem için bana yüklü bir para ödedi.";
			link.l1.go = "tibo_4";
		break;
		
		case "tibo_4":
			dialog.text = "Lanet olsun... Bu olamaz!";
			link.l1 = "Karar sizin, efendim. Martene sizi iki saatten fazla beklemeyecek. Kendi canını fazlasıyla düşünür. Hâlâ Tortuga kıyısında oyalanmasının tek sebebi, dostluğunun bir göstergesi olması; yoksa şimdiye çoktan Hollandalılarla bir yerde saklanıyor olurdu.";
			link.l1.go = "tibo_5";
		break;
		
		case "tibo_5":
			dialog.text = "Vay canına! Amcam bunu nasıl öğrendi?";
			link.l1 = "Diller, Henry. Geveze diller. Senin ve Robert’in, arkadaşının ele geçirdiği İngiliz briginden inen güzeli kaçırıp Levasseur’dan sakladığınızı ben bile duydum... tsk tsk. Gerçekten bu hikayeyi bilen tek kişinin ben olduğumdan mı şüphe ediyorsun?";
			link.l1.go = "tibo_6";
		break;
		
		case "tibo_6":
			dialog.text = "Doğruyu söylüyor gibisiniz, efendim. Martene'e söyleyin...";
			link.l1 = "Sanmıyorum ki durumu anladın, Henry. Martene seni beklemeyecek. Tek umudun, hem senin hem de Robert'ın boynuna ilmek geçiren o kızı buradan çıkarmak. Sakladığın yere koş, o güzel ellerinden tut ve onu Voltigeur'a getir. Hemen bul ve daha da hızlı getir. Amcan bu konuda benden tek kelime duymayacak.";
			link.l1.go = "tibo_7";
		break;
		
		case "tibo_7":
			dialog.text = "Pekâlâ. O zaman öyle yaparız. Nezaketiniz için teşekkür ederim, efendim!";
			link.l1 = "Bana teşekkür etmene gerek yok, monsieur. Benim işim zaten ödeniyor... Sadece senin paçayı kurtarmanı istiyorum, yoksa haşlanacaksın.";
			link.l1.go = "tibo_8";
		break;
		
		case "tibo_8":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Terrapin_wait.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_wait.win_condition.l1.date.hour  = sti(GetTime()+3);
			pchar.quest.Terrapin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l2 = "location";
			pchar.quest.Terrapin_wait.win_condition.l2.location = "Tortuga_tavern";
			pchar.quest.Terrapin_wait.function = "Terrapin_SetEnvoy";
			pchar.questTemp.Terrapin = "cave";
			AddQuestRecord("Terrapin", "8");
			SetFunctionTimerCondition("Terrapin_ReturnTibo", 0, 0, 10, false);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 4, false);
			} 
			else SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 2, false);
		break;
		
		// вариант с Кати
		case "tibo_9":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "Burada ne yapıyorsunuz, efendim? Sizi buraya ben çağırmadım.";
			link.l1 = TimeGreeting()+", Bay Thibaut. Sizi tanıyan bir adam adına geldim. Adı Kaptan Robert Martene.";
			link.l1.go = "tibo_10";
		break;
		
		case "tibo_10":
			dialog.text = "Hm. Ee? Sonra?";
			link.l1 = "Kaptan Martene şu anda Fisheye Plajı'nda sizinle görüşmek istiyor. Ama yalnız değil. Yanınızda Molly Jones'u da getirmenizi isterdi. Ne demek istediğimi anladınız mı?";
			link.l1.go = "tibo_11";
		break;
		
		case "tibo_11":
			dialog.text = "Ne yazık ki, efendim, bilmiyorum.";
			link.l1 = "That's what I was expecting you to say. Of course, I doubt you could have previously been introduced to Colonel Fox's daughter; you know Colonel Fox, of course, commander of the notorious Sea Foxes... the terror of England's enemies in the Caribbean? You and Robert have stirred up such a hornet's nest it's a miracle you haven't been stung yet! The girl Molly Jones that you captured from the English brig, that you've been concealing from Levasseur, is the daughter of Colonel Fox, Catherine Fox!";
			link.l1.go = "tibo_12";
		break;
		
		case "tibo_12":
			dialog.text = "N-ne?";
			link.l1 = "Oldukça solgun görünüyorsunuz, efendim. Şimdi beni dikkatle dinle, Henry, ve iyi kulak ver: sen ve arkadaşın Robert başınızı belaya soktunuz. Her an Cromwell’in donanma filosu Karayiplere varabilir. Sizi arayacaklar. Sadece amiral gemisi bile o meşhur La Roche’unuzu ve tayfanızı birkaç saat içinde paramparça edebilir. Ne düşünüyorsun? O İngiliz brigine saldırmak ve Fox’un kızını esir almak buna değdi mi sence?";
			link.l1.go = "tibo_13";
		break;
		
		case "tibo_13":
			dialog.text = "";
			link.l1 = "Ama hepsi bu kadar değil. Senin oyunların artık sadece bana değil, başkalarına da malum oldu. Sevgili amcan, vali, onun katı emirlerine karşı geldiğini ve ondan gizlediğin bir kızı öğrenecek—o yaşlı zampara kesinlikle o kızı kendine isterdi. Ne dersin Henry? Amcan sana ne yapar? Onun öfkesinin ne kadar ateşli olduğunu herkesten iyi sen bilirsin...";
			link.l1.go = "tibo_14";
		break;
		
		case "tibo_14":
			dialog.text = "Hepsi yalan!";
			link.l1 = "Öyle mi? Sevgili Henry, arkadaşın Martene'ye sorabilirsin. Beni gönderen oydu. Levasseur, güneş batmadan kızı sakladığını öğrenecek. Robert'ın bunu nasıl öğrendiğini sorma bana, sadece sözümü dinle: ödü kopmuş durumda ve hemen demir alıp ayrılmaya hazır. Kasabaya girmeye bile cesaret edemedi. Bu yüzden bu mesajı sana iletmemi istedi.";
			link.l1.go = "tibo_15";
		break;
		
		case "tibo_15":
			dialog.text = "";
			link.l1 = "Martene seni iki saatten fazla beklemeyecek. Kendi canını her şeyden çok düşünür. Hâlâ Tortuga kıyısında oyalanmasının tek sebebi, seninle olan dostluğuna bir işaret olarak, yoksa şimdiye çoktan Hollandalıların yanında bir yere saklanmış olurdu. Ama şu zavallı Robert, Molly Jones'un aslında kim olduğunu bile bilmiyor. Biliyor musun, siz ikiniz kadınların modası ve görünüşü konusunda gerçekten şaşırtıcı bir cehalet sergiliyorsunuz! Bir soylu kadını hizmetçisinden ayırt edemiyorsunuz!";
			link.l1.go = "tibo_16";
		break;
		
		case "tibo_16":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Sonunda, genç delikanlıdan da akıllıca bir söz çıktı! Peki Thibaut, şimdi onu sakladığın yere git, nazikçe bembeyaz ellerinden tut ve hızlıca onunla birlikte Martene'in Voltigeur'u beklediği Fisheye Plajı'na in. Ona planlarının değiştiğini söyle...";
			link.l1.go = "tibo_17";
		break;
		
		case "tibo_17":
			dialog.text = "";
			link.l1 = "Martene sözünü tutmalı, kızı kendi gemisine almaya bile kalkışmamalı. O, sahilde kalacak ve beni bekleyecek. Robert'a söyle, eğer yükümlülüklerini yerine getirmezse, ya da Catherine'i kaçırırsa, ya da onun güzel başındaki tek bir saç teline zarar gelirse, ömrümün sonuna kadar onu arayacağım. Ve bulduğumda, onu Albay Fox'a teslim edeceğim... hem de sağ olarak. Ama size gelince... sizi parça parça geri getireceğim. Evet, bu arada, bu seni de kapsıyor Thibaut.";
			link.l1.go = "tibo_18";
		break;
		
		case "tibo_18":
			dialog.text = "";
			link.l1 = "Kim olduğumu ve neler yapabileceğimi Robert'a sorabilirsin. O her şeyi gayet iyi bilir. Eğer ikiniz de dediklerimi yaparsanız, hepimiz kazanırız. Robert korsan işine devam edebilecek, sen de tüm ayrıcalıklarını koruyup o sevgili yaşlı amcanın mirasını o son nefesini verdiğinde alacaksın. Bana gelince... Ben de kaybeden olmayacağım. Her şey açık mı?";
			link.l1.go = "tibo_19";
		break;
		
		case "tibo_19":
			PlaySound("Voice\English\sharlie\Henry Thibault-03.wav");
			dialog.text = "Sana hizmet etmektense sonsuz cehennem ateşinde yanmayı tercih ederim... "+GetFullName(pchar)+"! Seni baştan tanıyamadım nasıl? Katil herif! Beni ya da Robert'ı sağ bırakmaya hiç niyetin yok! 'Yöntemlerin' herkesçe biliniyor! Molly'yi de... Catherine'i de sana, senin gibi pisliğe asla teslim etmem! Tortuga'dan sağ çıkamayacaksın, alçak!";
			link.l1 = "...";
			link.l1.go = "tibo_20";
		break;
		
		case "tibo_20":
			dialog.text = "";
			link.l1 = "Dur, korkak!";
			link.l1.go = "tibo_21"; // patch
		break;
		
		case "tibo_21":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload_window", "none", "", "", "Terrapin_LevasserRoomEnter", 5); // patch
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_window");
			LAi_RemoveLoginTime(npchar);
		break;
		
		case "tibo_22":
			pchar.quest.Terrapin_TiboCallOver.over = "yes"; //снять прерывание
			pchar.quest.Terrapin_tibo_call.over = "yes"; //снять прерывание
			PlaySound("Voice\English\sharlie\Henry Thibault-04.wav");
			dialog.text = "Nihayet! Kaptan "+GetFullName(pchar)+", geldiğine çok memnun oldum. Gir içeri, otur. Bir şeyler içmek ister misin? Sana oldukça kârlı bir iş teklifim var, dostum...";
			link.l1 = "Bugün ne kadar da naziksiniz, Mösyö Thibaut... Hadi oyalanmayalım. Doğrudan sadede gelelim.";
			link.l1.go = "tibo_23";
		break;
		
		case "tibo_23":
			dialog.text = "Teklif, senin de tanıdığın eski dostum ve yoldaşım, bir zamanlar 'Voltigeur' kalyonunun kaptanı olan Robert Martene ile ilgili...";
			link.l1 = "Yani, sen ve Robert artık arkadaş değil misiniz? İlginç bir gelişme.";
			link.l1.go = "tibo_24";
		break;
		
		case "tibo_24":
			dialog.text = "Kaptan, lütfen, yardımınızı istememin nedenlerini dinleyin, her şey açıklığa kavuşacak. Bildiğiniz gibi, Martene bir İngiliz brigine saldırdı ve esir olarak bir İngiliz kadın, Molly Jones adında bir hizmetçiyi aldı; bütün bu belanın çıkmasının sebebi de tam olarak buydu.";
			link.l1 = "Elbette, biliyorum. Bildiğim kadarıyla, tavsiyelerimi dinleyip kızı Martene'in gemisine götürmüşsün?";
			link.l1.go = "tibo_25";
		break;
		
		case "tibo_25":
			dialog.text = "Evet, yaptım. Ama her gün pişmanım. Bilmeni isterim ki Molly çok çekici ve güzel bir kız, onun gibisini daha önce hiç tanımamıştım. İtiraf etmeliyim, ona âşık oldum. O da benden hoşlandı, bunu kendi söyledi! Onu amcama bırakamazdım\nOnu 'Voltigeur'a götürürken umuyordum ki amcam, kimsenin ondan kızları saklamadığını öğrenince sakinleşir, o yaşlı zampara. Sonra Robert onu Tortuga'ya geri götürecekti, ben de Molly'yi güvenle yanıma alabilecektim. Zaten Martene ile anlaştığım şey buydu. Ama işler farklı gelişti\nAmcamın öldüğünü öğrendiğimde, Molly'yi saklamanın bir anlamı kalmamıştı, bu yüzden 'Voltigeur' Molly ile birlikte gelene kadar sabırla bekledim.";
			link.l1 = "Geldi mi?";
			link.l1.go = "tibo_26";
		break;
		
		case "tibo_26":
			dialog.text = "Evet. Ne yazık ki, Molly gemide değildi. Robert sanki bizzat Lucifer’le karşılaşmış gibi sarsılmıştı. Kısa süren seferi sırasında bir şekilde korkunç bir gerçeği öğrenmiş: O kız, Molly, aslında Molly Jones değilmiş, Catherine Fox’muş! Yani Albay Fox’un kızı, Deniz Tilkileri’nin komutanı, İngilizlerin seçkin deniz piyadeleri alayı! Bunun ne anlama geldiğini biliyorsun!";
			link.l1 = "Vay canına, bak sen şu işe! Demek ki Robert’in gerçekten korkacak bir şeyi var. Ama nasıl böyle oldu ki?";
			link.l1.go = "tibo_27";
		break;
		
		case "tibo_27":
			dialog.text = "Catherine esir alındığında, kimliğini gizlemek için bilerek Molly Jones adında, gemiye saldırı sırasında ölen bir hizmetçi kız gibi davrandı. Martene'nin gerçekte kim olduğunu öğrenmesinden korkuyordu. Ve onu kandırmayı başardı. Ama son yolculuk sırasında, Robert bir şekilde onun gerçeğini öğrendi. Bazı mektuplarını ya da belgelerini bulduğunu söyledi...";
			link.l1 = "Ve kız şimdi nerede, eğer 'Voltigeur'a binmediyse?";
			link.l1.go = "tibo_28";
		break;
		
		case "tibo_28":
			dialog.text = "Öldü. İngiliz brigine saldırdığı için Fox'tan gelecek cezadan korkan Martene, geriye kalan tek kanıtı suya atmaya karar verdi. O, Martene'nin 'Albatross'a saldırısının son tanığıydı.";
			link.l1 = "O zaman tüm tayfasını öldürse daha iyiymiş... Tıpkı Fernand Luc gibi. Yoksa bir gün sarhoş olup meyhanede dillerini fazla çözerler...";
			link.l1.go = "tibo_29";
		break;
		
		case "tibo_29":
			dialog.text = "Tüm mürettebatının ona kan bağıyla bağlı olduğuna inanıyor. Belki bunda biraz haklıdır. Ama Albay Fox'u tanıyorum! Kızını kaçıranın kim olduğunu bulana kadar ömrünün sonuna dek aramaktan vazgeçmez!";
			link.l1 = "Bundan şüphem yok. Özellikle de bir Fransız korsan karısını öldürdükten sonra. Şimdi de kızı... Bu arada, emin misiniz, monsieur, Catherine gerçekten öldü mü? Belki de Robert onu sizden bir yerde saklamıştır.";
			link.l1.go = "tibo_30";
		break;
		
		case "tibo_30":
			dialog.text = "Eminim. 'Voltigeur'den bir denizciyle konuştum. Ona inandım. Kendi gözleriyle görmüş; kızın boğazını kestiler, sonra ayaklarına bir top gülle bağlayıp denize attılar.";
			link.l1 = "Tanrı aşkına! O zavallı kadın... benden ne istiyorsun, Henry?";
			link.l1.go = "tibo_31";
		break;
		
		case "tibo_31":
			dialog.text = "O günden beri geceleri uyuyamıyorum. Sürekli gözümün önünde Molly... ya da Catherine. Onu ölüme ben sürükledim, "+GetFullName(pchar)+"! Bunun için kendimi affedemem. Üstelik Fox hakkında da hiçbir yanılsamam yok. O adam asla rahat durmaz, sanmam ki uyusun bile. Er ya da geç Martene'nin izini bulacak, birilerini konuşturacak ve kızını kimin öldürdüğünü öğrendiğinde ortalık fena karışacak. Bu işin ucundan kıyısından bulaşan herkesin başı büyük belaya girecek.";
			link.l1 = "Ben de buna dahilim.";
			link.l1.go = "tibo_32";
		break;
		
		case "tibo_32":
			dialog.text = "Evet, ben de öyle. Bu yüzden Martene'i Fox'tan önce bulmanı istiyorum. O alçağı bul ve öldür. Önce acı çektirebilirsen, çekindir. Zavallı Catherine için. İşin bittiğinde, elindeki o kalın yüzüğü parmağıyla birlikte kesip bana kanıt olarak getir.\nO yamuk parmağı ve yüzüğü iyi bilirim. Bunu yaparsan, sana çeyrek milyon gümüş ödeyeceğim.";
			link.l1 = "Görünüşe bakılırsa sevgili yaşlı amcandan yüklü bir miras kalmış, Allah rahmet eylesin, öyle mi? Söylesene Henry, bu meselede neden benden yardım istemeye karar verdin?";
			link.l1.go = "tibo_33";
		break;
		
		case "tibo_33":
			dialog.text = "Çünkü ben de senin hakkında birkaç şey öğrendim, "+GetFullName(pchar)+". Kolaydı, çünkü sen ünlü bir adamsın. Ama kimin için çalıştığın hâlâ bilinmiyor: de Poincy mi, Hollandalılar mı, İngilizler mi, yoksa Baron Jan Svenson mu... Ama bir şey açık: hassas, gizli işleri alıp başarıyla tamamlıyorsun. Sonra da bunun karşılığında yüklüce para alıyorsun. Ve en güzeli, İspanyollarla hiçbir bağlantın yok.\nSonuçta, amcamın servetini miras aldığım olaylarda da sen vardın. Bunu inkâr etme... Çeyrek milyon iyi paradır. Martene’i nerede bulacağını sana söyleyeceğim. Tek yapman gereken onun gemisini yakalayıp ele geçirmek.";
			link.l1 = "Bir yüz bin daha ver, Martene işini de hallederim.";
			link.l1.go = "tibo_34";
			link.l2 = "Ne yazık ki, Bay Thibaut, Martene ve Albay Fox'la ilgili sorununuzu benim katılımım olmadan çözmek zorunda kalacaksınız. Ben ise size söz veriyorum ki, kızının ve ölümünden sorumlu olanların akıbetiyle ilgili albayı bilgilendirmeyeceğim. Size en iyisini dilerim, efendim.";
			link.l2.go = "tibo_exit";
		break;
		
		case "tibo_exit":
			DialogExit();
			AddQuestRecord("Sharlie", "26");
			NextDiag.CurrentNode = "tibo_over";
		break;
		
		case "tibo_34":
			dialog.text = "Efendim, Allah aşkına... Hazine sandıklarında milyonlarım yok, inanın bana! Hizmetlerinizin bedeli olduğunu anlıyorum, bu yüzden size hemen iki yüz elli bin teklif ettim... Peki... Tamam, üstüne elli bin altın daha ekleyeyim. Daha fazlasını veremem!";
			link.l1 = "Pekâlâ. Anlaştık. Martene'i en son nerede gördün?";
			link.l1.go = "tibo_35";
		break;
		
		case "tibo_35":
			dialog.text = "Caracas'taki İspanyol Ana Karası'na doğru yelken açtı ve Don Diego Francisco de Kerres, valisiyle görüşmeyi başardı. Görünüşe göre ona bir şekilde rüşvet verdi, çünkü Don Diego Robert'a İspanyol tacının korumasını sağladı. 'Voltigeur'u sattı ve şimdi ağır bir kalyon olan 'Infanta'nın kaptanı. Görünen o ki, valiye rüşvet vermeye ve böyle büyük bir savaş gemisini satın alıp donatmaya yetecek kadar iyi birikimi varmış.\nŞimdi ise yeni gemisiyle Caracas'tan Santo Domingo'ya, bir İspanyol filosunun parçası olarak yelken açacak. Ajanımın bulabildiği tek şey bu. Martene'i yakalamanın tek yolu, o İspanyol filosuna yetişmek.\nEğer Santo Domingo'ya varırlarsa, iş biter. Robert'ın bir sonraki durağına dair hiçbir ipucu yok. Bir tavşan gibi deliğine saklanacak ve onu asla bulamayacağız.";
			link.l1 = "Anladım. Onları yolundan çevireceğim.";
			link.l1.go = "tibo_36";
		break;
		
		case "tibo_36":
			dialog.text = "Ve yüzüğün olduğu parmağı da unutma! Bu, anlaşmamızın vazgeçilmez şartı! Robert’ın kesinlikle öldüğünden emin olmak istiyorum!";
			link.l1 = "Pekala. Hiç vakit kaybetmeyelim, hemen yelken açıyorum!";
			link.l1.go = "tibo_37";
		break;
		
		case "tibo_37":
			DialogExit();
			AddQuestRecord("Sharlie", "27");
			Terrapin_CreateRoberConvoy();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			NextDiag.CurrentNode = "tibo_time";
		break;
		
		case "tibo_time":
			dialog.text = "Martene hâlâ Karayipler'i varlığıyla kirletiyor mu, kaptan?";
			link.l1 = "Çok vakti kalmadı!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_time";
		break;
		
		case "tibo_38":
			dialog.text = "Martene Karayipler'i varlığıyla kirletiyor mu, kaptan?";
			link.l1 = "Artık değil. Albay Fox'tan artık korkmana gerek yok, ve Catherine'in intikamı alındı. İşte kanıtın.";
			link.l1.go = "tibo_39";
		break;
		
		case "tibo_39":
			RemoveItems(pchar, "finger", 1);
			dialog.text = "Evet... Bu kesinlikle Martene'in parmağı, hiç şüphe yok. Etkilemeyi asla bırakmıyorsun, Kaptan "+GetFullName(pchar)+"! Gerçekten de kazandığın ünü fazlasıyla hak ediyorsun.";
			link.l1 = "Hadi ödemeye geçelim, ne dersin Thibaut?";
			link.l1.go = "tibo_40";
		break;
		
		case "tibo_40":
			AddMoneyToCharacter(pchar, 250000);
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You've received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Her şey hazır. Al, ödülünü.";
			link.l1 = "Teşekkür ederim. Bunu önceden hazırlayabilmiş olmana sevindim. Neyse Henry, umarım bundan sonra böyle işlere bulaşmazsın ve gelecekte daha iyi arkadaşlar seçersin. Her şey gönlünce olsun!";
			link.l1.go = "tibo_41";
		break;
		
		case "tibo_41":
			dialog.text = "Yardımınız için teşekkür ederim, Kaptan! Sizi tüm arkadaşlarıma tavsiye edeceğim. Bol şanslar!";
			link.l1 = "...";
			link.l1.go = "tibo_42";
		break;
		
		case "tibo_42":
			DialogExit();
			AddQuestRecord("Sharlie", "31");
			NextDiag.CurrentNode = "tibo_stop";
		break;
		
		case "tibo_stop":
			dialog.text = "Evet, Mösyö "+GetFullName(pchar)+"? Benimle bir işin mi var?";
			link.l1 = "Hayır, Mösyö Thibaut. Sadece bir anlığına uğramak istedim. Hoşça kalın!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_stop";
		break;
		
		case "tibo_late":
			dialog.text = "Ah, "+GetFullName(pchar)+"...Hadi ama, neyi bu kadar uzatıyorsun! Şimdi, kim bilir Robert Martene nerede?! Albay Fox her şeyi öğrenirse, başım büyük belada olacak sanırım...";
			link.l1 = "Anladım. Çok geç kaldım. Özür dilerim, Mösyö Thibaut, ama beni gerçekten çok acil işler alıkoydu. Zamanınızı harcamayacağım. Hoşça kalın.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		case "tibo_over":
			dialog.text = "Ne istiyorsun, "+GetFullName(pchar)+"? Sohbet edecek vaktim yok. Daha önemli işlerim var. Martene'i Fox'tan önce bulmalıyım...";
			link.l1 = "Evet, evet. Geliyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		// посланник от Мартэна
		case "envoy":
			dialog.text = "Sen Kaptan mısın "+GetFullName(pchar)+"?";
			link.l1 = "Doğru adama geldin, dostum. Seni dinliyorum.";
			link.l1.go = "envoy_1";
		break;
		
		case "envoy_1":
			dialog.text = "Alacaklınız bana işi hallettiğimi ve balığın bir saatten az bir sürede ağa düşeceğini size iletmemi istedi. O yüzden acele edin.";
			link.l1 = "Anladım. Teşekkür ederim!";
			link.l1.go = "envoy_2";
		break;
		
		case "envoy_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Terrapin", "9");
			pchar.quest.Terrapin_cave.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_cave.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.Terrapin_cave.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l2 = "location";
			pchar.quest.Terrapin_cave.win_condition.l2.location = "Tortuga_cave";
			pchar.quest.Terrapin_cave.function = "Terrapin_LevasserInCave";
		break;
		
		// Левассер в пещере
		case "levasser_cave":
			pchar.quest.Terrapin_LateDungeon.over = "yes"; //снять таймер
			dialog.text = "Ne halt ediyorsun burada? Kimsin sen? Hemen cevap ver!";
			link.l1 = "Sen de kimsin, bana bu kadar saçma soruları neden soruyorsun?";
			link.l1.go = "levasser_cave_1";
		break;
		
		case "levasser_cave_1":
			dialog.text = "Ne?! Sen ne biçim bir serserisin! Ben kimim biliyor musun? Ben bu adanın valisiyim, François Levasseur, Señor de Renet de Boidouflet de Lettre! Ve bu adadaki her şey benim yetkim altında! Sen de buradayken buna dahilsin, velet!";
			link.l1 = "Vay vay... Büyük kötü kurt bizzat kendisi, öyle mi? Biraz kaybolmuşsun, Levasseur, Señor de Renet ya da her neysen. Vaktin doldu. Genel Vali François Longvilliers de Poincy'nin emriyle görevinden alındın ve derhal idama mahkûm edildin! Hem hakimin hem celladın benim! Son sözlerin var mı?";
			link.l1.go = "levasser_cave_2";
		break;
		
		case "levasser_cave_2":
			dialog.text = "";
			link.l1 = "Sanırım vazgeçmeyeceksin, benden merhamet dilemenin de sana bir faydası olmayacak, o halde hadi bakalım, kılıcını çek!";
			link.l1.go = "levasser_cave_3";
		break;
		
		case "levasser_cave_3":
			dialog.text = "Lanet olsun! Bu de Poincy'nin ajanı! Kılıçlarınızı çekin! Onu öldürün!";
			link.l1 = "Hadi dans edelim.";
			link.l1.go = "levasser_cave_4";
		break;
		
		case "levasser_cave_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_cave")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=2; i<=4; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
			int iScl = 30 + 2*sti(pchar.rank);
			for (i=5; i<=9; i++)
			{		
				sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "citiz_5"+i, "man", "man", iRank, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2+50);
				ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserCaveDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Левассер в комнате таверны
		case "levasser_room":
			dialog.text = "Sen burada ne halt ediyorsun? Kimsin sen? Hemen cevap ver!";
			link.l1 = "Ne dersiniz! Bunu hiç beklemiyordum... Bizzat Bay Levasseur, sanırım?";
			link.l1.go = "levasser_room_1";
		break;
		
		case "levasser_room_1":
			dialog.text = "Evet, bu adanın valisi benim, François Levasseur, Seigneur de Renet de Boidouflet de Lettre! Ve bu adadaki her şey benim yetkim altında! Burada, benim toprağımda yürürken sen de buna dahilsin, seni serseri! Soruları cevapla! Çavuş, kapıyı kilitle. Bu adamın bir iş çevirdiği belli!";
			link.l1 = "Gerçekten çok zekisiniz, Mösyö Levasseur, Seigneur de Renet bilmem ne. Burada olmam sizi hiç de memnun etmeyecek. Genel Vali François Longvilliers de Poincy'nin emriyle, görevden alındınız ve derhal idama mahkûm edildiniz! Hem yargıcınızım, hem celladınız!";
			link.l1.go = "levasser_room_2";
		break;
		
		case "levasser_room_2":
			dialog.text = "";
			link.l1 = "Sanırım vazgeçmeyeceksin ve benden merhamet dilemenin de sana bir faydası olmayacak, o halde hadi bakalım, kılıcını çek! Bu sadece işim, kişisel bir mesele değil. Sadece Kraliyet'e hizmet ediyorum, ha! Çavuş, genel valinin emirlerini yerine getirirken karışmanı tavsiye etmem!";
			link.l1.go = "levasser_room_3";
		break;
		
		case "levasser_room_3":
			dialog.text = "Ona kulak verme, çavuş! O bir İspanyol ajanı! Onu öldür! Muhafızlar, yardım edin! Burada İspanyollar var!";
			link.l1 = "Aslında hiç İspanya'ya gitmedim, sadece Narbonne'a.";
			link.l1.go = "levasser_room_4";
		break;
		
		case "levasser_room_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserRoomDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// девушка на балконе
		case "roof_girl":
			dialog.text = "Ah! Yardım edin! Askerler!";
			link.l1 = "Sessiz ol, aptal! Bağırmazsan sana bir şey yapmam!";
			link.l1.go = "roof_girl_1";
		break;
		
		case "roof_girl_1":
			dialog.text = "Beni öldürme!";
			link.l1 = "Aptalca konuşma! Buradan on dakika önce bir adam geçti. İyi giyimli bir soyluydu. Nerede saklanıyor? Ve sakın bana onu görmediğini söylemeye kalkma!";
			link.l1.go = "roof_girl_2";
		break;
		
		case "roof_girl_2":
			dialog.text = "Monsieur Thibaut?";
			link.l1 = "Pekâlâ, demek onu tanıyorsun! Nereye kayboldu? Cevap verecek misin, yoksa kafanı biraz sarsmam mı gerekecek ki çalışmaya başlasın?";
			link.l1.go = "roof_girl_3";
		break;
		
		case "roof_girl_3":
			dialog.text = "Aman Tanrım, lütfen bana zarar vermeyin! Monsieur Thibaut o tarafa, denize doğru kaçtı. Vinçten atladı, doğrudan suya düştü. Muhtemelen öldü, orası çok yüksekti...";
			link.l1 = "Bence öyle değil. O, intihar edecek biri değil. İçeri girmelisin. Bu gece burada olmak tehlikeli.";
			link.l1.go = "roof_girl_4";
		break;
		
		case "roof_girl_4":
			dialog.text = "Ah! Ah! Ateş etme!";
			link.l1 = "Ne?!";
			link.l1.go = "roof_girl_5";
		break;
		
		case "roof_girl_5":
			DialogExit();
			LAi_SetActorType(pchar);
			PlaySound("People Fight\MushketShot.wav");
			DoQuestCheckDelay("Terrapin_GirlShot", 1.0);
		break;
		
		// Кати
		case "kathy":
			PlaySound("Voice\English\Armo02.wav");
			dialog.text = "Sen kimsin? Beni öldürmeye mi geldin, yoksa... daha kötüsünü mü yapacaksın?";
			link.l1 = "Hiç de öyle değil, hanımefendi. Sizi, Catherine Fox, St. John's'taki babanıza geri götüreceğim. Eğer o da size, emirlerine karşı geldiğiniz için, sonrasında bir ceza verirse, o zaman suçluluğum iki katına çıkacak. Yine de umuyorum ki, albay tüm endişelerine rağmen kızını sağ salim gördüğüne sevinecektir.";
			link.l1.go = "kathy_1";
		break;
		
		case "kathy_1":
			dialog.text = "Tanrıya şükür! Herhalde rüya görüyorum! Kim olduğumu bilmiyor musun? Sen bir Fransızsın ve Katoliksin, ama yine de beni kendi yurttaşlarımın elinden kurtarmak için buraya geldin? Sırf Albay Fox'un kızı için hayatını tehlikeye attın?";
			link.l1 = "Burada, Tortuga'da bulunmamın asıl nedeni bambaşkaydı. Ama güzel bir hanımefendiyi de bir grup hırsız ve haydutun eline bırakamazdım.";
			link.l1.go = "kathy_2";
		break;
		
		case "kathy_2":
			dialog.text = "Ne kadar asil bir beyefendisiniz! Adınız nedir, monsieur?";
			link.l1 = ""+GetFullName(pchar)+". Kaptan "+GetFullName(pchar)+".";
			link.l1.go = "kathy_3";
		break;
		
		case "kathy_3":
			dialog.text = "Bana söyle Kaptan, beni gerçekten St. John's'taki babama götürecek misin?";
			link.l1 = "Evet, gerçi Fransızlardan pek hoşlanmaz. Neyse, ona İngilizler arasında da alçaklar olduğunu hatırlatırım, hem de İngiliz subayları dahil! En az birine bizzat şahit oldum... Adı Richard Fleetwood'du.";
			link.l1.go = "kathy_4";
		break;
		
		case "kathy_4":
			dialog.text = "Antigua'ya varırsak, Fransızlar arasında gerçek şövalyeler olduğunu babama kanıtlamak için elimden geleni yapacağım.";
			link.l1 = "Bunu gerçekten takdir ederdim... Peki, umarım koruyucu meleklerim şehirdeki çatıların üzerinden geçtiğim yolu göz kulak olmuşlardır ve şimdiden dönüşümüzü bekliyorlardır.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_OwrInGrot");
		break;
		
		case "kathy_5":
			PlaySound("Voice\English\Armo01.wav");
			dialog.text = "Şimdiye kadar sözünü tutacağına inanamamıştım! Son zamanlarda başıma öyle korkunç ve iğrenç şeyler geldi ki... Sana minnettarım kaptan, insanlara ve şövalyeliğe olan inancımı yeniden kazandırdın. Fırsat bulduğunda mutlaka babamı ziyaret etmelisin!\nO senin gibi insanlara saygı duyar. Fransız olman hiç önemli değil. Babamın ülkenize bakışını değiştirmesi için elimden geleni yapacağım.";
			link.l1 = "Teşekkür ederim, Catherine. Belki de bu nazik teklifinden yararlanırım.";
			link.l1.go = "kathy_6";
		break;
		
		case "kathy_6":
			dialog.text = "Umarım öyle olur, kaptan. Bana yaptıklarınız için size bir kez daha çok teşekkür ederim. Bunu asla unutmayacağım.";
			link.l1 = "Haydi, babanın yanına acele et. Seni gördüğüne çok sevinecek. Belki de tarladan dönmüştür bile. Neyse, artık benim de gitmem gerek. Hoşça kal!";
			link.l1.go = "kathy_7";
		break;
		
		case "kathy_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.lifeday = 0;
			SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место
			pchar.questTemp.Terrapin_KathyReward = "true"; // награда за спасение Кати 160912
		break;
		
		// наш матрос
		case "terrapin_grot":
			dialog.text = "İşte buradasınız, Kaptan! Bizi öyle bir endişelendirdiniz ki! O kiremitli çatıların üstünde öyle bir koşu ve ardından o mide bulandıran yükseklikten atlayış... Görülmeye değerdi! Tanrı şahidimiz olsun, başaramayacaksınız diye korktuk... Tekrar hoş geldiniz, Kaptan, sandal hazır!";
			link.l1 = "Harika. Catherine, beni takip et!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_GotoShip");
		break;
		
		case "tibo_sailor":
			dialog.text = "Merhaba, monsieur. Siz kaptan mısınız "+GetFullName(pchar)+"?";
			link.l1 = "Evet, benim. Ne oluyor?";
			link.l1.go = "tibo_sailor_1";
		break;
		
		case "tibo_sailor_1":
			dialog.text = "Of, sana zar zor yetişebildim... Sana, tanıdığın bir centilmen olan Henry Thibaut adına geldim.";
			link.l1 = "Henry mi? Ne istiyor ki? Merhum sevgili amcasının ölümünden sonra mirasın beklenmedik şekilde kucağına düşmesinin sevincini mi paylaşacak?";
			link.l1.go = "tibo_sailor_2";
		break;
		
		case "tibo_sailor_2":
			dialog.text = "Monsieur Thibaut, sizi en kısa zamanda Tortuga’daki malikanesinde görmek istediğini acilen bildirdi. Sizin için iyi ücretli bir işi varmış. Ayrıca size bir ismi özellikle iletmemi söyledi: Robert Martene. Bu ismin ilginizi çekeceğinden eminim.";
			link.l1 = "Öyle mi? Peki, Henry'ye bu fikri veren neydi?";
			link.l1.go = "tibo_sailor_3";
		break;
		
		case "tibo_sailor_3":
			dialog.text = "Ayrıca, eğer bu seni onu ziyaret etmeye ikna etmediyse, bana şunu da eklememi özellikle istedi: 'Robert Martene ölmeli'.";
			link.l1 = "Pekala, pekala... Şimdi işler ilginçleşmeye başladı. İki yeminli dost tartışmaya tutuştu... Dediğin gibi, fırsat bulunca Henry'yi ziyaret etmeye çalışacağım.";
			link.l1.go = "tibo_sailor_4";
		break;
		
		case "tibo_sailor_4":
			dialog.text = "Monsieur Thibaut, ziyaretinizi geciktirmemenizi istedi. 'Balık on gün içinde ağdan kaçar' dediği tam olarak buydu...";
			link.l1 = "O da Robert gibi konuşuyor. Peki, Henry'ye bir uğrayacağım.";
			link.l1.go = "tibo_sailor_5";
		break;
		
		case "tibo_sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Terrapin_TiboCallOver", 0, 0, 10, false);
			AddQuestRecord("Sharlie", "25");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
