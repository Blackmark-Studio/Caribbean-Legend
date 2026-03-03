// Брат Шарля, Мишель де Монпе, он же Дичозо, он же воплощение Кукулькана, он же главный злодей
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
		case "First time":
			if (pchar.questTemp.Sharlie == "takeknife")
			{
				dialog.text = "Hoş geldin, Gezgin Charles! Martinique'in doğu kıyısındaki o korsanları nasıl yendiğini duydum. Artık seninle ilgili yanılmadığımdan tamamen eminim, kardeşim.";
				link.l1 = "İt kopukları beni tuzağa düşürdü. Ama bizi hafife aldılar. Ben, rotacım ve tayfam galip çıktık. Yine de itiraf etmeliyim, sevgili kardeşim, başlarda... işler pek iç açıcı görünmüyordu.";
				link.l1.go = "trial";//промежуточная стадия
				break;
			}
			if (pchar.questTemp.Sharlie == "gambitstage")
			{
				bool bFMQM = CheckAttribute(pchar,"questTemp.FMQM") && pchar.questTemp.FMQM != "fail" && pchar.questTemp.FMQM != "end";
				bool bFMQN = CheckAttribute(pchar,"questTemp.FMQN") && pchar.questTemp.FMQN != "fail" && pchar.questTemp.FMQN != "end";
				bool bFMQT = CheckAttribute(pchar,"questTemp.FMQT") && pchar.questTemp.FMQT != "fail" && pchar.questTemp.FMQT != "end";
				bool bFMQP = CheckAttribute(pchar,"questTemp.FMQP") && pchar.questTemp.FMQP != "fail" && pchar.questTemp.FMQP != "end";
				bool bFMQG = CheckAttribute(pchar,"questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && pchar.questTemp.FMQG != "end";
				bool bFMQL = CheckAttribute(pchar,"questTemp.FMQL") && pchar.questTemp.FMQL != "fail" && pchar.questTemp.FMQL != "end";
				if(bFMQM || bFMQN || bFMQT || bFMQP || bFMQG || bFMQL)
				{
					if (sti(pchar.rank) < 12)
					{
						dialog.text = "Selam, kardeşim! Beni buradan çıkarmak için gösterdiğin içten çabayı takdir ediyorum, ama bir sonraki adım için henüz hazır değilsin. Planım deneyimli bir kaptan gerektiriyor. Karayipler'i keşfetmeye devam et, ödüller kazan ve öğren! Hazır olduğunda devam edeceğiz.";
						link.l1 = "Pekala, ne dersen de, kardeşim. Burada oturan sensin, ben değilim.";
						link.l1.go = "exit";
					} 
					else 
					{
						dialog.text = "Seni görmek güzel, kardeşim. Başkalarına olan sorumluluklarını unutma. Ne zaman müsait olursan, seni bekliyor olacağım – bir sonraki adımımız için bazı fikirlerim var!";
						link.l1 = "Anladım, kardeşim. Sözlerimi tutacağım, ama yakında döneceğim!";
						link.l1.go = "exit";
					}
					break;
				}
				if (sti(pchar.rank) < 12)
				{
					Log_info("Level 12 is required");
					dialog.text = "Denizci Charles! Maceralarını duydum! Planımın bir sonraki aşamasına neredeyse hazırsın. Biraz daha deneyim kazandığında hemen geri gel.";
					if (sti(pchar.rank) < 7)
					{
						dialog.text = "Selam, kardeşim! Beni buradan çıkarmak için gösterdiğin içten çabayı takdir ediyorum, ama bir sonraki adım için henüz hazır değilsin. Planım deneyimli bir kaptan gerektiriyor. Karayipler'i keşfetmeye devam et, ödüller kazan ve öğren! Hazır olduğunda devam edeceğiz.";
					} 
					else 
					{
						if (sti(pchar.rank) < 10)
						{
							dialog.text = "Seni görmek güzel, kardeşim! Duyduğuma göre ilerleme kaydediyorsun! Ama henüz planımın bir sonraki adımına hazır değilsin. Şimdilik yaptıklarını yapmaya devam et ve hazır olduğunda bana geri dön.";
						}
					}
					link.l1 = "Pekala, ne dersen de, kardeşim. Burada oturan sensin, ben değilim.";
					link.l1.go = "exit";
					if(sti(pchar.rank) > 8)
					{
						link.l2 = "Bence öyle değil, kardeşim. Belki sen bu kafese çoktan alıştın, ama ben burada uzun süre kalmaya niyetli değilim – babamız sonsuza kadar bekleyemez. Hadi anlat.";
						link.l2.go = "gambitA";
					}
					break;
				}
				else
				{
					dialog.text = "İyi günler, Charles. Seni görmek kalbimi sevince boğuyor: kesinlikle olumlu yönde değişiyorsun.";
					link.l1 = "Öyle mi? Peki, bunu neye dayanarak söylüyorsun?";
					link.l1.go = "gambit";//переход на Гамбит
					break;
				}
			}
			if (!CheckAttribute(npchar, "quest.givelink_saga") && CheckAttribute(pchar, "questTemp.HWIC.Detector"))//признак, что Гамбит пройден или провален
			{
				dialog.text = "Anladım. Bana bir haberin var, Charles! Peki, nedir durum? Umarım kötü bir şey değildir?";
				link.l1 = "Sana geçen sefer verdiğin tavsiyeye uydum...";
				link.l1.go = "saga";//переход на Сагу
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Fail1") && CheckAttribute(pchar, "questTemp.HWIC.Fail2") && CheckAttribute(pchar, "questTemp.HWIC.Fail3"))//признак, что Гамбит провален по всем трем вариантам
			{
				dialog.text = "Nihayet geldin... Ne haber, sevgili kardeşim?";
				link.l1 = "Sana geçen sefer verdiğin tavsiyeyi dinledim...";
				link.l1.go = "gambit_fale";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "mishelle")//Сага готова к старту
			{
				dialog.text = "Seni görmek ne güzel, Charles! Chevalier de Poincy'yi gördün mü? Görüşmeniz nasıl geçti?";
				link.l1 = "Evet, sevgili kardeşim. Tanıştık. Sana iki haberim var: biri iyi, biri kötü. Önce iyi olanı söyleyeyim. De Poincy'ye olan borcunu hallettim. Kötü haber ise, seni ancak onun adına şu sapkınla ilgili verdiğin sözü yerine getirirsem serbest bırakacak...";
				link.l1.go = "saga_5";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && !CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью
			{
				dialog.text = "La Vega'da nasıl geçti, kardeşim?";
				link.l1 = "Övünecek bir şey yok aslında. Tyrex ilginç bir adam, ama onun iş yapma tarzı bana göre değil.";
				link.l1.go = "saga_17e";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью, но дальше 4 квеста
			{
				dialog.text = "La Vega'da nasıl geçti işler, kardeşim? Bazı söylentiler duydum ve dürüst olmak gerekirse, bunlardan hiç memnun değilim... Charlie Prince.";
				link.l1 = "Bence o söylentilerin neyle ilgili olduğunu biliyorum. Ama hepsi geçmişte kaldı. Artık Tyrex'le çalışmıyorum, o iş bana fazla kirli gelmeye başladı.";
				link.l1.go = "saga_17f";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete") // пиратская линейка пройдена полностью
			{
				dialog.text = "Pekâlâ, selamlar... Korsan Charlie Prens. Söylesene Charles, nasıl bu kadar dibe vurabildin? Buna inanamıyorum. Bir zamanlar İspanyol bir tüccar gemisini yağmalamaktan bahsettiğimde suratını buruşturan kardeşim, şimdi bu bölgenin en çok aranan ve en tehlikeli korsanlarından biri olmuş! Ben bile, şu bataklığın içinde otururken, senin namın kulağıma her ulaştığında utanıyorum. Seni La Vega'ya gönderdiğim güne lanet ettim. Ne ayıp! Bir Fransız soylusu korsanlara katıldı ve kısa sürede hepsinin en kötüsü oldu! Şimdi ne olacak kardeşim? Korsan baronu pozisyonunda bir açık mı arıyorsun?";
				link.l1 = "Hayır. Korsanlıkla işim tamamen bitti, sonsuza dek.";
				link.l1.go = "saga_17g";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			
			dialog.text = "Başka ne var, Charles? Sanırım her şeyi konuştuk. Zaman nakittir, sevgili kardeşim – acele et!";
			link.l1 = "Evet, evet, gidiyorum...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "Mishelle_prisoner":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Maltie_officer"));
			QuestPointerDelLoc("FortFrance_Dungeon", "quest", "quest1");
			SetCurrentTime(13, 30);
			dialog.text = "Charles!.. Seni görmek ne güzel, kardeşim! Elbette inanması zor olabilir, anlıyorum, ama burada olduğuna gerçekten çok sevindim...";
			link.l1 = "Ha! Şuna bak! Ne kadar da mutlu! Sen burada 'Düzen'inle burnundan kıl aldırmazken, Charles ailenin yüz karasıydı, zavallı bir ressam, hayatını kadınların parasıyla sürdüren bir asalak, sarayın sözde 'şövalyesi', öyle mi? Ama şimdi, kendi dostların tarafından hapse tıkıldığında, o hiçbir işe yaramaz kardeşini görmekten 'dünyalar kadar mutlu' oluyorsun!";
			link.l1.go = "Mishelle_prisoner_1";			
		break;
		
		case "Mishelle_prisoner_1":
			dialog.text = "Charles, sen...";
			link.l1 = "Daha bitmedi! Neden kendinle ilgili Fransa'ya hiçbir haber göndermedin?! Yazışma hakkın mı elinden alındı?! Babamız senin için endişelenmekten tamamen hasta oldu! Ve benden de en azından başına ne geldiğini öğrenmemi istedi!..";
			link.l1.go = "Mishelle_prisoner_1a";
		break;
		
		case "Mishelle_prisoner_1a":
			dialog.text = "Charles, babama başıma gelenleri nasıl anlatabilirim ki? Ona ne yazacağım? Hayır, kardeşim, ne kadar zor olsa da, babamızın şimdilik hiçbir şey bilmemesi daha iyi. Sana yazmak da anlamsız olurdu – Paris'te sürekli başka başka adreslerdesin... Beni nasıl buldun?..";
			link.l1 = "Babanın isteği üzerine Malta'ya gittim. Orada, dostun Chevalier de La Brignais'den bazı bilgiler aldım. Bana başındaki dertlerden ve muhtemelen Martinique civarında olduğundan söz etmişti. Sonra Fransa'ya döndüm ve babanı ziyaret ettim. Ve tüm bunlardan sonra, şu cehennem çukuruna, kavurucu sıcağa geldim; burada sivrisinekler insanı resmen canlı canlı yiyor...";
			link.l1.go = "Mishelle_prisoner_1b";
		break;
		
		case "Mishelle_prisoner_1b":
			dialog.text = "Bütün bunları babana anlattın mı?";
			link.l1 = "Hayır. Ve Chevalier de La Brignais de mektuplarına cevap vermedi, kötü sonuçlardan korktuğu için... Babamız hâlâ senin akıbetinden habersiz. Seni bulup bu işin aslını öğrenmeye karar verdim. Bilmiş ol, Martinique'e senin için değil, zavallı babamız için geldim!";
			link.l1.go = "Mishelle_prisoner_2";
		break;
		
		case "Mishelle_prisoner_2":
			dialog.text = "Gerçekten mi? Charles, ne zamandan beri aileni umursuyorsun? Hadi dürüst olalım kardeşim, Paris'te herkes babanın kim olduğunu biliyor. Belki de Maure soyadını taşıyorsun, ama asıl derdin de Monper adının lekelenmemesi. Çünkü öyle olursa, soylu kökenini kullanıp herkese kahramanlık hikâyeleri anlatamazsın, değil mi? Paris'in en seçkin evlerinin kapıları sana kapanır, Louvre'un yakınına bile yaklaştırmazlar. Sahi, babamızın vatan için savaşan adamlarını boynuzlarken gönlünü çaldığın o metreslerin ve sevgililerin, bir devlet suçlusunun kardeşiyle birlikte olmaktan mutlu olacaklarına gerçekten inanıyor musun? Sanırım buraya da yine evli bir kadının yatağından çıktığın gibi geldin, yanılıyor muyum? Charles, yüzünde ne var öyle? Bir damarıma mı bastım?";
			link.l1 = "Sen... Sen!..";
			link.l1.go = "Mishelle_prisoner_3";
		break;
		
		case "Mishelle_prisoner_3":
			dialog.text = "Pekâlâ, kardeşim. Birbirimize laf soktuk, bu kadar yeter. Mükemmel olmadığımı kabul ediyorum. Ama sen de melek değilsin. Charles, gerçekten şimdi tartışmanın zamanı değil. İkimizin de amacı aynı: Monper ailesinin onurunu ve itibarını kurtarmak... sebeplerimiz ne olursa olsun. Kardeşim, hayatımızda bir kez olsun, huzur için kini bir kenara bırakalım. Anlaştık mı?";
			link.l1 = "Deneyelim bakalım... Ama bana neyle suçlandığını açıklar mısın?";
			link.l1.go = "Mishelle_prisoner_4";
		break;
		
		case "Mishelle_prisoner_4":
			dialog.text = "Resmiyette, mesele Cemiyetin parasının harcanması gibi görünüyor. Gerçekte ise, işin aslı çok daha derin.";
			link.l1 = "Demek, örgütünün parasını zimmetine geçirdin? Vay, vay...";
			link.l1.go = "Mishelle_prisoner_5";
		break;
		
		case "Mishelle_prisoner_5":
			dialog.text = "Sana söylediklerim resmi suçlamalardı. Bir tek louis d'or bile almadım. Olay şöyle oldu... bak, sana her şeyi ayrıntısıyla anlatamam, çünkü hâlâ parmaklıklar ardındayım. Topluluğumuzun sırlarını açığa çıkarmaya ahlaki hakkım yok.";
			link.l1 = "Lütfen, anlatmaya çalış, sevgili kardeşim. Bilme hakkım var, sence de öyle değil mi?";
			link.l1.go = "Mishelle_prisoner_6";
		break;
		
		case "Mishelle_prisoner_6":
			dialog.text = "Pekâlâ. Karayipler'deki siyasi dengeleri değiştirmesi beklenen, son derece tehlikeli ve hassas bir operasyon için para aldım. Fransız kolonilerinin genel valisi Philippe de Poincy'nin doğrudan emriyle hareket ediyordum. Ama tüm çabama rağmen operasyon başarısız oldu.\nDe Poincy, tüm umutlarını bağladığı planları suya düşünce öfkeye kapıldı. Tutuklanmam için emri bizzat kendisi imzaladı ve yerine getirilmesini sağladı. Sonra buraya gelip, eğer ben ya da akrabalarım operasyona harcanan parayı geri ödemezsek, beni zimmete para geçirmek ve Tarikat'a ihanetle suçlayacağını açıkladı.";
			link.l1 = "İşte güzel bir rezalet. Nerede bu para, ki anladığım kadarıyla ailemiz senin saçmalıklarının bedelini ödemek zorunda?";
			link.l1.go = "Mishelle_prisoner_7";
		break;
		
		case "Mishelle_prisoner_7":
			dialog.text = "Operasyonu hazırlamak için harcandı. Rüşvetler, seferlerin düzenlenmesi, her türlü mal ve ekipmanın satın alınması... Oldukça yüklü masraflarım oldu. Dediğim gibi - bir kuruş bile almadım.";
			link.l1 = "Ve istenen miktar nedir?";
			link.l1.go = "Mishelle_prisoner_8";
		break;
		
		case "Mishelle_prisoner_8":
			dialog.text = "Bir milyon.";
			link.l1 = "Merde! Şaka yapıyorsun, değil mi?!";
			link.l1.go = "Mishelle_prisoner_9";
		break;
		
		case "Mishelle_prisoner_9":
			dialog.text = "Şaka yapacak bir halde mi görünüyorum? Hayır, sevgili kardeşim, bu acı gerçek. De Poincy'ye bir milyon peso teslim etmemiz gerekecek.";
			link.l1 = "Ama kahretsin! Ailemizin o kadar parası yok ki! Yirmi yılda bir araya getiremeyiz o kadarını!";
			link.l1.go = "Mishelle_prisoner_10";
		break;
		
		case "Mishelle_prisoner_10":
			dialog.text = "Eğer parmaklıklar ardında olmasam ve Cemiyet’e olan yükümlülüklerim olmasa, altı ayda, en fazla bir buçuk yılda bu işi halledebilirdim. Charles, burası Yeni Dünya. Burada her şey farklı. Hırslı ve azimli biri, Avrupa’daki gibi ömrünü buna adamadan da burada servet kazanabilir.";
			link.l1 = "Yarım yılda bir milyon mu?! Aklını mı kaçırdın? Bu kadar eminsen, neden gidip bunu de Poincy'ye anlatmıyorsun? Bıraksın seni. Elinden geleni yap...";
			link.l1.go = "Mishelle_prisoner_11";
		break;
		
		case "Mishelle_prisoner_11":
			dialog.text = "Saçmalama Charles! Poincy'nin beni bu hücreden salıvereceği falan yok. O kadar kolay olsaydı, senden yardım istemezdim.";
			link.l1 = "Yani, senin özgürlüğün için parayı bulmak bana mı kaldı?!";
			link.l1.go = "Mishelle_prisoner_12";
		break;
		
		case "Mishelle_prisoner_12":
			dialog.text = "Sadece benim özgürlüğüm değil. Yoksa unuttun mu? Saraylar, balolar ve soylu fahişelerle seks üzerine sohbetimize geri mi dönelim? Evet, Charles, bunu yapmak zorunda olan sensin. Tabii ki, Paris'teki o sahte hayatını eskisi gibi sürdürmek istiyorsan. Bunu istersin, değil mi kardeşim?";
			link.l1 = "Ama Allah kahretsin, bunu nereden bulacağım peki?! Buralarda louis d'orların yaprak yerine yetiştiği eski ormanlar falan biliyor musun?";
			link.l1.go = "Mishelle_prisoner_13";
		break;
		
		case "Mishelle_prisoner_13":
			dialog.text = "Tüm Yeni Dünya para ağaçlarıyla dolu bir koru gibi, ama insanlar kafalarını kaldırıp dallara uzanacak kadar bile zahmete girmiyorlar. Merak etme Charles, senin işin yolunda gidecek. Seni çocukluğumuzdan beri tanıyorum ve eğer seni aptal ya da tembel biri olarak görseydim, babamızı buraya göndermesi için ikna etmeye asla zaman harcamazdım.\nDaha önce bahsettiğim eksiklerine rağmen, cesursun, hırslısın, zekisin, dilin de yeterince sivri ve rapier kullanmayı biliyorsun ki, burada sahip olunması gereken en önemli becerilerden biri bu...";
			link.l1 = "Çok teşekkür ederim. Sevgili kardeşim gerçekten beni övmeye tenezzül etti mi? Oysa ben kendimi zavallı bir ressam, bir saray soytarısı sanıyordum...";
			link.l1.go = "Mishelle_prisoner_14";
		break;
		
		case "Mishelle_prisoner_14":
			dialog.text = "Saçmalamayı bırak. Anlaştık mı, anlaşmadık mı?";
			link.l1 = "Affedersin kardeşim. Ağzımdan kaçtı. Senden böyle sözler duymaya alışık değilim. Sokak fahişesinin ruh kurtarmaktan bahsetmesi gibi bir şey bu.";
			link.l1.go = "Mishelle_prisoner_15";
		break;
		
		case "Mishelle_prisoner_15":
			dialog.text = "Devam edelim, kardeşim. Dediğim gibi, burada başarılı olmak için gereken her şeye sahipsin. Üstelik yalnız da değilsin. Sana ne yapman ve nasıl yapman gerektiği konusunda yardımcı olacağım. Beni dinle, birlikte bu işin üstesinden alnımızın akıyla çıkarız. Bana güven, tecrübemde birini kolay kolay bulamazsın. Artık boş lafı bırakıp esas konuya geçmeye hazır mısın?";
			link.l1 = "Evet, galiba burada bir süre kalacağım... Peki. Seni dinliyorum, Michel.";
			link.l1.go = "Mishelle_prisoner_16";
		break;
		
		case "Mishelle_prisoner_16":
			dialog.text = "Evet kardeşim, burada bir süre kalacaksın. Bunu şimdi görebiliyor olman iyi. Eğer Paris'te seni bekleyen bir saraylı varsa, onu unutmanı tavsiye ederim. Ama üzülme, buradaki kızların da kendine has cazibeleri var.\nYalnız, onlar gerçek erkekleri sever; güçlü, kendine güvenen, hatta biraz sert olanları. Yani bir koloni kızıyla birlikte olacaksan, şiirle, resim sohbetleriyle ya da ay ışığında yürüyüşlerle bir yere varamazsın. Bunlar onlara göre değil.";
			link.l1 = "Pekâlâ, kardeşim. Yoksa yine gevezelik nöbetin mi tuttu? Lafı dolandırma. Tavsiyeni dinlerim, ama o iğrenç imalarını değil.";
			link.l1.go = "Mishelle_prisoner_17";
		break;
		
		case "Mishelle_prisoner_17":
			dialog.text = "Harika. Başarıya ulaşmak için bir gemin olmalı. Karayipler bir takımada. Bunu biliyorsun, değil mi? Hayat burada denizle iç içe. Kendi gemisi olan birinin kazanç ufku sonsuzdur.";
			link.l1 = "Ama ben denizci değilim!";
			link.l1.go = "Mishelle_prisoner_18";
		break;
		
		case "Mishelle_prisoner_18":
			dialog.text = "O halde, kaptan olmanın zamanı geldi. Zaten başka seçeneğin yok. Liman memuru olmayı ya da garnizona kaydolmayı düşünmedin herhalde, değil mi? Hayır mı? O zaman kaptan olacaksın.";
			link.l1 = "Kariyerimde ne olaylar oldu! Şimdi kendime bir gemiyi nereden bulacağım?";
			link.l1.go = "Mishelle_prisoner_19";
		break;
		
		case "Mishelle_prisoner_19":
			dialog.text = "Limanımızdaki tersanede harika bir lugger seni bekliyor. Büyük sayılmaz, ama oldukça rahat bir tekne; denizciliğe ilk adımlarını atmak için tam sana göre. Bu lugger özellikle benim için yapıldı. Arkadaşlarımın yardımıyla gemi için beş bin peso kapora verdim. Gemi yapımcısına git ve ona Michel de Monper'in seni gönderdiğini söyle. Neden geldiğini anlayacaktır.";
			link.l1 = "Geminin fiyatı sadece beş bin mi? Bu biraz garip...";
			link.l1.go = "Mishelle_prisoner_20";
		break;
		
		case "Mishelle_prisoner_20":
			dialog.text = "Kardeşim, beni dinliyor musun? Beş bin sadece kapora. Lagger'ın fiyatı yirmi bin peso civarında. Yani geri kalan parayı kendin kazanman gerekecek. Ayrıca, bir tayfa ve bir dümenci tutmak için de paraya ihtiyacın olacak.";
			link.l1 = "Harika!   Peki, onu nasıl alacağım?";
			link.l1.go = "Mishelle_prisoner_21";
		break;
		
		case "Mishelle_prisoner_21":
			dialog.text = "Burada şaşılacak bir şey yok. Hak et. Başka nasıl olacak? Burada para her köşe başında bulunur, yeter ki nerede arayacağını bil ve zorluktan korkma. Şuradaki çeşitli mekânlarda dolaş. Yerli insanlarla konuş. Mutlaka bir iş bulursun. Ama dikkatli ol, dürüst insanlardan çok daha fazla üçkâğıtçı var. Eğer sen de dürüst biri değilsen, evlerden değerli bir şeyler çalmayı deneyebilirsin.";
			link.l1 = "Ama biz soyluyuz, değil mi?";
			link.l1.go = "Mishelle_prisoner_22";
		break;
		
		case "Mishelle_prisoner_22":
			dialog.text = "Burada unvanların hiçbir önemi yok. Herkes gibi çalış, dövüş, çal. Bir tekne aldıktan sonra bir mürettebat tutmalısın. Başta tekneyi kendin süremeyeceksin, bu yüzden bir dümenciye ihtiyacın olacak. Bunların hepsini meyhaneciyle konuşabilirsin, sana yardımcı olur. Tabii ki kaybolmamaya dikkat et. Denize açıldığında doğrudan Guadalupe'ye yelken aç...";
			link.l1 = "Bu da ne? Bir kasaba mı?";
			link.l1.go = "Mishelle_prisoner_23";
		break;
		
		case "Mishelle_prisoner_23":
			dialog.text = "Burası buradan neredeyse iki gün uzaklıkta bir ada. Bir an önce takımadanın haritasını edinmeye bak ve 'Rabbin Duası' gibi ezberle, yoksa bir kasabayla bir adanın farkını ayırt edebilen herkesin gözünde rezil olursun. Takımada çevresinde epeyce dolaşman gerekecek, o yüzden şimdiden hazırlıklı ol.";
			link.l1 = "Hm. Peki. Peki bu, şeyde... Guadeloupe'ta ne yapmam gerekiyor?";
			link.l1.go = "Mishelle_prisoner_24";
		break;
		
		case "Mishelle_prisoner_24":
			dialog.text = "Orada 'Fadey' adında bir adamı bul. Limanın yakınlarında kendi evi var. Ona beni tanıdığını söyle ve borcunu ödemesini iste – kart oyununda bana fena halde kaybetti. Alacağın para, yeniden toparlanmana yardımcı olur. Onu işlerini yoluna koymak için kullan.";
			link.l1 = "Ne demek, işleri yoluna koymak?";
			link.l1.go = "Mishelle_prisoner_25";
		break;
		
		case "Mishelle_prisoner_25":
			dialog.text = "Yani, bu parayı kullanıp daha fazlasını kazan, ticaret yap mesela. Bu konuya sonra tekrar döneriz. Şimdi gemiye göz kulak ol, Guadeloupe'a git, o şişman Moskova'lıyı bul ve ondan borcu tahsil et. Tabii ki kelimesi kelimesine değil. Fadey, Guadeloupe'ta çok saygın biridir ve yerel valinin de dostudur. Yani kavga etmenin bir anlamı yok. Tam tersine, onunla dost olmaya çalış. Parayı alınca hemen bana dön. Anlaşıldı mı, kardeşim?";
			link.l1 = "Anladım. Ah, neden... Ne yaptım da bu cezayı hak ettim...";
			link.l1.go = "Mishelle_prisoner_26";
		break;
		
		case "Mishelle_prisoner_26":
			dialog.text = "Üzülme, Charles. Bunu kaçınılmaz bir kötülük ya da... belki de gizli bir nimet olarak kabul et. Zamanla, hayatının bu yöne sapmasına kaderine minnettar olacaksın. Sen, kardeşim, sonunda gerçek bir adam olduğunu kanıtlama şansına sahipsin. Hatta belki de düzgün bir insan olabilirsin...";
			link.l1 = "(START TUTORIAL) Yine o saçmalık mı?";
			link.l1.go = "Mishelle_prisoner_27";
			link.l2 = "(EĞİTİMİ ATLA) Kardeşim, buna ayıracak vaktim yok. Sıkıcı kısmı atlamak ve hemen denizlere açılmak istiyorum. Bir gemim olur olmaz, sen de şu berbat yerden kurtulacaksın. Yoksa burada daha fazla mı kalmak istersin?";
			link.l2.go = "Mishelle_prisoner_29"; // Addon 2016-1 Jason пиратская линейка 1
		break;
		
		case "Mishelle_prisoner_27":
			dialog.text = "Hayır, hayır. Yanlış anlama... Peki Charles, vakit kaybetme. Ne yapman gerektiğini biliyorsun. Fadey'nin parasıyla, kendi geminin kaptanı olarak Guadeloupe'tan dönmeni bekleyeceğim. İyi şanslar, kardeşim. Sana güveniyorum.";
			link.l1 = "Seni hayal kırıklığına uğratmamaya çalışacağım. Peki, Michel. Bir dahaki sefere görüşürüz!";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_28":
			DialogExit();
			pchar.questTemp.Sharlie = "ship";//флаг на старт мини-квестов для сбора денег
			//LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);// таверна закр
			if(!bHardcoreGame) LocatorReloadEnterDisable("Fortfrance_town", "reload7_back", true);// ЦЕРКОВЬ закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", true);// ростовщик закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", true);// тюрьма закр
			bDisableFastReload = false;//open быстрый переход
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5");
			//Sharlie_CreateGigoloMan();//мини-квесты на бордель и на джунгли
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_PortMan"), "questmarkmain");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
				QuestPointerToLoc("Fortfrance_town", "reload", "reload3_back");
			}
			QuestPointerToLoc("Fortfrance_town", "reload", "reload6_back");
			/*pchar.quest.CreateGigoloMan.win_condition.l1 = "Hour";
			pchar.quest.CreateGigoloMan.win_condition.l1.start.hour = 17.00;
			pchar.quest.CreateGigoloMan.win_condition.l1.finish.hour = 18.00;
			pchar.quest.CreateGigoloMan.function = "Sharlie_CreateGigoloMan";*/
			/* pchar.quest.SharlieremoveLocks.win_condition.l1 = "HardHour";
			pchar.quest.SharlieremoveLocks.win_condition.l1.hour = 23;
			pchar.quest.SharlieremoveLocks.win_condition.l2 = "location";
			pchar.quest.SharlieremoveLocks.win_condition.l2.location = "FortFrance_Town";
			pchar.quest.SharlieremoveLocks.function = "Sharlie_removeLocks"; */
			//устанавливаем прерывание на джунгли
			pchar.quest.Jungle_jew.win_condition.l1 = "location";
			pchar.quest.Jungle_jew.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Jungle_jew.function = "Junglejew_CreateIndians";
			
			ref location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
		break;
		
		case "Mishelle_prisoner_29": // Addon 2016-1 Jason пиратская линейка 1
			dialog.text = "Heh! Bu 'sıkıcı kısım' bir gün hayatını kurtarabilir... Neyse. Şu anda parayı bulmanın kolay bir yolu var.\nYerel kiliseye git ve Başrahip Benoit ile konuş. O, babamızın eski bir dostudur. Durumu anlat, dizlerinin üstüne çök ve sana bir gemi alacak kadar para ödünç vermesi için ona yalvar.";
			link.l1 = "(EĞİTİMİ GEÇ) Şimdi çok daha iyi! Başrahibe gidiyorum.";
			link.l1.go = "Mishelle_prisoner_31";
			link.l2 = "(START TUTORIAL) Borçlarını daha da artırmamı ister misin? Beni aptal mı sanıyorsun, kardeşim? Bununla bana hiç yardımcı olamayacağını görüyorum. Demek her şey yine bana kaldı.";
			link.l2.go = "Mishelle_prisoner_30";
		break;
		
		case "Mishelle_prisoner_30":
			dialog.text = "Vay canına! Seninle ilgili yanılmamışım, kardeşim. Guadeloupe’dan kendi geminin kaptanı olarak ve Fadey’nin parasıyla dönmeni dört gözle bekliyorum. Yolun açık olsun!";
			link.l1 = "Görüşürüz. Burada iyi eğlenceler.";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_31":
			DialogExit();
			AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
			pchar.questTemp.Sharlie = "ship_fast"; // ускоренный старт
			pchar.questTemp.Sharlie.FastStart = "true";
			LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5-1");
			location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			Sharlie_removeLocks("");
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Korkutucu olduğunu mu söylemeye çalışıyorsun? Gerilme, kardeşim. Hiçbir sorun yok. Ben de ilk deniz savaşımda kendimi kahraman gibi hissetmemiştim. Saçmalık. Bir iki aya kadar, böyle karşılaşmalar sana sıradan bir olay gibi gelecek... Fadey'i gördün mü?";
			link.l1 = "Yaptım... Ama böyle bir başarıyla... Neden uğraştım ki?";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Hm. Neden böyle?";
			link.l1 = "Çünkü kendisi de zor durumda. Kısa süre önce soyulmuş ve kendi maddi sıkıntıları varmış. Bunun yerine bana koleksiyonundan bir hançer teklif etti. Değerli olduğunu ve tüm borcun toplamından daha fazla ettiğini söyledi. Ben de kabul ettim...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Fadey mi? Sıkıştı mı? Para sıkıntısı mı? Ha-ha-ha! Güldürdün beni, sevgili kardeşim! O lanet Moskof seni hemen çözdü, acemi olduğunu anladı ve... ah, o herif! Hadi, bana şu ihtiyarın borcuna karşılık verdiği hançeri göster.";
			if (CheckCharacterItem(pchar, "knife_01"))
			{
				link.l1 = "Buyurun...";
				link.l1.go = "trial_3";
				PlaySound("interface\important_item.wav");
			}
			else
			{
				link.l1 = "Yanımda değil. Dışarıdan bakınca sıradan bir hançer gibi görünüyor. Fadey bana bir Hintli şaman tarafından büyülendiğini ve 'Reisin Pençesi' olarak adlandırıldığını söyledi.";
				link.l1.go = "trial_4";
			}
		break;
		
		case "trial_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "Hm. Bakalım... Tanrı o tombul ayıyı yargılayacak. Böyle bir hurdayı, Charles, herhangi bir dükkandan alabilirdin. Tecrübesizliğinden faydalanıp seni kandırmış... Al bakalım, bu çelik parçasını geri al. Hatıra olarak sakla. Kamaranın yatağının üstüne asarsın.";
			link.l1 = "Herifin teki! Boşver... Guadeloupe'a dönüp o yağlı pisliğin yakasına yapışacağım!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_4":
			dialog.text = "Bir şaman tarafından büyülendi mi? Şefin Pençesi mi? Evet... her şey açık. Tanrı o tombul ayıyı yargılayacak. Böyle bir hurdayı, Charles, herhangi bir dükkandan alabilirdin. Tecrübesizliğinden faydalanıp seni kandırmış... Bana da bir sürü masal anlatmaya kalktı, ben de haddini bildirdim. O yüzden bu pençeyi hatıra olarak kamaranda yatağının üstüne asabilirsin... Tabii hâlâ çöpe atmadıysan.";
			link.l1 = "Orospu çocuğu! Boşver... Guadeloupe'a dönüp bu yağlı herifi bir sarsacağım!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			dialog.text = "Sakin ol, sevgili kardeşim, rahatla. Buna gerek yok, tabii Basse-Terre zindanında birkaç ay geçirmek istemiyorsan. Sana ne dediğimi unuttun mu? O kendini beğenmiş ayı, Guadeloupe valisi Claude François de Lyon'un dostu. Buradan çıkar çıkmaz onunla konuşacağım... açık açık. Hiçbir yere gitmiyor.";
			link.l1 = "Pekâlâ. Onunla sen ilgilensen iyi olur... Görünen o ki, bana vaat edilen başlangıç parası da yalan oldu?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Öyle görünüyor, Charles. Ama moralini bozma. Karayipler'de gemisi ve aklı yerinde olan biri yolunu bulur. Senin de ikisi de var, değil mi?";
			link.l1 = "Ne ima etmeye çalışıyorsun? Bu hançerle işim karıştı, peki şimdi ne yapmamı bekliyorsun...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "Sakin ol, sevgili kardeşim! Neden birdenbire bu kadar huzursuz oldun? Sakin ol, daha uzun yaşarsın. Hiçbir şey ima etmiyorum. Aklımdan bile böyle bir şey geçmedi!";
			link.l1 = "Üzgünüm, Michel. Sadece biraz... yani, beni de anlamaya çalış!";
			link.l1.go = "trial_8";
		break;
		
		case "trial_8":
			dialog.text = "Anlıyorum. Ve gerçekten sana yardım etmek istiyorum! O yüzden iyi dinle. Daha ciddi işlere girişmeden önce biraz tecrübe kazanmalı ve en azından biraz para biriktirmelisin. Gerekli hazırlık olmadan maceralara atılmak tam anlamıyla intihar olur. Henüz bu yerin seni ezip geçmesini istemem.";
			link.l1 = "Çok etkileyici. Ne tür maceralardan bahsediyorsun, Michel? Nedense senin gevezeliklerini takip edemez oldum.";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "Kardeşim, sana hatırlatmak isterim ki, daha doğrusu, biz, de Poincy'ye bir milyon peso borçluyuz. Bunu gerçekten dürüstçe kazanabileceğini mi sanıyorsun? Elbette, ticaretle bu kadar kazanmak mümkün, şansın yaver giderse olabilir, ama Karayipler'de ticaret de pek huzurlu bir iş sayılmaz.\nMacera seni ister istemez bulacak—soru şu: zamanı geldiğinde hazır olacak mısın? En iyisi önce davranmak. Si vis pacem, para bellum, Charles...";
			link.l1 = "Yine mi o süslü laflar? Rica ediyorum, açık konuş...";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "Bu Latince, sevgili kardeşim. 'Barış istiyorsan, savaşa hazırlan' dedim. Bu sözü, harekete geçmek için bir liderlik anlayışı olarak gör. Günlüğüne yazıp, her sabah duadan sonra tekrar okuyabilirsin. Öğrenmen gereken çok şey ve kavraman gereken daha da fazlası var...";
			link.l1 = "Pekala, bu kadar yeter. Bilimsel makalelerinden bıktım artık. Sadede gelelim.";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			dialog.text = "I am being specific, you just don't understand yet. Fine. First, you need to get familiar with the archipelago and get used to your new life as captain of a ship. You will have to work hard to ensure your well-being and a wage for your crew. There are many ways to make coin.\nTaking freights and passengers on board are the simplest. Merchants in stores may give you freight contracts and passengers will approach you on the streets themselves. You should also consider checking harbour offices; having a lugger or any fast ship will allow you to earn good money as a courier.\nHarbour masters will provide you with very profitable freight contracts once you acquire a bigger ship. Talk with people, don't boast about your lineage, be friendly and things will go just fine. Visit colony governors, they often offer well-paid work.\nYou may try trading but in that case you should hire a decent purser. Be careful at sea, avoid Spanish military squadrons and warships. If you meet a lone Spanish trader or an unprotected convoy, you may try to capture them.";
			link.l1 = "Ne?! Michel, kulaklarım mı sağır oldu? Bana korsan olmayı mı öneriyorsun? Sen, Cemiyet’in gururu, Tanrı ve Kutsal Üçleme’nin hizmetkârı, bana böyle bir hayatı mı teklif ediyorsun?";
			link.l1.go = "trial_12";
		break;
		
		case "trial_12":
			dialog.text = "Oh, Charles... Sana tavsiyem, bu titizliğinden bir an önce kurtul; burada kimse buna değer vermez. Ve Şövalyelik hakkında... saf olma, kardeşim. Belki Avrupa'da Louvre ve Escorial arasında bir tür barış vardır, ama burada savaş var. Herhangi bir İspanyol korsanı, gemini yağmalamaktan ve seni ve tayfanı seren direğine asıp kurutmaktan çekinmez.\nBu yüzden, düşman bir ülkenin ticaret gemisini yağmaladığın için kimse seni suçlamaz, emin ol. Hatta bir korsanlık mektubun olursa, yetkililerden resmi destek bile alırsın...";
			link.l1 = "Hayattaki prensiplerini anlamaya başlıyorum. Tıpkı altı ayda bir milyon 'kazanabileceğin' yöntemleri anladığım gibi.";
			link.l1.go = "trial_13";
		break;
		
		case "trial_13":
			dialog.text = "Ve bu yöntemleri kullanmak zorunda kalacaksın, Charles. Sonuçta, bu yöntemler yetkililer tarafından açıkça ya da gizlice destekleniyor. Ticaretle uğraşsan bile, bir gün korsanlarla ya da İspanyol akıncılarla savaşmak zorunda kalacaksın, çünkü onlar için sen ganimetsin.\nKendi iyiliğin için eski hayata bakış açını unutman en doğrusu olur. Bana güven, kardeşim, yüzünü kaybetmeden, hatta yetkililerin takdirini ve halkın sevgisini kazanarak pek çok şey yapabilirsin.";
			link.l1 = "Beni şaşırtmaktan hiç vazgeçmiyorsun, Michel. Şimdi de korsan olmamı söylüyorsun. Sırada ne var?";
			link.l1.go = "trial_14";
		break;
		
		case "trial_14":
			dialog.text = "Bunu fazla dramatize etme, Charles. Gerçekten çok basit: avla ya da avlan. Felsefenin tamamı bu. Ben ilkini tercih ediyorum ve senin de benim örneğimi takip etmeni isterim. Ve sana korsan ol demiyorum, sadece düşman bir devlete karşı askeri harekâta katılmanı, hem de yalnızca geçerli bir sebep olduğunda, söylüyorum.";
			link.l1 = "Bir ayrıcalık mı diyorsun?";
			link.l1.go = "trial_15";
		break;
		
		// Rebbebion, небольшое изменение диалога
		case "trial_15":
			dialog.text = "Gördün mü, anlıyorsun aslında, kardeşim. Ama artık yeter, lafa gerek yok. Kendini sınamanın zamanı geldi. Hazır hissettiğinde yanıma gel. Biraz para kazan, daha iyi bir gemi edin, takımadaları tanı ve yeteneklerini geliştir.\nAma unutma, önümüzdeki birkaç ayı meyhanelerde ve genelevlerde geçirip hiçbir işe yarar şey öğrenmezsen... o zaman hiç geri dönme. Anlaştık mı, Charles?";
			link.l1 = "Endişelenme. Buraya eğlenmeye gelmedim... Peki, sonra ne olacak?";
			link.l1.go = "trial_16";
		break;
		
		case "trial_16":
			dialog.text = "Daha sonra bundan sonra ne yapacağını sana anlatacağım. Planımı çoktan hazırladım. Eğer tavsiyelerimi ve önerilerimi dikkatle dinlersen, seni parlak bir gelecek bekliyor Charles.";
			link.l1 = "Böylesine parlak ve görkemli bir gelecektense, mütevazı geçmişimi tercih ederim...";
			link.l1.go = "trial_17";
		break;
		
		case "trial_17":
			dialog.text = "Bana güven kardeşim, değersiz geçmişine bir gün gülüp geçecek ve kaderin seni ondan kurtardığı için şükredeceksin. Umutlu ve pozitif ol. Bu hayatı seveceksin. Göreceksin.\nBir de, ortak dostumuz Fadey'i ziyaret et ve ondan sana bir iş bulmasını iste. Ayının iyi bağlantıları var, eminim sana bir şey ayarlayacaktır. Oyalanma, yoksa bir fırsatı kaçırabilirsin. Ve lütfen beni mahcup etme.";
			link.l1 = "Yine ahlaki öğütler... Tanrım, bu ne zaman bitecek? Peki Michel... Gidebilir miyim artık?";
			link.l1.go = "trial_18";
		break;
		
		case "trial_18":
			dialog.text = "Bekle. Birkaç taktik tavsiye daha. Eğer bir ülkeyle ters düşer ve kanun kaçağı olursan, yerel kiliseye git ve Başrahip Benoit ile konuş. Ona seni benim gönderdiğimi söyle. Hem Papist hem de Kalvinist cemiyetlerinde bağlantıları var ve bu konularda bana defalarca yardımcı oldu. Ama unutma, bu işler ne kolay ne de ucuz; o yüzden düşman edinmemeye çalış.\nDur, bir şey daha! Biz soyluyuz ama hele burada, ellerimizle bir şeyler yapmaktan çekinmek aptallık olur. Gerekli alet ve malzemelerin varsa birçok faydalı eşya üretebilirsin... Söylesene kardeşim, tabancalarından herhangi birini nasıl dolduruyorsun?";
			link.l1 = "Hm. Her zamanki gibi, bir kurşun ve bir tutam barut.";
			link.l1.go = "trial_19";
		break;
		
		case "trial_19":
			dialog.text = "Ha! Farklı bir şey duymayı beklemiyordum zaten.";
			link.l1 = "Başka bir yol biliyor musun, sevgili kardeşim?";
			link.l1.go = "trial_20";
		break;
		
		case "trial_20":
			dialog.text = "Elbette. Ama bunu yapan pek az kişi var, çünkü çoğu ya bilmiyor ya da üşeniyor. Birkaç saatinizi ayırıp barut ve kurşunla kâğıt kartuşlar hazırlayabilirsiniz. Bunları kullanınca tüfeğinizi yarı sürede doldurursunuz. Etkilendin mi?";
			link.l1 = "Hm. Sanırım öyle. İlginçmiş.";
			link.l1.go = "trial_21";
		break;
		
		case "trial_21":
			pchar.alchemy.known = 1;
			AddQuestRecordInfo("Recipe", "cartridge");
			SetAlchemyRecipeKnown("cartridge");
			dialog.text = "Bu kağıt fişek yapımı talimatlarını al, boş zamanlarında incele ve yeni öğrendiklerini uygulamaya üşenme\Dur bir dakika, kardeşim. Sevgili valimizi ziyaret etmeyi unutma.";
			link.l1 = "Bir sebep mi var?";
			link.l1.go = "trial_22";
		break;
		
		// Rebbebion, намёк на "Травлю крысы"
		case "trial_22":
			dialog.text = "Valilerle arayı iyi tutmak her zaman iyidir, hele ki akrabalarınızı adalarında hapse atmışlarsa.";
			link.l1 = "Bana ondan bahset.";
			link.l1.go = "trial_23";
		break;
		
		case "trial_23":
			dialog.text = "Martinique tahtını herkes koruyamaz. Tarikatın, Taç'ın, korsanların çıkarları... ve bir soylu kendi çıkarlarını da unutmamalı. Parquet bu kadar gevşek ve günaha meyilli olmasaydı, belki Poincy onu ciddiye alırdı.";
			link.l1 = "Ve ona ne faydam dokunabilir ki?";
			link.l1.go = "trial_24";
		break;
		
		case "trial_24":
			dialog.text = "Resmî görevlilerin her zaman serbest kaptanlara işi olur. Ama genelde cimri davranırlar ve yalnızca kamu çıkarı söz konusuysa ödeme yaparlar, şahsi meselelerde değil. Yine de, Karayipler'de onurunu korumanın ve ulusal ilişkileri geliştirmenin valilere hizmet etmekten daha iyi bir yolu yok. Fırsatı kaçırma, hele ki Parquet şu sıralar bazı sorunlarla uğraşıyorken. Ne tür sorunlar?";
			link.l1 = "Ne tür bir bela?";
			link.l1.go = "trial_25";
		break;
		
		case "trial_25":
			dialog.text = "Üzgünüm, kardeşim. Burada Tarikat'ın çıkarları söz konusu. Sadece şunu söyleyebilirim: Kolay yoldan zenginleşmek isteyen tek biz değiliz.";
			link.l1 = "Yine üstü kapalı konuşuyorsun... Neyse, vaktim olunca uğrarım.";
			link.l1.go = "trial_26";
		break;
		
		case "trial_26":
			dialog.text = "Şimdi git. İyi şanslar, kardeşim!";
			link.l1 = "Teşekkür ederim... Sonra görüşürüz, Michel.";
			link.l1.go = "trial_27";
		break;
		
		case "trial_27":
			DialogExit();
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Sharlie_Mishelle_OpenWorld");
		break;
		
		case "gambitA":
			dialog.text = "Öyle olsun o zaman. Sana inanıyorum, kardeşim. Şimdi sana baktığımda, gerçekten daha iyiye doğru değiştiğini hissediyorum.";
			link.l1 = "Yok artık. Nasıl yani?";
			link.l1.go = "gambit";
		break;
		
		case "gambit":
			dialog.text = "Seni görebiliyorum, sevgili kardeşim. Yürüyüşünü ve yüzündeki ifadeyi görebiliyorum. Sonunda, beni deliliğin eşiğine getiren o kendini beğenmiş genç çocuğun maskesi senden silinmiş. Yeni hayatın sana artık gerçekten yaramış.";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Anlayamıyorum kardeşim, söylediklerin övgü mü hakaret mi. Ama sana gerçeği söyleyeyim: Oradan benim hakkımda ne düşündüğün umurumda değil. Borcunu ödemek için gereken milyonları topladım, yakında özgür olacaksın. De Poincy'i nerede bulabilirim?";
				link.l1.go = "gambit_1_1";
			}
			else
			{
				link.l1 = "Anlayamıyorum kardeşim, sözlerin övgü mü yoksa hakaret mi. Ama sana gerçeği söyleyeyim: Oradan benim hakkımda ne düşündüğün umurumda değil. İlgilenmem gereken bir yığın değil, bir deniz dolusu işim var ve burada durup seninle laf yarıştıracak vaktim yok. Söyleyecek önemli bir şeyin var mı? Yoksa, ben yoluma devam edeceğim...";
				link.l1.go = "gambit_1";
			}
			DelLandQuestMark(npchar);
			DeleteQuestCondition("Sharlie_GambitStage_level_9");
			DeleteQuestCondition("Sharlie_GambitStage_level_12");
			// уберем маркеры, если ФМК не стали проходить
			DelMapQuestMarkCity("Baster");
			DelMapQuestMarkCity("Fortfrance");
			DelMapQuestMarkCity("Charles");
			DelMapQuestMarkCity("Tortuga");
			DelMapQuestMarkCity("Portpax");
			
			if(CharacterIsAlive("FMQG_pass_1"))
			{
				sld = CharacterFromID("FMQG_pass_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQM_carpenter"))
			{
				sld = CharacterFromID("FMQM_carpenter");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQN_seafox_1"))
			{
				sld = CharacterFromID("FMQN_seafox_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQT_girl"))
			{
				sld = CharacterFromID("FMQT_girl");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") 
			{
				DeleteAttribute(pchar, "questTemp.FMQP");
				sld = CharacterFromID("PortPax_waitress");
				DelLandQuestMark(sld);
			}
			if(CharacterIsAlive("FMQG_cureer"))
			{
				sld = CharacterFromID("FMQG_cureer");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("Guide_y"))
			{
				sld = CharacterFromID("Guide_y");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
		break;
		
		case "gambit_1_1":
			dialog.text = "You've managed to put together a million? Well done, Charles, simply impeccable! But unfortunately, Philippe de Poincy is no longer at his residence; he has departed on Society business, off on a secret expedition. So you'll have to wait a little before visiting him.";
			link.l1 = "Sana da gizli işlerine de lanet olsun! Bütün bunlar bitecek ve eve döneceğim sanmıştım, ama şimdi...";
			link.l1.go = "gambit_1_2";
		break;
		
		case "gambit_1_2":
			dialog.text = "Ve şimdi, sadece daha fazla para kazanma fırsatını açmakla kalmadın, dahası da var. Kardeşim, o yaşlı tilkinin istediği miktarı toplaman gerçekten inanılmaz, ama ben senin kadar kendinden emin ya da rahat olmazdım... De Poincy tam bir kaygan yılan, ve senin mütevazı şahsına fazlasıyla ilgi gösterdi, ve...";
			link.l1 = "Ve şimdi bir milyonun ona yetmeyeceğinden mi korkuyorsun?! Yoksa geçen sefer bir şeyi eksik mi anlattın?";
			link.l1.go = "gambit_1_3";
		break;
		
		case "gambit_1_3":
			dialog.text = "Hiçbir şeyden korkmam, ama seni uyarmalıyım ki Poincy sıradan biri değildir. O yokken, kendine biraz itibar kazandırma fırsatın var; böylece onunla bir hizmetkâr gibi değil, bir eşit olarak konuşabilirsin. Bu yüzden, şimdi sana açıklayacağım planıma uymanı şiddetle tavsiye ederim.";
			link.l1 = "Pekâlâ. Dökülen süt için ağlamanın anlamı yok. Bu cehennem çukurunda biraz daha oyalanacağım. De Poincy sonsuza dek ortalıkta dolaşacak değil ya. Planını bana anlat, neler oluyor?";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_1":
			dialog.text = "Oh! Takdire şayan bir cevap. Charles, artık bir adam olduğuna sevindim. Fakat kardeşine karşı bu kadar sert olma. Doğrusu, sana söyleyeceklerim var. Yeniden buluşmamızı dört gözle bekliyordum ve senin için şimdiden bir sonraki adımının planını hazırladım.";
			link.l1 = "Güzel. O zaman anlat bakalım.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_2":
			dialog.text = "Bak. Elbette, Karayipler'de para önemli bir rol oynar, tıpkı dünyanın her yerinde olduğu gibi, ama para her şeyi çözemez. Başarılı bir adamın sadece dolu bir kesesi değil, aynı zamanda geniş ve çeşitli bağlantıları olmalı; hem de ayak takımından değil, bu dünyada söz sahibi insanlardan.\nOnların hangi milletten ya da sınıftan olduğu önemli değil. Bağlantılar, parayla açılamayan kapıları açar. 'Para ve bağlantıların' birleşimi, bir adama dünyadaki en değerli şeyi verir: güç.\nBöyle bağlantılar kurmayı düşünmelisin ve bunu yük taşımakla, ticaretle, ufak tefek korsanlıkla ya da valilerin gözüne girerek başaramazsın.";
			link.l1 = "Ne öneriyorsun?";
			link.l1.go = "gambit_3";
		break;
		
		case "gambit_3":
			dialog.text = "There are not that many powerful organisations in the Caribbean. One of them is the Dutch West India Company. You can join them. Their headquarters are in Willemstad on Curaçao. The Company often hires third-party captains and offers special long-term contracts to the most useful of them.\nIf you are lucky, you may make a decent career there. I heard that they are experiencing serious trouble now – some English privateer has taken up arms against the Company and is constantly sinking their ships. They can't do anything about him; he is a navy officer, making him too tough for them.\nThey say that he is somehow connected to British military intelligence, and they are very serious people. So, perhaps, taking the side of this captain will be even more profitable for you, but the problem is – I don't know his name, I only know that Antigua is his operational base.\nYou may sail there and ask around. I also heard about some strange organisation which also takes part in this English-Dutch conflict, but I don't know which side they are on. All I know is that the trail leads to Barbados, to Bridgetown...";
			link.l1 = "Yani bana Hollandalılara katılmamı, ya da karanlık bir kaptan veya daha da karanlık bir 'örgüt' aramamı mı öneriyorsun?";
			link.l1.go = "gambit_4";
		break;
		
		case "gambit_4":
			dialog.text = "Seçim senin. Her halükarda, Karayipler'de başkalarının kaderine hükmeden ve büyük güce sahip olanların arasına hızlıca girmenin başka bir yolu yok. Umarım iki üç iyilikle valinin gözüne girip doğrudan Kraliyet Donanması’na kabul edileceğini sanmıyorsundur.";
			link.l1 = "Biliyor musun, sevgili kardeşim. Fransız donanmasında askeri bir kariyerim olacağına hiç inanmadım. Tanrı korusun, senin gibi bir görevi başaramayıp hücreye tıkılıp kalmak istemem... Peki, anladım. Hollanda Şirketi'nin Genel Karargahını bulmakta zorlanacağımı sanmıyorum ama diğer tarafları nasıl arayacağım hakkında en ufak bir fikrim yok";
			link.l1.go = "gambit_5";			
		break;
		
		case "gambit_5":
			dialog.text = "İngiliz korsanına gelince, Antigua'daki St. John's'ta etrafa sorabilirsin. Kesinlikle biri sana yardımcı olacaktır. İngiliz filosunda iş aradığını söyle. 'Üçüncü güç' meselesine gelince, bunun için de Bridgetown'daki insanlarla konuşabilirsin. Orada mutlaka bu örgütle bağlantısı olan biri vardır.";
			link.l1 = "Yaptıkları iş en azından karşılığını bulacak mı? Şirket, bu korsan... Yoksa her şey sadece 'bağlantılar' uğruna mı olacak?";
			link.l1.go = "gambit_6";			
		break;
		
		case "gambit_6":
			dialog.text = "Charles, beni şaşırtıyorsun. Hollanda Batı Hindistan Şirketi, bir kralın bile imreneceği paralarla iş yapar. Sana bahsettiğim korsan, o kadar çok Hollanda gemisini yağmaladı ki, servete boğulmuş olmalı. Ve 'örgüt'ten olanların sadece çok parası yok. Onların elinde tam anlamıyla bir servet var.   Onlar için çalışmak, her zaman pastadan güzel bir pay almanı garanti eder. Onlar gibi insanlar hep büyük oynar. Eğer akıllıysan, kendi oyununu oynayıp daha da fazlasını kazanabilirsin.";
			link.l1 = "Pekala. Düşünüp en iyi seçeneğime karar vereceğim. Başka bir talimatın var mı?";
			link.l1.go = "gambit_7";
		break;
		
		case "gambit_7":
			dialog.text = "Evet. Navigasyon araçlarını nasıl kullanacağını öğrenmelisin. Ne yazık ki, birçok denizci yalnızca pusula ve yıldızlarla yön bulabiliyor ve koordinatlarını tahmin edemiyor. Oysa bu çok önemli.\nŞimdi. Enlemi ölçmek için boussole kullan. Bu alet oldukça nadirdir ve mağazalarda bulamazsın, fakat iki yaygın aletle - pusula ve astrolab - kendin yapabilirsin. Al, işte talimatlar.\nBoylamı hesaplamak biraz daha zordur. Bunun için hassas bir kronometreye ihtiyacın olacak. Sıradan bir gemi kronometresini kum saatiyle ayarlayarak bunu yapabilirsin. Sorun şu ki, böyle bir alet yalnızca bir ay kadar doğru çalışır, sonra hatalar yüzünden fazla sapar.\nKronometreyi sık sık sıfırlamak gerekir. Kum saatlerini Hollanda Batı Hindistan Şirketi'nin ofisinden alabilirsin. Ben de kronometreleri oradan almıştım. Al, işte bu talimatlar.";
			link.l1 = "Teşekkür ederim. Hemen çalışmaya başlayacağım.";
			link.l1.go = "gambit_8";
		break;
		
		case "gambit_8":
			AddQuestRecordInfo("Recipe", "bussol");
			SetAlchemyRecipeKnown("bussol");
			AddQuestRecordInfo("Recipe", "clock2");
			SetAlchemyRecipeKnown("clock2");
			dialog.text = "Tüm bu aletleri en kısa sürede edinmeye bak. Deneyimli ve saygın kaptanların hepsi enlem ve boylamla yol alır. O rakamların ne anlama geldiğini bilene kadar denizcilikte acemi sayılırsın.\nPekâlâ, son zamanlarda konuştuğumuz meselelerde başarıya ulaştığında gelip övünmeyi unutma. Yolun açık olsun, Charles!";
			link.l1 = "Teşekkür ederim, sevgili kardeşim. Eminim bu çok işime yarayacak!";
			link.l1.go = "gambit_9";
		break;
		
		case "gambit_9":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Sharlie = "gambit";//флаг на Голландский Гамбит
			pchar.questTemp.HWIC.CanTake = "true"; //Голландский Гамбит доступен для взятия
			AddQuestRecord("Sharlie", "20");
			npchar.greeting = "mishelle_3";
			AddMapQuestMarkCity("Bridgetown", false);
			AddMapQuestMarkCity("Villemstad", false);
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			// Rebbebion, убираем марки
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "gambit_fale":
			dialog.text = "Peki, senin övünecek neyin var?";
			link.l1 = "Şimdilik bir şey yok. Üç örgütü de buldum ve onlarla çalışmayı denedim, ama puro gibi, her şey daha en başında havaya uçtu. Sanki kader bana karşı oyun oynuyor...";
			link.l1.go = "gambit_fale_1";			
		break;
		
		case "gambit_fale_1":
			dialog.text = "Demek söylentiler doğruymuş... Sevgili kardeşim, kader sana karşı işlemiyor. Buna aptallık ve beceriksizlik denir. Beni hayal kırıklığına uğrattın. Fransa'ya dön, burada yapacak başka bir şeyin yok.";
			link.l1 = "Ama nasıl...";
			link.l1.go = "gambit_fale_2";			
		break;
		
		case "gambit_fale_2":
			dialog.text = "Artık bu senin işin değil. Bununla kendim ilgileneceğim. Bana yardım edebilecek daha yetenekli insanlarım var. Sana güvenmekten korktum, çünkü burada ömrümün sonuna kadar kalmak zorunda kalırım diye düşündüm. Neyse. Hadi git buradan, gene o sevgililerine dön.";
			link.l1 = "Pekâlâ, cehenneme git...";
			link.l1.go = "gambit_fale_3";
		break;
		
		case "gambit_fale_3":
			DialogExit();
			NextDiag.CurrentNode = "gambit_fale_4";
			npchar.lifeday = 30;
		break;
		
		case "gambit_fale_4":
			dialog.text = "Seninle konuşacak hiçbir şeyim yok. Git.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gambit_fale_4";
		break;
		
		case "saga":
			switch(pchar.questTemp.HWIC.Detector)
			{
				case "holl_win": sTemp = "I've entered service with the Dutch West India Company and become a special tasks agent and close friend of the vice administrator of the Company, Lucas Rodenburg. I managed to carry out several serious missions, in particular, I liquidated the actual English privateer. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "holl_fail": sTemp = "I've entered service with the Dutch West India Company, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "eng_win": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship' and did away with Lucas Rodenburg himself, vice administrator of the Company. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "eng_win_half": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship'. Of course, Fleetwood departed to England and my service with him is over, but still..."; break;
				
				case "eng_fail": sTemp = "I've entered service with the English privateer from Antigua, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "self_win": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, and achieved quite a bit: I did away with that English privateer, Richard Fleetwood, put Lucas Rodenburg, the vice administrator of the Company, behind bars, become a close friend of governor Matthias Beck and the company's director Peter Stuyvesant. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "self_fail": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, however it all went down in dust at the moment of truth..."; break;
			}
			dialog.text = "Ee? Hadi ama, sevgili kardeşim, uzatma artık. Nedir güzel haber? Çalışkanlığınla ilgili bazı söylentiler kulağıma geldi ama her şeyi bizzat senden duymak istedim.";
			link.l1 = sTemp;
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "eng_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "Mükemmel! Harika iş çıkardın, Charles! Sana bir an bile şüphe etmedim! Çok yol kat edeceksin, sevgili kardeşim... Böyle kendini meşgul tutman ve bu kadar önemli insanlarla ilişkiler kurman—doğrusu, bunu beklemiyordum. Tebrikler!";
			}
			else
			{
				dialog.text = "Üzülme, Charles. Olmadıysa, yapacak bir şey yok. İstediğimiz sonuca ulaşmak için başka yollar deneriz.";
			}
			link.l1 = "Şimdi ne yapacağız, Michel? Chevalier de Poincy'ye uğramanın zamanı geldi mi? Onunla konuşmaya kendimi oldukça hazır hissediyorum.";
			link.l1.go = "saga_2";	
		break;
		
		case "saga_2":
			dialog.text = "Gerekli bir milyon peso tutarını toplamayı başardın mı?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Evet, şu anda gereken miktara sahibim.";
				link.l1.go = "saga_3_1";
			}
			else
			{
				link.l1 = "Hayır, henüz o kadar param yok.";
				link.l1.go = "saga_3_2";
			}
		break;
		
		case "saga_3_1":
			dialog.text = "Harika! O zaman bu zindanda fazla oyalanmayacağım... Hadi, Capsterville'e git, Saint Christopher adasında, ve de Poincy'den bir görüşme talep et. Muhtemelen valilik sarayında, kaldığı yerde olacaktır. Ondan sonrası için duruma göre hareket et ve unutma: Poincy kurnazdır, hem de çok kurnaz... İçimde kötü bir his var, bu iş öyle kolayca hallolmayacak gibi. Hadi git, kardeşim, ve dikkatli ol!";
			link.l1 = "Uyarılarını aklımda tutacağım, Michel. Merak etme, ben de dün doğmadım. Şimdi şu tilkinin yanına gidiyorum. Sonra görüşürüz!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_3_2":
			dialog.text = "De Poincy ile konuşmanın anlamı yok. Seni içeri bile almaz. Parayı topla kardeşim, zaten bu işlerde epey tecrübelisin, o yüzden çok zorlanmazsın. Parayı bulunca hemen Saint Christopher’daki Capsterville’e git.\nŞövalye muhtemelen valilik sarayında olacak. Bir görüşme iste, seni içeri alacaklardır. Sonra kendin gör ve dikkatli ol: de Poincy kurnazdır, hem de çok kurnaz... İçimden bir ses bu hikâyenin öylece bitmeyeceğini söylüyor.";
			link.l1 = "Uyarılarını aklımda tutacağım, Michel. Merak etme, ben de dün doğmadım. Parayı bulur bulmaz doğruca o kurnaz tilkinin yanına gideceğim. Sonra görüşürüz!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			DialogExit();
			AddMapQuestMarkCity("Charles", false);
			AddLandQuestMark(characterFromId("Puancie"), "questmarkmain");
			npchar.quest.givelink_saga = "true";
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "saga";//флаг на Пиратскую Сагу
		break;
		
		case "saga_5":
			dialog.text = "Vay canına! Tam da bundan korkuyordum. Poincy uzun zamandır peşindeydi, Charles. O yüzden seninle bu kadar ilgileniyor! Karayipler'de kendine epey bir ün yaptın ve şimdi de seni, elinde patlayan işlerini halletmek için kullanmaya karar verdi...";
			link.l1 = "Michel, sanki her şeyin farkındaydın da bana önceden söylemek istemedin gibi bir his var içimde. Her şey fazlasıyla yolunda gidiyor... Önce para, şimdi de işin... Bunlar tesadüf olamaz.";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Charles, gizli bir mesaj arama, yok öyle bir şey. Keşke Poincy'ye parayı geldiğin ilk gün verseydin... Yani, diyelim ki paran olsaydı. Şövalye senden başka bir şey istemezdi. Ama şimdi, seninle ilgilenmeye başladı, burada ne kadar çabuk uyum sağladığını ve neler başardığını gördü, yeteneklerinden faydalanmaya karar verdi.";
			link.l1 = "Doğru... çünkü artık yeteneklerin onun için yeterli değil, öyle mi? Merde! Peki. Burada duvara tosladığımı anlıyorum. Kim bu heretik? Onu nasıl bulabilirim?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Onu aramaya gerek yok! Hiçbir zaman Tortuga'dan ayrılmaz; kendi inşa ettiği kalenin ve garnizonundaki sadık Huguenot askerlerinin koruması altında kalır. Bu yüzden, her bir asker ona sadıktır. Poincy, Tortuga valisi François Levasseur'dan bahsediyordu.\nİspanyollar hâlâ onu oradan çıkaramıyor, ama de Poincy benim bunu tek başıma, donanmanın desteği olmadan başarabileceğime gerçekten inanmıştı; çünkü bir iç savaş başlatmak, Santo Domingo garnizonunun yakınlığı yüzünden büyük bir siyasi hata olurdu.\nYaşlı düzenbaz, lekesiz kariyeri ve yaklaşan emekliliği için her şeyi riske atacak kadar gözü kara değil. Yine de, Levasseur artık sınırı aştı ve tahta tehdit oluşturmaya başladı.\nLevasseur'u bu göreve bizzat atayan de Poincy, bu korkutucu Huguenot'u kişisel düşmanı olarak görüyor ve yerine beni Malta'dan buraya getiren üstüm, Maltalı Şövalye de Fontenay'i getirmek için can atıyor.";
			link.l1 = "Harika! Önce bir milyon kazan, sonra Tortuga valisini öldür. Sıradaki görevim ne olacak? Escorial'da bir komplo mu düzenleyeceğim? Kahretsin! O işi batırmana şaşırmadım. Valiyi ortadan kaldırmak, İspanyol tüccarlarını soymaya benzemez. Ateşten kestaneleri çıkarmaya yemin ederken aklında bir plan var mıydı bari?";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Dürüst olmak gerekirse, hiçbir planım yoktu, çünkü zaten hizmetten ayrılıp, riskli girişimim başarılı olursa aile malikanemize dönmeyi düşünüyordum. Açıkçası, de Poincy'nin dertleri umurumda bile değil.\nEminim, Hint altınını gördüğünde çok daha esnek davranırdı... Ama şu anda tüm kozlar onun elinde. Sanırım Levasseur Tortuga valisi olduğu sürece burada kalacağım.";
			link.l1 = "Peki ya Maltalılar, de Fontenay önderliğinde, gözlerini vali koltuğuna dikmişken, neden Tortuga'yı kendileri basmasınlar?";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Şunu bir düşün. Tarikat, Louis'ye savaş mı ilan edecekmiş? Saçmalama! Böyle bir rezalet asla söz konusu olamaz. Sadece bir şahıs Tortuga'yı ele geçirebilir. Bir korsan ya da senin gibi Katolik bir maceraperest.\nSonrasında, adayı de Poincy'nin göndereceği yeni valinin yönetimine teslim edebilir. Böyle bir hareket, üst düzey yöneticiler açısından son derece uygun görünecektir.";
			link.l1 = "Peki korsanlarla pazarlık yapmanın bir anlamı var mı?";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Sorun şu ki, Levasseur sadece Kardeşlik'ten değil, birçok korsan üzerinde de otorite sahibi. Onlara Tortuga'nın toplarının arkasında saklanma ve yağmaladıklarını serbestçe satma izni veriyor, karşılığında ganimetten pay alıyor.\nEskiden bu payı de Poincy ile paylaşırdı, ama artık paylaşmıyor. Korsan gemileri Tortuga'yı ve garnizonunu koruyacak, bu da kaleyi ele geçirmeyi daha da zorlaştırıyor.";
			link.l1 = "Sence bu mesele tamamen umutsuz mu?";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "There is always a solution, little brother. It is just not always visible on the surface. Not all pirates are sympathetic to the Huguenots of Tortuga. I know at least two influential pirates who consider Levasseur a traitor and scum. I am talking about Steven Dodson, also known as the Shark, and the legendary baron of Mosquito Bay, Jan Svenson.\nI don't know where to find the Shark; I've heard rumours that something happened and he had to leave his base at Isla Tesoro. But you can always find Svenson in Blueweld. He is a significant figure there.";
			link.l1 = "Sence bu... Svenson bana yardım eder mi?";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "O, yardım edersen sana güvenecektir. Şu sıralar işleri pek yolunda gitmiyor ve sadık, yetenekli insanlara ihtiyacı var. Onunla ciddi bir konuşma yapmadan önce, önce ona ne kadar faydalı olabileceğini göstermen gerekecek. Oraya vardığında bunu nasıl yapacağını bulursun. Buradan sana akıl vermek zor.\nSürekli sorular sorduğuna göre, gitmeye karar verdin sanırım Charles?";
			link.l1 = "Bak Michel, de Poincy'ye kendi gümüşümden bir yığınını verdim. O parayı kan, ter ve gözyaşıyla biriktirdim! Ben senin yerinde olsaydım, sen benim için bir tane bile louis d'or riske atar mıydın, hiç emin değilim.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "Charles...";
			link.l1 = "Beni bölme! Babamın yanına eli boş dönmek aptallık olurdu. Sorun hâlâ çözülmedi, sen hâlâ parmaklıklar ardındasın ve Cemiyete ihanetle suçlanma tehlikesiyle karşı karşıyasın. Eğer Poincy'nin 'ricasını' yerine getirmezsem, Monper adını lekelemekten çekinmezdi. Yüzünden okunuyordu bu. O yüzden ben Blueweld'e gidip Svenson'a nasıl yaklaşabileceğimi bulacağım. Bu arada, bana 'unutup' anlatmadığın başka neler olduğunu bir düşün. Mesela, de Poincy'ye götürmen gereken bir Kızılderili altınından ilk kez senden duyuyorum.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "There are things that are better left hidden. You are right, I didn't tell you everything I know. Perhaps, one day I will tell you more, but not before you deal with Levasseur; it would be useless knowledge for now.\nI have no doubt that your touching concern for me is motivated only by your wish to save the honour of our family. By saving me, you are saving yourself first and foremost, and secondly, your chance to visit the finest houses in Paris. Am I wrong?";
			link.l1 = "Korkarım artık öyle değil, kardeşim. Haklıydın. Karayipler'de geçirdiğim bu son aylar beni ve dünyaya bakışımı tamamen değiştirdi. Üstelik bunun bana iyi geldiğine eminim. O Paris salonlarına artık gerçekten ihtiyacım yok ve bir gün Monper adını taşımadan da yoluma devam edebilirim. De Maure da ondan aşağı kalmaz...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "...";
			link.l1 = "Ve şimdi beni gerçekten üzen tek şey, senin rezilliğinin yaşlı babamızın adını lekeleyecek olması. O, burada gerçekte neler olup bittiğinden habersiz. Ayrıca, senin de doğru söylediğin gibi, aile mirası bu perişan halinden kurtarılmalı. Özgürlüğün için ödenen milyon ise hazinemi epeyce tüketti, bu yüzden onu mutlaka yeniden doldurmam gerekecek.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			dialog.text = "Hayatın tüm derslerini mükemmel bir şekilde kavramışsın, Charles. Senin adına gerçekten mutluyum. Ayrıca eve, Fransa'ya dönmek yerine de Poincy'nin isteğini kabul etmiş olmana da sevindim. Umarım her şey senin için iyi gider ve benim başaramadığımı sen başarabilirsin.";
			link.l1 = "Korkarım başka seçeneğim yok. Karayipler'e geldiğim ilk günden beri her şeyi tek başıma yapıyorum. Görüşürüz, Michel. Sanırım bir dahaki buluşmamızda serbest bırakılman için emir de olacak.";
			link.l1.go = "saga_17a";

		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "saga_17a":
            dialog.text = "Bir dakika! Jan Svenson'a gitmeden önce mutlaka Marcus Tyrex'i ziyaret et – o, Kanun Muhafızı'dır. Hispaniola'daki La Vega'yı yönetir. Korsanlar arasında sınırsız bir otoritesi vardır ve İspanyollar ondan ödleri kopar.";
			link.l1 = "Bize yardım edebilir mi?";
			link.l1.go = "saga_17b";
		break;
		
		case "saga_17b":
            dialog.text = "Doubt it. I can't really tell which side he's on; most likely, he stands only for himself. You will need the Shark and Svenson anyway, but at this moment, Tyrex is the most powerful pirate out here. They elected him as the Code Keeper for a reason. You shouldn't ignore such an important figure. It could prove useful to get to know the pirates better before you meet Svenson. You may even make a name for yourself among them...";
			link.l1 = "Ve yine korsan muhabbetine döndük. Bundan kaçmam mümkün değil, değil mi? Peki öyle olsun. Onu ziyaret edeceğim.";
			link.l1.go = "saga_17c";
		break;
		
		case "saga_17c":
            dialog.text = "Bir korsan olmakla onlarla iş yapmak tamamen farklı şeylerdir, kardeşim. Umarım aradaki farkı anlarsın. La Vega'ya git ve Tyrex'ten bir iş iste. Eğer anlaşamazsanız - onu unut ve bana geri dön.";
			link.l1 = "Pekâlâ, Michel. Görüşürüz!..";
			link.l1.go = "saga_17d";
		break;
		
		case "saga_17d":
            DialogExit();
			AddQuestRecord("Sharlie", "22");
			npchar.greeting = "mishelle_3";
			pchar.questTemp.Mtraxx = "to_lavega";
			pchar.questTemp.Saga = "pirate_line";
			AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
			AddMapQuestMarkCity("LaVega", false);
		break;
		
		case "saga_17e":
            dialog.text = "En azından denedin. Kötü şöhretli bir korsan baronuyla 'tanışma' fırsatın oldu. Boşver. Blueweld'de olan Jan Svenson'a git. Onu kendine müttefik yapmaya çalış, yoksa Levasseur'la işlerimiz kanlı bir savaşa dönüşecek.";
			link.l1 = "Pekâlâ. Geliyorum.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17f":
            dialog.text = "Durduğuna sevindim, kardeşim. Sana bir keresinde korsan olmakla korsanlarla iş yapmak arasında büyük fark olduğunu söylemiştim. Ve sen yolunu kaybettin. Umarım aynı hatayı Köpekbalığı ve Svenson'la da yapmazsın. İşini yap, ama onlardan uzak dur. Sonuçta sen bir Fransız soylususun, onlardan üstün olmalısın. Şimdi git, Jan Svenson Blueweld'de. Onu kendine müttefik etmeye çalış, yoksa Levasseur'la işlerimiz kanlı bitecek.";
			link.l1 = "Pekâlâ. Geliyorum.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17g":
            dialog.text = "Bunu duyduğuma gerçekten sevindim, eğer doğruyu söylüyorsan. Ama şehirleri yakan, ister İspanyol olsun ister başka, sivilleri ve kadınları öldüren bir korsanın sözüne gerçekten güvenebilir miyim?";
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice"))
			{
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "good")
				{
			link.l1 = "Dur... Tyrex'le geçirdiğim zaman boyunca yaptıklarım için gerçekten üzgünüm. Kendi gözlerimle cehennemi gördüm, kardeşim... Hayır, bitti! Korsanlıkla işim kalmadı ve La Vega'ya bir daha asla adım atmam. İtibarımı geri kazanmak için ne gerekiyorsa yapacağım.";
			link.l1.go = "saga_17gx";
				}
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "bad")
				{
					link.l1 = "İster inan ister inanma. Parmaklıklar ardında olan sensin, ben değilim.";
					link.l1.go = "saga_17gxa";
				}
			}
			else //заглушка
			{
				link.l1 = "Yeter artık... Tyrex'le çalışırken işlediğim iğrençlikler için gerçekten pişmanım. Cehennemi kendi gözlerimle gördüm, kardeşim! .. Hayır, korsanlık günlerim geride kaldı! Artık La Vega'da değilim. İyi ismimi geri kazanmak için elimden gelen her şeyi yapacağım.";
				link.l1.go = "saga_17gx";
			}
		break;
		
		case "saga_17gxa":
            dialog.text = "Ah, kardeşim... Tanrı'yı kızdırma... Umarım Svenson ve Shark ile de aynı şey yaşanmaz. Ne yapman gerekiyorsa yap, ama mesafeni koru ve bu insanların kimler olduğunu unutma. Bir Fransız soylusunun onlar gibi olması yakışık almaz. Kendini onların üstünde tut. Şimdi Blueweld'deki Jan Swenson'a git ve yaşlı korsana yaklaşmanın bir yolunu bulmaya çalış. O olmadan, Levasseur meselesini en az kan dökerek çözmek mümkün olmayacak.";
			link.l1 = "Pekâlâ. Gecikmeyeceğim.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;

		case "saga_17gx":
            dialog.text = "Bunun için çok çaba göstermen gerekecek, kardeşim. Sana daha önce ne demiştim, hatırlıyor musun? Korsan olmak başka, onlarla iş yapmak bambaşka bir şeydir. Sen... Boşver, umarım Shark ve Svenson'la aynı hatayı yapmazsın. İşini yap ama onlardan uzak dur. Sonuçta sen bir Fransız soylususun, onlardan üstün olmalısın. Şimdi git, Jan Svenson Blueweld'de. Onu kendine müttefik yapmaya çalış, yoksa Levasseur'la olan işlerimiz kanlı bir savaşa dönecek.";
			link.l1 = "Pekâlâ. Geliyorum.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;
		
		case "saga_17":
			DialogExit();
			AddQuestRecord("Sharlie", "22_1");
			pchar.questTemp.Saga = "blueveld";
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			npchar.greeting = "mishelle_3";
			if(CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
			{
				DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
				SetFunctionTimerCondition("DelCharleePrince", 1, 0, 0, false);
			}
			AddMapQuestMarkCity("SantaCatalina", false);
			AddLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("JS_girl"), "questmarkmain");
		break;
		
		case "Base_fight":
			dialog.text = "Şimdi konuşmak için doğru zaman değil, kardeşim! Düşman sığınağımızda!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Base_fight";
		break;
		
		case "Base_afterfight":
			sTemp = "";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) sTemp = "I see you've become a captain of the navy... I didn't see that coming to be honest. I truly congratulate you!";
			dialog.text = "Tam zamanında geldin, sevgili kardeşim! Seni gördüğüme öyle sevindim ki! Şu lanet Kastilyalılar Saint-Pierre'i tamamen ele geçirmişler bile. Kesinlikle işimiz bitti sanmıştım!"+sTemp+"";
			link.l1 = "Daha işimiz bitmedi, şehir temiz ama o alçaklar kaleye sığındı ve başlarında bir savaş gemisinin komuta ettiği koca bir filo var. Ama sana harika bir haberim var: Michel, özgürsün!";
			link.l1.go = "Base_afterfight_1";
		break;
		
		case "Base_afterfight_1":
			dialog.text = "Kulaklarıma inanamıyorum! Gerçekten mi? Özgürlük mü?!";
			link.l1 = "Levasseur öldü, Tortuga artık eski komutanının yönetiminde, ve o kurnaz tilki Poincy sana karşı tüm suçlamaları düşürdü. Artık, iyi ismimizi hiçbir şey tehdit etmiyor.";
			link.l1.go = "Base_afterfight_2";
		break;
		
		case "Base_afterfight_2":
			dialog.text = "Son ana kadar şüphe ettim... Beni şaşırttın Charles, benim acı bir başarısızlık yaşadığım yerde sen başarılı oldun.";
			link.l1 = "Audaces fortuna juvat, kardeşim... Gördüğün gibi, artık Latince de biliyorum. Hücrenin anahtarı nerede?";
			link.l1.go = "Base_afterfight_3";
		break;
		
		case "Base_afterfight_3":
			dialog.text = "Koğuşumun anahtarı nöbetçi subayın masasının üzerinde olmalı. Orada ara. Belki de yere düşüp bir yere kaymıştır...";
			link.l1 = "Onları bulup geri döneceğim!";
			link.l1.go = "Base_afterfight_4";			
		break;
		
		case "Base_afterfight_4":
			DialogExit();
			pchar.questTemp.Sharlie.DefendSP.SeekKey = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Base_afterfight_6":
			dialog.text = "Sonunda - özgürlük! Bu anı ne zamandır bekliyordum!";
			link.l1 = "Senin de ne kadar zamandır bunu beklediğimi tahmin bile edemezsin! Michel, karşı koymak için adam toplayabilir miyiz?";
			link.l1.go = "Base_afterfight_7";			
		break;
		
		case "Base_afterfight_7":
			dialog.text = "Aklında ne var, Charles?";
			link.l1 = "İspanyolların oluşturduğu tehdit henüz ortadan kalkmadı. Onları kaleden sürmek ve sonra karadan ve denizden birlikte saldırmak istiyorum! Burçtaki topları kullanarak savaş gemisiyle çarpışabileceğim!";
			link.l1.go = "Base_afterfight_8";			
		break;
		
		case "Base_afterfight_8":
			dialog.text = "Adamımız var. Birçok şövalye valinin sarayını korumaya gitti. Şehirde mutlaka birilerini buluruz... Bulabildiğim herkesi toplayacağım. Şehir kapılarının dışında görüşürüz!";
			link.l1 = "...";
			link.l1.go = "Base_afterfight_9";			
		break;
		
		case "Base_afterfight_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, ""); // скрытое бессмертие
			LAi_SetHP(npchar, 500, 500);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 30.0);
			pchar.quest.DefendSP_base2.win_condition.l1 = "location";
			pchar.quest.DefendSP_base2.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.DefendSP_base2.function = "DefendSP_CloseTown";
			AddQuestRecord("Sharlie", "36");
		break;
		
		case "Fort_attack":
			dialog.text = "İşte burada, kardeşim, ordumuz. Bulabildiğim herkes burada. Sayı olarak fazla değiliz ama Vatanımız için savaşacağız! Bu lanetli istilacıları kaleden söküp atacağız! Sürpriz etkisi de yanımızda – saldırımızı beklemiyorlar. İleri!";
			link.l1 = "Dulce et decorum est pro patria mori! İleri!";
			link.l1.go = "Fort_attack_1";
		break;
		
		case "Fort_attack_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (i=1; i<=7; i++)
			{
				sld = CharacterFromID("DefendSP_frafort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", true);
			pchar.quest.DefendSP_fort2.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort2.win_condition.l1.location = "FortFrance_fort";
			pchar.quest.DefendSP_fort2.function = "DefendSP_FortBattle";
			locations[FindLocation("FortFrance_fort")].QuestCapture = true;
		break;
		
		case "Fort_attack_2":
			dialog.text = "Oldu, kardeşim! Kale artık bizim!";
			link.l1 = "İspanyol filosuyla çarpışmada böyle ağır bir darbe alması üzücü... ama hâlâ bir savaşı yönetebilecek güçte.";
			link.l1.go = "Fort_attack_3";			
		break;
		
		case "Fort_attack_3":
			dialog.text = "Ben de üzerime düşeni yapacağım. Topları yükleyip düşmana sağlam bir darbe indireceğiz! Ama ancak filonuzun yaklaştığını gördüğümüzde, yoksa o kalyon bizi anında talaşa çevirir.";
			link.l1 = "İnsanları topla, Michel! Doğruca kıyıya gidiyorum!";
			link.l1.go = "Fort_attack_4";			
		break;
		
		case "Fort_attack_4":
			dialog.text = "Charles, unutma: filonun en tehlikeli gemisi savaş gemisidir! Önce onu etkisiz hale getirmeye çalış. Kalan kale toplarımızla da ateşimizi ona yoğunlaştıracağız.";
			link.l1 = "Pekâlâ, kardeşim. Belki de onu ele geçirmeliyim.";
			link.l1.go = "Fort_attack_5";			
		break;
		
		case "Fort_attack_5":
			dialog.text = "Şartlara bakılırsa, sana ders vermesi gereken ben değilim. Artık zamanımızı boşa harcamamalıyız!";
			link.l1 = "...";
			link.l1.go = "Fort_attack_6";			
		break;
		
		case "Fort_attack_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Shore38", "boat", false); // выпустить в море
			// закрываем городские заведения
			for (i=3; i<=10; i++)
			{
				LocatorReloadEnterDisable("FortFrance_town", "reload"+i+"_back", true);
			}
			LocatorReloadEnterDisable("FortFrance_town", "reload91", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", true);
			pchar.quest.DefendSP_fort3.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort3.win_condition.l1.location = "shore38";
			pchar.quest.DefendSP_fort3.function = "DefendSP_BeforeSeaBattle";
			pchar.quest.DefendSP_sea1.win_condition.l1 = "location";
			pchar.quest.DefendSP_sea1.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_sea1.function = "DefendSP_SeaBattle";
			AddQuestRecord("Sharlie", "37");
		break;
		
		case "Victory":
			dialog.text = "Zaferin kutlu olsun! Tebrikler kardeşim! Muhteşemdin! İspanyollar tamamen yok oldu!";
			link.l1 = "Umarım bu, Fransız kolonilerine saldırmadan önce iki kez düşünmelerini sağlar.";
			link.l1.go = "Victory_1";			
		break;
		
		case "Victory_1":
			dialog.text = "Şimdi söyle bana Charles: geçmişteki hayatın... buna kıyasla neye değer?";
			link.l1 = "Bana hatırlatma...";
			link.l1.go = "Victory_2";			
		break;
		
		case "Victory_2":
			dialog.text = "Burada ilk karşılaştığımızda sana ne demiştim, hatırlıyor musun? 'Bu hayatı seveceksin,' işte tam olarak bunu! Evet, bir de sana kocaman bir teşekkür borçluyum kardeşim, yardımın olmasaydı o yeraltı üssünden asla kurtulamazdım.";
			link.l1 = "Önemli değil, Michel. Sonuçta sen benim kardeşimsin ve sana yardım etmek benim görevimdi.";
			link.l1.go = "Victory_3";			
		break;
		
		case "Victory_3":
			dialog.text = "Just look at you, brother, I am impressed: so much strength in your eyes, confidence in your movements, stature in your posture... where did that wretched artist and court jester go? Indeed! You have surpassed my boldest expectations; truth be told, I never thought that you would become... this.\nIt even... frightens me a little. Because you will stop at nothing to achieve your goal. You are good, too good...";
			link.l1 = "Her nedense, seni yine anlamakta zorlanıyorum. Yine benden memnun değil misin?";
			link.l1.go = "Victory_4";			
		break;
		
		case "Victory_4":
			dialog.text = "Hayır! Ne diyorsun sen?... Hiç de bile! Sadece heyecanımı bastırmaya çalışıyordum.";
			link.l1 = "Peki. Peki, bundan sonra ne yapacaksın kardeşim? Cemiyet’e hizmet etmeye devam mı edeceksin? Yoksa ailemizin topraklarına mı döneceksin? Evet, az kalsın unutuyordum: Bana bir şey anlatacağına söz vermiştin.";
			link.l1.go = "Victory_5";			
		break;
		
		case "Victory_5":
			dialog.text = "Tam olarak ne hakkında?";
			link.l1 = "de Poincy için yaptığın hizmetten. Ona getireceğin söylenen o Hint altınından. Hapse düşmene yol açan her şeyden. Bana anlatmadığın çok şey var Michel, beni tamamen karanlıkta bıraktın. Yani...";
			link.l1.go = "Victory_6";			
		break;
		
		case "Victory_6":
			dialog.text = "Brother, I remember exactly what I said. I will tell you everything. But not in the middle of a burning city!\nWe both have plenty to do now. You need to settle your squadron, repair it, and get the ships ready again. The governor and I will organise and calm the locals.\nWe will discuss everything tomorrow morning over a glass of good French wine. Trust me, brother, I have a big plan. A truly big one. But not now. Visit Abbot Benoit tomorrow at nine a.m. I will spend the night at his place; he is an old friend of mine.";
			link.l1 = "Pekala, Michel. O zaman anlaştık. Yarınki sohbetimizi dört gözle bekliyorum.";
			link.l1.go = "Victory_7";			
		break;
		
		case "Victory_6A":
			dialog.text = "Диалог 28.";
			link.l1 = "Pekala, Michel. O zaman anlaştık. Yarınki sohbetimizi dört gözle bekliyorum.";
			link.l1.go = "Victory_7";
		break;
		
		case "Victory_7":
			dialog.text = "Elveda demene gerek yok, Charles!";
			link.l1 = "...";
			link.l1.go = "Victory_8";			
		break;
		
		case "Victory_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "DefendSP_OpenExit", -1);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Sharlie", "39");
			pchar.quest.DefendSP_final.win_condition.l1 = "Timer";
			pchar.quest.DefendSP_final.win_condition.l1.date.hour  = 9;
			pchar.quest.DefendSP_final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.DefendSP_final.function = "DefendSP_finaltalk";
			// раздача экспы
			ChangeCharacterNationReputation(pchar, FRANCE, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 10);
			AddComplexSeaExpToScill(500, 500, 500, 500, 500, 500, 0);
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 1000);
			AddSimpleRumour("All those residing in the French colony owe you, Captain. Defending Saint-Pierre from the vile attack of the Spanish is quite a feat!", FRANCE, 30, 15);
			AddSimpleRumour("It's an honor for me to speak with the brave Captain that has beaten a bunch of Spanish invaders hollow!", FRANCE, 30, 15);
			AddSimpleRumour("The French colonists may sleep in peace, while brave naval officers such as you are at the King's service!", FRANCE, 30, 15);
			AddSimpleRumourCity("We are all forever indebted to you, Captain! You have saved our colony from devastation!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are a brave and astute naval officer. All those residing in Saint-Pierre are praying for you, know that!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are the pride and joy of our nation and the hero of Saint-Pierre. We will never forget that!", "FortFrance", 30, 15, "");
			npchar.greeting = "mishelle_0";
		break;
		
		case "kukulkan":
			PlaySound("Voice\English\sharlie\mishelle-04.wav");
			dialog.text = "Yine karşılaştık, "+pchar.name+"   Uyarılarıma rağmen, beni aramaya devam ettin ve bu arayış seni çok, çok uzaklara sürükledi... ";
			link.l1 = "Michel?... Nedense hiç şaşırmadım. Miguel Dichoso yine Tayasal’a bir hazine avı için mi döndü? Hm-hm-hm. Evet, seninle görüşmek istiyordum, sevgili kardeşim. O utanmaz gözlerine bakmak için can atıyordum. Üstelik mezarlıkta bana suikast girişimin de cabası oldu. Ama önce söyle bakalım, sana nasıl hitap etmeliyim? Michel de Monper mi, yoksa Miguel Dichoso mu?";
			link.l1.go = "kukulkan_1";			
		break;
		
		case "kukulkan_1":
			dialog.text = "Bu isimler artık önemli değil, "+pchar.name+". Her şey geçmişte kaldı, ki çok yakında tarihin kendisinden bile silinecek. Şimdi ise, ilk kez karaya ayak bastığımdan beri çeyrek asır boyunca yavaş yavaş yaklaştığım hakikat anı geldi...";
			link.l1 = "Ne?!! Bu... bu olamaz!!!";
			link.l1.go = "kukulkan_2";			
		break;
		
		case "kukulkan_2":
			dialog.text = "Evet, "+pchar.name+". Yüzünden kim olduğumu anladığını ama inanamadığını görüyorum. Son aylarda tanışmayı arzuladığın kişi benim. Tanrının temsilcisi, Santiago'dan Engizitör, seninle savaşman için beni kutsadı.";
			link.l1 = "Kukulcan?!";
			link.l1.go = "kukulkan_change";			
		break;
		
		case "kukulkan_change":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kukulkan_3":
			dialog.text = "Katılıyorum. "+pchar.name+",   buna inanmak zor. Hayat,   en güzel masaldan bile daha karmaşık ve daha şaşırtıcı...";
			link.l1 = "Her şeye hazırdım, ama... kardeşim!";
			link.l1.go = "kukulkan_4";			
		break;
		
		case "kukulkan_4":
			dialog.text = "Kardeş mi? Sadece babamız ortak. Annelerimiz farklı, "+pchar.name+"Bil ki annem Kanek'in kızıydı, adı Shochikezhal'dı. Tayasal'dan düşüncesizce ayrıldıktan sonra, ünlü Nicolas Gotier komutasındaki Fransız korsanları tarafından kaçırıldı. Onu köleleştirmeye karar verdiler. Aralarında Serge Benoit adında bir adam da vardı. Kaptanının yaptıklarından utanan Serge, onu terk etti, rahip oldu ve şimdi sen onu Başrahip Benoit olarak tanıyorsun. O zamanlar Henri de Monper, yani babamız, donanma subayıydı. Shochikezhal'ı satın aldı ve onu Fransa'ya götürdü, orada ben doğdum. Aşağı yukarı aynı zamanlarda, sen de doğdun, "+pchar.name+" . Annen doğum sırasında öldü ve babamız, yasal eşinin ikiz doğurduğunu ilan etti.\nShochikezhal, benim annem, ikimize de sütanne oldu. Sen, Itza halkından bir Kızılderili kadının sütüyle büyütüldün, "+pchar.name+"! Sonra, annenin annesi seni eğitmek için yanına aldı ve sana annenin soyadı - de Maure - verildi.";
			link.l1 = "Bütün bunları nasıl öğrendin?!";
			link.l1.go = "kukulkan_5";			
		break;
		
		case "kukulkan_5":
			dialog.text = "Kardeşim, çoğu insandan daha fazla bildiğimi düşünmez misin? Ayrıca, babamız bana çok şey anlattı ve pek çok şeyin farkındayım... Dedikleri gibi, çoğu zaman içgüdülerime güveniyorum.";
			link.l1 = "Şimdi her şey anlaşıldı... Peki ya annen ne oldu? Onu neden hiç görmedim?";
			link.l1.go = "kukulkan_6";			
		break;
		
		case "kukulkan_6":
			dialog.text = "Hayatımı kurtarırken öldü. Doğumumdan biraz fazla bir yıl sonra, bir hastalıktan neredeyse ölüyordum. Annem, bir Itza rahibinin kızı olarak, benim için gizli bir Maya iyileştirme ayini yaptı. İyileştim, ama bu ayin sırasında gök gürültüsü, şimşek ve tropik bir kasırga şeklinde bazı... yıkıcı yan etkiler ortaya çıktı. Shochikezhal suçlandı, büyücülükle itham edildi ve Engizisyon tarafından diri diri yakıldı...";
			link.l1 = "Ve sen daha iyi oldun...";
			link.l1.go = "kukulkan_7";			
		break;
		
		case "kukulkan_7":
			dialog.text = "Bu ritüel beni iyileştirmenin yanı sıra, tanrıların dünyasına bir bağlantı açmakla kalmadı, bana başka yetenekler de kazandırdı. Gerisini zaten biliyorsun. Bildiğin gibi, beyaz ırkın bilgi ve deneyimini geçmişe taşıyıp Maya halkına aktaracağım. Tarih yeniden yazılacak ve siz, beyazlar, bu dünyaya hükmetmeyeceksiniz. Bunu sağlamak için elimden geleni yapacağım.";
			link.l1 = "Yani bütün hayatın, en iyi denizcilik akademisinde okumak, orduda ve Malta Şövalyeleri'nde hizmet etmek, aslında sadece askeri tecrübe biriktirmekten mi ibaretti?";
			link.l1.go = "kukulkan_8";			
		break;
		
		case "kukulkan_8":
			dialog.text = "Aynen öyle. Yeterince şey bildiğimi fark edince, Karayiplere atanmayı ayarladım. Chevalier de Poincy'yi Martinique'te bir üs kurmaya ikna ettim. Sonra Tayasal'a gitmem gerekiyordu. Bu benim için pek de kolay bir iş değildi, çünkü bu bedensel kabuk hâlâ ölümlü ve Karayiplerdeki geçitler düzgün çalışmıyordu.";
			link.l1 = "Ve sen Miguel Dichoso oldun...";
			link.l1.go = "kukulkan_9";			
		break;
		
		case "kukulkan_9":
			dialog.text = "Dear brother, I earned this nickname on the battlefields of Europe. I also met Ramón de Mendoza y Riba there. Do you think that life is made of chances? No, not at all; every chance is an unknown regularity. Much had been done for the sake of my return to Tayasal. I had to live two lives: Michel de Monper and Miguel Dichoso. I also had to make sure people believed them to be different men. I had to turn pirate, just like you, in service to de Poincy in order to gain his trust, favour, and money. I had to murder Blaze Sharp, one of the leaders of the pirates, as a favour for Ramón de Mendoza, in order to get soldiers for the expedition. I had to tempt both de Poincy and de Mendoza with tales of Tayasal's treasures. I received seven hundred and fifty thousand pieces of silver from de Poincy's treasury and sold the Spanish military frigate to the pirate Dodson. And then the expedition happened. I returned to Tayasal only to suffer failure...";
			link.l1 = "Anlıyorum... Sen daha beş yaşında, babamızın topraklarında kelebeklerin peşinde koşarken, büyük rahip Kanek, Don Alonso de Maldonado'nun Tayasal'a yaptığı istiladan korkup, geçmişe yolculuk için hayati öneme sahip olan Kukulcan maskesini güvenle sakladı... affedersin, yani SENİN maskeni.";
			link.l1.go = "kukulkan_10";			
		break;
		
		case "kukulkan_10":
			dialog.text = "Evet, Kanek burada kendi oyununa geldi. En zorlu ritüeli gerçekleştirdi, eski çağların bile cesaret edemediği bir ritüel. Maskeyi yeni oluşan ıssız adada sakladı ve Ksocheatem'in anahtarını - sözde Gerçeğin Muhafızı'nı - kaybetmeyi başardı. Aklımı kullanmam gerekiyordu. Ritüel, Taysal'ın hazinesinden korunan eşyaları taşıyan herhangi bir geminin Karayipler'den ayrılmasını engelliyor, bu tür gemileri Ksocheatem kıyılarına sürüklüyordu. Bunu kendi lehime kullanmaya karar verdim. Mendoza'yı memnun edecek kadar hazine aldım. Ayrıca ritüelle korunan özel bir eşya da aldım. Bu eşya gemide olduğu sürece, gemi kaçınılmaz olarak Ksocheatem'e, yani maskeme teslim edilecekti. Böylece denize açıldım ve Mendoza'ya kendimden haberdar ettim.";
			link.l1 = " Yani, Tayasal'dan kendi başına mı ayrıldın?";
			link.l1.go = "kukulkan_11";			
		break;
		
		case "kukulkan_11":
			dialog.text = "You mean without Mendoza's soldiers? Certainly. All the Spaniards were slain here, in Tayasal. The Itzas brought the treasures to the shore themselves, and I told Mendoza that the soldiers had been ambushed by the Miskito people. He believed me, since he was only interested in gold, not in people. I had planned to set up the ship with the treasures under the cannons of the 'Gryffondor', but it all went much better: the baron decided to send the treasures to Spain under my watch. That was the best possible outcome; I only had to wait until the ship crossed the invisible border of the Caribbean. However, it turned out that the captain had different orders. I found out that a special boarding unit was supposed to mutiny as soon as we reached the Atlantic Ocean, killing the crew and all the officers. The captain had orders to return the Indian gold to Mendoza afterwards. Such a fine specimen of the white race, isn't he, brother? I had to risk it; I didn't know when the mutiny was supposed to happen. But it all went according to plan: the storm hit us as soon as the 'Santa Quiteria' reached the eastern side of the island of Trinidad and Tobago. The frigate was swept back into the Caribbean towards Ksocheatem. I then suffered the greatest failure of my life—a wave washed me off the ship, and I found myself at Le Marin Cove on Martinique a couple of days later. Fishermen found me and took me to Le François. But de Poincy's men captured me while I was coming back to life at Cesar Craig's place. The 'Gryffondor' didn't find the 'Santa Quiteria' at the place I had specified. Chevalier de Poincy became furious as soon as he learned that the Indian gold was gone, together with the money taken from the Order's treasury and his own savings. He had me arrested. He couldn't kill me, though—he didn't want to. He wanted gold. Gold! That is the only thing your people want and care about! You will do anything to get it... I was in a terrible position: I had no mask on me, and I was left rotting in a cell without a single coin in my pockets. That was when I summoned you. Yes, yes, dear brother, you were supposed to free me, so I could do what I was born to do. And you did extraordinary work. It seems that the Itza milk you suckled did you some good.";
			link.l1 = "Benim merak ettiğim, Saint-Pierre'den kaçarken neye güveniyordun, peki? Planın neydi?";
			link.l1.go = "kukulkan_12";			
		break;
		
		case "kukulkan_12":
			PlaySound("Voice\English\sharlie\mishelle-05.wav");
			dialog.text = "Başından beri planım sendin, kardeşim. Kukulcan insanların kalplerini okuyabilir. Abbé'nin yanında sana bıraktığım mektup, seni harekete geçirmek içindi. Senin hakkında yanılmamışım. Santiago Engizitörü ile ilk karşılaştığından beri ilerleyişini izliyordum. Her şeyi benim için yaptın. Hakikatin Muhafızını sen yarattın. Rakipleri ortadan kaldırdın. Ksocheatem'i buldun.\nOradaydım, seni takip ediyordum. Gerçi Tayasal'a gireceğini beklemiyordum. Tüm beklentilerimi aştın. Ve senin yardımınla, doğduğum şeyi yapacağım. Ölümlü bir bedende doğmamın sebebini.";
			link.l1 = "Sevgili kardeşim, düşüncende sadece küçük bir pürüz var. Masken sende değil ve o olmadan hiçbir şeysin. Maske bende. Ve onu sana vermek için hiç de can atmıyorum. Onu sana vermektense paramparça ederim daha iyi.";
			if (CheckCharacterItem(pchar, "mask_true")) link.l1.go = "kukulkan_13";	
			else link.l1.go = "kukulkan_14";			
		break;
		
		case "kukulkan_13":
			dialog.text = "Kaderin önceden belirlediğini değiştiremezsin. Eserime zarar vermene asla izin vermem. Hissedebiliyorum... O sende. Ve sen buradasın, tapınağımda, gücümün doruğunda! Bu yerden asla çıkamayacaksın. Son sınavının vakti geldi, sevgili kardeşim; bakalım Kukulkan'a karşı bir savaşta neye değersin!";
			link.l1 = "Sanırım ölümlü bedenin hâlâ kanayabiliyor!";
			link.l1.go = "kukulkan_fight";		
		break;
		
		case "kukulkan_14":
			dialog.text = "Ha! Sana acıyorum Charles. Gerçekten çok üzücü. Ama bir tanrıyla dövüşme şansını hak ediyorsun. Boşuna olsa bile. İlk perdeyi atlarsan, sonra anlatırım.";
			link.l1 = "Sanırım ölümlü bedenin hâlâ kanayabiliyor!";
			link.l1.go = "kukulkan_fight";			
		break;
		
		case "kukulkan_fight":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "item", "button04");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "quest", "defend1", "", -1);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "defend2", "", -1);
			DoQuestFunctionDelay("Tieyasal_TempleFightGuard", 3.0);
		break;
		
		case "kukulkan_twice": // развилка финалов - есть настоящая маска или нет
			if (CheckCharacterItem(pchar, "mask_true"))
			{
				dialog.text = "";
				link.l1 = "Görünüşe göre güçlerin seni terk ediyor, ulu Kukulcan... Güçlü olabilirsin ama bedenin hâlâ ölümlü!";
				link.l1.go = "kukulkan_win";
			}
			else
			{
				dialog.text = "Bence bu kadar eğlence yeter. Gerçekten usta bir kılıç ustası ve büyük bir dövüşçüsün, hatta zamanının en büyük savaşçısı olduğunu bile söyleyebilirim, ama bu savaşı kaybettin. "+pchar.name+"...";
				link.l1 = "Sadece...";
				link.l1.go = "kukulkan_fail";
			}
		break;
		
		case "kukulkan_fail":
			DialogExit();
			SetMusic("music_teleport");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "attack_force_1", "Tieyasal_KukulkanKick", 1.0);
			LaunchBlast(npchar);
			PlaySound("Sea Battles\udar_metal_003.wav");
		break;
		
		case "kukulkan_fail_1":
			dialog.text = "Yeter artık, sevgili kardeşim. Kukulcan kendi yadigârıyla birleştiğinde onun gücüne karşı koyamazsın! Şimdiye kadar yaşamana izin vermemin tek sebebi, neler başarabileceğini görmekti.";
			link.l1 = "Siktir... O son darbe... Ama hangi eserden bahsediyorsun? Maske mi? O bende!";
			link.l1.go = "kukulkan_fail_2";
		break;
		
		case "kukulkan_fail_2":
			dialog.text = "Zavallı, zavallı Kaptan "+GetFullName(pchar)+"... You have come this far, survived all dangers, slain many of the strongest enemies only to be defeated in the end!.. The jade mask you found inside the metal box near the wrecks of the 'Santa Quiteria' on Ksocheatem is a fake! It is merely an ancient mask from Taysal's treasury. It is NOT THE MASK OF KUKULCAN!.\nI personally took it from here after my failed expedition; it is guarded by the ancient ritual. This mask was the reason why the storm carried the Santa Quiteria away to Ksocheatem. It also had a second purpose. It was meant to deceive anyone who came there seeking my TRUE artefact.";
			link.l1 = "Ama... Gerçek maske o zaman neredeydi?! Ksocheatem'in her yerini aradım!..";
			link.l1.go = "kukulkan_fail_3";
		break;
		
		case "kukulkan_fail_3":
			dialog.text = "Yapmadın, "+pchar.name+". Eserim, 'Santa Quiteria'nın karşı tarafında, sıkı korunan bir tapınakta yatıyordu. Oraya giden yol yeraltı mağaralarından geçiyor. Bulması zor, sıradan bir faninin gözüne hiç de açık değil. İşte orada! Ona iyi bak, son bir kez bak...";
			link.l1 = "Bu olamaz!";
			link.l1.go = "kukulkan_fail_4";
		break;
		
		case "kukulkan_fail_4":
			dialog.text = "Birçok savaştan sağ çıktın ve zafer kazandın, kardeşim. Ama bu sefer kaybettin, "+pchar.name+"...";
			link.l1 = "Ve şimdi ne olacak?";
			link.l1.go = "kukulkan_fail_5";
		break;
		
		case "kukulkan_fail_5":
			dialog.text = "Doğrudan onuncu yüzyıla, yedi yüzyıl öncesine gideceğim. Bu, Maya uygarlığının beyaz ırk üzerinde sarsılmaz bir askeri ve bilimsel üstünlük kurması için yeterli olacak.";
			link.l1 = "Peki ya bizim dünyamız ne olacak? Yok mu olacak?";
			link.l1.go = "kukulkan_fail_6";
		break;
		
		case "kukulkan_fail_6":
			dialog.text = "Hayır. Her şey değişecek. Belki senin için de bir yer olur, ama bu dünyada yaşananları asla hatırlamayacaksın. Burada doğanlardan bazıları orada hiç doğmayacak, bunun tersi de geçerli. Ölüler yeniden hayata dönecek, yaşayanlar ise bir şekilde ölecek; herkes, er ya da geç, yeniden doğacak. Suum cuique, herkes hak ettiğini bulur, "+pchar.name+".\nKorkma, küçük kardeşim. Ne olduğunu asla fark etmeyeceksin ve yeni gerçeği doğal olarak kabul edeceksin. Sadece ben, Kukulcan, anıları saklayacağım... Ama yeter! Kanek zaten ayini hazırladı.\nBeni takip edeceksin, "+GetFullName(pchar)+", ve bu gerçekliği korumak için bu kadar hevesli olduğun son anlara tanıklık edeceksin.";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_7";
		break;
		
		case "kukulkan_fail_7":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Tieyasal_Fail_ReloadTown", 2.0);
		break;
		
		case "kukulkan_fail_8":
			dialog.text = "Zamanın kapıları açıldı! Sevinin, çocuklarım, çünkü büyüklüğe bu kadar yakınsınız! Yeni bir dünya yaratacağız, solgun istilacılara yer olmayan bir dünya!\nElveda, "+pchar.name+", ve kaderin ne olursa olsun, onu kabule hazır ol. Suum cuique!";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_9";
		break;
		
		case "kukulkan_fail_9":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "kukulkan", "", -1);
			DoQuestCheckDelay("Tieyasal_Fail_TeleportStart", 4.0);
		break;
		
		case "kukulkan_win":
			dialog.text = "Bu savaş henüz bitmedi, ölümlü. Belli ki tükenmişsin, benim ise takviyelerim yolda! Eserimi bana teslim edeceksin. Ya bunu yaparsın, ya da cesedinden alırım – benim için hiçbir farkı yok...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_PrepareToWinBattle");
		break;
		
		case "kukulkan_win_1":
			dialog.text = "Urakan! Bu adamı derhal öldürmeni emrediyorum!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_2";
		break;
		
		case "kukulkan_win_2":
			dialog.text = "Urakan! Beni duymadın mı? Tekrar ediyorum: Sana ve savaşçılarına bu adamı yakalayıp öldürmenizi emrediyorum!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_3";
		break;
		
		case "kukulkan_win_3":
			dialog.text = "Urakan! Ne oluyor böyle? Kanek! Emrimi şu lanet oğluna tekrar et!!!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_4";
		break;
		
		case "kukulkan_win_4":
			DialogExit();
			sld = characterFromId("Kanek");
			sld.dialog.currentnode = "kanek_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "kukulkan_win_5":
			dialog.text = "Halkına ihanet ediyorsun, Urakan! Böyle büyük değişimlerin karşısında korkaklık ettin! Savaşçılar, size emrediyorum: kendini kardeşim ilan eden bu adamı da, hain Urakan'ı da yakalayıp öldürün!";
			link.l1 = "Savaşçılar, Cavil ve Hurakan adına size emrediyorum, yerinizde kalın, eğer hayatınızı önemsiyorsanız! Hiçbiriniz Cavil'e karşı bir dövüşten sağ çıkamazsınız! Bırakın tanrıların kendisi karar versin, aralarından hangisi yeryüzünde en güçlüsü!";
			link.l1.go = "kukulkan_win_6";
		break;
		
		case "kukulkan_win_6":
			DialogExit();
			LAi_SetActorType(PChar);
			LAi_ActorTurnToCharacter(PChar, characterFromID("Mishelle"));
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.8);
		break;
		
		case "kukulkan_win_7":
			dialog.text = "";
			link.l1 = "Bugün her şey gitgide daha da ilginçleşiyor. Olayların böyle gelişeceğini hiç beklemiyordun, değil mi kardeşim? Tanrılar aralarındaki en güçlünün kim olduğuna kendileri karar vermeli. Ve herkes hak ettiğini alacak, Michel. Suum cuique! Herkese hakkı olan...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_WinBattleStart");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
