// диалоги персонажей по квесту Долго и счастливо
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
		
		// вестовой капитан в порту
		case "cureer":
			dialog.text = "Monsieur de Maure, ne şans! Sizi aylardır arıyordum!";
			link.l1 = "Canım, sahte haritalar, şüpheli bilgiler ya da ev yapımı rom almam - teşekkürler! Yoksa kelle avcısı mısın? Peki, şu an kafama ne kadar ödül biçtiler?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Ah, monsieur, ben... Ben hurda ticareti yapmam ve kimseyi öldürmem - sakın kılıcınıza davranmayın, gerek yok, size zarar vermeye niyetim yok! Her şey çok daha sıradan aslında - ben bir kurye gemisinin kaptanıyım. Posta taşırım. Ve sizin için önemli bir mektubum var!";
			link.l1 = "Bir mektup mu? Gönderen kim, öğrenebilir miyim?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Bir rahip bunu bana verdi ve bizzat, elden ele, Kaptan de Maure’a teslim etmemi istedi. Seni bulmaktan umudumu kesmiştim, neredeyse Saint Pierre liman ofisine bırakacaktım ama ne şans ki - işte buradasın!";
			link.l1 = "Evet, buradayım, bekliyorum - ver mektubu.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Bir sorun var... Başrahip teslimatın alıcı tarafından ödeneceğini söyledi. Yani bana dokuz bin iki yüz peso borçlusun.";
			link.l1 = "Böyle bir paraya, mektubu açık denizde, sabah kahvemle birlikte kamarama getirmeliydin! Mektubu kendine saklayabilirsin.";
			link.l1.go = "cureer_6";
			if (sti(pchar.money) >= 9200)
			{
				link.l2 = "Ben neden posta dağıtımına girmedim ki?! Korsanlıktan daha kârlıymış meğer! Al bakalım gümüşünü, canım, zarfı ver şimdi.";
				link.l2.go = "cureer_4";
			}
		break;
		
		case "cureer_4":
			AddMoneyToCharacter(pchar, -9200);
			dialog.text = "Sizinle iş yapmak güzeldi! Abbot Benoit en iyi dileklerini iletiyor! Hoşça kalın, Monsieur de Maure!";
			link.l1 = "";
			link.l1.go = "cureer_5";
		break;
		
		case "cureer_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			LongHappy_RecibeLetter();
		break;
		
		case "cureer_6":
			dialog.text = "Dediğiniz gibi olsun. Zarfı liman ofisine bırakacağım. Ama fiyatı etkileyecek, sizi uyarıyorum. Ve evet - Başrahip Benoit size en iyi dileklerini iletiyor.";
			link.l1 = "Başrahip Benoit'tan gelen mektup mu? Neden en başta söylemedin! Bu kesinlikle önemli olmalı!";
			link.l1.go = "cureer_7";
		break;
		
		case "cureer_7":
			dialog.text = "O halde liman başkanından al. Önceden bir avans kredi almayı unutma. Hoşça kal, Kaptan de Maure.";
			link.l1 = "Senden daha samimi korsanlar tanıdım. İyi şanslar, canım.";
			link.l1.go = "cureer_8";
		break;
		
		case "cureer_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.LongHappy = "portman";
		break;
		
		// испанский офицер в Сантьяго
		case "spa_officer":
			dialog.text = "Kutsal Baba, bugün her zamankinden erken geldiniz. Lütfen, refakatçiniz sizi bekliyor. Ve siz, señor de Maure - Peder Vincento şehre geldiğinizi öğrendi ve sizi akşam yemeğine davet ediyor.";
			link.l1 = "Korkarım Engizitör yemeğini tek başına yiyecek. Umarım bu iştahını kaçırmaz. Başrahip Benoit da ona eşlik etmeyecek. Kim olduğumu biliyorsun, bu yüzden sana tavsiyem: Bize engel olma, sessizce yolumuzdan çekil ve Palotti Baba’ya selamlarımı ilet.";
			link.l1.go = "spa_officer_1";
		break;
		
		case "spa_officer_1":
			if(sti(pchar.reputation.nobility) > 80 || sti(pchar.reputation.nobility) < 20) // провести учёт чести и известности
			{
				Notification_Reputation(true, 81, "low");
				dialog.text = "Evet, senin hakkında çok şey duydum ve inatçı olursan şehri kana bulamamam için açık talimatlarım var. Geçebilirsin. Ama Peder Vincento... memnun kalmayacak. Bunu aklında tut.";
				link.l1 = "Makul davrandınız, monsieur. Bir şekilde hayatta kalırım, ama kalbim baba sorgucunun hayal kırıklığıyla sızlıyor. İyi akşamlar!";
				link.l1.go = "spa_officer_2";
			}
			else
			{
				Notification_Reputation(false, 81, "low");
				Notification_Reputation(false, 19, "high");
				dialog.text = "Evet, senin hakkında çok şey duydum... ilginç şeyler. Ancak, böyle davetleri reddetmek sağlığın için tehlikelidir, señor. Aynı şekilde, Peder Vincento'nun misafirlerini kaçırmak da öyle. Yakalayın onları!";
				link.l1 = "Herkes kendi seçimini yaptı. Keşke işler buraya varmasaydı. Silah başına, caballero!";
				link.l1.go = "spa_officer_3";
			}
		break;
		
		case "spa_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "", 15.0);
			}
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "spa_officer_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				LAi_group_Attack(sld, Pchar);
			}
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterNationReputation(pchar, SPAIN, -20);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "Guests_block":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		// Ян Свенсон патер
		case "Svenson":
			dialog.text = "Charles, tebrikler! Biliyor musun, seni her zaman sevmişimdir, Helen de bana bir kızım gibi. İkiniz adına çok mutluyum. Vay canına... Bir kilisede gözyaşı dökmek, hep istediğim şeydi. Yaşlanıyor muyum ne?";
			link.l1 = "Her şey yolunda, Jan, neredeyse sunağın önünde ağlayacaktım. Tütsüdendir, herhalde?";
			link.l1.go = "Svenson_1";
		break;
		
		case "Svenson_1":
			dialog.text = "Doğru ya, kafur, kahretsin. Gözlerimin neden yandığını, burnumun neden kaşındığını merak ediyordum! Peki, Sharptown'da konuşuruz, Gladys'e sarılırız ve diğerlerinin yanına gideriz. Sanki Westphalia Barışı'nı imzalıyoruz gibi suratları var.";
			link.l1 = "Geldiğin için teşekkür ederim, Jan. Seni görmek beni mutlu etti, bu Helen için de çok önemli.";
			link.l1.go = "Guests_block";
		break;
		
		// Ян Свенсон на Исла Тесоро
		case "Svenson_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Sonunda geldin, Charles! Korvetim seni neredeyse bir gün önce geçti – bu da övünmek için güzel bir sebep.";
			link.l1 = "Rica ederim Jan, ama Gladys nerede, ya da eşin?";
			link.l1.go = "Svenson_3";
		break;
		
		case "Svenson_3":
			dialog.text = "Gladys'i bir ticaret gemisiyle Blueveld'e geri gönderdim - bu kadar hareketli eğlenceleri hiç onaylamıyor. Joanna gelemedi - ah, Martinique'te sana anlatmaya fırsatım olmadı! Düşünsene, şu yaşımda meşru bir baba olacağım, nasıl ama? Bak, acele edersen bizim çocuklar neredeyse aynı yaşta olacak, hahaha!";
			link.l1 = "Jan, tebrikler, bu harika bir haber! Bunu kutlamalıyız!";
			link.l1.go = "Svenson_4";
		break;
		
		case "Svenson_4":
			dialog.text = "Kesinlikle! Ama önce, size ve eşinize! Hey, oradaki, sessizlik!!! Yaşlı Orman Şeytanı bir konuşma yapacak!\nÖhöm... Şimdi, sevgili Monsieur ve Madame de Maure... Kahretsin! Böyle konuşamıyorum! Charles, Helen - siz ikiniz bana kendi çocuklarım gibisiniz ve biliyorum ki bu odada sizin birliğiniz için mutlu olmayacak kimse yok! O halde, kardeşlerim, sadık dostlarımızın mutluluğuna, yelkenlerinde adil bir rüzgara ve Lady Fortune'un sevgisine, birbirlerine duydukları hisler kadar güçlü olmasına içelim!!! Şerefe!";
			link.l1 = "Şerefe! Teşekkürler Jan... ah, bu rom her zamankinden çok daha sert... Nathan içine ne karıştırdı acaba?";
			link.l1.go = "Svenson_5";
		break;
		
		case "Svenson_5":
			dialog.text = "Hiçbir fikrim yok, ama bana doğru gibi geliyor. Yaşlı Hawk genelde içkiler konusunda uzmandır. Hadi, diğerlerinin yanına git, ben de doyasıya içmek isteyen yüz kadar cana içki hazırlamalıyım.";
			link.l1 = "Ormanda Şeytan içki servisi yapıyor - ne manzara! Partiyi organize ettiğin için teşekkürler. Turlarımı bitirir bitirmez kesinlikle geri geleceğim - belki başka birinin de yardıma ihtiyacı vardır.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_6":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Svenson_6_1":
			dialog.text = "Her şey yolunda mı, Charles?";
			link.l1 = "Mükemmel, Jan!";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_7":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Ve sonunda geldin! Martinique'te nasıl geçti? Hayatının sonsuza dek değiştiğini hissediyor musun?";
			link.l1 = "Çok daha önce değişti, Jan. Ama her şey şaşırtıcı derecede iyi gitti. Johanna nerede ve...";
			link.l1.go = "Svenson_8";
		break;
		
		case "Svenson_8":
			dialog.text = "Helen mi? Kız, neyin peşinde olduğumuzu öğrenir öğrenmez yelken açtı ve ufka doğru gitti. Sana türlü türlü sıcak tebrikler gönderdi, ama yine de... onun kalbini kırdın, gerçekten kırdın. Yine de, her şey yoluna girecek, bu sadece gençlik.";
			link.l1 = "Kalp ne isterse onu ister, anlıyorsun.";
			link.l1.go = "Svenson_9";
		break;
		
		case "Svenson_9":
			dialog.text = "Evet, öyle. Johanna gelemedi, düşün bir – şu yaşımda resmen baba olacağım, nasıl ama? Bak, acele edersen bizim çocuklar neredeyse aynı yaşta olacak, hahaha!";
			link.l1 = "Jan, tebrikler, bu harika bir haber! Bunu kutlamalıyız!";
			link.l1.go = "Svenson_10";
		break;
		
		case "Svenson_10":
			dialog.text = "Kesinlikle! Ama önce, sana ve eşine! Hey, oradaki, sessizlik!!! Yaşlı Orman Şeytanı bir konuşma yapacak!\nCharles ve Mary, tüm Kardeşlik şu anda şerefine kadeh kaldırıyor! Gerçek dostların mutluluğu, her deniz kurdunun ruhunu İspanyol altınının görkemi kadar sevindirir, ha-ha! Yolunuz açık olsun, ailenizle çıktığınız bu yolculukta rüzgar hep arkanızdan essin!!! Şerefe!";
			link.l1 = "Şerefe! Teşekkürler Jan... ah, bu rom her zamankinden çok daha sert... Nathan içine ne karıştırdı acaba?";
			link.l1.go = "Svenson_11";
		break;
		
		case "Svenson_11":
			dialog.text = "Hiçbir fikrim yok, ama bana oldukça doğru geliyor. Yaşlı Hawk genelde içkiler konusunda uzmandır. Hadi, diğerlerinin yanına git, ben de karnını doyurmak için sabırsızlanan yüz kişiye içki hazırlamam lazım.";
			link.l1 = "Bu meyhanenin adını kesinlikle değiştirmek lazım - 'Orman Şeytanı'nın kendisi burada tezgahın arkasında duruyordu'! Teşekkürler Jan, herkesle konuştuktan sonra mutlaka geri döneceğim - belki birinin yardıma ihtiyacı vardır.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_12":
			dialog.text = "Nasıl gidiyor, Charles? Düğün nasıl?";
			link.l1 = "Çok içten, Jan. Hepimizi buraya getirebildiğimize sevindim. Görünen o ki, Hawk'ın rom fıçıları dibini göstermeye başladı, değil mi?";
			link.l1.go = "Svenson_13";
		break;
		
		case "Svenson_13":
			dialog.text = "Evet, öyleler! O halde, buraya getirdiğin şeyi açmanın zamanı geldi. Bir de başka bir şey var - bana ilk başta yardım eden o adamlar arka odada fazlasıyla sarhoş olmuşlar. Sen hâlâ ayakta gibisin, damat bey - bir kasa şeri getirebilir misin?";
			link.l1 = "Tabii, sadece nereye gitmem gerektiğini söyle. Belki yol üzerinde bana yardım edecek birkaç ayık kafa bulurum. Gerçi, adamlarımın çoğu muhtemelen şimdiden sızmışlardır.";
			link.l1.go = "Svenson_14";
		break;
		
		case "Svenson_14":
			dialog.text = "Şaraplar, tersanenin altındaki mahzenlerde saklanıyordu, hatırlıyor musun? Hawk, ''bayram için saklayalım'' diye, en uzak koridora koymamızı söyledi. Bir de oradaki sıcaklık ve nemin tam ideal olduğunu, tam bir şarap mahzeni olacağını söylüyor. Gerçekten tam bir züppe.";
			link.l1 = "Doğru kararı verdi, Jan. Gideceğim, ama önce söyle - karımı gördün mü?";
			link.l1.go = "Svenson_15";
		break;
		
		case "Svenson_15":
			dialog.text = "O ve Dannie bir yerlere gittiler. Bırak kızlar konuşsun Charles, asıl eğlenceyi başlatmamız lazım. Sen mahzenlere in, ben de yemeklerle ilgileneyim. Çünkü yakında kuzu kaburga yerine kömür yiyecekmişiz gibi kokuyor!";
			link.l1 = "Pekala, sen eti kurtar, ben de şarabımızı alayım.";
			link.l1.go = "Svenson_16";
		break;
		
		case "Svenson_16":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			LongHappy_IslaTesoroToVineGo();
		break;
		
		case "Svenson_17":
			dialog.text = "Charles, Nathan, ne oldu, sarhoş kavgası mı çıkardınız?!";
			link.l1 = "Hayır Jan, zindanlarda birlikte silahlı kesicilere karşı savaştık. Onlarla başa çıktık ama onlar sadece keşifçiydi - asıl birlik hemen arkamızda!";
			link.l1.go = "Svenson_18";
		break;
		
		case "Svenson_18":
			dialog.text = "Takım mı? Neyden bahsediyorsun?! Marcus, buraya gel! Charles, hadi, her şeyi anlat bize.";
			link.l1 = "Dediğim gibi: Tersanenin altındaki zindanlarda birkaç alçak var. İyi silahlanmışlar. Nathan'la birlikte onlarla savaştık ve mucize eseri hepsini alt ettik. Ama daha fazlası yolda - içlerinden birinin yardım çağırmaya gittiğini duydum. Ve evet, aralarından biri Jacques adında birinden bahsetti.";
			link.l1.go = "Svenson_19";
		break;
		
		case "Svenson_19":
			DialogExit();
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "Terrax_7";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay8");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Svenson_20":
			dialog.text = "Yüzlerini tanıyorum... şu adamı ve kapının yanında yatan o alçağı. Bunlar Jacques the Kindman'ın adamları. İsimlerini hatırlamıyorum ama eminim.";
			link.l1 = "Yani bu Barbazon'un suçu mu? Aklını mı kaçırmış bu adam, nedir?!";
			link.l1.go = "Svenson_21";
		break;
		
		case "Svenson_21":
			dialog.text = "Bilmiyorum, ama görünen o ki Kindman fırsatı değerlendirmeye karar vermiş ve Brethren baronları arasında köklü bir değişiklik planlamış.";
			link.l1 = "Bu durumda, umarım kendisi gelir - ona birkaç kurşun deliği açmayı uzun zamandır hayal ediyorum. O alçak, düğünümü mahvetti, bir düşünsene! Hadi, sokağa çıkalım! Misafirlerimizi layıkıyla karşılayacağız!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernReload");
		break;
		
		case "Svenson_22":
			dialog.text = "Ve işte yorgun kahramanımız geldi! Hah, Charles, bu gerçekten bir şeydi! Jacques, tam bir alçak! Bak nasıl her şeyi ayarlamış - neredeyse başarıyordu!";
			link.l1 = "Evet, belki de Jackman'la işimiz bittiğinde o herifi de öldürmeliydik. Ama olan oldu. Barbazon öldü.";
			link.l1.go = "Svenson_23";
		break;
		
		case "Svenson_23":
			if (CheckAttribute(pchar, "questTemp.LongHappy.SvensonsShipSink")) dialog.text = "Pekala, bitti diyemem aslında - hayatımız devam ediyor! Gerçi kendimi tam anlamıyla bitkin hissediyorum. Alevler içindeki bir gemiden denize atlayıp, köpekbalıklarına göz kulak olarak bir saat boyunca kıyıya yüzmek için artık çok yaşlıyım. Umarım hâlâ biraz romumuz kalmıştır...";
			else dialog.text = "Eh, bunun bittiğini söyleyemem - hayat devam ediyor! Kahretsin, kendimi on yaş daha genç hissediyorum! Uzun zamandır böyle dövüşmemiştim! Umarım şu kargaşada rom ve şarap stokların çalınmamıştır - buna güzelce içmemiz lazım!";
			link.l1 = "Evet, ben de içerdim ama önce konağı kontrol etmem lazım, sana söylediler mi bilmiyorum...";
			link.l1.go = "Svenson_24";
		break;
		
		case "Svenson_24":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				dialog.text = "Hindli arkadaşınla mı ilgili? Evet, duydum, nasıl oldu?";
				link.l1 = "Bir alçağın sıktığı kurşundan karımı ve Dannielle'i korumak için önlerine atladı. Hadi gidelim, yürürken anlatırım.";
			}
			else
			{
				dialog.text = "Nathan hakkında mı? Evet, duydum, sadece nasıl olduğunu anlamadım?";
				link.l1 = "Bir piçin sıktığı kurşundan eşlerimizi korumak için araya atladı. Hadi gidelim, yolda anlatırım.";
			}
			link.l1.go = "Svenson_25";
		break;
		
		case "Svenson_25":
			DialogExit();
			DoQuestReloadToLocation("Pirates_townhall", "goto", "goto4", "LongHappy_DannyInResidence");
		break;
		
		case "Svenson_26":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Güçlü ol, Charles. Oğulların için gerçekten üzgünüm. Bugün birçok iyi adam hayatını kaybetti, ve her biri için Barbazon'un cehennemdeki kazanına daha fazla yağ dökülecek.";
				link.l1 = "Bu hiç mantıklı değil... kahretsin! Zor, Jan... Zaten arkadaşlarımı kaybettim, ama buna alışamıyorum. Artık devam edebilir miyim bilmiyorum.";
				link.l1.go = "Svenson_28";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Şu sessiz doktor mu? Üzgünüm Charles, gerçekten. İyi bir adamdı.";
					link.l1 = "Evet, Jan, ben de öyle. Ama korkarım ki bilim dünyası benden çok daha fazlasını kaybetti. O bir dahiydi... hepsi gibi sofistike, ama... kahretsin...";
					link.l1.go = "Svenson_27";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sTemp = "your Indian guy";
					else sTemp = "Nathan";
					dialog.text = "Görünüşe bakılırsa, her şey bitti. Bugün birçok iyi adamı kaybettik ve her biri için cehennemde Barbazon kazanına biraz daha yağ ekleyecek, ama "+sTemp+" iyi olacak, esas önemli olan da bu.";
					link.l1 = "Haklısın Jan, bu da içimi rahatlattı. Diğer baronlar nasıl? Onlar da iyi mi?";
					link.l1.go = "Svenson_32";
				}
			}
		break;
		
		case "Svenson_27":
			dialog.text = "Jacques Barbazon'un son pisliği. Haklısın, onu daha önce öldürseydik her şey farklı olabilirdi.";
			link.l1 = "Ama geçmişe üzülmenin ne faydası var? Geçmişi değiştiremeyiz. Diğer baronlar nasıl? Herkes hayatta mı?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_28":
			dialog.text = "Kimse buna alışamaz. Adamlarımız için bir kadeh kaldıralım mı? Masada bir şişe buldum, bu karmaşadan mucizevi bir şekilde sağ çıkmış.";
			link.l1 = "Dök, ben... Kahretsin... bin kere lanet olsun!";
			link.l1.go = "Svenson_29";
		break;
		
		case "Svenson_29":
			dialog.text = "Bana onlardan bahset. Bu doktor akıllı görünüyordu. Kendini öyle akıllıca ifade etti ki.";
			link.l1 = "Yaptı. Ama korkarım ki, bilim dünyası sadece beni değil, çok daha fazlasını kaybetti. O bir dahiydi... hepsi gibi zarif, sofistike biriydi. Mucizelerin ustasıydı!";
			link.l1.go = "Svenson_30";
		break;
		
		case "Svenson_30":
			dialog.text = "Hintli adam hakkında mı? Onu nerede buldun?";
			link.l1 = "Rescued him from prison on Guadeloupe almost immediately after my arrival. Really funny and stupid story. So, he stayed with me. He chose to; I gave him freedom, but he stayed by my side – I saved him, and he thought he owed me till the end of his life. Terse, dressed oddly, but more loyal than any knight, he had a talent too – he could hit a coin with a musket mid-air at any distance.";
			link.l1.go = "Svenson_31";
		break;
		
		case "Svenson_31":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Pekala, sana borcunu ödedi, ne diyebilirim ki. Kurtuldun "+sld.name+" ve Dannielle'i o alçaktan kurtardım. Bana kalırsa, böylesine cesur bir savaşçı için bu uygun bir son.";
			link.l1 = "Evet, Jan. Düşenlerin anısına içelim... Huzur bulsunlar. Diğer baronlar nasıl? Hepsi iyi mi?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_32":
			dialog.text = "Bu gece bize çok pahalıya mal oldu. Kardeşliğin bu katliamdan ne zaman toparlanacağını bile bilmiyorum. Kindman saldırmak için zamanı ve yeri kusursuz seçti. Neredeyse amacına ulaşıyordu – biraz daha ve her şey kaybedilecekti. Ama kaybedebileceğimizden çok daha azını kaybettik.";
			link.l1 = "";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) link.l1.go = "Svenson_33";
			else link.l1.go = "Svenson_35";
		break;
		
		case "Svenson_33":
			dialog.text = "The Shark is in the infirmary, his ship took a volley from twenty-four pounders. He was thrown overboard, broke a couple of ribs, swallowed seawater, but he lives; in a few days he will be as good as new.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry")) link.l1.go = "Svenson_34"; // был Венсан
			else link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_34":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard sadece birkaç çizik aldı - kıyıyı savunuyor ve yeraltı mezarlarını temizliyordu. Şimdi limanda, yaralılar için hastaneler ve daha az şanslı olanlar için cenazeler organize ediyor.";
			else dialog.text = "Bernard'ın şansı yaver gitmedi. Saldırıdan sonra yeraltı mezarlarından çıkıp evleri temizliyordu, ambarlarda o alçaklardan bir grup ile karşılaştı. Kafasına kurşun yedi, hem de tam alnından. Yazık oldu, iyi bir kaptandı... Tyrex bunu öğrenince çılgına dönecek.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard sadece birkaç çizik aldı – kıyıyı savunuyor ve yeraltı mezarlarını temizliyordu. Şimdi limanda, yaralılar için hastaneleri ve şanssızlar için cenazeleri organize ediyor.";
			else dialog.text = "Bernard'ın şansı yoktu. Saldırıdan sonra yeraltı geçitlerinden evleri temizlerken, ambarlarda o heriflerden bir grup ile karşılaşmış. Kafasından vurulmuş, hem de tam alnından. Yazık oldu, iyi bir kaptandı... Tyrex bunu öğrenince deliye dönecek.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_36":
			dialog.text = "Hawk hakkında, biliyorsun. Dannie onu en az bir ay adadan ayrılmasına izin vermez, bu kesin. Tek düşündüğü bir şey vardı... neyse.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Svenson_37";
			else link.l1.go = "Svenson_38";
		break;
		
		case "Svenson_37":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free"))
			{
				dialog.text = "Marcus her zamanki gibi dimdik duruyor. Karaya çıkar çıkmaz, bütün bu rezilliğe göz yuman nöbetçilerin canına okudu. Hâlâ kasabada düzeni sağlamak için emirler yağdırıyor. Şüphesiz, tam anlamıyla demir gibi bir adam.";
				link.l1 = "Demir daha yumuşak. Sanırım baronumuz bilime henüz bilinmeyen bir metalden yapılmış, haha!";
			}
			else
			{
				pchar.questTemp.LongHappy.Terrax.Lost = "true";
				dialog.text = "Only Marcus's situation is unclear; his ship was boarded, but the survivors claim he managed to jump overboard. I've already sent the longboats to search the bay. I hope it turns out our baron is tough enough not to give up so easily.";
				link.l1 = "Bu kötü, ama onu kaybetmek için henüz çok erken. Marcus bizi öyle kolay kolay bırakmazdı. Arama sonuçlarını bekleyelim.";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_38":
			if (CheckAttribute(pchar, "questTemp.LongHappy.TerraxShipSink"))
			{
				dialog.text = "Marcus, gemisi battıktan sonra kıyıya yüzerek çıktı. Biliyorsun, Tyrex böyle bir önemsiz şey yüzünden boğulacak biri değil. Şimdi kasabada bir yerlerde. Muhtemelen bütün bu rezilliği gözden kaçıran nöbetçilerin ödünü patlatıyordur. Gerçekten demir gibi bir adam.";
				link.l1 = "Demir batar. Sanırım baronumuz hâlâ bilime yabancı bir maddeden yapılmış, haha!";
			}
			else
			{
				dialog.text = "Marcus her zamanki gibi dimdik duruyor. Karaya çıkar çıkmaz, bütün bu pisliği gözden kaçıran nöbetçilerin canına okudu. Hâlâ kasabada düzeni sağlamak için emirler yağdırıyor. Gerçekten demir gibi bir adam, hiç şüphe yok.";
				link.l1 = "Demir daha yumuşak. Sanırım baronumuz bilime henüz bilinmeyen bir metalden yapılmış, haha!";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_39":
			dialog.text = "Hepsi bu. Eh, daha kötü olabilirdi. Hatta senin düğünün bile, Charles, biraz... çetin geçti. Önemli olan ikinizin de hayatta olması. Küçük bir tavsiye, genel olarak... sevin... ve sakın aşkınız için mücadeleden vazgeçmeyin!";
			link.l1 = "Teşekkür ederim, Jan. Hepinize teşekkür ederim... İtiraf etmeliyim ki, bir kutlamayla başladığımızı unutmuşum.";
			link.l1.go = "Svenson_40";
		break;
		
		case "Svenson_40":
			dialog.text = "İşte, bir hatırlatma.";
			link.l1 = "Evet, o... çılgın bir partiydi.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) link.l1.go = "Svenson_41";
			else link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_41":
			dialog.text = "Evet, kesinlikle öyleydi, bir dakika bekle. Bir şey var - yanında bir Hintli adam vardı sanırım, değil mi, hep yanında ya da etrafına bakınıyordu sanki biri sana nişan alıyormuş gibi. Tuhaf giyimliydi ve kalabalıkta hemen fark ediliyordu.";
			link.l1 = "Evet, Tichingitu, bu karmaşanın en başında ortadan kayboldu. Açıkçası endişelenmeye başlıyorum. Sen bir şey biliyor musun?";
			link.l1.go = "Svenson_42";
		break;
		
		case "Svenson_42":
			pchar.questTemp.LongHappy.Tichingitu_Wife = "true";
			dialog.text = "Öyle görünüyor. Bizim barmen, saldırıdan önce yeğeninin kaçırıldığını söyleyip ortalığı ayağa kaldırıyordu. Kızın, kasabanın doğusundaki sahil boyunca onu omzunda taşıyan bir Hintliyle görüldüğünü söylüyor. Kindman’ın pislikleri arasında Hintli görmedim ama senin adamını hatırladım, o yüzden sesimi çıkarmadım. Başına bir iş gelmeden onu bulsan iyi olur. Çünkü barmen, önce bulursa öldüreceğini söylüyor. İyi adamdır, ama yeğeni için gözünü kırpmadan birinin kafasını koparır.";
			link.l1 = "Evet, o tipleri bilirim, merak etme, ve sağ ol Jan, hemen gidip onu arayacağım.";
			link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_43":
			dialog.text = "Yani, genel olarak böyle bir şey... Affedersin, konuşma işinde pek iyi değilim. Şimdi ise daha da kötüyüm - bu gece hepimizin suyunu çekti. Hepimiz en az bir gün dinlenmeliyiz - sonra nasıl devam edeceğimize karar veririz.";
			link.l1 = "Haklısın Jan. Gitmeliyim, kafamı toparlamam gerek.";
			link.l1.go = "Svenson_44";
		break;
		
		case "Svenson_44":
			DialogExit();
			DoQuestReloadToLocation("Pirates_town", "reload", "reload3", "LongHappy_WifeInTown");
		break;
		
		case "Svenson_45":
			dialog.text = "İyi görünüyorsun, Charles. İyi uyudun mu?";
			link.l1 = "Evet, şehrin dışında bize rahat bir ev verdiler. Hatta dün olan bütün o deliliği rüya sandım bir an. Ve işte buradasın Jan, perişan görünüyorsun. Başka ne oldu?";
			link.l1.go = "Svenson_46";
		break;
		
		case "Svenson_46":
			dialog.text = "Ah, yok bir şey, sadece henüz uyuyamadım. Biliyorsun... burada olanlardan sonra şehri toparlamak kolay iş değil.";
			link.l1 = "Dannie ve Nathan nasıl? Herkes nerede?";
			link.l1.go = "Svenson_47";
		break;
		
		case "Svenson_47":
			dialog.text = "Dinleniyorlar. Rahatsız etme, Dannie bugün silahlarla yatağa girdiğini herkese söyledi... Dodson denizde, adayı bir daha böyle bir şey yaşamayacak şekilde korumak için daha fazla gemi bulmaya gitti, diğerleri ise adanın kuzeyinde kayıpları gömüyor.";
			link.l1 = "";
			link.l1.go = "Svenson_48";
		break;
		
		case "Svenson_48":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner") && !CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free")) dialog.text = "Marcus henüz bulunamadı, ama biz hallederiz, merak etme. Hepimiz için çok şey yaptın, kendini üzme. Tyrax er ya da geç dönecek - onu bulacağız.";
			else dialog.text = "Marcus burada işini bitirdi ve birinin lügeriyle Hispaniola'ya doğru yola çıktı. Barbazon'un ölümünden sonra ortaya çıkan bazı meseleleri çözmesi gerekiyor. Sana ve eşine selamlarını ve en iyi dileklerini gönderiyor.";
			link.l1 = "";
			link.l1.go = "Svenson_49";
		break;
		
		case "Svenson_49":
			dialog.text = "Well, the Brethren have withstood this blow. Soon, we shall rise even stronger than before. Kindman and Jackman have been undermining our unity for too long; now they're gone, and I feel in my heart that we shall make the Caribbean tremble more than once. The Golden Age is coming for those to whom laws and kings are no friends, remember my words.";
			link.l1 = "Bu güzel olurdu. Eski Dünya'ya daha fazla dayanabileceğimden emin değilim. Buraya geldiğimde, denizin özgürlüğüne, bu vahşi günbatımı ve gün doğumu renklerine aşık olacağımı, dünyanın en iyi kadınını bulacağımı ve... hayatımı emanet edebileceğim dostlar edineceğimi hiç hayal etmemiştim.";
			link.l1.go = "Svenson_50";
		break;
		
		case "Svenson_50":
			dialog.text = "Pekâlâ, yolu biliyorsun, sadece kararını ver. Evlerimizde her zaman hoş karşılanırsın.";
			link.l1 = "Teşekkürler, Jan. Bu benim için çok şey ifade ediyor.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete") link.l1.go = "Svenson_51";
				else link.l1.go = "Svenson_54";
			}		
			else link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_51":
			pchar.questTemp.LongHappy.Baron = "true";
			dialog.text = "Ama önce, önemli bir şey kaldı. Charles, sen uyurken biz toplandık ve karar verdik\nBarbazon öldüğüne göre, Kardeşliğin yeni bir barona ihtiyacı var. Burada çoğunluğumuz olduğu için ve karar oybirliğiyle alındığı için, işte böyle. Tebrikler - artık Le François'nın yeni Baronu sensin. Ama dur ... Anlıyorum - sen dünyayı bilen bir adamsın, bu güzel yerin işlerini yönetmeye vaktin yok, bu yüzden oraya güvenilir birini yerleştirdik, sen de istediğini yapabilirsin. Sadece unutma - artık Kardeşlik'te senin de bir söz hakkın var.";
			link.l1 = "Jan, ben... ben ne diyeceğimi bilemiyorum... Bu büyük bir onur, ne desem bilemiyorum...";
			link.l1.go = "Svenson_52";
		break;
		
		case "Svenson_52":
			dialog.text = "Hadi ama! Tyrex'le olan işte ve sonra Sharp'ın mirasıyla ilgili tüm o hikâyede kendini mükemmelce kanıtladın. Sen Tanrı'nın bize bir lütfusun. Senin için hiçbir şey değişmeyecek – planladığın gibi devam et, yokluğunda ise adamın tüm işleri üstlenecek.\nUmut vadeden biri var, Jan David, Korsanlardan biri. Fransız, dürüst bir adam, parlak bir zekâsı var ve bunu senin gibi kullanmayı biliyor. Ama onu bulmam biraz zaman alacak – görünüşe göre İspanyollar tarafından yakalanmış, ama bu halledilebilir, endişelenme. İşlere alışır alışmaz payını sana göndereceğinden emin olacağım.";
			link.l1 = "Gerçekten de işlerin böyle gelişeceğini hiç beklemiyordum. Peki, madem kararını verdin, öyle olsun. Korsan Baron Charles de Maure!";
			link.l1.go = "Svenson_53";
		break;
		
		case "Svenson_53":
			dialog.text = "Yaşasın baron! Eğer bu unvanı hak eden biri varsa, o sensin. Onu gururla taşı ve unutma – artık sen de bizdensin, ne kadar güzel bir üniforma giyersen giy, burada, tam altında, gerçek bir korsanın kalbi atıyor.";
			link.l1 = "Bilmiyorum, belki de abartıyorsun... Ama güvenini boşa çıkarmamak için elimden geleni yapacağım.";
			link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_54":
			dialog.text = "Şimdi ne yapacaksın? Avrupa'ya, babanın yanına dönüp ona eşini mi tanıştıracaksın?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") || CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				link.l1 = "Evet, ama önce birine veda etmem gerek... Ne demek istediğimi anlıyorsun.";
				link.l1.go = "Svenson_56";
			}
			else	
			{
				link.l1 = "Belki de hemen değil. Bir kez daha takımadalar arasında yelken açacağım, bu özgürlük havasını son kez solumak istiyorum.";
				link.l1.go = "Svenson_55";
			}
		break;
		
		case "Svenson_55":
			dialog.text = "Pekâlâ, bir gemin var, istediğin zaman eve dönebilirsin.";
			link.l1 = "Umarım öyle olur. Teşekkürler Jan, hepinize teşekkür ederim ve sonra görüşürüz, eski dostum! Şahinlere ve Köpekbalığı'na selam söyle!";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_56":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died")) sTemp = "They deserve";
			else sTemp = "He deserve";
			dialog.text = "Evet, zor, ama bunu yapmak zorundayız. Denize doğru?";
			link.l1 = "Hayır, Antigua'ya yelken açacağım. "+sTemp+" bir süreliğine de olsa evimiz olan bir yerde huzur içinde yatmak için.";
			link.l1.go = "Svenson_57";
		break;
		
		case "Svenson_57":
			dialog.text = "Benim adıma da birkaç güzel söz söyle. Ve merak etme – bundan sonra kendi başımıza hallederiz. Her şey yoluna girecek.";
			link.l1 = "Teşekkürler, Jan. Yakında görüşürüz, eski dostum! Kartallara ve Köpekbalığı'na selamımı söyle!... Demek Antigua'ya gidiyoruz.";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_58":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_IslaMarryComplete", 10.0);
		break;
		
		case "Svenson_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Svenson_";
		break;
		
		// Глэдис
		case "Gladis":
			dialog.text = "Genç adam, bugün gözümde daha da büyüdün. Helen için öyle çok şey yaptın ki, teşekkür etmek için kelimeler yetmez. Tek dileğim, ona bundan sonra da göz kulak olman. Babası hayatta olsaydı ve bunları görseydi, ne kadar mutlu olurdu... ah, affedersin.";
			link.l1 = "Sorun değil, Gladys. Bugün Helen'e destek olmak için tüm takımadaları aştın. Hem ben hem de Jan ziyaretin için gerçekten minnettarız, teşekkür ederiz.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер Мэри
		case "forge":
			dialog.text = "Maure Bey, bu samimiyetim için özür dilerim, ama şöyle söyleyeceğim - Charles, dostum, senin adına gerçekten çok mutluyum! Sana ya da gelinine yardımcı olabileceğim bir şey olursa, sadece söylemen yeterli!";
			link.l1 = "Sana teşekkür ederim Baron, çok mutluyum ve babamın çeyiz olarak istediği üzüm bağları konusunda kendimi affettirebileceğime inanıyorum – neyse ki, Yeni Dünya’daki zamanımda maddi durumum oldukça düzeldi.";
			link.l1.go = "forge_1";
		break;
		
		case "forge_1":
			dialog.text = "Evet, sanırım artık istediğin her şeyi karşılayabilirsin, Charles. Affedersin, ama baba olarak katkımı sunacağım – Bugün, Maliye Bakanı olan iyi dostuma yazacağım. Seçtiğin kişi bir soyluluk unvanı alacak ve sanırım ona iyi bir malikâne buluruz, diyelim ki Gaskonya’da, borçlar yüzünden el konulanlardan birini, ve bunu geriye dönük olarak ona tahsis ederiz. Böylece kimse Chevalier de Monper’in düşük statüde bir kadınla evlendiğini söylemeye cesaret edemez!";
			link.l1 = "Böyle dedikodulara pek aldırış ettiğimi sanmıyorum, ama yine de sağ ol, Baron. Yine de, sen yapmamalısın";
			link.l1.go = "forge_2";
		break;
		
		case "forge_2":
			dialog.text = "Elbette yapmalıyım! Şimdi git, Charles, ilgini diğer misafirlerle de paylaş. Ve bir kez daha, en içten tebriklerimi kabul et!";
			link.l1 = "Eşim ve ben size teşekkür ederiz. Görüşmek üzere, Baron.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер ГГ
		case "forge_3":
			dialog.text = "Monsieur de Maure, bu samimiyetim için özür dilerim ama şöyle söyleyeceğim – Charles, dostum, senin adına gerçekten çok mutluyum! Senin ya da gelinin için yapabileceğim bir şey olursa, yeter ki söyle!";
			link.l1 = "Teşekkür ederim Baron, ama benim için zaten fazlasıyla şey yaptınız. Davetimize icabet etmeniz bizim için yeterli.";
			link.l1.go = "forge_4";
		break;
		
		case "forge_4":
			dialog.text = "Nasıl karşılık vermezdim ki, Charles! Ama dinle – sana ve güzel gelinine layık bir hediye vermek istiyorum, fakat parayla ya da kılıçla elde edemeyeceğin bir şey bulamıyorum. Bu yüzden Paris’teki Maliye Bakanı dostuma yazacağım ve Avrupa’ya vardığında, de Monper adını Barons de Monper unvanına yükselten kraliyet fermanını imzalaman için seni bekliyor olacaklar! Hayır, tek kelime etme, bu senin için yapabileceğim en az şey.";
			link.l1 = "Ne diyeceğimi bile bilmiyorum Baron... Babam çok memnun olacak. Gerçekten teşekkür ederim.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже гость
		case "forge_5":
			dialog.text = "Charles, lütfen en içten tebriklerimi kabul et! Seçtiğin kişi gerçekten harika biri! Bugün sömürge modasının bambaşka bir yöne doğru güçlü bir ivme kazandığına inanıyorum. Senin özgünlüğün her zaman beni etkilemiştir! Sen ve güzel eşin sonsuza dek mutlu yaşayın!";
			link.l1 = "Teşekkür ederiz, Baron. Ziyaretinizle bizi onurlandırdınız.";
			link.l1.go = "forge_6";
		break;
		
		case "forge_6":
			dialog.text = "Senden uzak durabilir miydim, dostum? Birlikte çok şey yaşadık ve seni dostum olarak görmekten gurur duyuyorum, Charles. Unutma – ne olursa olsun kapım sana her zaman açık.";
			link.l1 = "de Monper ailesinin kapıları size her zaman açık olacak, Baron.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер Мэри
		case "puancie":
			dialog.text = "Charles, dostum, bugün çok önemli bir gün ve bunu seninle paylaşmaya davet ettiğin için çok mutluyum. Seninle birlikte uzun ve zorlu bir yol katettik ve mademoiselle'in... lütfen affet beni - Madame de Maure'un temsilci babası olmak, benim için büyük bir onur, inan bana. Tüm kalbimle sana mutluluk diliyorum! Ve lütfen, Avrupa'ya ne zaman gideceğini bana bildir – seçtiğin kişinin temsilci babası olarak, babana gerekli tüm düğün hediyelerini göndereceğim. İnan bana, kimse Chevalier de Monper'in gelininin fakir ya da değersiz olduğunu söyleyemez!";
			link.l1 = "Eğer izin verirseniz, Şövalye, Monper malikanesinin birkaç mil kuzeyinde iyi üzüm bağları var, onlar La Brigne ailesine ait ve ben...";
			link.l1.go = "puancie_1";
		break;
		
		case "puancie_1":
			dialog.text = "Bir kelime daha etme dostum, bir kelime daha! Hemen Lyon’daki yetkili temsilcime yazacağım – sen oraya vardığında, bu bağlar seçtiğin kişiye verilecek.";
			link.l1 = "Teşekkür ederim, Şövalye. Haklısın – bizim... dostluğumuz çok şey yaşadı. Ama bugün burada bizimle olduğun için gerçekten mutluyum. Görüşmek üzere, tekrar teşekkürler!";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер ГГ
		case "puancie_2":
			dialog.text = "Charles, dostum, bugün çok önemli bir gün ve bunu seninle paylaşmaya davet ettiğin için çok mutluyum. Uzun ve zorlu bir yol katettik ve bugün düğününde yanında olmak benim için bir onur. Tüm kalbimle sana mutluluklar diliyorum! Avrupa'ya ne zaman gideceğini bana bildir – babana uygun düğün hediyeleri göndereceğim.";
			link.l1 = "Buna gerek yok, Şövalye. Davetimi kabul ettiğiniz için teşekkür ederim.";
			link.l1.go = "puancie_3";
		break;
		
		case "puancie_3":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry2", 50);
			TakeNItems(pchar, "jewelry3", 50);
			TakeNItems(pchar, "jewelry4", 50);
			dialog.text = "Dediğim gibi - bu benim için bir onur! Ama dur, dostum, bu vesileyle sana bir şey sunmak isterim - eminim hem seni hem de seçtiğini memnun edecektir. Yeni Guyana’daki madenlerimizden güzel taşlar - bunları zarif bir çerçeveye taktır, Madame de Maure kraliyet davetinde bile parlayacaktır! Tabii onu elbise giymeye ikna edebilirsen...";
			link.l1 = "Ah, gerçekten gerek yoktu, şövalye. Yine de teşekkür ederim.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси гость
		case "puancie_4":
			dialog.text = "Charles, dostum, seni tebrik etmek isterim! Uzun ve zorlu bir yol katettik ve bugün burada olmaktan gerçekten mutluyum. Tanrı şahidim olsun – mutluluğu hak ediyorsun! Ona sahip çık ve koru – sana uzun ve mutlu yıllar diliyorum!";
			link.l1 = "Teşekkür ederiz, Şövalye, eşim ve ben size minnettarız.";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей патер
		case "fadey":
			dialog.text = "Charles, ne kutlama ama, ne kadar da önemli insan var! Sana tüm kalbimle mutluluk, sağlık ve sana neşe getirecek çocuklar diliyorum! Bizim oralarda deriz ki - 'gor'ko'!";
			link.l1 = "Teşekkür ederim, Fadey, gelmeyi kabul ederek beni onurlandırdın.";
			link.l1.go = "fadey_1";
		break;
		
		case "fadey_1":
			dialog.text = "Ama neden burada bu kadar çok insan var, sanki evlenmiyoruz da büyük bir ticaret anlaşması yapıyoruz, hem de bana göre hâlâ yeterince bira ya da votka yok... haha! Şaka yapıyorum Charles, neden bembeyaz oldun? Hadi gel, bana sarıl, evli kaptan!";
			link.l1 = "Vay canına... Fadey, ayı gibi güçlüsün!";
			if (CheckAttribute(pchar, "questTemp.Persian"))
			{
				if (pchar.questTemp.Persian == "time" || pchar.questTemp.Persian == "end") link.l1.go = "fadey_2";
				else link.l1.go = "Guests_block";
			}
			else link.l1.go = "Guests_block";
		break;
		
		case "fadey_2":
			GiveItem2Character(pchar, "blade_22");
			GiveItem2Character(pchar, "blade_23");
			GiveItem2Character(pchar, "blade_24");
			Log_Info("You got three Persian sabres");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bekle, Charles, hemen gitme - bir misafirin düğüne hediyesiz gelmesi olmaz. Al, bunları senin için hazırladım. Biliyorum, bu kılıçların hepsini bulmaya çalıştın ve bazılarını gerçekten beğendin. O yüzden kabul et onları - aile konağına as ve Fadey Moskovit’i güzel bir sözle hatırla!";
			link.l1 = "Bu gerçekten büyük bir hediye! Teşekkür ederim, Fadey. Bunlar gerçekten harika silahlar ve söz veriyorum, de Monper malikanesinde hak ettikleri yeri alacaklar!";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей гость
		case "fadey_3":
			dialog.text = "Charles, ne kutlama ama, ne kadar da önemli insanlar var! Sana tüm kalbimle mutluluk, sağlık ve sana neşe getirecek çocuklar diliyorum! Bizde derler ki - 'acı olsun'! Hadi sarıl bana, evli kaptan!";
			link.l1 = "Vay canına... Fadey, ayı gibi güçlüsün!";
			link.l1.go = "Guests_block";
		break;
		
		// Проспер Трубаль
		case "Prosper":
			dialog.text = "Charles, bunu kaçırmak istemedim, seni ve seçtiğin kişiyi tüm kalbimle tebrik ediyorum! Mutlu olun! Biliyor musun, birkaç ay önce kızımı iyi bir adama verdim, birbirlerine âşıklar ama açıkçası, sen olmadığın için üzülmüştüm... Neyse... ne diyorum ben şimdi - tebrikler! Bir ömür boyu mutlu yaşayın!";
			link.l1 = "Teşekkürler Prosper, geldiğine sevindim.";
			link.l1.go = "Guests_block";
		break;
		
		// Тичингиту
		case "Tichingitu":
			dialog.text = "Tebrikler, kaptan! Garip bir tören, ama güzel – Tichingitu beğendi. Gerçi, kaptan aslında kadını kaçırıp ailesine fidye göndermeliydi.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Aslında bir bakıma öyle oldu, ama bu sadece bir formalite. Teşekkür ederim, dostum!";
			else link.l1 = "Aslında bir bakıma öyle, ama bu sadece bir formaliteydi. Teşekkür ederim dostum! Sharptown'da daha çok konuşacağız seninle – orada resmi işlerden çok, gerçek eğlence olacak, söz veriyorum!";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Yine ateş suyu mı? Tichingitu bundan pek hoşlandığını söyleyemez. Belki kutlama için bir gemiye çıkmak daha iyi olurdu, ya da en azından bir ateşin etrafında dans etmek?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Umarım son gelmeden önce ateşlerin etrafında dans etmek zorunda kalmayız ve gemi basmaktan da kaçınmak isterim. Tamam, sabırlı ol – az kaldı, sonra doğruca meyhaneye gideceğiz.";
			else link.l1 = "Korkarım ki son gelmeden önce ateşlerin etrafında dans etmeye başlarız, ve gemiye çıkıştan kaçınmayı tercih ederim. Peki, sabırlı ol – az kaldı, hemen Sharptown'a yelken açacağız.";
			link.l1.go = "Guests_block";
		break;
		
		case "Tichingitu_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Kaptan, tekrar tebrikler! Tichingitu bu kutlamadan öncekinden daha çok keyif alıyor. Kaptan dostlarını seçmeyi biliyor - burada daha fazla samimiyet, daha az ikiyüzlülük ve daha az sahte saç var.";
			link.l1 = "Teşekkür ederim, dostum! Ama sakın ateş suyunu içme – burada çok serttir.";
			link.l1.go = "Tichingitu_4";
			link.l2 = "Teşekkür ederim, dostum! Bir içki içelim mi? Biliyorum, pek hoşlanmazsın ama bugün bir denemelisin!";
			link.l2.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			pchar.questTemp.LongHappy.Tichingitu_Rum = "true";
			dialog.text = "Tichingitu ateşi suyu sevmez, ama kaptan ısrar ederse, bugün olur. Senin mutluluğuna ve karına!";
			link.l1 = "Ve sana, Tichingitu! Dostluğuna ve sadakatine!";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			DialogExit();
			npchar.dialog.currentnode = "Tichingitu_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_57";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tichingitu_4_1":
			dialog.text = "Güzel bir parti, kaptan.";
			link.l1 = "Memnun kalmana sevindim.";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Kaptan, yıldızlara bakmaya mı çıktınız? Bu gece çok güzel olacak gibi görünüyor. Tichingitu deniz üzerindeki geceyi çok sever. Çok huzurludur.";
			link.l1 = "Seni hala ayakta görmek güzel, dostum! Nathaniel ve ben yardımına ihtiyacımız var – meyhanedeki adamların içkisi bitmiş, tersanenin altındaki depodan birkaç kasa içki getirmemiz gerekiyor.";
			link.l1.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = "Öne geç, kaptan. Tichingitu her zamanki gibi seni takip ediyor.";
			link.l1 = "Pekala, hadi gidelim!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Tichingitu_8":
			dialog.text = "Kaptan, insanlar var ve silahlılar. Tichingitu silahlarının şakırtısını duyuyor, sesi her geçen saniye daha da yükseliyor. Bu hoşuma gitmiyor. Hadi saklanalım.";
			link.l1 = "Hadi ama dostum - burası Sharptown, burada insanlar tuvalete bile tabancayla gider. Hey Nathan... vay canına! Bir şişe daha gitti. Böyle devam ederse, bütün şişeleri kıracaksın! Ayağa kalk, kahretsin! Ha-ha!";
			link.l1.go = "Tichingitu_9";
		break;
		
		case "Tichingitu_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LongHappy_SetBandosInDungeon();
		break;
		
		case "Tichingitu_10":
			dialog.text = "Kaptan... sen... Tichingitu'nun başı fırtınadaki direk gibi dönüyor. Ne oldu?";
			link.l1 = "Ben de sana aynı şeyi soracaktım! Bunca zamandır neredeydin?!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Tichingitu bir saat önce bu kızın çığlıkları yüzünden uyandı. Kız neredeyse çıplak halde sahil boyunca koştu, bir şeyler bağırıyordu kaçıranlar ve vahşiler hakkında... Ama burada bizden başka kimse yok. Sende su var mı? Yine o ateşli olanından olmasın, Tichingitu artık ondan nefret ediyor.";
			link.l1 = "Bir yerde bir matara vardı, eğer onu savaşta kaybetmediysem... al bakalım. Bunu nasıl başardın? Onun amcası, buradaki bir barmen, yeğenini kaçıran Hintliyi arıyor ve onu bulursa paramparça edeceğine yemin ediyor, o tüylü boş kafasıyla birlikte. Sence kimi kastediyor?";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu hatırladı. O, tavernada Orman Şeytanı’na düğün hazırlıklarında yardım ediyordu. Seninle ateş suyu içtik, Tichingitu daha fazlasını istedi. Ve sonra, o kız... çok güzeldi ve... Kaptan, sanırım hatırladım! Tichingitu onunla evlenmek istedi... Bir kano yapıp onu götürmek istedi... Merhametli ruhlar adına! Çok kötü insanlar ateş suyunu getirdi. Belki de şeytanlar ya da kötü ruhlardı! Tichingitu bir daha asla ...";
			link.l1 = "Onu alıp götürmek mi? Kendi kayığını mı yapacaksın?! Ahah, sen tam bir romantiksin dostum... Ha-ha... ha-ha-ha-ha-ha-ha ah, duramıyorum... Gülmekten kendimi alamıyorum!";
			link.l1.go = "Tichingitu_13";
		break;
		
		case "Tichingitu_13":
			dialog.text = "Kaptan, Tichingitu kadını kaçırdı, evet... ama, şey, biz... şimdi evlenmesek olur mu? O... papağan gibi bağırıyor ve... pek de güzel sayılmaz.";
			link.l1 = "Evet dostum, bütün gece eğlenen kadınlar sabah olduğunda perişan bir halde olurlar. Merak etme, kahraman âşık, bir çaresini buluruz. Hadi, Sharptown'a geri dönmemiz lazım, tatil konaklamanı kaçırdın...";
			link.l1.go = "Tichingitu_14";
		break;
		
		case "Tichingitu_14":
			dialog.text = "Bir gemiye çıkma mı? Kaptan daha önce bir savaştan bahsetmişti. Düşünceler hâlâ Tichingitu'ya itaat etmiyor. Kasabada ne oldu?";
			link.l1 = "Karada ve denizde gerçek bir savaş yaşandı. Toplar bütün gece ateş etti sanırım, muhtemelen San Jose'den bile duyulmuştur. Ama sen başka bir 'savaşla' meşguldün, sorun değil, anlıyorum... Hadi, yolda her şeyi anlatırım.";
			link.l1.go = "Tichingitu_15";
		break;
		
		case "Tichingitu_15":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("LH_waitress");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.longhappy_shoregirl1.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl1.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_shoregirl1.function = "LongHappy_ReturnShoreGirl";
		break;
		
		case "Tichingitu_16":
			dialog.text = "Teşekkür ederim, kaptan... Tichingitu asla...";
			link.l1 = "Evet, 'uzak bozkırların aygırı', kesinlikle artık içmemelisin. Git biraz uyu. Ben de zaten yorgunluktan düşmek üzereyim.";
			link.l1.go = "Tichingitu_17";
		break;
		
		case "Tichingitu_17":
			DialogExit();
			npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			LAi_SetImmortal(npchar, false);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			LAi_SetOfficerType(npchar);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			npchar.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_55";
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Tichingitu_18":
			dialog.text = "Kaptan, bir kez daha tebrikler! Tichingitu bu kutlamadan öncekinden daha çok keyif alıyor. Kaptan dostlarını seçmeyi biliyor – burada daha fazla samimiyet, daha az ikiyüzlülük ve daha az peruk var.";
			link.l1 = "Ve çok daha fazla ateş suyu. Bu arada, benimle bir kadeh içer misin? Biliyorum pek hoşlanmıyorsun ama bugün sıradışı bir günümüz var!";
			link.l1.go = "Tichingitu_19";
		break;
		
		case "Tichingitu_19":
			dialog.text = "Tichingitu ateşi suyu sevmez, ama kaptan isterse, bugün olur. Mutluluğunuz için, ve güzelinize! Aynı yolda yürüyün, güneş ve ay yolunuza hep ışık tutsun.";
			link.l1 = "Teşekkür ederim, dostum. Şerefe, Tichingitu! Dostluğumuza!";
			link.l1.go = "Tichingitu_4";
		break;
		
		// губернаторы
		// Сен Пьер
		case "FortFrance_Mayor":
			if (pchar.questTemp.GoldenGirl == "end")
			{
				dialog.text = "Harika ... kutlama, senin adına çok sevindim Charles. Yine de seni hâlâ anlayamıyorum... Eşsiz bir gülü avuçlarında tutup onu... bir kır çiçeğiyle değiştirmek. Ama kalp ne isterse onu ister... Mutlu ol dostum. Bir ömür boyu mutlu yaşa!";
				link.l1 = "Elinde tuttuğun çiçekteki en güzel şey, ona duyduğun his. O his olmadan, sadece solup giden bir et yığını olurdu. Geldiğine sevindim, Ekselansları.";
				link.l1.go = "FortFrance_Mayor_1";
			}
			else
			{
				dialog.text = "Harika bir gün, dostum, ve harika bir vesile! En içten tebriklerimi kabul et! Ben üç kez evlendim ve her seferinde ilk defa gibi titredim, ah, gençlik...";
				link.l1 = "Bayım, yaşlılıktan hâlâ uzaktasınız, cesaretinizi kaybetmeyin. Geldiğiniz için teşekkürler, Jacques!";
				link.l1.go = "Guests_block";
			}
		break;
		
		case "FortFrance_Mayor_1":
			dialog.text = "Bekle, Charles. Beni yanlış anladın, tüm kalbimle gerçekten mutluyum! Ve evet... al, işte burada. Ortak... dostumuz özellikle bugün bunu sana vermemi istedi.";
			link.l1 = "Bunun kimden geldiğini tahmin edebiliyorum. Teşekkür ederim, yakında görüşürüz.";
			link.l1.go = "Guests_block";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2-1");
					else AddQuestRecordInfo("Letter_Marquesa", "1-1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4-1");
					else AddQuestRecordInfo("Letter_Marquesa", "3-1");
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2");
					else AddQuestRecordInfo("Letter_Marquesa", "1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4");
					else AddQuestRecordInfo("Letter_Marquesa", "3");
				}
			}
		break;
		
		// Бас Тер
		case "BasTer_Mayor":
			dialog.text = "Ne hoş bir tören, değil mi Charles? Senin adına gerçekten çok mutluyum! Kendim ve Basse-Terre halkı adına, sana ve... zarif eşine tebriklerimizi sunuyorum. Harika bir çift olmuşsunuz! Bir ömür boyu mutlu yaşayın!";
			link.l1 = "Teşekkür ederim, Ekselansları. Beğenmenize sevindim.";
			link.l1.go = "Guests_block";
		break;
		
		// Порт Принс
		case "PortPax_Mayor":
			dialog.text = "Böylesine harika bir hizmet, monsieur de Maure, gerçekten harika! Ve gelin bu kıyafetle... çok özgün görünüyor. Şehrimizin tüm sakinleri adına - en içten tebriklerimi kabul edin! Size uzun ve mutlu yıllar diliyorum!";
			link.l1 = "Teşekkür ederim, Ekselansları.";
			link.l1.go = "Guests_block";
		break;
		
		// Тортуга
		case "Tortuga_Mayor":
			dialog.text = "Ne kadar da zarif – siz ve gelininiz, monsieur de Maure, gerçekten çok özeldiniz! Fakat siz zaten sıra dışı bir adamsınız. Size uzun ve mutlu bir evlilik hayatı diliyorum. Bir ömür boyu mutlu yaşayın!";
			link.l1 = "Sana gerçekten minnettarım, Ekselansları.";
			link.l1.go = "Guests_block";
		break;
		
		// д'Ойли
		case "PortRoyal_Mayor":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_03.wav");
			dialog.text = "Düğününüz uğruna Karayipler'i aşmaya değdi! Tüm İngiliz kolonileri adına tebrikler, kaptan! Siz ve gelininiz—pardon, artık eşiniz—harika bir çiftsiniz!";
			link.l1 = "Ziyaretiniz ve nazik sözleriniz için teşekkür ederim, Albay!";
			link.l1.go = "Guests_block";
		break;
		
		// Исла Тесоро
		// Тиракс
		case "Terrax":
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "Ve bu evli süslü adam benim korsan sahilimde ne arıyor, ha?! Söylesene, monsieur, eski dostum - o sert Korsan Charlie Prince'e ne yaptın?";
					link.l1 = "Charlie Prince öldü, hatırlıyorsun değil mi Marcus... Ha-ha-ha, buraya gel, deniz şeytanı! Seni görmek ne güzel! Nasılsınız burada, herkes toplandı mı?";
					link.l1.go = "Terrax_1_1";
				}
				else // 28-03-20
				{
					dialog.text = "Ve bu evli süslü adam benim korsan sahilimde ne arıyor, ha?! Söyle bakalım, monsieur, eski dostum - sert Kaptan Charles de Maure'a ne yaptın?";
					link.l1 = "Ah, Marcus, seni görmek de beni mutlu etti! Nasılsınız burada, herkes toplandı mı?";
					link.l1.go = "Terrax_1";
				}
			}
			else
			{
				dialog.text = "Ve bu evli süslü adam benim korsan sahilimde ne arıyor, ha?! Söyle bakalım, monsieur, eski dostum sert Kaptan Charles de Maure'a ne yaptın?";
				link.l1 = "Ah, Marcus, seni görmek de güzel! Nasılsınız burada, herkes toplandı mı?";
				link.l1.go = "Terrax_1";
			}
		break;
		
		case "Terrax_1":
			dialog.text = "Evet, Orman Şeytanı daha dün geldi ve hemen emirler yağdırmaya başladı - yani misafirler burada ve kutlama için her şey hazır. Gemin kayalıkların yakınında görüldü, çocuklar da dayanamadı - doğruca meyhaneye daldılar ve muhtemelen çoktan o Hawk'un fıçısını açtılar bile. Acele et, belki hâlâ bir kadeh paylaşma şansımız vardır - Nathaniel bunun özel bir rom olduğunu övüp duruyordu!";
			link.l1 = "İşte böyle yapıyoruz - gemiden doğruca partiye! Eşim gelsin, hemen arkandayız Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_1_1":
			dialog.text = "Evet, Orman Şeytanı daha dün geldi ve hemen emirler yağdırmaya başladı – misafirler burada ve kutlama için her şey hazır. Gemin kayalıkların yakınında görüldü, çocuklar da kendilerini tutamadı – doğruca meyhaneye daldılar ve muhtemelen çoktan o Hawk'ın fıçısını açtılar. Acele et, belki hâlâ bir kadeh içme şansımız vardır – Nathaniel bunun özel bir rom olduğunu övünerek anlattı!";
			link.l1 = "İşte böyle yapıyoruz - gemiden doğruca partiye! Ben hayatımın aşkını bekleyeceğim ve hemen arkandayız, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_2":
			DialogExit();
			DoQuestReloadToLocation("Pirates_tavern", "reload", "reload1", "LongHappy_IslaTesoroTavern");
		break;
		
		case "Terrax_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles de Maure ile evlendim - hâlâ alışamadım... Önce Svenson, şimdi sen - sonra kim? Papaz Marlow mu, yoksa İyi Kalpli Jacques mı?";
			link.l1 = "Şahinleri unuttun. Peki ya sen, Marcus? Yalnız bir deniz kurdu olmaktan bıkmadın mı?";
			link.l1.go = "Terrax_4";
		break;
		
		case "Terrax_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				dialog.text = "Dannie ve Nathan uzun zamandır bilinen bir mesele - ben artık kabullendim, ama sen beni gerçekten şaşırttın, söylemeliyim! Yine de Orman Şeytanı'nın çırağı tam bir güzellik - gerçekten, hem lafıyla hem de tabancasıyla her zaman hazır, fırtınalara göğüs gerebilecek biri. Daha değerli bir kadın bulman pek mümkün değil. Şanslısın kaptan - ona iyi bak!";
			}
			else
			{
				dialog.text = "Dannie ve Nathan eski bir mesele - buna çoktan alıştım, ama sen beni gerçekten şaşırttın, söylemeliyim! Gerçi, duyduğuma göre senin Mary kılıçlardan iyi anlıyor ve onları kullanmayı da biliyor - saygılarımı sunarım! Gerçek bir silah arkadaşı. Sana bir sır vereyim, böyle bir kız için ben bile bekar kalma kararımı tekrar gözden geçirebilirim. Şanslı adamsın kaptan - ona iyi bak!";
			}
			link.l1 = "Biliyorum, o bir mucize ve ben yine mutluluktan yedinci cennetteyim - tıpkı ilk tanıştığımız günlerdeki gibi!";
			link.l1.go = "Terrax_5";
		break;
		
		case "Terrax_5":
			dialog.text = "O halde, bir kadeh kaldıralım!... Aşka!... Ama bizi eşiğin ötesine, ufka sürükleyen aşka değil!... Bizi bu eşikte bekleyen aşka! Bizi dünyanın öbür ucundan, altın dağlardan bile geri çeken aşka! Onunla yaşa ve mutlu ol!";
			link.l1 = "Harika bir kadeh kaldırdın Marcus, teşekkürler!";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6_1":
			dialog.text = "Şerefe, evliliğine, dostum!";
			link.l1 = "Teşekkür ederim, Marcus...";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6":
			DialogExit();
			npchar.dialog.currentnode = "Terrax_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Terrax_7":
			dialog.text = "Jacques? Bu kesinlikle iyi değil...";
			link.l1 = "Marcus, sence...";
			link.l1.go = "Terrax_8";
		break;
		
		case "Terrax_8":
			dialog.text = "Zaman yok! Kapıların arkasındalar! Herkes silah başına!";
			link.l1 = "Başlıyoruz!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernFight");
		break;
		
		case "Terrax_9":
			dialog.text = "Bir partide en son ne zaman bu kadar eğlendiğimi hatırlamıyorum! Daha bitmedi! Duyuyor musun? Dışarıda birileri ateş ediyor! Hadi sokakları onların kanıyla dolduralım!";
			link.l1 = "Bekle! Bunlar da kim!? Ve ne halt etmeye buradalar?!";
			link.l1.go = "Terrax_10";
		break;
		
		case "Terrax_10":
			DialogExit();
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		// Натаниэль Хоук
		case "Nathaniel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Evli Kaptan de Maure, bir kadeh kaldırmak için bundan daha hakiki bir sebep bulmak zordur. Kaldırın bardaklarınızı – bu sıradan bir lahana içkisi değil. Doğu Hindistan'dan siyah çayla demlenmiş ve gerçek İran baharatlarıyla tatlandırılmış!";
			link.l1 = "Ve boğazımda erimiş kurşun içmişim gibi neden yanıyor diye merak ediyordum. Neyse, Nathan, şerefe...";
			link.l1.go = "Nathaniel_1";
		break;
		
		case "Nathaniel_1":
			dialog.text = "Bekleyin, önce bir kadeh kaldıralım! Hey, beyler, kupalarınızı kaldırın! Bugün, dostumuz ve ortağımız Charles de Maure aile hayatına adım atıyor. Bizden en derin başsağlığı dilekle... ah, Dannie, lütfen silahı indir! Tabii ki tebrikler! Artık aynı geminin yelkenlerisiniz, öyleyse onu her fırtınadan en bereketli kıyılara sürün!";
			link.l1 = "Teşekkür ederim, Nathan, içtenlikle. Sen ve Danielle bizim için örnek alınacak insanlarsınız.";
			link.l1.go = "Nathaniel_2";
		break;
		
		case "Nathaniel_2":
			dialog.text = "Bunu duymak güzel. Karımla ben belki dünyanın en iyi çifti değiliz, ama birlikte mutluyuz ve sen bizim için çok şey yaptın, bu yüzden bana sorarsan, artık ailemin bir parçasısın ve ne zaman bana ihtiyacın olursa burada olacağım. Mutlu ol, lütfen bir içki al!";
			link.l1 = "Hadi içelim o zaman! Ah... bu rom Kutsal Engizisyon'un cephaneliğinde yerini almalı. Kahretsin! İçimden aşağıya kadar yakıyor... aghhh! Ohh!... Sevdim bunu!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_3":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_3_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Nathaniel_3_1":
			dialog.text = "Sen tıpkı yirmi yıl önceki Dannie ve bana benziyorsun!";
			link.l1 = "Bir bardak daha, Nathan!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Ne!? Jan seni şarap getirmek için mahzene mi gönderdi? Hadi biraz yürüyelim, sana yardım ederim, biraz temiz hava da ikimize iyi gelir.";
			link.l1 = "Ama Dannie ve  "+sld.name+"? Jan bana onların konuşmaya gittiklerini söyledi.";
			link.l1.go = "Nathaniel_5";
		break;
		
		case "Nathaniel_5":
			dialog.text = "Evet, Dannie en iyi silah arkadaşının bile varlığının talihli beyefendilere tam anlamıyla rahatlama fırsatı vermeyeceğini biliyor. Bu yüzden aldıkları tüm iltifatları dinlediler ve erkeklerin eğlenmesi için konağa gittiler.";
			link.l1 = "Pekâlâ, haydi gidelim! Birkaç kupa içmeyi başardım ama kahretsin, şimdi gerçekten güzelce sarhoş olmanın zamanı geldi!";
			link.l1.go = "Nathaniel_6";
		break;
		
		case "Nathaniel_6":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableFastReload = true;//закрыть переход
			pchar.quest.longhappy_isla_vine.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_vine.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_isla_vine.function = "LongHappy_IslaTesoroToAlexus";
		break;
		
		case "Nathaniel_7":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "İşte sandık burada. Taşıyabildiğimiz kadarını alıp hemen geri dönüyoruz, yoksa bu huysuz ihtiyar bizi burada kilitlemeden önce.";
			link.l1 = "Abartıyorsun, Nathan. O kadar da kötü biri değil... Bekle, bunu duydun mu?";
			link.l1.go = "Nathaniel_8";
		break;
		
		case "Nathaniel_8":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Jan muhtemelen daha fazla adam bulup bize yardım etmeleri için göndermiştir. Kahretsin!";
			link.l1 = "Hadi, şişeleri şans getirsin diye kırıyoruz. Bir tane daha al ve gidelim.";
			link.l1.go = "Nathaniel_9";
		break;
		
		case "Nathaniel_9":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				sld.dialog.currentnode = "Tichingitu_8";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else LongHappy_SetBandosInDungeon();
		break;
		
		case "Nathaniel_10":
			dialog.text = "Ne oluyor burada, kim bu herifler? Hiçbir şey anlıyor musun, Charles?";
			link.l1 = "Bilmiyorum, Nathan, ama onlardan biri yardım getirmeye koştu ve daha fazla ayak sesi duyuyorum gibi geliyor. Hemen meyhaneye dönmeliyiz!";
			link.l1.go = "Nathaniel_11";
		break;
		
		case "Nathaniel_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			pchar.quest.longhappy_totavern.win_condition.l1 = "location";
			pchar.quest.longhappy_totavern.win_condition.l1.location = "Pirates_tavern";
			pchar.quest.longhappy_totavern.function = "LongHappy_TavernAlarm";
		break;
		
		case "Nathaniel_12":
			LongHappy_TownRepose();
			dialog.text = "Bu alçakları yere serdik, ama denizden topların gürlediğini duyuyor musun? Sadece iki tayfamız savaşa hazır, Marcus'un fırkateyninde ve Jan'ın korvetinde. Ben, Dannie ve diğerleri adamlarımızı karaya çıkardık – düğün sonuçta – yani Centurion devre dışı. Peki ya senin gemin? Ne yapacağımıza karar vermeliyiz, hem de hemen!";
			link.l1 = "Mürettebatın yarısını karaya çıkardım, umarım geri kalanı ayıktır. Ama önce eşimi bulup iyi olduğundan emin olmam gerek.";
			link.l1.go = "Nathaniel_13";
		break;
		
		case "Nathaniel_13":
			dialog.text = "Evet, Dannie de ortalarda yok. O zaman şöyle yapıyoruz - Tyrex ve Svenson limana çoktan koştular, teknelerle gemilerine ulaşacaklar. Biz eşler için konağa gidiyoruz, kalanlar ise kıyıda savunmayı organize etmeli. Subaylarından birkaçını geminde insan toplamak için gönderebilir misin? Orada yardım kesinlikle işe yarar.";
			link.l1 = "Pekala, herkes, hadi hareket edin! Her saniye önemli!";
			link.l1.go = "Nathaniel_14";
		break;
		
		case "Nathaniel_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		break;
		
		case "Nathaniel_15":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Daha hızlı, yukarı! Dannie ve "+sld.name+" orada olmalı! Ve eğer o alçaklar onlara zarar verdiyse...";
			link.l1 = "Bunu aklından bile geçirme! Yukarı! Hadi gidelim!";
			link.l1.go = "Nathaniel_16";
		break;
		
		case "Nathaniel_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_townhall", "reload1_back", true);
			pchar.quest.longhappy_isla_bedroom.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_bedroom.win_condition.l1.location = "Location_reserve_04";
			pchar.quest.longhappy_isla_bedroom.function = "LongHappy_IslaTesoroBedroom";
		break;
		
		case "Nathaniel_17":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Kahretsin! Arkadaşın, o alçak kızlara ateş etmesin diye silaha doğru atıldı!";
			link.l1 = "Ve kurşun yedi... Bekle, Nathan... nefes alıyor! Hâlâ hayatta! Kahretsin, Gino'ya ihtiyacım var! "+sld.name+", tatlım, nasılsın?";
			link.l1.go = "Nathaniel_18";
		break;
		
		case "Nathaniel_18":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_19";
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_7_1";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Nathaniel_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "İyiyiz Charles! Onu çözeceğim. Limanda silah sesleri duyuyorum - sen ve Nathan oraya gitmelisiniz, yoksa Barbazon bütün gemilerimizi yok edecek. Zaman kaybetmeyin!";
			link.l1 = "Gino'yu bulup buraya göndereceğim, o yardımcı olur ... olmalı! "+sld.name+"Sevgilim, burada kal, ona göz kulak olun, ikiniz de.";
			link.l1.go = "Nathaniel_19";
		break;
		
		case "Nathaniel_19":
			dialog.text = "Charles, acele et! Ne karar vereceksen ver, çünkü artık zaman altın değerinde! Eğer Jacques'in gemileri kıyıya ulaşırsa, her şey boşa gidecek!";
			link.l1 = "Evet, biliyorum. Kahrolası herif!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Nathaniel_20":
			dialog.text = "Daha hızlı, konuşacak vaktimiz yok!";
			link.l1 = "";
			link.l1.go = "Nathaniel_20_1";
		break;
		
		case "Nathaniel_20_1":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_20";
		break;
		
		case "Nathaniel_21":
			dialog.text = "Kahretsin! Affet beni, Charles. Yukarıda sıkışıp kaldık, bir düzine o alçak vardı... Keşke zamanında yetişebilseydim, ama görüyorum ki durumu en iyi şekilde halletmişsin.";
			link.l1 = "Bunu yapmak kolay olmadı, ama o 'iyi adamı' öldürmekten inanılmaz bir zevk aldım! Artık karaya çıkma zamanı, Nathan. İnsanlarımız orada bizi bekliyor!";
			link.l1.go = "Nathaniel_22";
		break;
		
		case "Nathaniel_22":
			dialog.text = "Evet, Hintli çocuğunu ziyaret etmemiz gerek, burada işimizi bitirip sonra Sharptown'a gidelim.";
			link.l1 = "Haklısın, hemen arkandayım.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Nathaniel_23";
			else link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_23":
			dialog.text = "Bu arada, Marcus'u bulduk! Kargo ambarındaydı, elleri bağlı ve baygındı.";
			link.l1 = "Hayatta mı?";
			link.l1.go = "Nathaniel_24";
		break;
		
		case "Nathaniel_24":
			dialog.text = "Durumu pek iyi değil, ama merak etme, iyi olacak. Tyrex demirden daha sağlamdır, o yüzden endişelenme; zaten gemine alındı ve bir pala istedi.";
			link.l1 = "Nihayet, güzel bir haber! Tamam, burada işimizi bitirip geri dönelim.";
			link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		// Даниэль Хоук
		case "Danielle":
			dialog.text = "Merhaba, Charles. Bir bakayım sana – daha da yakışıklı olmuşsun, şikayet edemem! Neredeyse Nathan gibi, on yıl önceki haliyle! Hadi, içeri gel, kapıda durma, herkes seni bekliyordu!";
			link.l1 = "Teşekkür ederim, Dannie, seni gördüğüme çok sevindim! Birazdan sana ve Nathan'a uğrayacağım, sonra konuşuruz!";
			link.l1.go = "Danielle_1";
		break;
		
		case "Danielle_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "tables", "stay1", "LongHappy_DannyNorm", -1); 
		break;
		
		case "Danielle_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, otur lütfen - Nathan ve ben senin adına çok mutluyuz! Marcus, Jan ve kocam senin için bir şeyler hazırladı - ama hediyeler biraz bekleyecek. Şimdilik, seni tebrik etmek ve mutluluklar dilemek istiyorum! Sevgilin gerçekten harika biri! Söylesene, Martinique'te ona beyaz bir elbise giydirmeyi başaramadın, değil mi?";
			link.l1 = "Teşekkürler, Dannie. Evet, elbiseyle ilgili olanlar oldukça eğlenceli sonuçlandı – eminim düğünümüz yüksek sosyetede epeyce dedikoduya yol açmıştır. Herkes kibarca bakışlarını kaçırdı ve sanki hiçbir tuhaflık olmuyormuş gibi davrandı. Görgü kuralları işte – ama dedikodular umurumda değil, onu seviyorum ve en önemlisi de bu.";
			link.l1.go = "Danielle_3";
		break;
		
		case "Danielle_3":
			dialog.text = "Kesinlikle haklısın! Ben de aynı şekilde, kuşak arkasında bir kılıç ve bir çift tabancayla sunağa yürüdüm. Ama bu Port Royal'deydi, daha orası saygın bir koloni yerleşimi olmadan önce. O zamanlar öyle bir eğlence vardı ki, Levasseur zamanında Tortuga'dan bile fazlaydı, kimse de şaşırmazdı... eh. Neyse, ben hep konuşuyorum - git, konukların arasında dolaş, herkes seni burada bekliyordu, bana da bir sarıl!";
			link.l1 = "Ah Dannie, sana nasıl hayır diyebilirim ki, ha-ha! Karım ve ben seni ve arkadaşlarını gördüğümüze öyle sevindik ki, anlatamam!";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_4":
			DialogExit();
			npchar.dialog.currentnode = "Danielle_4_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Danielle_4_1":
			dialog.text = "Çok yakışıyorsunuz, Charles!";
			link.l1 = "Teşekkürler, Dannie...";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_5":
			dialog.text = "Charles, o haklı... başka seçeneğin yok. Jacques the Kindman'ın Tyrex ve diğerleriyle işini bitirdikten sonra merhamet göstereceğine inanmıyorum. Ne yapman gerektiğini biliyorsun.";
			link.l1 = "";
			link.l1.go = "Danielle_6";
		break;
		
		case "Danielle_5_1":
			dialog.text = "Ona kulak verme! Eğer Kingman böyle bir delilik yapmaya karar verdiyse, kimseyi sağ bırakmaz!";
			link.l1 = "";
			link.l1.go = "Danielle_6_1";
		break;
		
		case "Danielle_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_39";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_6_1":
			DialogExit();
			sld = characterFromId("LH_Dussak");
			sld.dialog.currentnode = "Dussak_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_7_1":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "İyiyiz Charles! Onu çözeceğim. Limandan top sesleri geliyor, sen ve Nathan hemen oraya gitmelisiniz, yoksa Barbazon gemilerimizi fıçıdaki ördekler gibi batırır. Bir dakika bile kaybetmemelisiniz!";
			link.l1 = "Gino'yu bulup buraya göndereceğim, o yardımcı olur ... olmalı, kahretsin! "+sld.name+", canım, burada kal ve Tichingitu'ya göz kulak ol.";
			link.l1.go = "Danielle_8_1";
		break;
		
		case "Danielle_7":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nathan, hayır!!!";
			link.l1 = "O anda fırsatı yakaladı ve seni korumak için topa koştu, Dannie... "+sld.name+", tatlım, nasılsın?";
			link.l1.go = "Danielle_8";
		break;
		
		case "Danielle_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_41";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_8_1":
			DialogExit();
			sld = characterFromId("Nathaniel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_9":
			dialog.text = "Evet, Charles, hayatta! Kalbi zar zor atıyor ama yaşıyor! Ne yapmalıyız?!";
			link.l1 = "Gino'ya hemen ihtiyacımız var! Onu bulup buraya göndereceğim, o yardım edecek... etmesi gerek!";
			link.l1.go = "Danielle_10";
		break;
		
		case "Danielle_10":
			dialog.text = "Charles, vaktimiz yok! Eğer Jacques'in gemileri kıyıya ulaşırsa, her şey boşa gidecek! Kocam... yapması gerekeni yaptı. Şimdi sıra sende. Ben onun yanında kalacağım. Siz ikiniz gidip Gino'yu bulun!";
			link.l1 = "Evet, biliyorum. O kahrolası herif, bunun bedelini ödeyecek!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Danielle_11":
			dialog.text = "Sonunda geldin! Herkes iyi mi?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				link.l1 = "İyiyiz, Dannie, merak etme. Jacques öldü, gemileri denizin dibinde. Tichingitu nasıl?";
				link.l1.go = "Danielle_17";
			}
			else
			{
				link.l1 = "İyiyiz Dannie, merak etme. Jacques öldü, gemileri denizin dibinde. Nathan nasıl?";
				link.l1.go = "Danielle_12";
			}
		break;
		
		case "Danielle_12":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "O iyi! İtalyan doktorun tam bir deha! Nathan yukarıda uyuyor ama Gino'ya göre ona hiçbir şey olmayacak. Bir iki hafta yatakta dinlenme, kırmızı şarap ve, Gino'nun dediği gibi, 'kendisine iyi niyetli bir hanımefendinin ziyareti' öhöm... Yani, her şey yolunda, bizi yine kurtardın Charles, sana nasıl teşekkür edebilirim?";
				link.l1 = "Karımı ve seni kurtaran Nathaniel'di. Bunun için ona sonsuza dek minnettar kalacağım. İyileştiğini duymak beni öyle mutlu etti ki, anlatamam. Bırak biraz dinlensin, sonra tekrar uğrar bakarım.";
				link.l1.go = "Danielle_13";
			}
			else
			{
				dialog.text = "Durumu iyi, kurşun vücudunu delip geçmiş, üstelik 'Centurion'dan gelen cerrahımız da yakındaydı. Bütün bu karmaşadan saklanıyordu. Yani Nathan yaşayacak, birkaç hafta yatakta kalacak - önemsiz bir mesele!";
				link.l1 = "Dannie, karımı ve seni bir kurşundan korudu, bunun için ona sonsuza dek minnettar olacağım. İyileştiğini duymak beni öyle mutlu etti ki anlatamam. Bırak dinlensin, sonra yine uğrarım.";
				link.l1.go = "Danielle_14";
			}
		break;
		
		case "Danielle_13":
			dialog.text = "Elbette! Ama şimdi gitmem gerek, kocamın yanına dönmeliyim... Arkadaşınızı ödünç almamıza bir sakınca var mı? Nathan iyileştiğinde, onu bizzat Antigua'ya getireceğim. Centurion mucizevi bir şekilde hayatta kaldı, sadece yeni bir mürettebat toplaması gerekiyor.";
			link.l1 = "Peki Dannie, Gino ve Nathan'a selam söyle. Ben artık gitmeliyim.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_14":
			dialog.text = "Elbette, Charles, ama... Kötü bir haberim var. Düğününde olan o İtalyan, Guineili... Cesedi meyhanedeki bir odada bulundu. Ben... Üzgünüm, Charles.";
			link.l1 = "Ne? Gino mu?! Hayır! Nasıl?";
			link.l1.go = "Danielle_15";
		break;
		
		case "Danielle_15":
			dialog.text = "Bilmiyorum, muhtemelen kasabayı basan ve yeraltı mezarlarından geçen o alçaklardan biri. Görünüşe göre orada saklanıyorlarmış, kaçmak için fırsat kolluyorlarmış ve onu bulmuşlar...";
			link.l1 = "Kahretsin! Hayır, inanamıyorum...";
			link.l1.go = "Danielle_16";
		break;
		
		case "Danielle_16":
			pchar.questTemp.LongHappy.Jino_died = "true";
			dialog.text = "Üzgünüm Charles. Bu tam bir katliamdı ve o bir savaşçı değildi... İsterseniz, cenazesini geminize gönderelim, böylece onu memleketine götürüp layıkıyla defnedebilirsiniz. Gerçekten çok üzgünüm...";
			link.l1 = "Teşekkür ederim, Dannie. Cesedi bir gemiye yüklemelerini emret. Şimdi gitmeliyim... Düşünmem gerek. Ve Nathan’a selam söyle.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_17":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "İyi durumda! O İtalyan doktorun tam bir dahi! Yukarıdaki odada uyuyor, Gino da ona göz kulak oluyor. Diyor ki, 'bir iki haftaya toparlar'.";
				link.l1 = "Harika haber! Sanırım onu hemen ziyaret edemem, değil mi?";
				link.l1.go = "Danielle_18";
			}
			else
			{
				dialog.text = "Çok üzgünüm, Charles. Centurion'dan cerrahımızı buldum ama o da bir şey yapamadı... Arkadaşın birkaç saat önce hayatını kaybetti.";
				link.l1 = "Tichingitu?! Hayır! Buna inanamam!!!";
				link.l1.go = "Danielle_19";
			}
		break;
		
		case "Danielle_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Hayır, İtalyan kesinlikle rahatsız edilmemesini, dinlenmesini istedi, ve bunca endişeden sonra Gino'nun da dinlenmesi gerek. Hatta ben bile söyledim "+sld.name+" dışarı çıkıp biraz yürüyelim dedik, her şeyin yoluna gireceğini öğrendiğimizde\nBir de... arkadaşın, beni kurşundan korudu. Ona nasıl teşekkür edeceğimi bile bilmiyorum. Lütfen ona söyle, artık o da ailemizin bir parçası. Ve sen – yine bizi kurtardın, Charles!";
			link.l1 = "Her şey iyi biterse iyidir, Dannie. Nathan'a git, seni bekliyor, ben de burada biraz dinlenip kendi işime bakacağım "+sld.name+".";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_19":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Üzgünüm, elimden gelen her şeyi yaptım, ve "+sld.name+", o da. Bizi o kurşundan korudu, ve bunu asla unutmayacağım, inan bana.";
			link.l1 = "...   Uzun zaman önce benim için öleceğini söylemişti... Sanırım, bir gün hepimiz için hayatını feda edeceğini hiç düşünmemişti... Ve şimdi bir kahraman oldu, ben de onu bundan daha azıyla hatırlamayacağım... Nerede "+sld.name+"? O iyi mi?";
			link.l1.go = "Danielle_20";
		break;
		
		case "Danielle_20":
			dialog.text = "Öyle diyemem... Yani, fiziksel olarak evet. Ama... biliyorsun... Dışarı çıkıp biraz hava almak istediğini söyledi. Muhtemelen seni demirlemiş görünce fark etmiştir ve yakında döner.";
			link.l1 = "Sana lanet olsun, Jacques Barbazon... Onu daha önce öldürmeliydik!";
			link.l1.go = "Danielle_21";
		break;
		
		case "Danielle_21":
			dialog.text = "Bekle... daha bitmedi. O İtalyan, Guineili, değil mi? O sessiz genç adam. O... cesedi bir meyhanede bulundu... Bilmiyorum, muhtemelen kasabaya saldırıp yeraltı geçitlerinden geçen o alçaklardan biriydi. Görünüşe göre orada saklanıyorlarmış, kaçmak için fırsat kolluyorlarmış ve onu bulmuşlar...";
			link.l1 = " Gino da mı?! Bugün gerçekten de uğursuz bir gün...";
			link.l1.go = "Danielle_22";
		break;
		
		case "Danielle_22":
			pchar.questTemp.LongHappy.Tichingitu_died = "true";
			dialog.text = "Üzgünüm, Charles... İstersen, cesetlerini gemine göndeririz, adamlarını memleketlerine götürüp hak ettikleri gibi gömeriz. Gerçekten çok üzgünüm...";
			link.l1 = "Teşekkürler, Dannie. Yap bunu... Gitmeliyim... Düşünmem... gerek.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		// Додсон
		case "Dodson":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, bu düğününle kaç kızın kalbini kırdığını hayal edebiliyor musun? Evet, takımadadaki kızların yarısı düğününden sonra yas tutmuş olmalı, haha!";
			link.l1 = "Ne yapabilirim ki - sadece birine ihtiyacım vardı ve onu aldım. Ama kızların üzülmesi için henüz erken, çünkü hâlâ seni, Stiven, yanlarında bulacaklar.";
			link.l1.go = "Dodson_1";
		break;
		
		case "Dodson_1":
			dialog.text = "Ve bu doğru! Burayı bitirelim, sonra onlarla hemen ilgileneceğim, kahretsin! Hadi Charles, şansına ve aile hayatına içelim. Yani, derler ya, sonsuza dek mutlu yaşayın!";
			link.l1 = "Teşekkür ederim, dostum!";
			link.l1.go = "Dodson_2";
		break;
		
		case "Dodson_2":
			DialogExit();
			npchar.dialog.currentnode = "Dodson_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Dodson_2_1":
			dialog.text = "Mutlu bir aile hayatına, ha-ha!";
			link.l1 = "Şerefe!";
			link.l1.go = "Dodson_2";
		break;
		
		// Венсан
		case "Vensan":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, bu evliliğinle kaç kızın kalbini kırdığını hayal edebiliyor musun? Evet, takımadadaki kızların yarısı düğününden sonra yas tutmuştur, haha!";
			link.l1 = "Ne yapabilirim ki - sadece birine ihtiyacım vardı ve onu aldım. Ama kızların üzülmesi için henüz erken, çünkü hâlâ seni, Bernard, yanlarında bulacaklar.";
			link.l1.go = "Vensan_1";
		break;
		
		case "Vensan_1":
			dialog.text = "Ve bu doğru! Burayı bitirelim, sonra onlarla hemen ilgileneceğim, kahretsin! Hadi Charles, şansına ve aile hayatına içelim. Yani, derler ya, sonsuza dek mutlu yaşa!";
			link.l1 = "Sonsuza dek mutlu yaşadılar!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_2":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_2_1":
			dialog.text = "Mutlu bir aile hayatı için, ha ha!";
			link.l1 = "Harika kadeh!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Ha, Charles, demek sen de evlenip sıkıcı biri oldun, tıpkı bizim eski Nathan gibi! Çılgın maceralar ve her şey artık geçmişte kaldı, öyle mi? Tam bir aile babası olmuşsun!";
			link.l1 = "Bekle bakalım, Bernard! Karım, bir aile harabesinin penceresinin altında oturmaktan sıkılacak kadınlardan değildir! Değişecek tek şey, buradan Curaçao'ya kadar genelev kızlarının keselerinin doluluğu olacak!";
			link.l1.go = "Vensan_4";
		break;
		
		case "Vensan_4":
			dialog.text = "Bence büyük bir kayıp değil! Bir torba bakırdan iyidir bir altın para. Hadi içelim! Sana ve eşine şerefe! Altınını iyi sakla ve mutlu ol!";
			link.l1 = "Teşekkür ederim, Bernard. Ah, bu gerçekten sert bir rommuş. Vay be!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_5":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_5_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_5_1":
			dialog.text = "Gelinine, yani, artık karın olan kadına!";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_6":
			dialog.text = "Tam zamanında geldin, Charles, teşekkür ederim!";
			link.l1 = "Burada ne eğlence var? Limanda gemilere yükleniyor olmanız gerekmiyor muydu zaten?";
			link.l1.go = "Vensan_7";
		break;
		
		case "Vensan_7":
			dialog.text = "Marcus beni sahilde savunmayı organize etmem için bıraktı. Adamımız az, limandaki çocukların baruta ihtiyacı var. Uğrayıp birkaç varil alayım dedim ... ve sonra bu serseriler çıkageldi. Hah, saklanıyorlarmış herhalde, bekleyip durumu atlatmayı ya da birini soymayı umuyorlardı. Üstelik hâlâ Hawk'ın romuyla doluyum, yani sen olmasaydın, hâlâ hayatta olur muydum bilmiyorum.";
			link.l1 = "Her zaman hoş geldin. Peki Bernard, kasabanın güvende olduğundan emin ol, ben de gitmeliyim. Kendine dikkat et!";
			link.l1.go = "Vensan_8";
		break;
		
		case "Vensan_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.LongHappy.Vensan_alive = "true";
		break;

		// Джино
		case "Jino":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Kaptan, sizi ve sevgilinizi bu mutlu gününüzde içtenlikle tebrik ederim! Hep mutlu olun ve birbirinize iyi bakın!";
			link.l1 = "Teşekkürler, Gino. Geldiğine sevindim! Umarım buranın... renkleri seni rahatsız etmez?";
			link.l1.go = "Jino_1";
		break;
		
		case "Jino_1":
			dialog.text = "Bu... gerçekten öğretici bir yolculuk. Şunu söylemeliyim ki - uzun zamandır Antigua'dan dışarı çıkmamıştım ve bu toplumda kendimi rahat hissetmek kolay değil. Ama sen insanları anlamayı hep bilirdin, bu yüzden sana güvendiğim için sakin kalmaya çalışacağım.";
			link.l1 = "Belki de daha sert bir şey içmelisin? Rahatla ve konuşacak birini bul?";
			link.l1.go = "Jino_2";
		break;
		
		case "Jino_2":
			dialog.text = "Thank you, captain, I've had enough watered wine. Alcohol, I must warn you, is not very good for the liver and possibly the heart. As for conversation, I tried to discuss the healing properties of Chirik-Sanango with that gentleman over there; it is also called Manaka. The natives of Maine use it for...";
			link.l1 = "Let me guess - that gentleman couldn't handle the discussion? Gino, for my sake and just for today - try the rum that Jan over there is pouring at the counter. If you can guess all its ingredients, Nathaniel Hawk, over there, will be extremely impressed. I am sure he will be glad to have your company, as will Svenson, the man at the counter; both of them respect educated people.";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_3":
			DialogExit();
			npchar.dialog.currentnode = "Jino_3_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
				{
					sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Baker") != -1)
					{
						sld = characterFromId("Baker");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						if (GetCharacterIndex("Tichingitu") != -1)
						{
							sld = characterFromId("Tichingitu");
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
						else
						{
							sld = characterFromId("Mary");
							sld.dialog.currentnode = "LongHappy_57";
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
					}
				}
			}
			else if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Jino_3_1":
			dialog.text = "Sağlığınıza ve zarif eşinizin sağlığına!";
			link.l1 = "Teşekkür ederim, dostum!";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_4":
			dialog.text = "Kaptan, sizsiniz, Tanrı'ya şükür! O maskeli insanlar... Onları gördüm ve buraya saklandım, kapıyı kırmaya çalıştılar...";
			link.l1 = "Tamam Gino, artık kimse sana zarar vermeyecek. Seni bulmam büyük şans, yardıma ihtiyacım var. Arkadaşım yaralı - vuruldu ve çok kan kaybetti. Acele etmeliyiz!";
			link.l1.go = "Jino_5";
		break;
		
		case "Jino_5":
			dialog.text = "Kurşun... kan... İyiyim, kaptan. Buraya gelirken, yaralanma ihtimaline karşı bütün aletlerimin olduğu tıbbi sandığımı yanıma aldım. Beni ona götür, neler yapabileceğime bakayım. Ve o... maskeli adamlar, belki de başka bir yere saklandılar?";
			link.l1 = "Eminim onlar sonuncusuydu. Gino, limanda bir çatışma var ve hemen oraya gitmem lazım. Sen de rezidansa kendi başına gitmelisin, uzak değil. Büyük ev köşede - gözünden kaçmaz. Korkma - sokaklar bizim insanlarımızla dolu, ve lütfen acele et, yalvarıyorum!";
			link.l1.go = "Jino_6";
		break;
		
		case "Jino_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 7.0);
			LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", false);
			pchar.questTemp.LongHappy.Jino_alive = "true";
			AddQuestRecord("LongHappy", "18");
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sld = characterFromId("Tichingitu");
			else sld = characterFromId("Nathaniel");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName1", sTemp);
		break;
		
		case "Jino_7":
			dialog.text = "Kaptan, bu uğurlu günde sizi ve sevdiğinizi tüm kalbimle tebrik ederim! Mutlu olun ve birbirinize iyi bakın.";
			link.l1 = "Teşekkürler, Gino. Gelmeye karar verdiğine sevindim! Umarım yolculuğun sorunsuz geçti?";
			link.l1.go = "Jino_8";
		break;
		
		case "Jino_8":
			dialog.text = "Her şey yolunda, kaptan, ilginiz için teşekkür ederim. Şunu söylemeliyim ki - uzun zamandır Antigua'dan dışarı çıkmamıştım ve seçkinler arasında... pek rahat hissetmiyorum. Ama buraya gelmemin sebebi bana başka bir seçenek bırakmadı. Bu arada - hizmet harikaydı, ikiniz adına da çok sevindim! Gelin bu kıyafetle çok zarif görünüyor - bu yeni bir moda mı? Hayatı yaşamaktan biraz geri kalmışım gibi görünüyor, ama hoşuma gitti, gerçekten.";
			link.l1 = "Moda... Bir bakıma evet, ya da en azından yakında öyle olacak. Peki, iyi eğlenceler Gino, eğer soylu muhatapların sana sıkıcı gelirse limana gel. Tüm tayfa meyhanede. Çocuklar seni görmekten memnun olacaklar.";
			link.l1.go = "Guests_block";
		break;
		
		case "Jino_9":
			dialog.text = "Kaptan, bir kez daha sizi ve güzel eşinizi tebrik ediyorum! Birlikte uzun ve mutlu yıllar diliyorum!";
			link.l1 = "Teşekkürler, Gino. Geldiğine sevindim! Umarım buranın... renkleri seni rahatsız etmiyordur?";
			link.l1.go = "Jino_10";
		break;
		
		case "Jino_10":
			dialog.text = "Bu toplumda kendimi rahat hissetmek kolay değil. Ama sen insanları seçmeyi hep bilirdin, bu yüzden sana güvendiğim için sakin kalmaya çalışacağım.";
			link.l1 = "Belki de daha sert bir şey içmelisin? Rahatla ve konuşacak birini bul?";
			link.l1.go = "Jino_11";
		break;
		
		case "Jino_11":
			dialog.text = "Teşekkür ederim kaptan, sulandırılmış şarap bana yeter de artar. Alkol, sizi uyarmalıyım, karaciğer için pek iyi değildir, hatta belki kalp için de zararlı olabilir. Sohbete gelince, o beyefendiyle Chirik-Sanango’nun iyileştirici özelliklerini konuşmaya çalıştım, ona Manaka da denir. Maine yerlileri bunu şu amaçla kullanır...";
			link.l1 = "Let me guess - that gentleman couldn't handle the discussion? Gino, for my sake and just for today - try the rum that Jan over there is pouring at the counter. If you can guess all of its ingredients, Nathaniel Hawk, over there, will be extremely impressed. I am sure he will be glad to be in your company, as will Svenson, the man at the counter; both of them respect educated people.";
			link.l1.go = "Jino_3";
		break;
		
		// Лонгвэй
		case "Longway":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Şimdi bu yabancı diyarda yalnız başıma, kendimi bir yabancı gibi hissediyorum; böylesine parlak bir bayram gününde, ailemi her zamankinden daha çok özlüyorum";
			link.l1 = "Longway, kelimelerin ustası olduğunu hiç düşünmemiştim!";
			link.l1.go = "Longway_1";
		break;
		
		case "Longway_1":
			dialog.text = "Üzgünüm Kaptan, son zamanlarda çok düşündüm. Bunlar Wang Wei'nin sözleri - memleketimde çok uzun zaman önce hüküm süren Tang hanedanı döneminde yaşamış bir şair.";
			link.l1 = "Bu sözler öyle güzel ki. Umarım bir gün memleketini tekrar görürsün...";
			link.l1.go = "Longway_2";
		break;
		
		case "Longway_2":
			dialog.text = "''Gizemli taş levhaların kemerinin altında, oradan geçmeye çalışırken, ötesinde U-lin vadisinin bulunduğu bir geçit bulmanın imkânsız olduğuna gerçekten emin olabilir miyiz?'\nHayır, Kaptan, sen de biliyorsun ki - Longway artık eve dönmeyecek. Artık burası benim evim ve bugün burada büyük bir olayımız var! Sana ve güzel gelinine en iyi dileklerimi gönderiyorum! Mutluluğunuz Yangtze Nehri kadar uzun, yıldızların elmaslarıyla süslü, nilüferlerin incileri arasında olsun.";
			link.l1 = "Teşekkür ederim, eski dostum. Sözlerin Wang Wei'ninkiler kadar güzel.";
			link.l1.go = "Longway_3";
		break;
		
		case "Longway_3":
			dialog.text = "Bir içki içelim, Kaptan! Bu rom, kederi kovar ve neşeyi tıpkı maotai gibi geri getirir.";
			link.l1 = "Sağlığına, Longway!";
			link.l1.go = "Longway_4";
		break;
		
		case "Longway_4":
			DialogExit();
			npchar.dialog.currentnode = "Longway_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Longway_4_1":
			dialog.text = "Harika bir düğün, kaptan!";
			link.l1 = "İç ve eğlen!";
			link.l1.go = "Longway_4";
		break;
		
		// Книппель
		case "Knippel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "Zincirli top atışı yap! Tüm adamlarımız seni tebrik ediyor! Atış nasıl geçti?";
				link.l1 = "Her şey yolunda, Charlie! Artık resmen evliyim ve saygın biriyim, birinci subayım da artık Madame de Monper.";
			}
			else
			{
				dialog.text = "Beni zincir gülleyle vur, ne olay ama, kaptan! Kardeşliğin neredeyse tüm baronları burada! Sanırım her İspanyol puritanı cehennemi böyle hayal ediyordur! Ve rom... bambaşka bir şey, fıçıma zincir gülle gibi geldi!";
				link.l1 = "Evet, buradaki insanlar en kuralcı olanlar değil, ama biz de melek sayılmayız Charlie, ve bu insanların her biri bana kendi yoluyla çok değerli.";
			}
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "Harika, zincirli gülle popoma gelsin! Kaptan, yani, bu kutlama sizin şerefinize, şey, ben... tebrik ederim, yani... ayrıca... Mutluluklar ve... işte, konuşma yapmakta pek iyi değilim. Ama bilmelisiniz ki, ikinizi de çok seviyoruz ve cehenneme bile gitseniz peşinizden geliriz, kaptan!";
				link.l1 = "Teşekkür ederim, eski dostum.";
			}
			else
			{
				dialog.text = "Bekle, yani... Ne demek istiyorum ki, zincir gülle popoma mı?! Kaptan, demek istediğim bugün senin şerefine, yani, ben... seni tebrik ediyorum... ve ayrıca... mutluluklar diliyorum ve... ve affet Kaptan, galiba konuşma yapacak kadar ayık değilim, zincir gülle boynuma, uzun zamandır ayık gezmiyorum ha-ha-ha!";
				link.l1 = "Hah! Sorun yok... sağ ol, eski dostum.";
			}
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 20);
			dialog.text = "Ah! Ve evet, kaptan, lütfen bunu kabul edin. Sizin ve hanımefendiniz için. Bu taşları kötü günler için saklamıştım... Altınınız eksik olmadığını biliyorum ama bunlar da fazlalık olmaz, değil mi?";
			link.l1 = "Charlie, gerçekten cömert bir ruhsun ve bu zümrütler Madame de Monper'in aile küpelerinde harika duracak!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			dialog.text = "Pekala, buna içelim, zincirli gülle... hm. Sadece mutlu olun, hem sen hem de güzelliğin, kaptan!";
			link.l1 = "Yapacağız, Charlie!";
			link.l1.go = "Knippel_4";
		break;
		
		case "Knippel_4":
			DialogExit();
			npchar.dialog.currentnode = "Knippel_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Knippel_4_1":
			dialog.text = "Harika bir düğün, kaptan!";
			link.l1 = "İç ve eğlen!";
			link.l1.go = "Knippel_4";
		break;
		
		// Тонзаг
		case "Tonzag":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Hiç düşünmemiştim kaptan, seni evlenirken göreceğimi. Genelde seçtiğimiz yol, yalnız bir mezara çıkan ıssız bir patikadır. Benim hatırladığım kadarıyla, bundan kurtulmayı başaran ilk sensin. Bu da fazladan bir kadehi hak etmiyor mu, sence de öyle değil mi?";
			link.l1 = "İşte bu, dostum! Ve gerçekten, hayatımın bu bölümünün geride kalmasına seviniyorum. Şerefe!";
			link.l1.go = "Tonzag_1";
		break;
		
		case "Tonzag_1":
			dialog.text = "Birlikte uzun ve mutlu bir hayatınız olsun, şerefe! Kahretsin, size bakınca, ben de bir zamanlar evliydim diye hatırladım.";
			link.l1 = "Sen mi? Evli misin? Bu ilginç bir haber! Peki, ne oldu?";
			link.l1.go = "Tonzag_2";
		break;
		
		case "Tonzag_2":
			dialog.text = "Ne sandın, kaptan, ben hep barut ve kan kokan yaşlı bir tek gözlü müydüm? Hayır. Madame Tonzag... sanırım beni severdi. Ama sonra tatsız bir hikaye yaşandı. Tonzag çifti öldü ve geriye sadece bir avuç yara iziyle Kel Gaston sağ kaldı.";
			link.l1 = "Üzgünüm, Hercule, bilmiyordum...";
			link.l1.go = "Tonzag_3";
		break;
		
		case "Tonzag_3":
			dialog.text = "Boşver kaptan, o hikaye çok uzun zaman önce yaşandı. Ama şimdi sana bakınca, hikayemin hâlâ mutlu bir sonu olabileceğini düşünüyorum. O halde, buna içelim!";
			link.l1 = "Bırakalım bunu, dostum. Biliyor musun, seni tanıdığım ilk günden beri sana hep kendi babam gibi baktım, belki bir gün sen de büyükbaba olma şansını yakalarsın. Neyse, şerefe! Diğer işlerle ilgilenmem lazım, sonra konuşuruz.";
			link.l1.go = "Tonzag_4";
		break;
		
		case "Tonzag_4":
			DialogExit();
			npchar.dialog.currentnode = "Tonzag_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tonzag_4_1":
			dialog.text = "Büyük kutlama, Kaptan!";
			link.l1 = "İç ve eğlen!";
			link.l1.go = "Tonzag_4";
		break;
		
		// Бейкер
		case "Baker":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "İşte kaptanımız! Tebrikler, sen ve eşin çok güzel bir çift olmuşsunuz! Bir ömür boyu mutlu yaşayın!";
			link.l1 = "Teşekkür ederim, Raymond.";
			link.l1.go = "Baker_1";
		break;
		
		case "Baker_1":
			sTemp = "Sharptown";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) sTemp = "Sent Pierre";
			dialog.text = " Kaptan, kendi düğününe göre fazla ayıksın gibi görünüyor. Bunu düzeltmek ister misin? Bardaktan harika bir şeri aldım. Yerel romla karıştırınca gayet güzel oluyor!";
			link.l1 = "İsterdim, ama burada birinin göz kulak olması gerekiyor. Yoksa, "+sTemp+" sabah olduğunda sadece meyhaneyi değil, başka şeyleri de özleyeceğim.";
			link.l1.go = "Baker_2";
		break;
		
		case "Baker_2":
			DialogExit();
			npchar.dialog.currentnode = "Baker_2_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Baker_2_1":
			dialog.text = "Harika yemekler ve harika rom, kaptan! Sana ve genç eşine şerefe!";
			link.l1 = "Teşekkürler!";
			link.l1.go = "Baker_2";
		break;
		
		// Алексус
		case "Alexus":
			dialog.text = "Gençler, neden içeri dalıyorsunuz, sorabilir miyim? Tersane kapalı, belli değil mi? Yarın gelin.";
			link.l1 = "Üstat, sizi rahatsız ettiğim için üzgünüm, sadece zindanlardan geçeceğiz. Düğün için erzak var ve meyhanede neredeyse hiç içki kalmadı.";
			link.l1.go = "Alexus_1";
		break;
		
		case "Alexus_1":
			dialog.text = "Oh, Charles de Maure ve Nathan Hawk bizzat gelmiş! Birinin düğününü kutlamaya geldiniz, değil mi? Peki - gidin içkinizi alın. Gençler eğlenmeli - bu her zaman böyledir. Ama dönüşte şişeleri sallamayın - uyuyacağım!";
			link.l1 = "Teşekkür ederiz, efendim, en sakin nehir kadar sessiz olacağız.";
			link.l1.go = "Alexus_2";
		break;
		
		case "Alexus_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			pchar.GenQuestBox.Bermudes_Dungeon = true;
			pchar.GenQuestBox.Bermudes_Dungeon.box3.items.potionwine = 100;
			pchar.quest.longhappy_isla_box.win_condition.l1 = "locator";
			pchar.quest.longhappy_isla_box.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator_group = "box";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator = "box3";
			pchar.quest.longhappy_isla_box.function = "LongHappy_IslaTesoroDungeon";
		break;
		
		case "Alexus_2_1":
			dialog.text = "Hadi, öylece durma, git! Peki kaptan, her şeyden memnun musun?";
			link.l1 = "...";
			link.l1.go = "Alexus_2_2";
		break;
		
		case "Alexus_2_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
		break;
		
		// пиратус в подземелье
		case "DungeonPirate":
			dialog.text = "Ne oluyor lan?! Jacques 'Buraya kimse gelmez' demişti! Hugo - geri koş, diğerlerini çağır, yolu açacağız. Öldürün onları, çocuklar!";
			link.l1 = "Kahretsin!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BandosInDungeonFight");
		break;
		
		// киллеры
		case "killer":
			dialog.text = "Çocuklar, sandıkları boşverin, misafirlerimiz var!";
			link.l1 = "Senin gibi piçlerin Jackman'la birlikte öldürüldüğünü sanmıştım. Peki, o zaman, hadi bitirelim bunu!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_ResidenceFight");
		break;
		
		case "killer_1":
			dialog.text = "Lanet olsun... Bizi buldular! Alarm!";
			link.l1 = "Çekil önümden, seni pislik!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernKillerFight");
		break;
		
		// Ангерран
		case "Shivo":
			dialog.text = "Monsieur de Maure, iyi akşamlar, yoksa sabah mı olmak üzere? Buyurun, oturun lütfen.";
			link.l1 = "Angerran De Chievous! Seni burada görmek hiç şaşırtmadı! Kadınlarla dövüşmekten başka bir işe yaramayan zavallı adam! Onları da mı bağladın?! Şimdi Martinique'deki düelloda başladığımı bitireceğim!";
			link.l1.go = "Shivo_1";
		break;
		
		case "Shivo_1":
			dialog.text = "Sakin ol, delikanlı, şu silahı görüyor musun? İki namlusu var. Belki iyi bir kılıç ustası değilim ama nişancılığım fena değildir – kılıcını indir, yoksa birkaç güzel hanımdan mahrum kalırsın, sana garanti ederim.";
			link.l1 = "Piç... Kahrolası herif.";
			link.l1.go = "Shivo_2";
		break;
		
		case "Shivo_2":
			dialog.text = "Ve sen, monsieur korsan, silahını da bırak, aynen öyle, evet. Şimdi ise - otur, şarabı doldurabilirsin - orada, masanın üstünde. Biraz beklememiz gerekecek, monsieur Barbazon arkadaşların, korsan baronlarının gemilerini parçalamayı bitirene kadar. Sonra seninle aramızdaki... hm, anlaşmazlıkları nasıl çözeceğimize karar veririz.";
			link.l1 = "Anlaşmazlıkları çözmek mi? Nasıl yani? Düello mu istiyorsun?";
			link.l1.go = "Shivo_3";
		break;
		
		case "Shivo_3":
			dialog.text = "Bu kadar komik olma, Charles. Sen ve Madame Botot bana epeyce sıkıntı çıkardınız, ve ben de size bunun karşılığını fazlasıyla ödeyeceğim. Gerçi bana senden çok daha fazla baş ağrısı yaşattı... yine de, eğer sen ve o heybetli Bay Korsan uslu uslu oturursanız, size namusum üzerine söz veriyorum – eşleriniz hayatta kalacak. Ana Kara’daki İspanyol kolonilerinde böyle köleler değerli sayılıyor. Resmi olarak olmasa da. Ama yine de bu bir yaşam, öyle değil mi?";
			link.l1 = "Angerran, sen bir korkaksın, bir piçsin ve... Kahretsin, senin için henüz hiçbir dilde uygun bir kelime yok!";
			link.l1.go = "Shivo_4";
		break;
		
		case "Shivo_4":
			dialog.text = "Biliyorsun, başka seçeneğin yok. Sadece hızlı olacağına söz verebilirim. Yani, eğer bu kadınları düşünüyorsan - uslu dur, onların hayatını bağışla ve kendi kaderini hafiflet. Ve evet - eğer zahmet olmazsa kapıyı kilitle. Teşekkür ederim.";
			link.l1 = "";
			link.l1.go = "Shivo_5";
		break;
		
		case "Shivo_5":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Shivo_6":
			dialog.text = "Böylesine savaşçı hanımlar. Yine de sizden temkinli olmanızı rica edeceğim. Kadınları öldürmekten hiç hoşlanmam.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Shivo_7":
			dialog.text = "Lanet olsun...";
			link.l1 = "Geber ruhunu, alçak!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Дюссак
		case "Dussak":
			dialog.text = "Kaptan Charles de Maure, Baron Hawk - ne hoş bir sürpriz! Kendimi tanıtayım - Mauritz Dussak, adım bu.";
			link.l1 = "Çekil önümden, alçak! Karım nerede?!";
			link.l1.go = "Dussak_1";
		break;
		
		case "Dussak_1":
			dialog.text = "Sakin olun, beyler! Şu silahı görüyor musunuz? İki namlusu var. Bana bu lakabı boşuna takmadılar – kılıçları severim, doğru... ama inanın bana, nişanım da iyidir. Kılıçlarınızı bırakın yoksa birkaç parmağınızdan olabilirsiniz!";
			link.l1 = "Seni domuz gibi keseceğim, pislik...";
			link.l1.go = "Dussak_2";
		break;
		
		case "Dussak_2":
			dialog.text = "Ama zaten dul kalacaksın. Bunu istemiyor musun? O zaman sakin ol ve silahını indir. Baron Hawk, lütfen kapıyı kilitle. Hepimiz sakinleşip biraz bekleyeceğiz, bu sırada limanda Jacques Barbazon dışarıda Kardeşliğin liderlerini ortadan kaldıracak.";
			link.l1 = "Peki ya sonra? Sarılıp birlikte gün batımına mı gideceğiz?";
			link.l1.go = "Dussak_3";
		break;
		
		case "Dussak_3":
			dialog.text = "Bence öyle değil. Seni yakaladığım için Jacques beni altına boğacak. Belki de şansım yaver giderse baron olurum. Kadınlarını belki serbest bırakırız, ama senin için... ne yazık ki... Eğer şansın varsa, seni öldürme hakkını bizzat ben isterim, kaptan. Sen ünlü bir düellocusun - seni sınamak ilginç olurdu. Bilirsin, ben de kendimi usta sayarım.";
			link.l1 = "Gece evlere gizlice girip yarı uykulu kadınları bağlamakta usta mısın? Sen bir solucaksın, hem de zavallı bir solucan!";
			link.l1.go = "Dussak_4";
		break;
		
		case "Dussak_4":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Dussak_5":
			dialog.text = "Dinleyin hanımefendi, ben hiç kadın öldürmedim, beni buna zorlamayın, tamam mı? Kaptanı ve kocanızı huzursuz ediyorsunuz... Kahretsin!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Dussak_6":
			dialog.text = "Merdo...";
			link.l1 = "Geber ruhunu, alçak!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Барбазон
		case "Barbazon_boarding":
			dialog.text = "Lanet olası Fransız, bir kılıç ya da kurşun yok muydu?!";
			link.l1 = "Biliyor musun Jacques, ikisini de senin için sakladım. Açıkçası, Jackman'la olan numaralarını öğrendiğimde seni hayatta bıraktığıma neredeyse pişman oldum. Ama şimdi, bunu düzelteceğim.";
			link.l1.go = "Barbazon_boarding_1";
		break;
		
		case "Barbazon_boarding_1":
			dialog.text = "Kendi adamların etrafındayken mi cesaretlisin? Hadi bunu değiştirelim! Baronlarla sonra ilgileneceğim, ama sen buradan sağ çıkamayacaksın, fare!";
			link.l1 = "Bekleniyordu...";
			link.l1.go = "Barbazon_boarding_2";
		break;
		
		case "Barbazon_boarding_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			AddItems(npchar, "potion2", 1);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "LongHappy_BarbAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			sld = GetCharacter(NPC_GenerateCharacter("LH_BarbCabinHelper", "citiz_57", "man", "man", 35, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol4", "bullet", 300);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			AddItems(sld, "potion2", 2);
		break;
		
		// официантка
		case "waitress":
			dialog.text = "Kaptan, yardım edin, bu vahşi adam beni kaçırdı! Ben... Ben eve gitmeliyim - amcam muhtemelen çoktan bütün kasabayı altüst etmiştir!";
			link.l1 = "Sakin ol, güzelim, her şey yoluna girecek. Bir kenara çekil, senin 'vahşi'yle konuşmam lazım.";
			link.l1.go = "waitress_1a";
		break;
		
		case "waitress_1a":
			DialogExit();
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "waitress_1":
			dialog.text = "Teşekkür ederim, kaptan! Beni kurtardınız! Bu sabah bu sahilde uyandığımda... bu vahşiyle evleneceğime inanamıyorum, o...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 94)
			{
				link.l1 = "Evet, sabah, gecenin umut kristalini sertçe ezen bir çekiçtir. Anlıyorum. Ama o Muscogee kabilesinden ve kendi topraklarının sert kurallarına göre yaşıyor. Seni senin rızanla kaçırdı ve geceyi birlikte geçirdiniz. Artık onun tanrılarının gözünde karı kocasınız. Hadi gidip eşyalarını toplayalım, fidye işini de amcanla ben hallederim.";
				link.l1.go = "waitress_2";
			}
			link.l2 = "Bunun için üzgünüm. Tichingitu kendi kabilesinin kurallarına göre yaşar, ama iyi bir insandır. Lütfen, bu kaçırılma hikayesini unutun.";
			link.l2.go = "waitress_5";
		break;
		
		case "waitress_2":
			dialog.text = "Karısı mı? Onun tanrılarının gözünde mi?! Hayır, kaptan, yalvarırım, beni bundan kurtarın! Bu sadece... bir maceraydı, çok nazik ve centilmendi, buradaki köylüler gibi değildi... Ama evlilik mi? Bir vahşiyle bir kulübeye taşınmak için çok gencim!";
			link.l1 = "O benim subayım ve en yakın dostum, merak etme, ona iyi para veriyorum ve sen de isteyebileceğin en güzel kulübeye sahip olacaksın. Tichingitu usta bir avcıdır, sana yiyecek sağlar, sen de doğum yapar ve çocuklara bakarsın.";
			link.l1.go = "waitress_3";
		break;
		
		case "waitress_3":
			dialog.text = "Çocuklar mı? Yiyecek bulmak mı?! Hayır, kaptan, lütfen bana bunu yapma, yalvarırım sana!";
			link.l1 = "Well, maybe I can convince him. But it won't be easy. The Muskogue tribe is very serious about such things; if someone finds out that he stole a squaw and didn't get married...";
			link.l1.go = "waitress_4";
		break;
		
		case "waitress_4":
			dialog.text = "Lütfen denemelisin, ne olur! Kimseye söylemem, kimse bilmeyecek! Amcama da yalan söylerim, ilk defa yapmıyorum ki!";
			link.l1 = "Peki, gitmelisin güzel kız. Arkadaşımı uzak tutmaya çalışacağım.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_5":
			dialog.text = "Beni çaldı... ahırdan keçi çalar gibi! Herkese anlatacağım! Amcam onu öldürür! O sinirlendi mi korkunç olur! Eskiden İspanyol gemilerini soyardı – onunla şaka olmaz!";
			link.l1 = "Peki, sus, güzel hanım, sus. Belki de onu affetmen için yirmi bin 'sebep' sözlerimden daha etkili olur? Yoksa onları amcana mı vereyim, bir eş için fidye gibi? Sonuçta herkes adada, değil mi? Yarın bir düğün daha düzenleyebiliriz...";
			link.l1.go = "waitress_6";
		break;
		
		case "waitress_6":
			if (sti(Pchar.money) >= 20000) AddMoneyToCharacter(pchar, -20000); 
			dialog.text = "Hayır, hayır, kaptan, durun! Beni ikna ettiniz. Amcamı kızdırmayacak bir şey bulurum. Elveda! Ve sana da veda, uzak bozkırların aygırı! Bir dahaki gelişinizde görüşürüz...";
			link.l1 = "Doğru. Anlaştığımıza sevindim. Hadi, evine koş güzelim.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// тавернщик Сен Пьер
		case "tavernkeeper":
			dialog.text = "Pekala, Kaptan, her şeyden memnun kaldınız mı? En iyi rom, kuzu kaburga, domuz jambonu ve hatta bilim insanı dostunuz için özel mahzenimden harika şarap! Ve - size ve güzel eşinize tebriklerimi sunarım!";
			link.l1 = "Teşekkürler! İtiraf etmeliyim, her şeyi mükemmel bir şekilde organize etmişsin. Umarım mahzenlerinde yeterince rom vardır, sabaha daha çok var.";
			link.l1.go = "tavernkeeper_1";
		break;
		
		case "tavernkeeper_1":
			dialog.text = "Merak etmeyin, fıçıların içi boşalırsa liman deposuna bir yardımcı yollarım. Keyfinize bakın, monsieur, hiçbir şeyi dert etmeyin.";
			link.l1 = "Peki, "+npchar.name+". O halde misafirlerimin yanına gideceğim.";
			link.l1.go = "tavernkeeper_2";
		break;
		
		case "tavernkeeper_2":
			DialogExit();
			npchar.dialog.currentnode = "tavernkeeper_3";
		break;
		
		case "tavernkeeper_3":
			dialog.text = "Ne arzu edersiniz, kaptan? Kızarmış kaburga, füme jambon ya da dana brisket? Belki eşiniz için biraz şarap ister misiniz?";
			link.l1 = "";
			link.l1.go = "tavernkeeper_2";
		break;
		
		// моряки в таверне Сен Пьер
		case "sailor":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Kaptanın ve eşinin sağlığına!","Bir ömür boyu mutlu yaşayın, Kaptan!","İkinize de uzun ömür ve mutluluklar dilerim!"),LinkRandPhrase("Yaşasın kaptan ve onun güzeli!","Kaptana ve eşine hayatları boyunca şans hep yoldaş olsun!","Ailenize huzurlu rüzgarlar essin, kaptan!"));
			link.l1 = LinkRandPhrase("Teşekkürler!","Teşekkür ederim!","Şerefe!");
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor";
		break;
		
		// босс Ле Франсуа
		case "JanDavid":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sen deli misin? Kasap mı olmak istedin? Bütün korsanlar sana kızgın, dostum, o yüzden buradan gitmen en iyisi olur.","Görünüşe bakılırsa, dostum, kafayı yemişsin. Biraz ellerini açmak mı istedin? Alınma ama burada işin yok. Kaybol!");
				link.l1 = RandPhraseSimple("Dinle, işleri yoluna koymak istiyorum...","Bana bu sorunu çözmemde yardım et...");
				link.l1.go = "pirate_town";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron"))
			{
				if (!CheckAttribute(npchar, "quest.Baron"))
				{
					dialog.text = "Ah, ziyaretinizi bekliyordum, patron. Jan Svenson bana kesinlikle Le Francois'daki işleri kontrol etmeye geleceğinizi söyledi. Her şeyi kendi ellerime aldım ve yıldırımlar adına yemin ederim ki, bu köy o lanet Kindman'ın zamanından çok daha iyi gelişecek. Onunla cehennemin en karanlık mahzenlerinde şeytanlar eğlensin!";
					link.l1 = "Sen Jean David'sin, değil mi? Svenson bana payımdan bahsetmişti...";
					link.l1.go = "JanDavid_2";
				}
				else
				{
					dialog.text = TimeGreeting()+" patron. Le François'da her şey her zamanki gibi yolunda. Neden geldiniz? Size bir konuda yardımcı olabilir miyim?";
					link.l1 = "Sadece nasıl gittiğine bakmak için uğradım.";
					link.l1.go = "JanDavid_1";
					if (sti(pchar.questTemp.LongHappy.BaronMoney) > 0)
					{
						link.l2 = "Benim payım ne olacak?";
						link.l2.go = "JanDavid_5";
					}
				}
			}
			else
			{
				dialog.text = TimeGreeting()+" dostum. Neden geldin? Sana bir konuda yardımcı olabilir miyim?";
				link.l1 = "Sadece selam vermek için uğradım.";
				link.l1.go = "JanDavid_1";
			}
		break;
		
		case "JanDavid_1":
			DialogExit();
			npchar.dialog.currentnode = "JanDavid";
		break;
		
		case "JanDavid_2":
			npchar.quest.Baron = "true";
			dialog.text = "Emrinizdeyim, patron! Payınıza gelince - her ayın beşinde, adamlarımızın işlerinden gelen altın paraların bir kısmı sizin için ayrılacak ve ne kadar isterseniz sizi bekleyecek. Gelecek aydan itibaren gelip alabilirsiniz.";
			link.l1 = "Güzel!";
			link.l1.go = "JanDavid_3";
		break;
		
		case "JanDavid_3":
			dialog.text = "Gerisini ben hallederim. Orman Şeytanı, Le Francois gibi önemsiz meselelerle uğraşacak vaktin olmayacağını söyledi...";
			link.l1 = "Doğru söylemişler. Peki Jean, sana güveniyorum, umarım beni hayal kırıklığına uğratmazsın.";
			link.l1.go = "JanDavid_4";
		break;
		
		case "JanDavid_4":
			dialog.text = "Her şey yolunda olacak, patron. Burada her şey kontrol altında, ha-ha, ve eğer bir şeyi berbat edersem, ömrüm boyunca bir daha asla rom içmeyeyim!";
			link.l1 = "Peki, görüşürüz!";
			link.l1.go = "JanDavid_1";
			// запуск отчисления доли
			pchar.questTemp.LongHappy.BaronPart = "true";
			pchar.questTemp.LongHappy.BaronMoney = 0;
		break;
		
		case "JanDavid_5":
			dialog.text = "Seni bekliyoruz, kaptan. Bu arada senin için toplandık "+FindRussianMoneyString(sti(pchar.questTemp.LongHappy.BaronMoney))+". Al bunu.";
			link.l1 = "Ha, fena değil. Aferin, Jean.";
			link.l1.go = "JanDavid_6";
		break;
		
		case "JanDavid_6":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.LongHappy.BaronMoney));
			pchar.questTemp.LongHappy.BaronMoney = 0;
			dialog.text = "Elimden gelenin en iyisini yaparım, patron. Gelecek ay ya da ne zaman istersen geri gel – paran bende güvende olacak.";
			link.l1 = "Pekala, görüşürüz, Jean.";
			link.l1.go = "JanDavid_1";
		break;
		
		case "pirate_town":
             dialog.text = " Sorunu çözmek mi? Ne yaptığının farkında mısın sen? Neyse, bana bir milyon peso getir, adamlara bu işi unutturmaya çalışırım. Eğer bu fikir hoşuna gitmediyse, defol git o zaman.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Pekâlâ, ödemeye hazırım.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Anladım. Gidiyorum.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Güzel! Kendini tekrar temiz sayabilirsin. Ama umarım bir daha böyle iğrenç şeyler yapmazsın.";
			link.l1 = "Yapmam. Benim için çok pahalı. Hoşça kal...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
} 
