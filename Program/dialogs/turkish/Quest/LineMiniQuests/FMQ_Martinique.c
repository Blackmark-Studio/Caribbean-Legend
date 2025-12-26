// Addon-2016 Jason, французские миниквесты (ФМК) Мартиника
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
		
		// квестодатель
		case "carpenter":
			DelMapQuestMarkCity("Fortfrance");
			LAi_SetImmortal(npchar, false);
			npchar.lifeday = 0;
			DelLandQuestMark(npchar);
			dialog.text = TimeGreeting()+", kaptan. Kendimi tanıtmama izin verin - "+GetFullName(npchar)+".   Gerçi çok uzun zaman önce tanışmadık, ama beni hatırlayacağından şüpheliyim.";
			link.l1 = "Selamlar, monsieur. Sizi daha önce nerede görmüş olabilirim?";
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
			sTemp = "lugger 'Adeline'";
			if (pchar.questTemp.Sharlie.Ship == "sloop") sTemp = "sloop 'Black Dog'";
			dialog.text = "Tersanemiz. Bir satın alma yaptınız "+sTemp+" . Şimdi hatırladın mı? Orada marangozum.";
			link.l1 = "Evet, o gemiyi gerçekten satın aldım. Peki ne istiyorsun, monsieur "+GetFullName(npchar)+"?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
			sld = characterFromId("FortFrance_shipyarder");
			AddLandQuestMark(sld, "questmarkmain");
			dialog.text = "Tersanecimiz "+GetFullName(sld)+"   sizinle konuşmak istiyor. Sanırım bir iş teklifi var. Geminizi limanımızda görmüş ve beni sizi bulmam için gönderdi. Daveti kabul eder misiniz?";
			link.l1 = "Pekâlâ. Şehirdeki işimi bitirince patronuna uğrayacağım.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			pchar.questTemp.FMQM = "begin";
			AddQuestRecord("FMQ_Martinique", "1");
			SetFunctionTimerCondition("FMQM_Denial", 0, 0, 2, false);
		break;
		
		case "officer":
			PlaySound("Voice\English\soldier_arest_4.wav");
			dialog.text = "Vay vay... Ağıma yeni düşmüş kaçakçılar var demek!";
			link.l1 = "Eh...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			dialog.text = "Saçmalamayı bırak! Bu tersanede birkaç varil reçine var. Kaptan, onları suç ortağına teslim ettin. İkiniz de tutuklusunuz ve yükü kanun adına el koyuyorum!";
			link.l1 = "...";
			link.l1.go = "officer_2";
		break;
		
		case "officer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_3":
			dialog.text = "Aptal numarası yapma, usta! Hangi variller? Şu denizcinin gemisinden yeni indirdiğin varillerden bahsettiğimi gayet iyi biliyorsun! İkiniz de zindanda çürüyüp gideceksiniz! Yürüyün, alçaklar...";
			link.l1 = "";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\soldier\soldier arest-02.wav");
			dialog.text = "Bu reçine, sevgili usta gemi yapımcım, stratejik öneme sahip bir maldır ve doğrudan valimizin kontrolü altındadır! Madem hepsinin senin olduğunu iddia ediyorsun - öyle olsun. Tutuklusun, bu geceyi bizim konforlu zindanlarımızda geçireceksin ve yarın bize onu nasıl elde ettiğini ve ne amaçla kullandığını ayrıntılı şekilde anlatacaksın. Merak etme, eninde sonunda her şeyi öğreneceğiz. Sen, kaptan, gidebilirsin. Bugün şanslı günündesin.";
			link.l1 = "";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("FMQM_officer"));
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_3", "FMQM_ArestContinue", 8);
		break;
		
		case "officer_7":
			PlaySound("Voice\English\soldier_arest_2.wav");
			dialog.text = "Bu gemide bir gariplik olduğunu biliyordum... Görünen o ki seni hafife almışım, kaptan.";
			link.l1 = "Aynen öyle, teğmen. O kadar da aptal değilim. Tersaneciyle aranızdaki o rahat işbirliği artık tehlikede.";
			link.l1.go = "officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "officer_8":
			dialog.text = "Anladım. Tebrikler, demek beni bulup gafil avlayacak kadar yeteneklisin. Şimdi söyle bakalım, ne istiyorsun.";
			link.l1 = "Anlamıyor musun? Reçinemi geri istiyorum. Sen ve arkadaşın benden çaldınız o reçineyi.";
			link.l1.go = "officer_9";
		break;
		
		case "officer_9":
			dialog.text = "Peki. Alabilirsin, ama sadece partinin yarısını verebilirim. Burada sakladığım hepsi bu kadar. Umarım bu sana yeter, çünkü verebileceğim tek şey bu.";
			link.l1 = "Hâlâ beni kandırmaya mı çalışıyorsun? Diğer yarısını ya altınla ya da arkanda sakladığın mallarla telafi et.";
			link.l1.go = "officer_10";
		break;
		
		case "officer_10":
			dialog.text = "Olmaz. Diğer yarısı için ortak dostumuza sor.";
			link.l1 = "Benimle dalga mı geçiyorsun? Buna gerçekten inanıyor musun "+GetFullName(characterFromId("FortFrance_shipyarder"))+" bana fıçıları mı geri verecek? Bu saçmalık.";
			link.l1.go = "officer_11";
		break;
		
		case "officer_11":
			dialog.text = "Kaptan, sahip olduğum tüm reçineyi al, canını kurtar ve defol buradan. Üstüne üstlük, St. Pierre'de sana hiçbir sorun çıkarmayacağıma da söz veriyorum. Bu son teklifim.";
			link.l1 = "Hayatım ne zamandan beri pazarlığın bir parçası oldu? Ha!";
			link.l1.go = "officer_12";
		break;
		
		case "officer_12":
			dialog.text = "Looks like you still consider yourself invincible after the fight, captain. Let me explain this to you: those were rookies, untrained and unmotivated; you have no chance against my squad. I could have you killed right here without any bargaining, but I value the lives of my men. Some of them might get injured or even killed in the process of killing you. So you either accept my generous offer or stay here forever. Time to choose.";
			link.l1 = "Siktir git, teğmen, ama şartlarını kabul etmek zorundayım. Burada açıkça dezavantajdayım.";
			link.l1.go = "officer_13";
			link.l2 = "Fazla mı kendine güveniyorsun, teğmen? Sanırım sana ve paralı askerlerine bir ders vermeliyim. Seni lanet reçine köpeği!";
			link.l2.go = "officer_15";
		break;
		
		case "officer_13":
			dialog.text = "Sen aklı başında bir adamsın, kaptan. Al fıçılarını ve kaybol. Uyarayım, vali karşısında bana parmak sallaman bir işe yaramaz. Bugün sakladığım yeri değiştireceğim. Zamanını boşa harcama.";
			link.l1 = "Yapmayacaktım. Yetkililere başvurmanın ne kadar anlamsız olduğunu anlıyorum.";
			link.l1.go = "officer_14";
		break;
		
		case "officer_14":
			dialog.text = "Acele et, fazla vaktim yok.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_PeaceExit");
		break;
		
		case "officer_15":
			DialogExit();
			AddDialogExitQuestFunction("FMQM_BattleExit");
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_02.wav");
			dialog.text = "Ah! Ne tesadüf! Merhaba, monsieur! Güzel bir gece geçiriyor musunuz?";
			link.l1 = "İyi geceler... ah, sen misin! Seni hatırlıyorum, Karayipler'e ilk geldiğim gün tanışmıştık. Mösyö Gregoire Valinnie.";
			link.l1.go = "greguar_1";
		break;
		
		case "greguar_1":
			dialog.text = "Hâlâ hatırlıyor olman güzel. Şimdi kaptan olmuşsun görüyorum. Kaptan "+GetFullName(pchar)+" . Tebrikler.";
			link.l1 = "Teşekkürler...";
			link.l1.go = "greguar_2";
		break;
		
		case "greguar_2":
			dialog.text = "Keyifin yok gibi, kaptan. Burada ne oldu? Bir sorun mu var?";
			link.l1 = "Bir şeyler ters gidiyor...";
			link.l1.go = "greguar_3";
		break;
		
		case "greguar_3":
			dialog.text = "Beyefendi, caddenin ortasında durmak yerine bir meyhaneye gidelim. Bir iki bardak içki iyi gelir size. Orada konuşuruz. Hadi!";
			link.l1 = "...";
			link.l1.go = "greguar_4";
		break;
		
		case "greguar_4":
			DialogExit();
			NextDiag.CurrentNode = "greguar_5"; 
			FreeSitLocator("Fortfrance_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Fortfrance_tavern", "sit", "sit_front4", "FMQM_InTavern", -1);
		break;
		
		case "greguar_5":
			LAi_SetSitType(Pchar);
			dialog.text = "Doldur bakalım, kaptan...";
			link.l1 = "Devam et...";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,20);
			RecalculateJumpTable();
			dialog.text = "Vay... Şimdi lütfen bana neyin var söyle? Geçen hafta asılan adam gibisin. O da darağacında tam olarak böyle bakıyordu.";
			link.l1 = "Bakın, Mösyö Gregoire... Şöyle diyelim, işimde bazı sıkıntılarım var.";
			link.l1.go = "greguar_7";
		break;
		
		case "greguar_7":
			dialog.text = "Kaptan, benimle her şeyi paylaşabilirsin. Seni valiye ya da komutana ispiyonlayacak değilim, buna güvenebilirsin. Bana güvenmiyor musun?";
			link.l1 = "Sana güveniyorum, monsieur.";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			dialog.text = "O zaman itiraf et ve ruhunu rahatlat. Belki sana yardım edebilirim.";
			link.l1 = "Yerel bir gemi yapımcısı, beni Trinidad'dan ayrılan bir İspanyol kervanını yağmalamam için tuttu. Reçineye çok ihtiyacı vardı, hedefim de oydu, varil başına on beş dublon ödeyeceğine söz verdi. Kervanı buldum, yağmaladım ve malları buraya getirdim. Gemimi tamire aldılar ve varilleri tersaneye boşalttılar. Tam anlaşmamızı bitirmek üzereydik ki o subay çıkageldi... Bunu nasıl öğrendi acaba?";
			link.l1.go = "greguar_9";
		break;
		
		case "greguar_9":
			dialog.text = "";
			link.l1 = "Hepsi buydu, yakalandık. Sanırım gemi yapımcısına hakkını teslim etmeliyim – bütün suçu üstlendi, reçinenin kendisine ait olduğunu söyledi ve benimle hiçbir ilgisi olmadığını anlattı. Sonunda o tutuklandı ve param da gitti. İspanyol kervanıyla yaşanan karmaşa ise tam bir zaman ve para kaybıydı, ama hapse girmediğim için şanslıydım. Bir kadeh daha doldur, monsieur Gregoire.";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			dialog.text = "Yani, gemi yapımcısı tutuklandı mı?";
			link.l1 = "Evet, öyle. Tam da bahsettiğim subay tarafından hapse götürüldü. Onları görmeliydin.";
			link.l1.go = "greguar_11";
		break;
		
		case "greguar_11":
			dialog.text = "Evet, ikisini de gördüm, ama Teğmen Felicien Gronier’in eski dostunu tutuklayabileceği aklımın ucundan bile geçmezdi.";
			link.l1 = "Ne... ne dedin az önce?";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Doğru duydun. Teğmen Felicien Gronier ve gemi yapımcısı "+GetFullName(characterFromId("FortFrance_shipyarder"))+" eski dostlardır. Eskiden Avrupa'da birlikte orduda hizmet etmişlerdi. Gronier ise orduda kalmaya devam etti ve "+GetFullName(characterFromId("FortFrance_shipyarder"))+"   kendi işini kurmayı başardı.";
			link.l1 = "Demek birbirlerini tanıyorlar... Şimdi anlıyorum...";
			link.l1.go = "greguar_13";
		break;
		
		case "greguar_13":
			dialog.text = "Sevgilim "+pchar.name+",   görünüşe göre kandırılmışsın.   Burada hâlâ yenisin ve bundan faydalanmışlar.   Bahse girerim yüz dublon ki monsieur "+GetFullName(characterFromId("FortFrance_shipyarder"))+" üç gün ya da daha kısa bir sürede yine tersanesinde dolaşıyor olacak.";
			link.l1 = "Galiba haklısınız, monsieur. Beni fena kandırmışlar. O subayın reçineden haberi olması imkânsızdı. Zamanlama da tam yerindeydi.";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			dialog.text = "Burası Karayipler, monsieur "+pchar.name+". Alış artık buna. Görünüşe aldanma, burada en aşağılık herifler bile saygın bir soylu gibi görünür.";
			link.l1 = "Bu lafı daha önce bir yerden duymuştum... Onlarla ne yapmalıyım? Valinin yanına gidip haber mi vereyim?";
			link.l1.go = "greguar_15";
		break;
		
		case "greguar_15":
			dialog.text = "Bu durumda korkarım ki "+GetFullName(characterFromId("FortFrance_shipyarder"))+"Sana başka bir hikaye anlatacağım ve sonunda kendini hapiste bulacaksın.";
			link.l1 = "Tabii ya. Peki o zaman! Madem yasa benden yana değil, ben de kendi bildiğimi yaparım, kahretsin! Öylece pes edecek değilim.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			dialog.text = "Lütfen sakin ol "+pchar.name+".   Bu öfke ve romun etkisiyle konuşuyorsun, kendin değilsin. Biraz uyu, sonra tekrar düşün. Belki de en iyisi bu meseleyi bırakmandır. Teğmen Felicien Gronier ve "+GetFullName(characterFromId("FortFrance_shipyarder"))+" Burada çok güçlü insanlar var, senin boyunu aşarlar. Sakın aptalca bir şey yapma.";
			link.l1 = "Göreceğiz. Beni aydınlattığın için teşekkür ederim. Seninle tanıştığıma memnun oldum.";
			link.l1.go = "greguar_17";
		break;
		
		case "greguar_17":
			dialog.text = "Dikkatli ol. Sana söylediklerimi unutma.";
			link.l1 = "Yapacağım. Şimdi son bir kadeh daha içelim!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_OutTavern");
		break;
		
		case "greguar_18":
			PlaySound("Voice\English\LE\Greguar\Greguar_03.wav");
			dialog.text = "Kaptan "+GetFullName(pchar)+"!";
			link.l1 = "Ah, Mösyö Gregoire! Yine siz!";
			link.l1.go = "greguar_19";
		break;
		
		case "greguar_19":
			dialog.text = "Yes. After our tavern talk, I made inquiries regarding Lieutenant Felicien Gronier. It turns out that he requested a ten-day leave not long ago. His petition was approved. I saw him today; he took a longboat to a tartane which soon sailed to Guadeloupe. She's called the Topaz. I've told you everything; it's your call now. I'm sure you can see the pattern in Gronier's sudden request for leave and his departure from the island on a newly built tartane.";
			link.l1 = "Artık her şey apaçık ortada, bundan hiç şüphem yok! Bu tartanede reçinem ambarında saklanıyor! Monsieur Gregoire, teşekkür ederim, gerçekten büyük bir iyilik yaptınız! Size nasıl karşılık verebilirim?";
			link.l1.go = "greguar_20";
		break;
		
		case "greguar_20":
			dialog.text = "Ah, hadi ama dostum. Biz soylu insanlarız, birbirimize yardım etmeliyiz. Hayatımız böyle geçiyor. Sen de benim yerimde olsan aynısını yapardın, inanıyorum. Bir dakika bile kaybetme, kuzeye yelken aç ve subayı bul. Sakın çatışmaya girme, sadece izini sür ve ne peşinde olduğunu öğren. Acele et, kaptan!";
			link.l1 = "Tekrar teşekkür ederim!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_HurryToSea");
		break;
		
		case "pirate":
			dialog.text = "Ne bakıyorsun? Burada ne istiyorsun?";
			link.l1 = "Hey dostum, mallarımı almaya geldim. Şu varilleri görüyor musun? O reçine benim, ama bana tek kuruş ödemediler.";
			link.l1.go = "pirate_1";
			DelLandQuestMark(characterFromId("FMQM_Enemy_crew_2"));
		break;
		
		case "pirate_1":
			dialog.text = "Sen aptal mısın yoksa? Hâlâ şansın varken kaybol buradan!";
			link.l1 = "Bu reçineyi elde etmek için çok uğraştım, birkaç pislik beni durduramaz.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Şu şık takımını tam burada gömeceğiz!";
			link.l1 = "Ah, gömmeyi teklif etmen ne hoş, ama korkarım ki seni burada, kumsalda bırakıp martıların bağırsaklarını yemesine izin vereceğiz!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_ShoreFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
