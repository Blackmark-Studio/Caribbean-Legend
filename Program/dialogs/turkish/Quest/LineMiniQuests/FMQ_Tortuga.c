// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Açık bir hata. Bunu geliştiricilere bildir.";
			link.l1 = "Ah, yapacağım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "girl":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Oh, merhaba monsieur! Tortuga'ya hoş geldiniz! Sizin gibi asil kaptanlar burada nadiren misafir olur...";
			link.l1 = "Selamlar, madam. Sıcak karşılamanız için teşekkür ederim. Ama nasıl yani? Böyle önemli bir limanın, benim gibi biriyle kıyaslanamayacak kadar soylu talihli beyefendilerin her zaman ilgisini çektiğini sanıyordum.";
			link.l1.go = "girl_1";
		break;
		
		case "girl_1":
			dialog.text = "Ah, monsieur... Siz açıkça buralarda yenisiniz, değil mi? Yakında kendiniz göreceksiniz. Valinin sarayında dans edecek değerli birini bulmak ne kadar zor, bilemezsiniz. Belki bana eşlik etmek istersiniz...?";
			link.l1 = "Böylesine güzel bir kadına nasıl yardımcı olabilirim?";
			link.l1.go = "girl_2";
		break;
		
		case "girl_2":
			dialog.text = "Vay canına, ne kadar da centilmenlik! (kıkırdar) Belki bu akşam saat altıda bize uğrarsınız? Valimizin eşi, sarayın hizmetkarlar bölümünde sık sık samimi toplantılar düzenler. Böyle etkinliklerde ilginç bir misafirimiz olması nadir bir fırsat bizim için. Bizi ziyaret edecek misiniz? Lütfen gelin, çok memnun oluruz.";
			link.l1 = "Sizi onurlandırmak isterim, madam. Bu gece sizi ziyarete geleceğim.";
			link.l1.go = "girl_3";
			link.l2 = "Beni affedin, madam, ama halletmem gereken acil işlerim var. Belki başka bir zaman?";
			link.l2.go = "girl_exit";
		break;
		
		case "girl_exit":
			dialog.text = "Yazık. Görünen o ki, bana ve arkadaşlarıma eşlik edecek başka birini bulmam gerekecek... Hoşça kal.";
			link.l1 = "Elveda.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			FMQT_ClearChest();
		break;
		
		case "girl_3":
			dialog.text = "Teşekkür ederim! Sana söz veriyorum, bu geceyi asla unutamayacaksın, monsieur! Au revoir!";
			link.l1 = "Görüşürüz...";
			link.l1.go = "girl_4";
		break;
		
		case "girl_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_serveroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "1");
		break;
		
		case "girl_5":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Selam, denizci! Bugün seni buraya hangi uğurlu rüzgâr getirdi? Tortuga'da böyle yakışıklı adamları pek nadir görürüz.";
			link.l1 = "Sana da merhaba, mademoiselle, iltifatlarınla beni utandıracaksın neredeyse. Kendi gemimin kaptanıyım ve meşgul bir adamım, ama eminim ki bu ada, benim gibi bir maceraperestin burada eğlenmesi için fazlasıyla şey sunuyordur.";
			link.l1.go = "girl_6";
		break;
		
		case "girl_6":
			dialog.text = "(kıkırdar) Ah evet efendim, eminim bu konuda yardımcı olabiliriz! Tortuga'nın her zaman sunacak bir şeyi vardır. Benim de... Neden, iyi bir deniz hikayesi duyduktan sonra neredeyse *her şeyi* yapabilirim. Onlara bayılırım! Bir kaptan bana bir keresinde, ıssız bir adada mahsur kalmaktan deniz kaplumbağalarından sal yaparak nasıl kurtulduğuna dair uzun bir hikaye anlatmıştı. Ne cesur bir adam! Siz de yapabilir miydiniz?";
			link.l1 = "Ne yapabilir miyim?";
			link.l1.go = "girl_7";
		break;
		
		case "girl_7":
			dialog.text = "(kıkırdar) Deniz kaplumbağalarından sal yapabilir misin?";
			link.l1 = "Sana daha iyisini anlatayım. Bir keresinde, kaçak bir çırakken, sadece bir balta kullanarak İngiliz Donanması'nın en hızlı gemisini ele geçirdim. Ayrıca on dakika boyunca nefesimi tutabilirim. Görmek ister misin?";
			link.l1.go = "girl_8";
		break;
		
		case "girl_8":
			dialog.text = "Belki sonra. Valimizin sarayında hizmetçi olarak çalışıyorum. Bu akşam saat altıda oraya gel, beni ve arkadaşımı çardakta bul. O zaman bize maceralarını anlatırsın...";
			link.l1 = "Kaçırılmayacak bir davet gibi geliyor. Bu gece altıda görüşürüz.";
			link.l1.go = "girl_9";
			link.l2 = "Valinin sarayına gizlice girmek mi? O iş bana biraz fazla gelir. Ben almayayım, canım. Gerçek bir adamın dostluğunu istersen beni meyhanede bulursun. Yo ho ho!";
			link.l2.go = "girl_exit_2";
		break;
		
		case "girl_exit_2":
			dialog.text = "Ph-f. Ne halin varsa gör, ben senden daha iyi ve daha iri bir adam bulurum zaten. Zaten senin donun da pek küçük görünüyor. Güle güle.";
			link.l1 = "Senin Rüzgarlı Geçidin’den geçen bir savaş gemisi bile küçük görünürdü.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_9":
			dialog.text = "Dört gözle bekliyorum!";
			link.l1 = "...";
			link.l1.go = "girl_10";
		break;
		
		case "girl_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_bedroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "2");
		break;
		
		case "wife":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Ah, işte buradasın! Kaptan "+GetFullName(pchar)+"! Sizi tanıdığıma çok memnun oldum, uzun zamandır böyle soylu ve saygın bir misafirim olmamıştı!";
			link.l1 = "Sizinle burada olmak benim için büyük bir onur ve mutluluk, madam. Peki ya diğer misafirler? Çok mu erken geldim?";
			link.l1.go = "wife_1";
		break;
		
		case "wife_1":
			dialog.text = "Ah, onlar meşguller ve gelemezler. Ama boşver onları, gel şarap içip sohbet edelim... Ah, burada ne kadar sıkıldığımı ve yalnız hissettiğimi bir bilsen! Tortuga, pisliklerle, haydutlarla ve korsanlarla dolu bir batakhane! Korsanlar! Ve sonunda, evimde değerli bir centilmen! Keşke kocam senin gibi birinin sınıfı ve yetenekleriyle daha çok iş yapsa! Ama hayır, her yerde sadece korsanlar, korsanlar! Paris'te Majestelerinin Kraliyet Sarayı'nda yeni bir moda popüler olmaya başlamış, duydun mu? Senin bu konuda fikrin ne?";
			link.l1 = "Üzgünüm, tam olarak ne hakkında fikrimi soruyorsun? Korsanlar mı? Yoksa moda mı?";
			link.l1.go = "wife_2";
		break;
		
		case "wife_2":
			dialog.text = "Ah efendim, beni öyle iyi anlıyorsunuz ki! Buna inanmakta zorlanıyorum. Kocam korsanlarından MİLYONLAR kazanırken bana kuruşlar veriyor, düşünsenize! Korsanlar! Elbiselerimi bu pis deliğe sipariş etmek zorunda kalıyorum, ama geldiklerinde zaten altı ay gecikmiş oluyorlar! Benim statümdeki bir kadın böyle paçavraları nasıl giyebilir? Ah, Paris'in modalarını görmek ve giymek için can atıyorum! Sizce ben o kıyafetlerle güzel görünür müyüm?";
			link.l1 = "Madam, çok güzel görünüyorsunuz. Bunun için Paris'ten gelen modaya ihtiyacınız yok, bu zaten bu güzel adadaki her erkeğe açıkça belli.";
			link.l1.go = "wife_3";
		break;
		
		case "wife_3":
			dialog.text = "Bana fazla iyilik yapıyorsunuz... Kaptan, itiraf etmeliyim ki, büyük bir sıkıntıdayım. Ama siz zavallı bir kadına yardım edersiniz, değil mi?";
			link.l1 = "Elbette, madam. Ne isterseniz.";
			link.l1.go = "wife_4";
		break;
		
		case "wife_4":
			dialog.text = "Dikkatli olun, monsieur kaptan, yoksa başımı kaybedeceğim! (cilveli bir kıkırdama) Kocam bana son zamanlarda tek bir kuruş bile vermedi. O kaba adam evimize sıradan kadınları getiriyor, bana ise hiç aldırmıyor!\nOnun haksız kazançla elde ettiği bazı hazineleri nereye sakladığını biliyorum, ofisindeki bir sandıkta. Bu para, bir eş ve bir kadın olarak benim hakkım. Bana borcunu almamda yardım ederseniz, ödüllendirileceksiniz... Altınla ve... başka hoş şeylerle.";
			link.l1 = "Bu gerçekten ilginç bir teklif. Peki hanımefendi, size yardım edeceğim. Bu sandık nerede ve nasıl açılır?";
			link.l1.go = "wife_5";
			link.l2 = "Pekâlâ, hanımefendi, sandığın içindekileri size getireceğim. Parayı alırız ve sonrasında çok keyifli bir 'sohbetimiz' olur. Hangi adam böyle bir teklifi reddedebilir ki? Bu sandık nerede ve nasıl açılıyor?";
			link.l2.go = "wife_6";
			link.l3 = "Madam, beni baştan çıkarmaya çalışıyorsunuz. Üzgünüm, ama onurum gereği teklifinizi reddetmek zorundayım. Size üzülüyorum, daha iyisini hak ediyorsunuz, ama oyununuz için başka bir oyuncu bulmanız gerekecek.";
			link.l3.go = "wife_exit";
		break;
		
		case "wife_exit":
			dialog.text = "Yazık. O halde konuşacak başka bir şeyimiz kalmadı, monsieur. Git ve unutma: Eğer kocama bundan tek kelime edersen, pişman olursun!";
			link.l1 = "Elveda.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.FMQT.Common");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "4");
		break;
		
		case "wife_5":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Bunu senden beklemezdim... Sandığı... Onu sonra hallederiz, önce o pis korsanın çaldığı yedek anahtarı bulmamız lazım. Şu anda bir meyhanede kafayı çekiyor, domuz gibi içiyor. Acele et ve yedek anahtarı bana geri getir. Seni bekliyor olacağım.";
			link.l1 = "Öyleyse vakit kaybetmeye gerek yok!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_6":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Bundan pişman olmayacaksınız, kaptan. Önce, pis bir korsanın çaldığı yedek anahtarı bulmamız gerekiyor. Şu anda bir meyhanede kafayı çekiyor, domuz gibi içiyor. Acele edin ve yedek anahtarı bana geri getirin. Sizi bekliyor olacağım.";
			link.l1 = "O halde vakit kaybetmeyelim!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_PirateInTavern", 10.0);
			pchar.quest.FMQT_late2.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late2.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQT_late2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late2.function = "FMQT_TavernTime";
			AddQuestRecord("FMQ_Tortuga", "6");
		break;
		
		case "wife_8":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Kaptan "+GetFullName(pchar)+"! Aman Tanrım! Özel odamda bir adam! Şaşırdın mı? Bu gece buradaki tek misafir sensin. (kıkırdar)";
			link.l1 = "Şaşırdım hanımefendi. Ama hiç rahatsız olmadım. Bu bir iş görüşmesi mi, yoksa keyif için mi geldiniz?";
			link.l1.go = "wife_9";
		break;
		
		case "wife_9":
			dialog.text = "Ne kadar doğrudan bir yaklaşım! Senin gibi adamları severim. Sana bir iş teklifim var, kaptan. Başarırsan, çabalarının karşılığını alacaksın.";
			link.l1 = "Devam et.";
			link.l1.go = "wife_10";
		break;
		
		case "wife_10":
			dialog.text = "Ah... Kocamın bir sandık dolusu parası ve mücevheri var. Ondan nefret ediyorum ve yaşadığım sıkıntılar için daha büyük bir harçlık istiyorum.";
			link.l1 = "Madam, çok güzelsiniz. Bunun için Paris'ten daha fazla mücevher ya da moda kıyafetlere ihtiyacınız yok, Hispaniola'daki her erkek için bu zaten apaçık ortada.";
			link.l1.go = "wife_11";
		break;
		
		case "wife_11":
			dialog.text = "Bana karşı fazla naziksiniz... Kaptan, itiraf etmeliyim ki büyük bir sıkıntıdayım. Zor durumdaki bir kadına yardım eder misiniz?";
			link.l1 = "Elbette, madam. Onur bunu gerektirir. Ne isterseniz.";
			link.l1.go = "wife_12";
		break;
		
		case "wife_12":
			dialog.text = "Dikkatli olun, monsieur kaptan, yoksa başımı kaybedeceğim! (cilveli bir kıkırdama) Kocam bana son zamanlarda tek kuruş vermedi. O kaba adam evimize sıradan kadınları getiriyor ve bana hiç aldırmıyor!\nOnun haksız kazancının bir kısmını nereye sakladığını biliyorum, ofisindeki bir sandıkta. Bu para benim, hem karısı hem de bir kadın olarak hakkım. Bana borcunu almamda yardım ederseniz, ödüllendirileceksiniz... Altınla ve... başka hoş şeylerle.";
			link.l1 = "Pekâlâ. Bunu yapacağım. Sandık nerede ve nasıl açılır?";
			link.l1.go = "wife_13";
			link.l2 = "Ha! Hiç şüphem yok, senin gibi bir kadın için bunu yaparım. Pişman olmayacaksın, canım. Parayı alacağız ve birlikte çok güzel vakit geçireceğiz. Bu sandık nerede, ve nasıl açılıyor?";
			link.l2.go = "wife_14";
			link.l3 = "Ben değilim, hanımefendi. Bir adamı aynı gecede hem boynuzlayacak hem de soyacak bir centilmen değilim. En azından bu şekilde değil. Bu oyun için başka bir oyuncu bulun kendinize.";
			link.l3.go = "wife_exit_2";
		break;
		
		case "wife_13":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Ah... Sana her geçen gün daha çok ısınıyorum... Önce, pis bir korsanın çaldığı yedek anahtarı geri almamız gerek. Şu anda bir meyhanede kafayı çekiyor, domuz gibi içiyor. Acele et ve yedeği bana getir. Seni bekliyor olacağım.";
			link.l1 = "O halde vakit kaybetmeyelim!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_14":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Sakin ol, monsieur, bunun için daha sonra bolca vaktimiz olacak. (kıkırdar) Önce, pis bir korsan tarafından çalınan yedek anahtarı geri almalıyız. Şu anda bir meyhanede kafayı çekiyor, domuz gibi içiyor. Acele et ve yedeği bana getir. Seni bekliyor olacağım. Bunu halledebileceğinden emin misin?";
			link.l1 = "Benden şüphe etme, çoktan yoldayım.";
			link.l1.go = "wife_7";
		break;
		
		case "wife_exit_2":
			dialog.text = "Utanmaz herif! Gözüm görmesin seni! Sakın kocama bundan bahsetmeyi aklından bile geçirme, yoksa pişman olursun!";
			link.l1 = "Hoşça kal, tatlım.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_15":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_late3.over = "yes";
			dialog.text = "Kaptan! Anahtarı aldın mı?";
			link.l1 = "Evet, bende. Sandık nerede?";
			link.l1.go = "wife_16";
		break;
		
		case "wife_16":
			dialog.text = "Oh! O alçak kocam sonunda hak ettiğini mi bulacak? Gerçekten inanılmaz bir adamsınız, kaptan! Önünüzde parlak bir gelecek var, biliyor musunuz? Sandığı boşverin. Onu kendim hallederim. Yarın ödülünüzü almak için yanıma gelin. Pişman olmayacaksınız, kaptan...";
			link.l1 = "Pekâlâ. Nasıl istersen. Yarın seni görmeyi dört gözle bekliyorum.";
			link.l1.go = "wife_17";
			link.l2 = "Hayır, ben meşgul bir adamım ve bekleyerek zaman kaybetmek istemem. Neden bekleyeyim? Ne yapılması gerektiğini söyle, ben hallederim. Böyle güzel bir kadının zarif ellerinin bir kilit ve anahtarla uğraşıp zarar görmesine izin veremem.";
			link.l2.go = "wife_18";
		break;
		
		case "wife_17":
			RemoveItems(pchar, "kaleuche_key", 1);
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			dialog.text = "Altıda yanıma gel, cesur şövalyem...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_Deceive");
		break;
		
		case "wife_18":
			dialog.text = "Emin misiniz? Sizin için tehlikeli olabilir. Hayatınızı riske atmak istemenizin sebebi ne, kaptan?";
			link.l1 = "Pekala. Sen bilirsin. Yarın seni görmeyi dört gözle bekliyorum.";
			link.l1.go = "wife_17";
			link.l2 = "Kararımı çoktan verdim. Tam olarak ne yapmam gerekiyor?";
			link.l2.go = "wife_19";
		break;
		
		case "wife_19":
			dialog.text = "Bir aslan yürekli!... Kocamın ofisine git, sandığı orada bulacaksın. Yedek anahtarı kullan. Bu saatte orada kimse olmaz, acele etme. O sandığın içinde... elmaslar var. Hem de bir sürü. Hepsini al ve bana geri dön. Seni bekliyor olacağım. Güvenimi boşa çıkarma... lütfen.";
			link.l1 = "Yakında döneceğim.";
			link.l1.go = "wife_20";
		break;
		
		case "wife_20":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Tortuga", "11");
			sld = &Locations[FindLocation("Tortuga_townhallRoom")];
			sld.private2.key = "kaleuche_key"; // допуск к сундуку
			pchar.questTemp.FMQT = "chest";
		break;
		
		case "wife_21":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "Ah, kaptan! Ben... Sen... Bitti mi? Ah, bu da kim?! A-ah!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_MercenAttackRoom");
		break;
		
		case "wife_22":
			dialog.text = "Aman Tanrım! Kaptan, beni kurtardınız! Siz... siz benim kahramanımsınız! O adam kocamın adamıydı, sizi öldürmek istedi! Ona yapmaması için yalvardım! Yaralandınız mı? Elmasları getirdiniz mi?";
			link.l1 = "Ha. Gerçekten mi? Kocan kıskanç bir adam... Ne yapalım. Onun canı cehenneme, bende o cesaret var.";
			link.l1.go = "wife_23";
		break;
		
		case "wife_21x":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "Oh kaptan! Ben... Sen... Bitti mi?";
			link.l1 = "Küçük bir aksilik oldu ama şimdi hallettim. Neden solgunsunuz, madam? İyi misiniz? Mücevherler bende, bu sizi neşelendirir, değil mi?";
			link.l1.go = "wife_23";
		break;
		
		case "wife_23":
			dialog.text = "Tanrıya şükür! İntikamım alındı! Benim şövalyem! Kaç tane elmas vardı?";
			if (GetCharacterItem(pchar, "jewelry2") >= 100)
			{
				link.l1 = "Şövalyeniz macerasından ganimet dolu bir çuvalla döndü. Bunun yarısını hanımefendisine bırakacak ki, Paris'ten en güzel kıyafetleri alabilsin. Size verdiğim sözü tuttum.";
				if (CheckAttribute(pchar, "questTemp.FMQT.Honour")) link.l1.go = "wife_25";
				else link.l1.go = "wife_26";
			}
			else
			{
				link.l1 = "Elmas çoktu ama sana hiçbir şey yok. Beni öldürmek için bir katil tuttun, seni orospu! Bunca şeyden sonra seninle paylaşacağımı mı sandın? Eğer bu konuda tek kelime edersen, kocan onu soymak ve aldatmak istediğini öğrenecek. O yüzden çeneni kapa.";
				link.l1.go = "wife_24";
			}
		break;
		
		case "wife_24":
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_03.wav");
			dialog.text = "Alçak! Namussuz! Bunun hesabını vereceksin!";
			link.l1 = "Ha, bunu daha önce de duymuştum.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoJewelry");
		break;
		
		case "wife_25":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "Sen diğerleri gibi değilsin... İstediğini alırsın. Önünde parlak bir gelecek var. Yoğun bir insan olduğunu biliyorum ama... bir süre benimle kalır mısın? Kimse bizi rahatsız etmeyecek, söz veriyorum.";
			link.l1 = "Her zaman senin gibi güzel bir hanımefendiye vaktim var. Kocanın şarabından bir şişe açmamı ister misin?";
			link.l1.go = "wife_sex";
		break;
		
		case "wife_sex":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
			DoQuestCheckDelay("PlaySex_1", 1.0);
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "Fuck"; 
		break;
		
		case "wife_26":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "Sanırım onlarsız da yaşayabilirim. Burada para harcamanın binbir yolu var. Tortuga'da ne kadar yakışıklı ve değerli adam var... Her şey için teşekkür ederim, kaptan. Ama bilmiş olun, lütfen bu meseleyi kimseye anlatmayın yoksa kocam sizi darağacında sallandırır. O iyi biri değildir. Elveda.";
			link.l1 = "Bu kadar mı? Gerçekten öğretici bir deneyimdi. Elveda hanımefendi, size de tavsiyem bu konuda sessiz kalmanız, ben de iyi biri sayılmam. Ama bunu zaten biliyorsunuz, değil mi?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoSex");
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "NoFuck"; 
		break;
		
		case "wife_27":
			PlaySound("Voice\English\Girls_2.wav");
			dialog.text = "Sen kimsin ve burada ne yapıyorsun?";
			link.l1 = "Ne yapmaya çalışıyorsun? Bir anlaşmamız vardı...";
			link.l1.go = "wife_28";
		break;
		
		case "wife_28":
			dialog.text = "Ne anlaşması, monsieur? Ben evli bir kadınım, başka erkeklerle iş yapmam! Şimdi odamdan çıkın yoksa kocamı ve muhafızlarını çağırırım!";
			link.l1 = "Öyle mi diyorsun? Pekâlâ, o zaman iyi kocanı biraz aydınlatayım bakalım!";
			link.l1.go = "wife_29";
		break;
		
		case "wife_29":
			dialog.text = "Defol şimdi, seni küstah herif, yoksa adamlarım seni Fort La Roche'un zindanına atacak! Tehditlerin umurumda değil! Defol!";
			link.l1 = "...";
			link.l1.go = "wife_30";
		break;
		
		case "wife_30":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "FMQT_FinalFail");
			pchar.questTemp.FMQT.Marceline = "Deception"; // Rebbebion, для "Путеводной звезды"
		break;
		
		case "pirate":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\tavern\Pyanici-03.wav");
			pchar.quest.FMQT_late2.over = "yes";
			FreeSitLocator("Tortuga_tavern", "sit_base2");
			dialog.text = "Sen kimsin? Ah, neyse. Kadınlara güvenme, dostum. Kitapta da yazdığı gibi... en saf fahişe bile oyunlarıyla seni cehennemin dibine sürükleyebilir. Otur şöyle, bir içki iç!";
			link.l1 = "Memnuniyetle!";
			link.l1.go = "pirate_1x";
		break;
		
		case "pirate_1x":
			DialogExit();
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_base2");
			LAi_SetSitType(pchar);
			npchar.Dialog.currentnode = "pirate_1";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 2.0);
		break;
		
		case "pirate_1":
			PlaySound("Voice\English\tavern\Pyanici-05.wav");
			dialog.text = "Ne bakıyorsun? Doldur hadi!!";
			link.l1 = "Şerefe sana!.. Bak dostum, burada vakit kaybetmeyeceğim. O sende olan yedek anahtara ihtiyacım var, ne demek istediğimi biliyorsun. Onu bana ver, yollarımızı ayıralım: sen içmeye devam edersin, ben de zor durumdaki hanımlara yardım etmeye.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Ah be adamım! Az önce söylediklerimden hiçbirini dinlemedin mi! Göründüğünden daha akıllı olmalısın... o fahişe için çalışıyorsun. Kocasının kim olduğunu biliyor musun? Daha geçenlerde, Vali Levasseur sadık zencisi Kampacho'yu gönderdi, 'konuşmak' için buradaki saygın bir tüccara. Zenci adamcağızı kendi dükkanında döve döve öldürdü! Meğer tüccar, bir baloda ya da öyle bir şeyde valinin karısına ufak bir saygısızlık etmiş. Ve işte aynı kaltak, hem güzelliğiyle hem de kocasının altınlarıyla beni baştan çıkardı\nYedek anahtar var. Fransa'da iyi bir kasa hırsızıydım, çocuk oyuncağıydı. Lyon komutanının kızı olmasaydı... asla korsan olmazdım. Bah! Siktir et!";
			link.l1 = "Bu gerçekten çok üzücü, ama iş konuşalım. Anahtar nerede?";
			link.l1.go = "pirate_3";
		break;
		
		case "pirate_3":
			dialog.text = "Dinliyor musun? Ben bu işten çekildim, dostum! Neler olacağını önceden görecek kadar akıllıydım! Gemim yelken açmaya hazır olur olmaz buradan temelli gidiyorum. Anahtarı istiyorsan, parasını öde. Açgözlülük etme, sanırım paraya artık pek ihtiyacın kalmayacak.";
			link.l1 = "Biliyor musun, haklısın. Bir kadının oyuncağı olmak istemiyorum. Tavsiyen için teşekkürler, denizde dikkatli ol!";
			link.l1.go = "pirate_4";
			link.l2 = "Bunun için mi para ödeyeyim? Sana mı? Sen zavallı bir hırsız ve korkaksın. O bok çukurunda kalmalıydın, Lyons. Kim bilir, belki oranın komutanı sana acır, yozlaşmış bir hırsızı damadı yapardı. Ama ben sana acımayacağım, orası kesin. Anahtarı bana kolay yoldan da verebilirsin, zor yoldan da; seçim senin.";
			link.l2.go = "pirate_5";
			link.l3 = "(iç çeker) Ne kadar?";
			link.l3.go = "pirate_6";
		break;
		
		case "pirate_4":
			dialog.text = "Akıllı çocuk, doğru kararı verdin dostum. Bol şans. Umarım bir gün gerçekten seven bir kadın bulursun. Tercihen kızıl ya da sarışın, değil mi?";
			link.l1 = "Elveda, dostum...";
			link.l1.go = "pirate_exit";
		break;
		
		case "pirate_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "9");
		break;
		
		case "pirate_5":
			dialog.text = "Bana hakaret ediyorsun! Çek kılıcını, alçak herif!";
			link.l1 = "Bakalım kolların olmadan kasaları ne kadar iyi açabiliyorsun!";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_duel":
			DialogExit();
			LAi_SetSitType(npchar);
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(npchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
			i = makeint(MOD_SKILL_ENEMY_RATE/4);
			pchar.questTemp.FMQT = "duel";
			PChar.questTemp.duel.enemy = NPChar.id;
			if (MOD_SKILL_ENEMY_RATE > 2) PChar.questTemp.duel.enemyQty = i;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
		break;
		
		case "pirate_6":
			dialog.text = "Sen işten anlayan bir adamsın, bunu kabul ediyorum. Belki de gerçekten başarabilirsin. Elli doblon. Masanın üstünde.";
			link.l1 = "Elli altın mı? Bir parça teneke için mi? Kahretsin. Anahtarı masaya bırak. Şimdi.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "Oldukça yüksek bir bedel... Peki. Al onları.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Pek de ucuz değilmiş... Peki. Onları yakında getireceğim. Burada kal.";
				link.l2.go = "pirate_wait";
			}
		break;
		
		case "pirate_wait":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_SetSitType(npchar);
			npchar.Dialog.currentnode = "pirate_dublon";
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
		break;
		
		case "pirate_dublon":
			NextDiag.TempNode = "pirate_dublon"; // mitrokosta правка явного бага
			dialog.text = "Elli doblon getirdin mi?";
			link.l1 = "Biliyor musun, bence onlarsız da yaşayabilirsin. Anahtar. Masanın üstünde.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "Evet. Al onları.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Hâlâ onları alıyorum.";
				link.l2.go = "exit";
			}
		break;
		
		case "pirate_7":
			dialog.text = "Dans edelim mi?";
			link.l1 = "Ben önderlik edeceğim.";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_8":
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			Log_Info("You have given 50 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "İyi. Aklını kullanırsan, buradan birkaç sekizlik ve başın yerinde çıkabilirsin. Anahtarı al ve tavsiyemi dinle. Bedava. Levasseur'un kadını balık kadar aptal ama kendini kurnaz sanıyor. Ona güvenme. Paçanı topla, ceplerine dikkat et. O pek dişli biri değil, sadece dikkatli ol ve kocasını bu işe bulaştırmaktan kaçın. Son bir şey daha – odasında takılarını sakladığı bir sandık var, kolayca açılır. Payını oraya koyacak. Duydun beni. Denizde dikkatli ol, kardeşim. Unutma, kardeşler kadınlardan önce gelir.";
			link.l1 = "Yolun açık olsun, dostum...";
			link.l1.go = "pirate_9";
		break;
		
		case "pirate_9":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "key";
			pchar.questTemp.FMQT.Caution = "true";
			FMQT_KeyNextDay();
			pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.FMQT_late3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
			AddQuestRecord("FMQ_Tortuga", "10");
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		break;
		
		case "mercen":
			PlaySound("Voice\English\EvilPirates10.wav");
			dialog.text = "Kahretsin! Beklemiyordum... o kadının canı cehenneme! Ustam bana onun gibilerden uzak durmamı söylemişti. Ama iş iştir. Sonunda seni yakalayacağım.";
			link.l1 = "Pekâlâ, dostum... Görünen o ki, ikimizi de kandırmak istemiş, şaşırdım diyemem. Neden kavga etmeye devam edelim ki? İş ister misin? Bende bir tane var. Sen yeteneklisin, benim de senin gibi adamlara ihtiyacım var. Yemek, yatak, düzenli maaş, rom ve elde edilen ganimetten adil bir pay. Sana bunun için söz veriyorum. Ne dersin?";
			//if(CheckCharacterPerk(pchar, "IronWill") || CheckCharacterPerk(pchar, "HT2") || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) link.l1.go = "mercen_1";
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) link.l1.go = "mercen_1";
			else link.l1.go = "mercen_4";
		break;
		
		case "mercen_1":
			//if(CheckCharacterPerk(pchar, "IronWill")) notification("Iron Will", "IronWill");
			//if(CheckCharacterPerk(pchar, "HT2")) notification("Mimicry", "Mimicry");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) notification("Skill Check Passed", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) notification("Skill Check Passed", SKILL_FORTUNE);
			dialog.text = "Senin dilin pek tatlı, ünün de senden önce geliyor, kaptan, bunu kabul ediyorum. Tamam, varım. Geminin adı ne?";
			link.l1 = "'"+pchar.ship.name+"'. Başçavuşla konuş, sana bir yatak ayarlayacaktır. Gemimize hoş geldin!";
			link.l1.go = "mercen_2";
		break;
		
		case "mercen_2":
			dialog.text = "Ha! Dünyada yükseliyorum. O kaltak için ona bir tekme savur benim yerime.";
			link.l1 = "...";
			link.l1.go = "mercen_3";
		break;
		
		case "mercen_3":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_MercenHire", 10.0);
			AddQuestRecord("FMQ_Tortuga", "17");
		break;
		
		case "mercen_4":
			//if(!CheckCharacterPerk(pchar, "IronWill")) notification("Perk check failed", "IronWill");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35) notification("Skill Check Failed (35)", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 21) notification("Skill Check Failed (21)", SKILL_FORTUNE);
			dialog.text = "Güzel konuşuyorsun. Ama gerçek profesyonelleri yanına almak istiyorsan, bu yeterince tatlı değil. Bunu aklında tut. Tabii bir geleceğin olursa.";
			link.l1 = "Bir dene bakalım. Çabuk ol, bir hanımefendiyle randevum var.";
			link.l1.go = "mercen_5";
			link.l2 = "Bugün ikinci bir şans yok. Ben meşgul bir adamım, halıyı kirletmeyelim. Sana, sıradan bir fahişe için ölecek kadar para ödemiyorlar. Hatta sana hiç ödeme yapıp yapmadıkları bile belli değil.";
			link.l2.go = "mercen_6";
		break;
		
		case "mercen_5":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQT_MercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "mercen_6":
			dialog.text = "Haklısın. Henüz kimse bana ödeme yapmadı... Şimdi bunu halledeceğim. Ne istersen yap...";
			link.l1 = "...";
			link.l1.go = "mercen_7";
		break;
		
		case "mercen_7":
			DialogExit();
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("FMQ_Tortuga", "18");
			pchar.questTemp.FMQT.Roomfight = "true";
			FMQT_WifeFinalTalk();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
