// Натаниэль Хоук - пиратский барон Марун-Тауна
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
			dialog.text = "Bir şey mi istiyorsun?";
			link.l1 = "Hayır, önemli bir şey değil.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "diffindoor":
			PlaySound("Voice\English\saga\Nataniel Hawk-02.wav");
			dialog.text = "Ah... sen de kimsin, kahretsin?.. Khe... (şiddetli, boğuk bir öksürük) Kahrolası halsizlik...";
			link.l1 = "Selam, Nathaniel. Sen Nathaniel Hawk'sın, değil mi?";
			link.l1.go = "diffindoor_1";
		break;
		
		case "diffindoor_1":
			dialog.text = "Evet, benim, eğer hâlâ kendime o isimle hitap edebiliyorsam. Bir zamanlar Nathaniel Hawk'tum, ama şimdi sadece zavallı bir paçavra gibiyim. Kahrolası heykel! Bütün yaşam enerjimi emdi.";
			link.l1 = "Bu duyguyu iyi bilirim...";
			link.l1.go = "diffindoor_2";
		break;
		
		case "diffindoor_2":
			dialog.text = "Nasıl anlayabilirsin ki, delikanlı, ne hakkında konuştuğumu bile fark etmiyorsun? A-ha... Bir dakika önce sağlıklı ve güçlü bir adamken, birdenbire yarı ölü bir ihtiyara dönüşmenin ne demek olduğunu biliyor musun?\nHayatımda çok şey gördüm. Gençliğimde ziyaret ettiğim o eski Hint tapınağının beni artık hiçbir şeye şaşırtamaz hale getirdiğini sanıyordum, ama bu... bunu nasıl göremedim! Şu lanet heykel, tapınağın kapısını açan eski putun aynısıydı!";
			link.l1 = "Pekâlâ, Nathan, konuşalım. Kendimi tanıtmama izin ver, ben "+GetFullName(pchar)+"Öncelikle, seni çok iyi anlıyorum, çünkü buraya senin gibi ben de Kukulcan portalından geldim.";
			link.l1.go = "diffindoor_3";
		break;
		
		case "diffindoor_3":
			dialog.text = "Gerçekten mi?! O zaman neden sen gayet iyi görünüyorsun? Yoksa o... Kukulcan sadece bana mı zarar verdi?";
			link.l1 = "Kaçmana yardım eden Miskito şamanı Snake Eye bana çok güçlü bir iksir verdi. San Augustine'de uyandığımda hemen içtim. Beni tamamen iyileştirdi. Eminim Snake Eye sana da yardımcı olabilir. Sadece seni ona götürmemiz gerekiyor.";
			link.l1.go = "diffindoor_4";
		break;
		
		case "diffindoor_4":
			dialog.text = "Ah, şu Kızılderili! Bir iksir mi? Peki neden bana da vermedi?";
			link.l1 = "Zaman olmadığını söyledi. Peşinizdeydiler ve onun yapabileceği tek şey size kaçış yolunu – geçidi – göstermekti.";
			link.l1.go = "diffindoor_5";
		break;
		
		case "diffindoor_5":
			PlaySound("Voice\English\saga\Nataniel Hawk-01.wav");
			dialog.text = "Kaçmak mı? Ah... Halimi görmüyor musun? Bir kılıcı bile tutamıyorum. Buna nasıl kaçış diyebilirsin? Neyse ki, bu dünyada hâlâ iyi insanlar var. Ole, Allah ondan razı olsun... Ole'yi tanıyor musun?";
			link.l1 = "Evet. Aslında, bana senden bahseden oydu; sana nasıl fare yedirdiğini ve senin de şişe üstüne şişe içmeye devam ettiğini anlattı...";
			link.l1.go = "diffindoor_6";
		break;
		
		case "diffindoor_6":
			dialog.text = "Rom içmezsem yanan bir mumdan daha hızlı ölürüm. Beni hayatta tutan tek şey bu. Rom...";
			link.l1 = "Hâlâ kendini bu kadar kötü mü hissediyorsun? Teleportasyondan sonraki gibi mi?";
			link.l1.go = "diffindoor_7";
		break;
		
		case "diffindoor_7":
			dialog.text = "Pekala, ben aynı şekilde hissetmiyorum... Ama daha iyi de sayılmaz. Dostum, söyle bakalım, neden ihtiyar Nathan'ı görmek istedin? Ne halt etmeye geldin buraya, şu eski, çürük tekneye? Sırf benimle sohbet etmek için mi?";
			link.l1 = "Aslında, evet. Bana inanmayacaksın ama tüm o teleportasyon zahmetine katlanmamın sebebi seni bulmaktı. Kıyı Kardeşliği için çalışıyorum ve Jan Svenson'u temsil ediyorum.";
			link.l1.go = "diffindoor_8";
		break;
		
		case "diffindoor_8":
			dialog.text = "Lanet olsun... Orman Şeytanı mı? Ah... Beni öldürmeye mi geldin? Aslında, gelmedin mi? Bir suikastçı için fazla konuşkansın. Lütfen - bana işkence etme. Eğer benden bir şey öğrenmen emredildiyse - her şeyi kendim anlatırım, saklayacak hiçbir şeyim yok.";
			link.l1 = "Ne demek istiyorsun? A-ah, anladım. Sen de, Danielle gibi, Svenson'ın selvada sana kurulan pusunun arkasında olduğunu düşünüyorsun. Sana temin ederim ki, Jan'ın bununla hiçbir ilgisi yok. Tam tersine, o senin tarafında ve kaybolduğun için çok endişeli.";
			link.l1.go = "diffindoor_9";
		break;
		
		case "diffindoor_9":
			dialog.text = "Gerçekten mi? Bunu duyduğuma çok sevindim. Zaten düşünüyordum... ama bunu kim yaptı? Birliğim dakikalar içinde yok edildi. Bizi bekliyorlardı. Hatta gemi topları bile vardı! Adamlarımın yarısını saçmayla biçtiler, sonra da bizi tüfeklerle bitirdiler...";
			link.l1 = "Açıkçası, ayrıntıları bilmiyorum ama tüm bunların arkasında Jackman olduğuna eminim. Çok fazla tesadüf var, önce Blaze, sonra sen... Jackman iktidarı ele geçirmek istiyor ve önünde duran herkesi ortadan kaldırıyor. Artık Maroon Town'u senin yerine o yönetiyor.";
			link.l1.go = "diffindoor_10";
		break;
		
		case "diffindoor_10":
			dialog.text = "Jackman mı? Alçak herif! Eh... Son birkaç yılda Kardeşlik bölündü, eskiden her şey bambaşkaydı. Zachariah dini saplantılarıyla aklını kaçırdı, Tyrex hiçbir şeyi umursamıyor, Barbazon'un ise tek derdi altın. Yirmi yıl önce her şey başkaydı...";
			link.l1 = "Seni nasıl yakaladılar? Bana daha fazlasını anlat.";
			link.l1.go = "diffindoor_11";
		break;
		
		case "diffindoor_11":
			dialog.text = "Anlatacak ilginç bir şey yok! Dediğim gibi, o haydutlar her şeyi önceden planlamıştı. Son derece düzenli, uyumlu hareket ettiler ve belli ki birinin emirlerini uyguluyorlardı. Beni yüz kez öldürebilirlerdi ama yapmadılar. Canlı olmamı istediler. Beni terk edilmiş bir madene götürdüler ve kulübelerden birine kilitlediler. 'Patron gelene kadar,' dediler. Başta patronun Svenson olduğunu sandım, ama görünen o ki Jackman yönetiyor. Benden ne isteyebileceğini bilmiyorum ama eminim onunla konuştuktan sonra fazla yaşamazdım.";
			link.l1 = "Bundan hiç şüphem yok. Svenson, Jackman'ın Blaze Sharp'ı öldürdüğünden emin... Peki sen nasıl kaçmayı başardın?";
			link.l1.go = "diffindoor_12";
		break;
		
		case "diffindoor_12":
			dialog.text = "O Hintli Snake Eye bir şekilde madene sızmayı başardı. Anladığım kadarıyla, Miskitolar haydutlardan hoşlanmaz. Her neyse, Snake Eye nedense benim kaçışımı ayarladı. Bana kadar bir tünel kazdı, içeri girdi, iplerimi kesti ve birlikte ormana kaçtık.\nBeni köyüne, Miskitolara götürmek istedi. Ama anlaşılan Jackman beni çok istiyordu, çünkü büyük bir av başlatıldı. Peşimize düştüler. Snake Eye onları kandırmak için elinden geleni yaptı ama onlar her seferinde izimizi buldu. İyi iz sürücüleri vardı, şüphesiz.\nSnake Eye'ın köyüne yaklaştığımızda sonunda bizi buldular. O noktada iki gündür açtım ve tamamen tükenmiştim, çünkü bacağımı da fena halde yaralamıştım. Gece yarısıydı ve hâlâ heykelin üzerindeki yıldızın ne kadar parlak olduğunu hatırlıyorum... Snake Eye, tek şansımın putun yanına gidip ona dokunmak olduğunu söyledi.\nAdamın deli olduğunu düşündüm ama boğulurken saman çöpüne sarılmak derler ya... Heykele doğru topallayarak gittim, dokundum... ve sonra çılgınca şeyler olmaya başladı!";
			link.l1 = "Devam etmene gerek yok, sonrasında ne olduğunu biliyorum.";
			link.l1.go = "diffindoor_13";
		break;
		
		case "diffindoor_13":
			dialog.text = "Kendimi batık bir geminin nemli ambarında buldum. Yarı ölüydüm. Yürüyemiyordum, sadece sürünebiliyordum. Her geçen dakika halim daha da kötüleşiyordu. Ole tam zamanında yetişti. İçime, tadı berbat bir Karayip karışımı döktü; hem panzehir, hem de iyileştirici bir öz gibiydi. Sonra bana rom verdi.\nHemen kendimi daha iyi hissettim. Sonra eski bir kütük bulup beni buraya taşıdı. Bir süredir burada yaşıyorum, ama tam olarak ne kadar oldu, söyleyemem—zaman kavramımı yitirdim.";
			link.l1 = "Her şey yoluna girecek, Nathan. Svenson ve benim büyük planlarımız var ve bu planlarda senin rolün çok önemli. Maroon Town’daki görevine dönmelisin, Jackman denen pislikle biz ilgileneceğiz.";
			link.l1.go = "diffindoor_14";
		break;
		
		case "diffindoor_14":
			dialog.text = "Maroon Town mı? Ve bunun nasıl işleyeceğini tam olarak nasıl hayal ediyorsun? Şu halime bak, roma bulanmış bir enkazım! Hiçbir işe yaramam... Hayır, Maroon Town üzerindeki otoritemin yılları sonsuza dek bitti. Bu lanet gemi mezarlığında sıkışıp kaldım. Ne kadar dayanırım? Bir ay mı, iki, bir yıl mı?\nSonunda şu çürük tahtaların üstünde yatıyor olacağım ve Ole, Nathaniel Hawk'tan geriye ne kaldıysa denize atacak. En kötüsü de, Dannie’mi bir daha göremeyecek olmam. Eh, bitti artık dostum.";
			link.l1 = "Bu kadar karamsar olma. Seni buradan çıkaracağım.";
			link.l1.go = "diffindoor_15";
		break;
		
		case "diffindoor_15":
			dialog.text = "Beni buradan nasıl çıkaracaksın? Peki buradan nasıl ayrılacağız? Hiç gemi yok. Sal mı yapmak istiyorsun?";
			link.l1 = "Hayır. Buradan geldiğim gibi gideceğim. Heykelin nerede olduğunu biliyorum... yani, kabaca. Onu bulacağım ve sonra seni ve Shark Dodson'ı almaya geri döneceğim. Sonra seni Snake Eye'a götüreceğiz. O seni iyileştirecek.";
			link.l1.go = "diffindoor_16";
		break;
		
		case "diffindoor_16":
			dialog.text = "Ne dedin? Shark Dodson mı? Steve de burada mı? Ne tuhaf bir yer...";
			link.l1 = "Evet, burada. O, tabiri caizse, bu adanın 'valisi'. Senden bahsettim, ama hiçbir şey bilmiyor.";
			link.l1.go = "diffindoor_17";
		break;
		
		case "diffindoor_17":
			dialog.text = "Ve görmemeli de. Beni bu halde görmesini istemiyorum. Şamanın beni iyileştireceğini söyledin... Buna inanmakta zorlanıyorum. Dannie'den de bahsettin... Onu gördün mü?";
			link.l1 = "Evet. Beni Blueweld'de kendi buldu. Svenson'la konuşmamı gizlice dinlemiş ve Jan'ın seni öldürmek gibi bir niyeti olmadığını, Jackman'a karşı çalıştığını anlamış. Seni bulmama yardım etmek için subay olarak gemime katıldı.";
			link.l1.go = "diffindoor_18";
		break;
		
		case "diffindoor_18":
			dialog.text = "Ah, sevgili Dannie'm! Hiç değişmemiş... Gençliğindeki kadar gözü kara... Şu an onu görmeyi ve kucaklamayı ne kadar çok istediğimi hayal bile edemezsin! Burada yatarken çok düşündüm. Bak dostum, insan ölümle burun buruna gelince hayata başka bir gözle bakıyor. Karımla ne kadar az vakit geçirmişim! Deniz seferleri, Kardeşliğin resmi işleri, Maroon Kasabası'nı yönetmek... Ve o her zaman her konuda bana destek oldu: haftalarca yalnız kaldı, ben yokken diğer korsanlarla tartıştı, gemimize komuta etti... Benim Dannie'm dünyadaki en harika kadın! Ve ben... Ona daha sık sevdiğimi söylemeliydim! Birlikte olmaya karar verdiğimiz günü hatırlıyorum! Aslında, o gün ilk kez doğaüstü şeylerle karşılaşıp savaştım. Bütün bunlar, şu heykellere tıpatıp benzeyen lanetli put yüzünden oldu. Bir hikaye dinlemeye itirazın yoktur umarım? Oldukça ilginçtir.";
			link.l1 = "Hiç de bile! Anlat bana!";
			link.l1.go = "story";
			link.l2 = "Nathan, hoş anılar için vaktimiz yok. Bunu sonra anlatırsın, Miskito köyünde bir şişe şarapla otururken.";
			link.l2.go = "diffindoor_19";
		break;
		
		case "story":
			dialog.text = "It was twenty-five years ago... I was young, ardent and restless. The Caribbean was my playground. I already knew Dannie back then. I liked her, I truly did, and the feeling was mutual. But we often fought, quarrelled and jibed at each other. Foolish youth... I believe we were great entertainment for the respected sailors back then! Anyway, somehow Dannie and I became involved in the same story. We had found a map of Khael Roa, and were told it was THE place to find Indian gold. We had also discovered a strange-looking golden idol, a smaller copy of the top part of the statues. The idol was dangerous; it drained vitality from those who carried it. But we needed that cursed item in order to reach the treasury inside the temple. The only problem was that we had no idea how to properly use it. Dannie and I sailed to the island. There was an ancient temple, overgrown with grass and trees. Once we entered, we found ourselves inside a huge labyrinth. We managed to find the right path and reached the central part of the labyrinth. We thought it was a dead end, but when desperation began to overtake us, we saw a strange platform with a small socket and a picture on it. I put the idol into the socket and...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "idol";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_1";
		break;
		
		case "story_1":
			dialog.text = "The stone platform sank a few inches, and one of the walls turned out to be a secret passage. The idol was left inside the platform; I failed to pull it back out. Finally, we reached a giant hall. Such a beautiful sight!   The most magnificent structure I've ever seen. Carvings on the walls, huge statues... We searched the whole hall, but found no sign of treasure.";
			link.l1 = "Heh, bu bizim gibi insanların başına sıkça gelir. Çok çaba harcanır, sonunda ise elde var sıfır...";
			link.l1.go = "story_2";
		break;
		
		case "story_2":
			dialog.text = "Boşuna değildi. Sonuçta, sonunda dev bir kuş heykeli olan bir taht salonuna girdik. Heykelin yanında gizemli bir ışık vardı, tıpkı gece yarısı putun üzerindeki ışığa benziyordu. Yaklaştık ve havada süzülen güzel bir küre gördük. Yemin ederim, sana gerçeği söylüyorum!\nGerçekti ama aynı zamanda gerçek değilmiş gibi hissettirdi. Düşünürken, Dannie – ah, o pervasız şeytan – küreye dokundu. Küre daha da parlak parlamaya başladı ve sonunda onun ellerinde küçük bir nesneye dönüştü...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "temple";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_3";
		break;
		
		case "story_3":
			dialog.text = "Sanki bir kutsal suçu işlemişiz gibi hissettik. Tapınak canlandı: etrafımızdaki her şey hareket etmeye başladı, duvarlar sallanıyor ve her şey çökmeye yüz tutmuştu. Sanki tüm Hintli iblisleri uyandırmışız ve onlar da bütün öfkelerini üzerimize salmışlardı...";
			link.l1 = "Vay canına!";
			link.l1.go = "story_4";
		break;
		
		case "story_4":
			dialog.text = "Biliyorum, inanması zor. Ama...";
			link.l1 = "Altı ay önce seni yalancı ilan ederdim. Ama Karayipler'de yeterince uzun süre yaşadım, artık sana güvenmemek için bir sebebim olmadığını biliyorum. Devam et. Nasıl hayatta kaldın?";
			link.l1.go = "story_5";
		break;
		
		case "story_5":
			dialog.text = "We ran out of the temple and were lucky enough to get aboard our ship in time. I ordered the anchor to be raised; we wanted to sail away from that place as soon as possible.";
			link.l1 = "Heh! Yani sonunda hazine yerine tuhaf bir eser mi buldun? Ne hoş ve eşdeğer bir ödül, he-he... Peki, nasıl kullanıldığını öğrenebildin mi? Yoksa işe yaramaz mıydı?";
			link.l1.go = "story_6";
		break;
		
		case "story_6":
			dialog.text = "Bir dakika bekle. Hikaye henüz bitmedi. Dannie'nin elinde eser vardı ve onu incelemek için kulübeye gitmeye karar verdiğimiz anda gökyüzü karardı, bir gemi ortaya çıktı. Tanrım! O...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "blackpearl";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_7";
		break;
		
		// вот тут делаем развилку, в зависимости прошёл ли игрок Калеуче
		case "story_7":
			dialog.text = "... Van der Decken'ın ta kendisi!!";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Van der Decken mi? Hm...";
				link.l1.go = "story_8_1";
			}
			else
			{
				link.l1 = "Ve o kim?";
				link.l1.go = "story_8";
			}
		break;
		
		case "story_8":
			dialog.text = "Uçan Hollandalı'yı hiç duymadın mı?";
			link.l1 = "Uçan Hollandalı'yı duymayan mı var! Ben zaten bir Hollandalı'yla karşılaştım ve kaptanını denizin dibine gönderdim. O sadece gemisini yosunlar ve yırtık yelkenler gibi maskeli balo süsleriyle donatmış sıradan bir korsandı.";
			link.l1.go = "story_9";
		break;
		
		case "story_8_1":
			dialog.text = "Evet, ama bu bizzat Van der Decken'di, Uçan Hollandalı'nın kaptanı!";
			link.l1 = "İlginç. Lütfen devam et. Nasıl başardın bunu?";
			link.l1.go = "story_11";
		break;
		
		case "story_9":
			dialog.text = "Eh-heh, dostum... Bir soytarıyı batırdın ama ben gerçek Uçan Hollandalı'dan bahsediyorum. Kocaman bir savaş gemisi. Tanrı seni açık denizde onunla karşılaşmaktan korusun. Kaptanı Van der Decken ve tayfası bir zamanlar lanetlenip sonsuza dek huzursuzca denizlerde dolaşmaya mahkûm edildi.\nOnun paramparça siyah yelkenlerini, güvertede kılıçlarını çekmiş ölü adamları ve bizzat kaptanı hatırlıyorum - siyah üç köşeli şapka takan korkunç bir iskelet... İsa...";
			link.l1 = "Doğruyu mu söylüyorsun?";
			link.l1.go = "story_10";
		break;
		
		case "story_10":
			dialog.text = "I can swear on the Bible that I am not lying... A meeting with the 'Flying Dutchman' only means certain death. She's powerful, very powerful; one volley from her guns can sink even a heavy frigate and its crew... but even worse, how are you supposed to fight the undead?";
			link.l1 = "Ama bu kâbustan sağ çıktın!";
			link.l1.go = "story_11";
		break;
		
		case "story_11":
			dialog.text = "Hepsi sevgili Dannie’me ve tapınaktan aldığımız o Hint eserine borçluyum. Herkese savaşmaya hazırlanmalarını emrettim, ama bunun sonumuz olacağını biliyordum. ‘Uçan Hollandalı’ bize doğru geliyordu; korkunç tayfasını ve Van der Decken’in bizzat kendisini güvertede görebiliyordum. Gemi toplarını bize çevirmeye başladı, ama...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "artefact";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_12";
		break;
		
		case "story_12":
			dialog.text = "Dannie   eseri havaya kaldırıp fırlattı. Neden böyle yaptığını hiç anlamamıştım. Kadın sezgilerinden bahsetti... Eser tekrar parlayan bir küreye dönüştü ve patladı, hayalet gemiye ağır hasar verdi, mürettebatını da moral olarak çökertti. Hollandalıya ateş açmamı emrettim.\nİlk salvo onları sarsmaya yetti. Tekrar saldırdık ve çürümüş gövdelerine ikinci darbeyi indirdik, onlar eserin etkisinden çıkıp karşılık vermeye başlamadan hemen önce...";
			link.l1 = "Yani, yine de onlarla savaşmak zorunda mı kaldın?";
			link.l1.go = "story_13";
		break;
		
		case "story_13":
			dialog.text = "Gerçekten öyle. Ve yemin ederim, hayatımın en zorlu dövüşüydü. O lanet tekneleri zar zor su üstünde kalıyordu ama yine de gövdemin yarısını mahvetmeyi başardılar, ta ki o lanet barut mahzenlerini havaya uçurup hepsini göğe savurana kadar.";
			link.l1 = "Peki batırdın mı? Uçan Hollandalı'yı gerçekten batırdın mı?";
			link.l1.go = "story_14";
		break;
		
		case "story_14":
			dialog.text = "Evet, kahretsin! Yaptım!..";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "ending";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_15";
		break;
		
		case "story_15":
			dialog.text = "O lanetli gemi battı. Güneş yeniden parladı, gökyüzü açıldı. Ve sonunda mutlu olmaya başladık... ah, ne kadar mutlu olduğumuzu hayal bile edemezsin. Ölümün kendisini kandırmıştık. Böyle anlar insanları birbirine yakınlaştırır. Ve o karşılaşmadan çok önce yapmamız gerekeni yaptık – birbirimize sarıldık, öpüştük, aşkımızı itiraf ettik ve sonsuza dek birlikte kalmaya yemin ettik.";
			link.l1 = "Hâlâ birlikte misiniz...";
			link.l1.go = "story_16";
		break;
		
		case "story_16":
			dialog.text = "Evet, öyleyiz. Dannie ile evlendik ve asla pişman olmadım. Ondan daha iyi bir eş ya da silah arkadaşı bulamazsın.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Demek sonunda o gizemli kaptanın, 'Uçan Hollandalı'yı batırmayı başaran kişinin kim olduğunu öğrendim... Gerçekten kahramansın!";
				link.l1.go = "story_17_1";
			}
			else
			{
				link.l1 = "Yani, siz ikiniz gerçekten kahraman mısınız? Ünlü hayalet gemiyi batırmayı başardınız. Durun bir dakika! 'Uçan Hollandalı'nın hala yüzdüğünü söylediniz... O zaman nasıl olur da denizin dibinde yatıyor?";
				link.l1.go = "story_17";
			}
		break;
		
		case "story_17":
			dialog.text = "Eh, dostum, hiçbir şey bilmiyorsun... Van der Decken'i batırabilirsin ama onu öldüremezsin. Onun ve tayfasının üzerindeki lanet çok güçlü, ölümden bile daha güçlü...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_17_1":
			dialog.text = "Bir kahraman olabilirim, ama Van der Decken öldürülemez. Onun, tayfasının ve gemisinin üzerinde dolaşan lanet ölümden bile daha güçlü...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_18":
			dialog.text = "Her seferinde gemiyi batırdığında, mürettebatı onu onarıp yamalar ve sonsuz yolculuklarına devam ederler.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Biliyorum, Nathaniel, biliyorum. Yine de, Uçan Hollandalı artık kimseye bela olmayacak.";
				link.l1.go = "story_22";
			}
			else
			{
				link.l1 = "Biliyorsun, bu kulağa bir masal gibi geliyor. Parçalanıp batırılmış bir gemiyi onarmak...";
				link.l1.go = "story_19";
			}
		break;
		
		case "story_19":
			dialog.text = "Gemiyi batırdıktan sonra insanlar onu defalarca gördüklerini söylüyor... Bu hikayelere inanıp inanmamak sana kalmış.";
			link.l1 = "Ve o tapınağın olduğu ada nerede, hani şu eseri bulduğun yer?";
			link.l1.go = "story_20";
		break;
		
		case "story_20":
			dialog.text = "Haritada olmayan, Karayip Denizi'nin doğusunda bir yerde. Adanın haritasını Maroon Town'da bıraktım ama senin de çok iyi bildiğin gibi, oraya şimdi gidemem. Açıkçası gitmek de istemiyorum. Hatırladığım tek şey adı - Khael Roa...";
			link.l1 = "Ne ilginç bir hikaye. O adayı bulmak isterim!";
			link.l1.go = "story_21";
		break;
		
		case "story_21":
			dialog.text = "Ah, bunu tavsiye etmem... Ben bir daha oraya gitmem, orası kesin.";
			link.l1 = "Yine de orayı görmek isterim... Peki, bu ilginç hikayeniz için teşekkürler! Artık eşiniz hakkında daha çok şey biliyorum. Siz ikiniz de yaşayan efsanelersiniz!";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
			pchar.questTemp.NatanStory = "true";
		break;
		
		case "story_22":
			dialog.text = "Ne demek istiyorsun, dostum? Az önce sana onun öldürülemeyeceğini söylemedim mi?";
			link.l1 = "Nathaniel, Khael Roa'ya yelken açtım. Ve senin, Danielle'in ve yaşlı bir adamın çeyrek asır önce bulunduğunuz Chavin tapınağını ziyaret ettim. O zamanlar tapınaktan aldığın eser 'yükselen güneşin küresi' olarak adlandırılıyordu. İşte o eser, 'Uçan Hollandalı'nın dikkatini sana çekti. Geminin kaptanı Chavin eserlerine düşkündü.";
			link.l1.go = "story_23";
		break;
		
		case "story_23":
			dialog.text = "Khael Roa'ya gittin mi? Ama bu imkânsız! Bana gerçekten doğruyu mu söylüyorsun?";
			link.l1 = "Yemin ederim. Bana labirentten ve dev kuş heykelinden bahsettiğinde, oranın neresi olduğunu hemen anladım. Karayipli şaman Tuttuathapak bana maceralarını anlattı. Beni o adaya yönlendiren de oydu. Saint Christopher'ın doğusunda yer alıyor. Çok küçük, halka şeklinde bir ada. Etrafı kayalarla çevrili ve içinde küçük bir koy var. Tapınağa giden, tamamen otlarla kaplanmış tek bir patika var, tapınak da bir piramit şeklinde inşa edilmiş.";
			link.l1.go = "story_24";
		break;
		
		case "story_24":
			dialog.text = "Evet! Burası Khael Roa. Ama oraya neden gittin?";
			link.l1 = "Caleuche'nin lanetini kaldırmak için... yani, 'Uçan Hollandalı'nın lanetini. Aslında, geminin adı 'Uçan Kalp'ti ve kaptanı da 'Balthazar de Cordes'ti. Elli yıl önce, Hintli Ölüm Tanrısı Yum Cimil tarafından lanetlendi. Balthazar'ın bir zamanlar tapınaktan çaldığı Yum Cimil'in yeşim kafatasını aldım ve o akbaba heykelinin önündeki kaideye geri koydum...";
			link.l1.go = "story_25";
		break;
		
		case "story_25":
			dialog.text = "";
			link.l1 = "...kafatasını geri vererek Caleuche'nin lanetini kaldırdım. Ve yanımda iki Chavin tılsımı daha olduğu için, o da adanın yakınlarında bana saldırdı, tıpkı o zaman sana yaptığı gibi. Ama lanet olmadan, Balthazar artık ölümsüz değildi, Tuttuathapak'ın dediği gibi. Yani... 'Uçan Hollandalı' artık yok. Onunla bizzat ilgilendim.";
			link.l1.go = "story_26";
		break;
		
		case "story_26":
			dialog.text = "Gök gürültüsü ve şimşek! Şaşkınım! Sen... Sen yaşlı Nathan'ı kandırmıyorsun, değil mi? Hayır, gözlerinde gerçeği söylediğini görebiliyorum! Gerçekten bir kahramansın!";
			link.l1 = "Kahraman mıyım bilmem ama ben de senin gibi az macera yaşamadım. Neyse, geçmişi daha çok konuşacağız gibi görünüyor, artık ortak bir meselemiz var.";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
		break;
		
		case "diffindoor_19":
			dialog.text = "Beni şimdi terk mi edeceksin, dostum?";
			link.l1 = "Evet, Nathan. Lütfen, dönene kadar dayan. Kendine dikkat et. Ve en önemlisi, ben dönene kadar hayatta kal, her şey yoluna girecek. Kıyı Kardeşliği'ne lazımsın, Danielle'in sana ihtiyacı var.";
			link.l1.go = "diffindoor_20";
		break;
		
		case "diffindoor_20":
			dialog.text = "Dannie artık mürettebatında mı? Ne olur, ona göz kulak ol. Gençliğinden beri hiç değişmedi, hâlâ tam bir gözü kara ve cehenneme bile çekinmeden girer. Ona onu çok sevdiğimi söyle...";
			link.l1 = "Elbette yapacağım. Sana söz veriyorum Nathan, birlikte geri döneceğiz. Dayan ve başını dik tut. Ole sana göz kulak olacak. Yakında görüşürüz!";
			link.l1.go = "diffindoor_21";
		break;
		
		case "diffindoor_21":
			DialogExit();
			LAi_SetGroundSitTypeNoGroup(npchar);
			NextDiag.CurrentNode = "diffindoor_wait";
			pchar.questTemp.LSC.NatanTalk = "true"; // атрибут - разговор с Натаном состоялся
			AddQuestRecord("BaronReturn", "10");
			npchar.greeting = "nathaniel_1";
		break;
		
		case "diffindoor_wait":
			dialog.text = "Ah, demek sensin, "+pchar.name+". Hâlâ adadan ayrılmadın mı?";
			link.l1 = "Endişelenme Nathan, her şey plana göre gidiyor. Şimdi dinlen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "diffindoor_wait";
		break;
		
		case "danny":
			PlaySound("Voice\English\saga\Nataniel Hawk-03.wav");
			dialog.text = "Danielle!.. Dannie! Benim Dannie'm!..";
			link.l1 = "...";
			link.l1.go = "danny_1";
		break;
		
		case "danny_1": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Nathaniel"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = "danny_2";
		break;
		
		case "danny_2":
			dialog.text = "Teşekkür ederim, dostum. Her şey için, özellikle de Dannie'm için teşekkür ederim...";
			link.l1 = "Rica ederim, Nathan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "danny_2";
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = "Bak kim gelmiş! Bu da "+GetFullName(pchar)+"  kendin gelmişsin! Buyur, buyur dostum! Nasılsın?";
			link.l1 = "Ben iyiyim.   Peki ya sen, Nathan?   Bakıyorum, keyfin yerine gelmiş.   Gayet iyi görünüyorsun.   Yılan Göz gerçekten harika iş çıkarmış!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Evet, şamanınız tam bir mucizeci. Şu lanetli ışınlanmadan önce olduğumdan bile daha iyi hissediyorum! Sanki on yaş gençleşmiş gibiyim! "+pchar.name+", Sana çok büyük bir borcum var. Ve gerçekten etkilendim: Hiç tanımadığın birine yardım ettin, lanetli portalı geçtin, beni ölümün pençesinden kurtardın ve karıma geri getirdin!\nVe dahası! Gemimizi ve yuvamızı da bize geri verdin. Artık bizim en değerli dostumuzsun. Sonsuza dek. Bir gün bir şeye ihtiyacın olursa - kime başvuracağını biliyorsun! Maroon Town sana her zaman koruma, destek ve sığınak sunacak.\nEğer tehlikede olursan, tüm köy senin için savaşır. Barış zamanlarında ise burada dostluk, en iyi rom, yumuşak bir yatak ve güzel bir dinlenme yeri bulacaksın. Dannie ve ben bunun için elimizden geleni yapacağız.";
			link.l1 = "Teşekkür ederim, Baron! Sizi sağ salim ve... Dannie ile birlikte görmekten gerçekten memnunum.";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			dialog.text = "Seni bekliyordum, "+pchar.name+", ve sana bir hediye hazırladım - nadir ve güçlü bir silah. Belki bir gün tek atışta birçok düşmanı alt etmen gerekecek, işte bu el havanı tam da bunun için. 'Sclopetta' özel el bombaları atıyor, bu yüzden onları nasıl yapacağını anlatan talimatları da hazırladım. Al, bu da senin.";
			link.l1 = "Ne harika bir silah! Teşekkür ederim!";
			link.l1.go = "marun_town_3";
		break;
		
		case "marun_town_3":
			GiveItem2Character(pchar, "grape_mushket"); 
			GiveItem2Character(pchar, "recipe_grenade"); 
			Log_Info("You have received a hand mortar");
			Log_Info("You have received a grenade instruction");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bizi daha sık görmeye gel, "+pchar.name+"! Dannie ve ben seni her zaman görmekten memnuniyet duyarız.";
			link.l1 = "Bu benim için bir zevk olacak. Yakında görüşmek üzere!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "marun_town_4":
			dialog.text = "Ah, dostum "+GetFullName(pchar)+" ! Buyurun, buyurun, Kaptan! Nasılsınız? Yardıma ihtiyacınız var mı?";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.NatanInfo"))
			{
				link.l2 = "Nathan, çok önemli bir mesele için sana geldim. Hatırlıyor musun, Terkedilmiş Gemiler Adası'nda bana senin ve Dannie'nin bir Kızılderili tapınağına gizlice girip 'Uçan Hollandalı'yı batırdığınızı anlatmıştın?";
				link.l2.go = "caleuche";
			}
			link.l1 = "Teşekkürler, iyiyim. Sadece ikinizi de görmek istedim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "caleuche":
			dialog.text = "Elbette, yaparım.";
			link.l1 = "O adada, tapınağın olduğu yere gitmem gerekiyor. Onu bulmam şart, çok acil. Elinde haritası olduğunu söylemiştin. Koordinatlarını söyleyebilir misin?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Ah, dostum, bu çok tehlikeli bir işe kalkışıyorsun, biliyorsun... Khael Roa tapınağı lanetli. Koridorlarında kimlerin yaşadığını bir bilsen...";
			link.l1 = "Şu anda orada, o zamanlar gördüklerinden çok daha korkunç canavarlar yaşıyor. Yine de oraya gideceğim.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Sana orada bir şey olursa, kendimi asla affetmem. "+pchar.name+", yalvarırım sana: bu işten vazgeç! Üstelik, 'Uçan Hollandalı'nın en çok görüldüğü yer de orası...";
			link.l1 = "Onunla zaten karşılaştım ve nasıl kurtulacağımı biliyorum. Nathan, lütfen bana Khael Roa'nın koordinatlarını ver ve o tapınak hakkında bildiğin her şeyi anlat, orada yaşayan ölü Kızılderililer dışında.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Ah, peki... Seni geri çeviremeyeceğim, ama... Dannie'yle orada neler yaşadığımızı asla bilemezsin! Khael Roa, Antigua'nın doğusunda yer alıyor. Haritasını Maroon Town'a döndüğümde buldum, tam olarak... (bakıyor) koordinatlar: 19 derece 32' Kuzey, 62 derece 25' Batı.";
			link.l1 = "Yerini günlüğüme yazacağım... Teşekkür ederim, Nathan!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "You can thank me later. Now the details. The island of Khael Roa is a ring of rocks with a cove inside. Seek for the passage between the crags - it's fairly deep there. In the cove, you should cast anchor and disembark at the beach. Look for an old path heading deeper into the island - there's only one there. It will lead you to an Indian pyramid - this is the temple you seek.\nThe island itself is quiet, but the temple is crawling with abominations of all sorts. The entrance is located at the top of the pyramid. There will be three passages inside; you should take the middle one. Then you walk down the corridor and you will find a platform with four entrances or exits. This is where the temple creatures attacked me for the first time, so you should be careful.\nThen there is a labyrinth. It's very complex, and I, for the life of me, can't remember the right route. There is a multitude of foul creatures in the labyrinth. You must kill them all, then walk up to a hall with two entrances, six columns and a platform with nine stone slabs. This is the vestibule of the sanctuary. Its stone wall is closed, and I have no idea how you're going to open it.\nThere is some kind of mechanism, but I swear to God that I have no clue how it functions! I used an idol as a key. I inserted it into the central slab, and the door opened. But you don't have such an idol, so you'll have to figure out how this mechanism functions.";
			link.l1 = "Pekala, elimden geleni yapıp işin aslını öğreneceğim.   Peki ya sığınak?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Kutsal alan, çok yüksek tavanlı ve büyük taş merdivenli geniş bir salon. Bu merdivenleri kullanamazsın – çoğu çok eski ve çökmüş durumda. Fakat tapınağın inşaatçıları anlaşılan büyük büyücülermiş. Kukulcan’ınkiler gibi portallar var ve bunlar seni bir yerden başka bir yere götürecek.\nOnları kolayca tanıyabilirsin – renkli girdaplar gibi görünüyorlar. İlk katta iki portal olacak, fakat bunlardan biri bir tuzak, dikkatli ol! Doğru portal seni ikinci kata çıkaracak. Orada daha da yukarıya çıkmak için başka bir portal bulmalısın ve ardından doğrudan tapınağın kalbine!\nOrada, büyük kuş heykelinin yanında, Dannie ile birlikte yanımıza aldığımız o büyülü eser yerleştirilmişti. Ve sonrasında ne olduğunu zaten sana anlatmıştım.";
			link.l1 = "Söylediklerini aklımda tutacağım. Teşekkür ederim, Nathaniel. Bana çok yardımcı oldun.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Kendine dikkat et, "+pchar.name+". Labirent ve tapınak salonları tehlikelerle dolu. Tek bir yanlış adım atarsan, orada sonsuza dek kalırsın.";
			link.l1 = "Önceden uyarılan, önlem alır, dostum. Uyarıldım, yani hazırlıklıyım. Şimdi gitmem gerek. Görüşürüz!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "İyi şanslar, "+pchar.name+"!";
			link.l1 = "Teşekkürler!";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NatanStory");
			DeleteAttribute(pchar, "questTemp.Caleuche.NatanInfo");
			AddQuestRecord("Caleuche", "35");
			NextDiag.CurrentNode = "marun_town_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
