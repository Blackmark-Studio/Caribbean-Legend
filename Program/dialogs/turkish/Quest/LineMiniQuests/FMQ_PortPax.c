// Addon-2016 Jason, французские миниквесты (ФМК) Порт-о-Пренс
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
		
		case "officer":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "Burada ne oluyor böyle, beyler? Kavga sesleri duydum.";
			link.l1 = "Merhaba memur bey, bir kadının çığlık attığını duydum ve...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_2":
			dialog.text = "";
			link.l1 = ""+GetFullName(pchar)+". Kaptan "+GetFullName(pchar)+".";
			link.l1.go = "officer_3";
		break;
		
		case "officer_3":
			dialog.text = "You are free to go for now, captain. I can see what happened here; we will summon you if we have any questions.";
			link.l1 = "Pekala...";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "Burada ne oluyor böyle, baylar? Kavga sesleri duydum.";
			link.l1 = "Of... Subayım, buraya meyhaneci kızın isteğiyle geldim — burada birinin öldürüldüğünü söyledi, ve gerçekten de öyleymiş — şu iki alçak bu soylu beyefendiye saldırdı. Ne yazık ki onu kurtaramadım. O herifler işini bitirdi.";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			dialog.text = "Gözlerim kör olsun... O bir İspanyol! Burada ne işi var ki? Hm. Peki, sen kimsin, "+GetAddress_Form(NPChar)+"?";
			link.l1 = ""+GetFullName(pchar)+". Kaptan "+GetFullName(pchar)+".";
			link.l1.go = "officer_7";
		break;
		
		case "officer_7":
			dialog.text = "Kaptan, şimdilik gidebilirsiniz. Sözleriniz tanığınkilerle örtüşüyor. Gerekirse sizi çağıracağız.";
			link.l1 = "Pekala...";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;
		
		case "noble":
			dialog.text = "Her şeyi açıklamama izin verin, memur bey! Ben, Santo Domingo'dan Don Domingo Ortiz Albalate, Port-au-Prince'e genç bir hanımefendinin davetiyle geldim. Buluşmamızı beklerken handa kaldım. Ama iki saat bile geçmeden, dos canallas malditas odamı bastı ve eğer zamanında gelen yardım olmasaydı "+GetSexPhrase("ortaya çıkan bu iyi señor","ortaya çıkan bu güzel señorita")+", başım gerçekten büyük belaya girebilirdi.";
			link.l1 = "Don Domingo Ortiz Albalate? İspanyol musunuz?";
			link.l1.go = "noble_1";
		break;
		
		case "noble_1":
			dialog.text = "Rey Felipe'nin kendisi kadar İspanyolum, ha! Ayrıca belgelerimin de buen orden olduğunu belirtmek isterim. Ben bir İspanyol soylusuyum, öyle sıradan bir pirata sucia değilim!";
			link.l1 = "Don Domingo, bu talihsiz olay için en içten özürlerimizi sunarız! Lütfen birkaç soru ve bir şişe şarap eşliğinde karakola gelin. Her şeyi halledeceğiz. Size gelince...";
			link.l1.go = "noble_2";
		break;
		
		case "noble_2":
			DialogExit();
			sld = CharacterFromID("FMQP_off");
			sld.Dialog.currentnode = "officer_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "noble_3":
			PlaySound("Voice\English\LE\Domingo\Domingo_01.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" Kaptan! "+UpperFirst(GetAddress_Form(NPChar))+" Kaptan! Santiago ve Kutsal Meryem adına yemin ederim ki, siz asil bir insansınız ve Kastilya'nın gerçek evladı her zaman böyle bir asaletin karşılığını verir! Buradaki işlerimi bitirdiğimde, sizin de ödüllendirildiğinizi görmek isterim. Lütfen, Santo Domingo'daki mütevazı evime uğrayıp bana onur verin! Şehir kapılarına yakın. Sizin için bir şölen hazırlayacağım, "+GetSexPhrase("canım dostum","beni kurtaran")+" ! Adımı unutma, Don Domingo Ortiz Albalate'yim!";
			link.l1 = "...";
			link.l1.go = "noble_4";
		break;
		
		case "noble_4":
			DialogExit();
			AddMapQuestMarkCity("santodomingo", true);
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;
		
		case "noble_5":
			dialog.text = "Kaptan "+pchar.lastname+"?! Aman Tanrım! Bu tam bir felaket! Bir katliam olmuş! Burada ne olmuş, "+GetSexPhrase("iyi dostum","beni kurtaranım")+"? Bunlar kim?";
			link.l1 = "Seni görmek güzel, Don Domingo. Bunlar... Sana bir ziyarete geldim. Şuradaki adamı görüyor musun? O Ugo, senin hizmetkârın, ve o...";
			link.l1.go = "noble_6";
		break;
		
		case "noble_6":
			dialog.text = "Ugo?! Aman Tanrım, kandırılmışsın kaptan!";
			link.l1 = "Anladım, bana da sık sık böyle şeyler olur. Üç serseri evine girmiş, sadık adamın Ugo'yu öldürmüş – cesedini yukarıda buldum zaten – sonra da sana pusu kurmuşlar. Benim gelişim planlarında yoktu. Karşılaşmamızdan sağ çıkamadılar.";
			link.l1.go = "noble_7";
		break;
		
		case "noble_7":
			dialog.text = "Santa Maria, bizim için dua et! Kılıcını Toledo'nun usta eskrimcileri gibi kullanıyorsun! Senin benim tarafımda olman büyük şans! Ah, zavallı Ugo! Çocukluğumdan beri beni o büyüttü ve şimdi... şu lanet alçaklar tarafından öldürüldü!";
			link.l1 = "Don Domingo, tehlike henüz geçmiş değil gibi görünüyor. Adamın Ugo bir şeyler biliyormuş, şu notu oku. Masanın üstünde buldum.";
			link.l1.go = "noble_8";
		break;
		
		case "noble_8":
			ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
			RemoveItems(pchar, "letter_parol", 1);
			dialog.text = "Ver onu bana... (okuyor) Bu olamaz... ah, hayır! Buna inanamıyorum! Tio Luis... Ama...";
			link.l1 = "Bunu kimin yaptığına dair bir ipucu var mı?";
			link.l1.go = "noble_9";
		break;
		
		case "noble_9":
			dialog.text = "Sadece şüpheler... korkunç şüpheler, "+GetSexPhrase("iyi dostum","beni kurtaran")+"! Annemin kardeşi nasıl böyle bir şey yapabilir?";
			link.l1 = "Beni biraz bilgilendirir misiniz? Üzgünüm Don Domingo, ama benim tecrübeme göre, bir adamın en büyük düşmanı çoğu zaman akrabalarıdır...";
			link.l1.go = "noble_10";
		break;
		
		case "noble_10":
			dialog.text = "Evet, doğru söylüyorsun, "+GetAddress_Form(NPChar)+"! Her şeyi anlatacağım! Beni zaten iki kez kurtardın ve şu anda güvenebileceğim tek kişi sensin! Ama hadi buradan çıkalım, burası midemi bulandırıyor. Bu rezaleti belediye başkanına bildirmeliyim, zavallı Ugo'yla onlar ilgilenir. Sinirlerimizi yatıştırmak için yerel tabernada biraz şarap içmeye ne dersin?";
			link.l1 = "Sinirlerin kesinlikle benimkinden daha çok ihtiyacı var, yolu sen göster, señor!";
			link.l1.go = "noble_11";
		break;
		
		case "noble_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;
		
		case "noble_12":
			LAi_SetSitType(pchar);
			dialog.text = "Şimdi, dostum, sana ailemin hikayesinin...kısaltılmış bir versiyonunu anlatmama izin ver. Annem, Doña Isabella Ortiz, babam el Marqués Ricardo Albalate ile evlendi ve geleneklere göre onun soyadını aldı. Onun erkek kardeşi, Luis Ortiz, kolonilerde bir garnizon komutanıydı, fakat annemin evliliğinden sonra babam tarafından Portobello'ya pek de uzak olmayan bir şeker plantasyonunun yöneticisi olarak atandı.\nBu, çok geniş ve zengin bir plantasyondu, gerçekten de oldukça kârlıydı. Birkaç yıl önce anne babamın denizde trajik bir şekilde ölmesinden sonra, tek oğulları olarak her şeyi, plantasyon da dahil, ben miras aldım. Amcam görevini sürdürdü ve bana ödediği kira ile yetinmiştim. Ödemelerini her zaman zamanında yapardı.";
			link.l1 = "Yani amcanın...";
			link.l1.go = "noble_13";
		break;
		
		case "noble_13":
			dialog.text = "Evet. Şu anda o sadece bir kiracı. Plantasyonun sahibi benim, o değil. Ama! Bana bir şey olursa - mülk onun olur.";
			link.l1 = "Biliyor musun Domingo, bu kadar cazip olmayan bir ödül için bile tüm akrabalarını gözünü kırpmadan öldürecek adamlar tanıdım.";
			link.l1.go = "noble_14";
		break;
		
		case "noble_14":
			dialog.text = "Sen daha iyi bir çevre edinmelisin, Carlos. Sevgili Ugo'm son notunda amcamın evraklarından bahsetmişti... Bu doğrudan bir ipucu. Ah, buna inanmak istemiyorum! Ama... İspanya'da yaşayan kuzenim Margarita Ortiz kısa süre önce nişanlandı. Acaba sebep bu olabilir mi, "+GetAddress_Form(NPChar)+" kaptan?";
			link.l1 = "Seni çok seven amcan birden paraya ihtiyaç duyabilir...";
			link.l1.go = "noble_15";
		break;
		
		case "noble_15":
			dialog.text = "Para mı?! Elbette... ama markilik unvanını da unutma! Kuzenim böylece gelecekteki kocası için layık bir eş olurdu! Tanrım! Ne kadar aptalmışım!";
			link.l1 = "O soyluluk unvanı, şeker tarlasından daha değerli.";
			link.l1.go = "noble_16";
		break;
		
		case "noble_16":
			dialog.text = "Wait a minute! I just remembered that this wasn't the first attempt on my life! I had an encounter with a beggar in the street a few weeks ago! The drunken canalla offended me in a manner I couldn't ignore. He turned out to be a damn good fencer; he drew steel and even managed to wound me with a rapier before I killed him.";
			link.l1 = "Peki, Port-au-Prince'deki bir meyhanede ne işin vardı? Hani şu genç señorita'dan bahsetmiştin?";
			link.l1.go = "noble_17";
		break;
		
		case "noble_17":
			dialog.text = "(yüzü kızararak) Efendim... Evet, kaptan, olay yerinde genç ve güzel bir señorita vardı... şimdi anlıyorum ki o sadece tuzaktaki yemmiş. Her yerde alçaklar, kimseye güven olmuyor! Zavallı Ugo... şimdi o da öldü.";
			link.l1 = "Bunun için bir şeyler yapmalısın, Domingo. İspanya'ya kaçmaya ne dersin?";
			link.l1.go = "noble_18";
		break;
		
		case "noble_18":
			dialog.text = "İspanya'ya mı? Ve plantasyonumu o alçağa mı bırakayım? Kaptan, ben Marquis Domingo Ortiz Albalate'yim!";
			link.l1 = "Ama...";
			link.l1.go = "noble_19";
		break;
		
		case "noble_19":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", yardımınızı isteyebilir miyim? Ugo öldüğünden beri yanımda güvenebileceğim kimsem kalmadı. Beni iki kez kurtardınız! İki kez! Size çok şey borçluyum, sonsuza dek minnettarım, ve yine de sizden bir iyilik daha istemeye cüret ediyorum. Kutsal Meryem Ana adına yemin ederim, karşılığını fazlasıyla alacaksınız!";
			if (startHeroType == 2)  
			{
				link.l1 = "Size nasıl yardımcı olabilirim, "+npchar.name+"?";
				link.l1.go = "noble_20";
			}
			else
			{
				link.l1 = "Pekâlâ, bir İspanyol için iyi bir adamsın. Senin için ne yapabilirim, Domingo?";
				link.l1.go = "noble_20";
			}
			
		break;
		
		case "noble_20":
			dialog.text = "Portobello’daki plantajıma gidelim! Amcamın şu anda Cartagena’da olduğunu biliyorum. Ugo bazı evraklardan bahsetti, o yüzden Don Luis Ortiz’in defterlerine ve belgelerine bakalım! Belki de onun pis komplosunu ortaya çıkarmamıza yardımcı olacak bir şeyler buluruz. Portobello epey uzakta ama yolculuğun ücretini tamamen ödeyeceğim!";
			link.l1 = "Bu noktada sizi reddetmek saçma olurdu, Don Domingo. Artık geri adım atamayacak kadar işin içindeyim.";
			link.l1.go = "noble_21";
		break;
		
		case "noble_21":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Tanrıya şükür, bana yardım edeceğini biliyordum dostum! Al, işte bu yirmi bin peso Portobello'ya yolculuğun ödemesi olarak. Ne zaman yola çıkıyoruz? Cartagena'dan amcam dönmeden acele etmeliyiz!";
			link.l1 = "O halde hiç vakit kaybetmeyelim.";
			if (startHeroType != 2 && CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20 && GetNationRelation2MainCharacter(SPAIN) == RELATION_NEUTRAL) {link.l1.go = "noble_22";}
			else {link.l1.go = "noble_22x";}
		break;
		
		case "noble_22x":
			GiveNationLicence(HOLLAND, 20);
			dialog.text = "İşte Hollanda Batı Hindistan Şirketi'nin bir ruhsatı. Yirmi günlük süresi var, hemen adını yazalım. Tamamdır. Bu sayede Costa Garda ile başımız belaya girmez.";
			link.l1 = "Excelente!";
			link.l1.go = "noble_22";
		break;
		
		case "noble_22":
			dialog.text = "Artık geminize çıkmama izin var mı, kaptan?";
			link.l1 = "Kendinizi onurlu bir misafir olarak görün. Doğru rüzgarı yakaladığımız anda yelken açıyoruz.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_OnBoard");
			AddMapQuestMarkCity("portobello", true);
		break;
		
		case "noble_23":
			dialog.text = "Yani, Kaptan Carlos, geldik işte. Şimdi amcamın evini bulup içinde ne var bakalım.";
			link.l1 = "Don Domingo, muhafızlarla bir sorun çıkmasını beklemeli miyiz?";
			link.l1.go = "noble_24";
		break;
		
		case "noble_24":
			dialog.text = "Hayır. Gerçi... hmm. Luis'in onları bana karşı çevirmiş olma ihtimali var. Her halükarda, tedbirli olmak her zaman cesaretten iyidir. Hadi, aradığımız evi bulalım.";
			link.l1 = "Bunu zaten bilmiyor musun? O senin plantasyonun.";
			link.l1.go = "noble_25";
		break;
		
		case "noble_25":
			dialog.text = "Hm... Dürüst olmak gerekirse, buraya en son geldiğimde sadece sekiz yaşındaydım. Yine de, bunu en kısa zamanda telafi etmeye niyetliyim!";
			link.l1 = "Anladım. O zaman aramaya başlayalım. Amcanın evi burada en büyük olan olmalı.";
			link.l1.go = "noble_26";
		break;
		
		case "noble_26":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("FMQ_Portpax", "7");
		break;
		
		case "noble_27":
			dialog.text = "Burada neyin var, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Bir bakın, Don Domingo. Muhasebe kayıtlarına benziyor. Bu ilginç olabilir.";
			link.l1.go = "noble_28";
		break;
		
		case "noble_28":
			ChangeItemDescribe("Almanac", "itmdescr_Almanac");
			RemoveItems(pchar, "Almanac", 1);
			dialog.text = "(okuyor) Hm... Evet. Şuna bak... Ay caramba! Yüz bin peso! Ve bir yüz elli bin daha! Ve burada... (sayfaları çevirir) Amca Luis!";
			link.l1 = "İlginç bir şey var mı?";
			link.l1.go = "noble_29";
		break;
		
		case "noble_29":
			dialog.text = "İlginç bir şeyler! Sevgili amcam bana söylediğinden beş kat fazla geliri varmış! Hırsız! Zimmetçi!";
			link.l1 = "Şaşırdığımı söyleyemem. Gerçek durumu arada bir kontrol etmeden kimseye tam anlamıyla güvenemezsin. Bu sadece sağduyu meselesi.";
			link.l1.go = "noble_30";
		break;
		
		case "noble_30":
			dialog.text = "Belki sıradan insanlar için sağduyu böyledir. Ama benim yetiştirilme tarzım, onurlu sandığım beyefendilerdeki böyle bir aldatmacayı görmemi engelledi! Her zamanki gibi haklısın, Carlos! Kendi amcam beni soyuyormuş! Mierda! Bu benim hatam, ama bunu düzelteceğim. Bu plantasyon bana ait ve amcam bugünden itibaren görevden alındı! Artık kimse değil! Onu güverte altında süründüreceğim!";
			link.l1 = "Don Domingo... Amcanız böyle bir karara karşı çıkmaz mı sizce?";
			link.l1.go = "noble_31";
		break;
		
		case "noble_31":
			dialog.text = "Umurunda bile değilim, kabul ediyor mu etmiyor mu! Ben Marqués Domingo Ortiz Albalate’im ve Luis Ortiz sadece bir kiracı, hem de eski bir kiracı! Ve o...";
			link.l1 = "Sakin ol, señor. Burada yabancı bir yüzsün ve ben de Hollanda lisansıyla seyreden bir Fransızım, İspanyol korsan karşıtı devriyelerle de... biraz karışık bir geçmişim var. Amcana gelince, bu kasaba neredeyse onun. Muhafızları ve yerel valiyi düşün. Gerçekten onların senin tarafını tutacağını mı sanıyorsun?";
			link.l1.go = "noble_32";
		break;
		
		case "noble_32":
			dialog.text = "Tam isabet ettin... Belki... Hayır. İspanyol askerleri asla bir soyluya el sürmeye cesaret edemez! Amcam bana meydan okuyabilir, eğer cesareti varsa!";
			link.l1 = "Yine de, başka bir yol denemeni öneririm. Ne dersin, mahkemeye gitsek?";
			link.l1.go = "noble_33";
		break;
		
		case "noble_33":
			dialog.text = "Ha! Doğru söylüyorsun, Carlos. Hadi gidip yetkililerle konuşalım. Amcam kaçakçılarla olan işlerini notlarında ayrıntılı şekilde yazmakla hata yaptı. Onlardan köleleri çok ucuza satın almıştı. Bu defterler bize büyük bir iyilik yapacak. O alçağın zindanda otururken bana zarar verebileceğinden şüpheliyim. Hadi gidelim! Portobello'ya!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;
		
		case "noble_34":
			//PlaySound("Voice\English\LE\Domingo\Domingo_04.wav");
			dialog.text = "Bu, iğrenç ve küstah bir yalandan başka bir şey değil! O, nasıl olur da anne babamın iyi adını o değersiz diliyle kirletmeye cüret eder! Kahrolası, bunun hesabını ona ödeteceğim! Kılıcını çek, katil!";
			link.l1 = "";
			link.l1.go = "noble_35";
		break;
		
		case "noble_35":
			DialogExit();
			sld = CharacterFromID("FMQP_Uncle");
			sld.Dialog.currentnode = "uncle_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noble_36":
			PlaySound("Voice\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Amca Luis, ruhu için ayrılmış olan yerde - cehennemde... "+pchar.name+", beni bana koruyucu meleğim gönderdi! Bu alçağın sözüne güvenmemene çok sevindim. Açıkçası, beni burada bu canalla ile baş başa bırakıp gideceğinden korkmuştum\nEvet "+GetAddress_Form(NPChar)+", ben de kusursuz değilim ama bu... bu iğrenç iftira, kendi ailemi öldürmek için korsanlar tuttuğum yalanı! Beni bununla suçlamak... bununla! Bah! Hak ettiği son.";
			link.l1 = "Başardığımıza sevindim, Don Domingo. Şimdi ne yapacağız? Umarım İspanyol yasalarına bulaşmamışızdır.";
			link.l1.go = "noble_37";
		break;
		
		case "noble_37":
			dialog.text = "Yasayla mı? Ha-ha! Hayır, "+pchar.name+", I will show this fine accounting book with all my uncle's smuggling operations in it. Do not forget about the several attempts on my life; we've got a great number of witnesses after his last try just now. Don't worry about it, "+GetAddress_Form(NPChar)+". This is my town, it's time to show them all!";
			link.l1 = "Lütfen dikkatli hareket edin, señor. Sizin hakkınızda, merhum amcanızdan daha iyi düşünsünler.";
			link.l1.go = "noble_38";
		break;
		
		case "noble_38":
			dialog.text = "Plan bu, kaptan. Ama bana karşı gelmeye cüret edenlere hiç acımam. Size içten teşekkürlerimi sunmak isterim, "+pchar.name+"! Lütfen tabernaya git, biraz dinlen, bir iki kadeh iç. Sana katılmak isterdim ama haklıydın. Artık akıllanıp plantasyonu kendim yönetmenin zamanı geldi. Yarın burada beni görmeye gel, kaptan!";
			link.l1 = "Pekâlâ, Don Domingo. Yarın görüşürüz.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;
		
		case "noble_39":
			DelLandQuestMark(npchar);
			PlaySound("VOICE\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Ah, işte buradasın, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "Nasıl gidiyor, don Domingo? Plantasyonunuz nasıl?";
			link.l1.go = "noble_40";
		break;
		
		case "noble_40":
			dialog.text = "Plantasyon harika, ama aynı şeyi para için söyleyemem – meğer sevgili amcam tüm parayı Cartagena’daki bankaya aktarıyormuş. Altınımı geri almak için avukatlara epey iş düşecek. Ama sorun değil, bunun da üstesinden gelirim. Üzülme kaptan, asaletin, dürüstlüğün ve dostluğun için sana söz verdiğim ödülleri mutlaka vereceğim!";
			link.l1 = "Senin yanında savaşırken ödül almayı hiç düşünmemiştim, señor...";
			link.l1.go = "noble_41";
		break;
		
		case "noble_41":
			dialog.text = "Bunu biliyorum kaptan, ve bu da karakteriniz hakkında çok şey söylüyor! Her iyilik ödüllendirilmeli. Şu anda param olmasa da, geminize plantasyonumdan mal yüklenmesi için emir vereceğim. Yani kahve, hem de büyük bir parti. Eminim ki bunu çok iyi bir fiyata satabileceksiniz.";
			link.l1 = "Oh! Bu güzelmiş...";
			link.l1.go = "noble_42";
		break;
		
		case "noble_42":
			dialog.text = "Üstelik, benim için pek değeri olmayan, ama senin gibi bir denizci için çok değerli birkaç eşyam var. Güzel bir dürbün ve üç muska. Lütfen bunları kabul et, artık hepsi senin.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "noble_43";
		break;
		
		case "noble_43":
			Log_Info("You have received a good spyglass");
			Log_Info("You have received three amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "Finally, I present you with my rapier as a token of my immeasurable gratitude. She served me well; now let her serve you even better. Look at her and remember your good Spanish friend - marquis Domingo Albalate!";
			link.l1 = "Çok teşekkür ederim, señor! Hiç beklemiyordum...";
			link.l1.go = "noble_44";
		break;
		
		case "noble_44":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "Ve şimdi, ne yazık ki, veda etmem gerek. Portobello'ya gidip valiyi görmeliyim, ardından Cartagena'ya... Kısacası, tasasız hayatım sona erdi, artık yetişkin biri gibi yaşama zamanı.";
			link.l1 = "Şimdi çok daha akıllısın...";
			link.l1.go = "noble_45";
		break;
		
		case "noble_45":
			dialog.text = "Doğru. Benim için bir zevkti, "+GetAddress_Form(NPChar)+"! Bir ara beni ziyarete gel. Denizde yolun açık olsun!";
			link.l1 = "Sana da plantasyon işlerinde bol şanslar, Don Domingo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;
		
		case "noble_46":
			PlaySound("Voice\English\YoungMan02.wav");
			dialog.text = "Eh, geç kaldık, señor! Ne yazık ki, iyi kalpli yaşlı amcam belgelerini çoktan güzelce temizlemiş. Görünüşe göre biri ona Santo Domingo'dan bahsetmiş ve o da önlem almış... Ama ben bu işi burada bırakmayacağım! Amcama karşı yasal işlem başlatmak için Portobello valisiyle görüşmeliyim. Servetimi yönetmesinden artık bıktım.";
			link.l1 = "İyi bir karar.";
			link.l1.go = "noble_47";
		break;
		
		case "noble_47":
			dialog.text = "I want to thank you, captain! It was a pleasure! I present you my rapier as a token of my gratitude. She served me well; now let her serve you even better. Look at her and remember your good Spanish friend – marquis Domingo Albalate!";
			link.l1 = "Çok teşekkür ederim, señor! Hiç beklememiştim...";
			link.l1.go = "noble_48";
		break;
		
		case "noble_48":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			dialog.text = "Ve şimdi, ne yazık ki, sana veda etmeliyim. Portobello'ya gitmeliyim. O tasasız günlerim geride kaldı, artık yetişkin gibi yaşama zamanı. Denizde yolun açık olsun!";
			link.l1 = "Amcanla ilgili bol şanslar, don Domingo! Eminim başarılı olacaksın!";
			link.l1.go = "noble_49";
		break;
		
		case "noble_49":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 40.0);
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "13");
			CloseQuestHeader("FMQ_Portpax");
			sld = &Locations[FindLocation("PortoBello_Plantation")];
			sld.soldiers = true;
		break;
		
		case "uncle":
			PlaySound("Voice\English\OliverTrast02.wav");
			if (pchar.sex == "woman") { dialog.text = "Tam zamanında geldim sanırım. Yoldan çıkmış yeğenim ve onun yeni gözdesi, Kaptan "+GetFullName(pchar)+"... Evet, evet, "+GetSexPhrase("delikanlı","senorita")+", şaşırma — senin hakkında biraz soruşturdum."; }
			else { dialog.text = "Tam zamanında gelmişim. Yaramaz yeğenim ve onun koruyucu meleği, Kaptan "+GetFullName(pchar)+"... Evet, evet, "+GetSexPhrase("delikanlı","señorita")+", şaşırma — senin hakkında biraz soruşturdum."; }
			link.l1 = "Luis Ortiz?";
			link.l1.go = "uncle_1";
		break;
		
		case "uncle_1":
			dialog.text = "Doğru söylüyorsun kaptan, ama geri kalan her şeyde yanılıyorsun. Başkalarının aile işlerine burnunu sokmamalısın. Kimi koruduğundan haberin yok. Benim sefih yeğenim Domingo tam bir serseri, her meyhanenin ve genelevin baş konuğu, gözüne kestirdiği her kızla yatmaya çalışan ya da en azından denemekten geri durmayan biri. Kirasını her ay ben ödüyorum, o ise birkaç günde har vurup harman savuruyor, sonra da sürekli daha fazlasını istiyor. Tekrar tekrar. Onun bu bitmek bilmeyen rezil davranışları annesini, yani kız kardeşimi, deliliğin eşiğine getirdi.\nDuyduğuma göre bu ahlaksız çocuk, Marquis Ricardo Albalate'a ait bir gemiyi batırmaları için bazı İngiliz korsanlarını tutup yönlendirmiş, o değerli adamı ve sevgili kız kardeşimi de o gemiyle birlikte mezara göndermiş. Domingo ailemizin parasını o kadar çok istiyordu ki, bunun için öldürmekten bile çekinmedi... Ne yazık ki, bu alçağı darağacına gönderecek kadar delil bulmayı başaramadım.";
			link.l1 = "";
			link.l1.go = "uncle_2";
		break;
		
		case "uncle_2":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_34";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "uncle_3":
			if (pchar.sex == "woman") { dialog.text = "Sevgili yeğenim, her zamanki gibi yine kendi ortamında. Çok fazla gürültü, şangırdayan kılıçlar ve tokuşan kadehler, ama özünde pek bir şey yok. Ona neden ilgi gösterdiğini anlamıyorum señorita, o..."; }
			else { dialog.text = "Sevgili yeğenim, her zamanki gibi yine kendi havasında. Çok fazla gürültü, şangırdayan kılıçlar ve tokuşan kadehler, ama özünde pek bir şey yok. Onun hakkında seni böyle değersiz bir veledi desteklemeye ikna eden şey neydi, bilmiyorum..."; }
			link.l1 = "Anladığım kadarıyla, yeğenine karşı hiçbir delil bulamayınca, onun peşine suikastçılar göndermeye başlamışsın. Oysa basit bir dava yeterli olurdu.";
			link.l1.go = "uncle_4";
		break;
		
		case "uncle_4":
			dialog.text = "Yalan söylüyorsun. Domingo burada sayısız düşman edindi. Arkasında terk edilmiş sevgililer ve aldatılmış kocalar bıraktı. Nasıl bu kadar uzun süre hayatta kalabildiğine şaşıyorum! Sor ona, kaç düğünü mahvetti? Kaç nişanlıyı yaraladı ya da öldürdü?";
			link.l1 = "Hizmetkârı Ugo...";
			link.l1.go = "uncle_5";
		break;
		
		case "uncle_5":
			dialog.text = "Ah, Ugo! Hepsinin en belalısı! Ugo, serseri efendisini çok severdi. Efendisinin tüm suçları ona çocuk oyuncağı gibi gelirdi. Unutma, "+GetSexPhrase("delikanlı","señorita")+", aile işi sadece aile içindir. Burnunu sokanlar kendilerini belada bulur.";
			link.l1 = "Şimdi de bana tehditler savuruyorsun.";
			link.l1.go = "uncle_6";
		break;
		
		case "uncle_6":
			int icpy = GetOfficersQuantity(pchar);
			iTotalTemp = 10000+10000*icpy;
			dialog.text = "Uyarı. Dinle, Kaptan: "+GetSexPhrase("çok ileri gittin, ama ","")+"seni bir düşman olarak görmediğim için—sadece yanlış yönlendirilmiş biri olarak gördüğüm için—sana bir teklifim var: geri dön ve git. Kan dökülmesini istemiyorum. Aile meselelerimizi sensiz halledeceğiz. "+GetSexPhrase("Yeğenimle ilgili tüm masraflarınızı karşılamaya hazırım:","İşini kolaylaştırmak için, sana ödeme yapmaya hazırım:")+" "+FindRussianMoneyString(iTotalTemp)+" nakit olarak. Al ve burayı unut. Yoksa adamlarım seni öldürür.";
			link.l1 = "Benim için aile her şeyden önce gelir, hep böyle derim. O zaman bana ne, parayı ver ve 'vaya con Dios.'";
			link.l1.go = "uncle_7";
			link.l2 = "Hikayen, plantanın gübresinden bile daha kötü kokuyor. Don Domingo aziz olmayabilir, ama siz, señor, tam bir şeytansınız!";
			link.l2.go = "uncle_8";
		break;
		
		case "uncle_7":
			AddMoneyToCharacter(pchar, iTotalTemp);
			dialog.text = "Senin aklı başında biri olduğunu biliyordum. Al paranı ve adios, kaptan. Bir dahaki sefere başkalarının kirli çamaşırlarını karıştırmamaya çalış – kimse hoşlanmaz bundan.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_UncleExit");
		break;
		
		case "uncle_8":
			if (pchar.sex == "woman") {dialog.text = "Şimdi anladım. Sen de yeğenim gibisin — düşüncesiz, pervasız bir kız. Ona tam uyuyorsun. İkinize de bir ders vermenin vakti geldi!";}
			else {dialog.text = "Şimdi anladım. Sen de yeğenimden farksızsın — aptal, kendini beğenmiş bir çocuksun! İkinize de haddini bildirme vakti geldi!";}
			link.l1.go = "exit";
			AddDialogExitQuest("FMQP_UncleFight");
		break;
		
		case "ugo":
			pchar.quest.FMQP_SantoDomingoOver.over = "yes";
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = TimeGreeting()+" "+GetAddress_Form(NPChar)+". Size nasıl yardımcı olabilirim?";
			link.l1 = "Selamlar. Affınıza sığınırım, ama burası Señor Domingo Albalate'in evi mi?";
			link.l1.go = "ugo_1";
		break;
		
		case "ugo_1":
			dialog.text = "Evet, burası Albalate ailesinin evi. Gösterişsiz ama rahattır. Benim adım Ugo, genç efendiye hizmet ediyorum. Onun için mi geldiniz?";
			link.l1 = "Evet, señor. Don Domingo beni kısa süre önce evine davet etti. Oldukça ikna ediciydi. Onu görebilir miyim?";
			link.l1.go = "ugo_2";
		break;
		
		case "ugo_2":
			dialog.text = "Ne yazık ki, iyi "+GetSexPhrase("caballero","senorita")+", Don Domingo şu anda evde değil. Açıkçası, o yaramaz çocuğu... pardon, genç señor'u nerede bulabileceğimi ben de bilmek isterdim. Kendisine ne için geldiniz, sorabilir miyim?";
			link.l1 = "Şey... Don Domingo'ya tesadüfen yardım ettim. Port-au-Prince'deki bir meyhanede iki serseri ona saldırdı. Efendinize kendini bu... nasıl demişti... maldita canalla'lardan koruması için yardım ettim. Don Domingo, soruşturma bittikten sonra beni buraya davet etti. Artık her şeyin çözülmüş olacağını düşündüm, bu yüzden onu evde bulmayı umuyordum.";
			link.l1.go = "ugo_3";
		break;
		
		case "ugo_3":
			dialog.text = "Madre de Dios! Ne korkunç hikayeler anlatıyorsunuz burada! Hemen komutanı görmem lazım – Don Domingo’nun şu anda karşı karşıya olduğu tehlikeler hakkında onu uyarmalıyım! "+UpperFirst(GetAddress_Form(NPChar))+", gitmelisin ve ben de acele etmeliyim!";
			link.l1 = "Sakin ol, Ugo. Genç efendin güvende. Belgelerinin tamam olduğunu söyledi, onu çoktan serbest bırakmaları gerekiyordu, bu yüzden buradayım. Sanırım yakında onu göreceğiz.";
			link.l1.go = "ugo_4";
		break;
		
		case "ugo_4":
			dialog.text = "Ah! Bunu nasıl yapabildin? O saf çocuk - hem de o kurbağa yiyen Fransızların elinde mi?! Bir de hayatını tehdit eden haydutlar varmış! Hayır, mutlaka komutanı görmeliyim! "+UpperFirst(GetAddress_Form(NPChar))+", lütfen git!";
			link.l1 = "Peki, peki, bu kadar ısrarcı olma. Gidiyorum.";
			link.l1.go = "ugo_exit";
			link.l2 = "Señor, neden bu kadar gerginsiniz? Size zaten söyledim, efendiniz için hiçbir tehlike yok. Bırakın burada kalıp Señor Domingo'nun gelişini bekleyeyim, uzun yolculuğumdan çok yoruldum ve misafirperverliğinizi takdirle karşılarım. Biraz serin, taze su ve boğazımdaki tuzlu havayı gidermek için sıcak bir banyo isterim. Sonra isterseniz yerel garnizona gidip ne isterseniz yapabilirsiniz.";
			link.l2.go = "ugo_5";
		break;
		
		case "ugo_exit":
			DialogExit();
			LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;
		
		case "ugo_5":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", derhal bu evden çık!";
			link.l1 = "Ugo, bir hizmetçinin bir beyefendiye bu şekilde konuşmasına izin verildiğinden gerçekten şüpheliyim. Ayrıca Don Domingo'nun hayatını kurtaran birine böyle davranılmasını onaylayacağını da sanmıyorum!";
			link.l1.go = "ugo_6";
		break;
		
		case "ugo_6":
			dialog.text = "Gerçekten mi? (yukarıya seslenerek) Çocuklar, aşağı gelin, bir sorunumuz var!";
			link.l1 = "Ne oluyor böyle?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
