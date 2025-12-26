// диалоги НПС по квесту НСО
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
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
			dialog.text = "Ne arıyorsun?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;
		
		// инспектор Ноэль Форже
		case "noel":
			dialog.text = "Sizi tanıdığıma memnun oldum, kaptan!";
			link.l1 = "Sizi tanıdığıma ben de memnun oldum, Mösyö Forget. Bu ıssız yerde metropolden bir misafirle karşılaşmak nadir bir olay...";
			link.l1.go = "noel_1";
		break;
		
		case "noel_1":
			DialogExit();
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_3";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "noel_2":
			dialog.text = "Bu yolculukta sizin geminizde olacağım için memnunum, kaptan. Chevalier de Poincy bana sizinle ilgili pek çok ilginç hikaye anlattı. Eminim yemekten sonra sohbet edecek çok konumuz olacak. Bir kadeh şarap da iyi giderdi.";
			link.l1 = "Ben her zaman keyifli bir sohbete varım, hele de karnım doymuşsa. Size eşlik etmekten memnuniyet duyarım, Baron. ";
			link.l1.go = "noel_3";
		break;
		
		case "noel_3":
			dialog.text = "Mükemmel. Bir kolonide olduğumuzda, senden beni valiye götürmeni isteyeceğim ve ona ne yapılması gerektiğini bizzat açıklayacağım. Sen sadece işlerimi bitirmemi bekleyeceksin. Anlaştık mı?";
			link.l1 = "Hoş geldiniz, Bay Forget. Gemimize buyurun!";
			link.l1.go = "noel_4";
		break;
		
		case "noel_4":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 12.0);
		break;
		
		case "noel_5":
			dialog.text = "Tortuga küçük bir koloni, Kaptan. Bu adada incelemem gereken her şeyi gözden geçirmem yaklaşık üç günümü alır diye tahmin ediyorum.";
			link.l1 = "Anlaşıldı, Baron. O halde üç gün sonra sizi almak için buraya geleceğim. Bol şans!";
			link.l1.go = "noel_6";
		break;
		
		case "noel_6":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "Patria_VisiterTortuga");
		break;
		
		case "noel_7":
			dialog.text = "Tortuga'daki işim bitti, demir alma vakti geldi.";
			link.l1 = "Anlaşıldı, Baron. Hemen yola çıkıyoruz.";
			link.l1.go = "noel_8";
		break;
		
		case "noel_8":
			DialogExit();
			Patria_VisiterTortugaSail();
		break;
		
		case "noel_9":
			dialog.text = "Yes, yes, we will definitely report this in Capsterville. The threat of such an important colony being conquered... unthinkable. I will personally ensure that Chevalier de Poincy takes strict and ruthless measures! Captain, I will remain on this island for a week; there are many plantations here, and it will take some time.";
			link.l1 = "Anladım, Baron. Yedi gün sonra valinin sarayının önünde seni bekliyor olacağım. İyi eğlenceler ve kendini fazla yorma!";
			link.l1.go = "noel_10";
		break;
		
		case "noel_10":
			DialogExit();
			DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "Patria_VisiterPortPax");
		break;
		
		case "noel_11":
			dialog.text = "İşte buradasınız, kaptan. Hispaniola'daki işim bitti, demir alma vakti geldi.";
			link.l1 = "Anlaşıldı, Baron. Hemen yola çıkıyoruz.";
			link.l1.go = "noel_12";
		break;
		
		case "noel_12":
			DialogExit();
			Patria_VisiterPortPaxSail();
		break;
		
		case "noel_13":
			dialog.text = "Kaptan, bu ada bana tanıdık geliyor. Burası Aziz Christopher değil mi?";
			link.l1 = "Evet, baron, tam olarak öyle. Neredeyse vardık.";
			link.l1.go = "noel_14";
		break;
		
		case "noel_14":
			dialog.text = "Neredeyse geldik mi?! Saint-Martin'e de uğramamız gerekmiyor muydu? Orası da Fransız kolonilerinden biri.";
			link.l1 = "Sen Sint Maarten'ı mı kastediyorsun? Burası Hollanda kolonisi, Mösyö Forget.";
			link.l1.go = "noel_15";
		break;
		
		case "noel_15":
			dialog.text = "Öyle mi? Paris'te Fransız sayılırdı. Nasıl oluyor bu?";
			link.l1 = "Hiçbir fikrim yok, Baron. Takımadalara ilk adım attığımdan beri Sint Maarten hep Hollanda kolonisi oldu. Belki de bilmediğim bir şey vardır. Bu meseleyi Chevalier de Poincy ile konuşmayı düşünmelisiniz.";
			link.l1.go = "noel_16";
		break;
		
		case "noel_16":
			dialog.text = "Peki kaptan, öyle olsun. Zaten neredeyse Capsterville'e vardık.";
			link.l1 = "...";
			link.l1.go = "noel_17";
		break;
		
		case "noel_17":
			DialogExit();
			Island_SetReloadEnableGlobal("Nevis", true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			pchar.quest.Patria_visiter_fin.win_condition.l1 = "location";
			pchar.quest.Patria_visiter_fin.win_condition.l1.location = "Charles_Roomtownhall";
			pchar.quest.Patria_visiter_fin.function = "Patria_VisiterFin";
			pchar.questTemp.Patria = "epizode_2_return";
		break;
		
		case "noel_18":
			dialog.text = TimeGreeting()+", kaptan. Sizi görmekten memnun oldum. Terfi ettiğinizi duydum, lütfen tebriklerimi kabul edin! Doğrusunu söylemek gerekirse, gerçekten de de Poincy'nin hizmetindeki en akıllı ve yetenekli subaylardan birisiniz.";
			link.l1 = "Teşekkür ederim, monsieur.";
			link.l1.go = "noel_19";
		break;
		
		case "noel_19":
			dialog.text = "Sonunda geriye sadece bir koloni kaldı, Saint-Martin. Açıkçası, bu yolculuklardan yoruldum. Bu denetimi bitirip bir sonraki Fransız Batı Hint Adaları ticaret seferini planlamaya başlamak için sabırsızlanıyorum. Demir almaya hazır mıyız?";
			link.l1 = "Tamam, Baron. Gemiye çık.";
			link.l1.go = "noel_20";
		break;
		
		case "noel_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBaron", 5.0);
		break;
		
		case "noel_21":
			dialog.text = "Kaptan, bana az önce ne olduğunu anlatır mısınız? Bu savaş anlamına mı geliyor? Tanrı aşkına, neden neredeyse Hollandalılar tarafından batırılıyorduk?";
			link.l1 = "Baron, ben de hiçbir şey anlamıyorum! Bu kesinlikle bir yanlış anlaşılma olmalı, hiç şüphem yok.";
			link.l1.go = "noel_22";
		break;
		
		case "noel_22":
			dialog.text = "Kaptan, bu 'yanlış anlaşılmanın' bir adı olduğuna bahse girerim! Saint-Martin'in sözde 'kiracısı' ve sevgili Chevalier de Poincy'nin ortağı Peter Stuyvesant!";
			link.l1 = "Hiçbir fikrim yok, Baron. En iyisi Capsterville'e aceleyle gidip bu meseleyi Genel Vali'ye bildirelim.";
			link.l1.go = "noel_23";
		break;
		
		case "noel_23":
			dialog.text = "Hiç şüphe yok, tam olarak bunu yapacağız! Ve bir açıklama isteyeceğim! Adayı Hollandalılara kiralamanın büyük bir hata olduğunu biliyordum! Hadi buradan olabildiğince çabuk gidelim kaptan, birisi peşimize düşmeden önce!";
			link.l1 = "Kesinlikle, monsieur ...";
			link.l1.go = "noel_24";
		break;
		
		case "noel_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBack", 5.0);
		break;
		
		case "noel_25":
			dialog.text = "Monsieur, first let me congratulate you on your promotion! I eagerly supported Monseigneur de Poincy's decision to grant you the rank of Vice Admiral. You truly deserve this title! Now, I have recently returned from Saint-Martin. At the warehouses of Philipsburg, we conducted an inspection; all Dutch goods were confiscated and now belong to the treasury of France. You, as the commander of the operation, have been granted a share of the spoils. I agree with the Chevalier that this is only fair. Your goods have been transferred to the warehouse of the St. Christopher store, and you may collect them whenever you wish.";
			link.l1 = "Teşekkür ederim, Baron. Mallar bir süre orada kalsın. Curaçao'dan döndüğümde onları alacağım.";
			link.l1.go = "noel_26";
		break;
		
		case "noel_26":
			dialog.text = "Bir sonraki seferinizde bol şanslar, Amiral Yardımcısı! Zaferle döneceğinizden ve o alçak Stuyvesant'ı hak ettiği cezaya çarptıracağınızdan eminim.";
			link.l1 = "...";
			link.l1.go = "noel_27";
		break;
		
		case "noel_27":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_start";
			AddQuestRecord("Patria", "58");
			pchar.questTemp.Patria.GoodsSM = "true";
		break;
		
		case "noel_28":
			dialog.text = "Burada kimi görüyoruz! Koramiral Charles de Maure! Sizi görmek ne güzel! Port-au-Prince'e ne vesileyle geldiniz?";
			link.l1 = "I'm pleased to meet you too, Baron. I'm here because of my duty; I had to pay monsieur Jeremy Deschamps du Mussaca a courtesy visit...";
			link.l1.go = "noel_29";
		break;
		
		case "noel_29":
			dialog.text = "Bu karşılaşma gerçekten büyük bir şans, çünkü seninle yüz yüze görüşmek için uzun zamandır bekliyordum. Seninle konuşmak istiyorum, ama burada değil.";
			link.l1 = "O halde meyhaneye gidelim, ne dersin?";
			link.l1.go = "noel_30";
		break;
		
		case "noel_30":
			DialogExit();
			FreeSitLocator("PortPax_tavern", "sit_base1");
			DoQuestReloadToLocation("PortPax_tavern", "sit", "sit_base1", "Patria_CondotierTavern");
		break;
		
		case "noel_31":
			LAi_SetSitType(pchar);
			dialog.text = "Burada istenmeyen kulaklar yok, rahatça konuşabiliriz...";
			link.l1 = "Sizi dinliyorum, Baron.";
			link.l1.go = "noel_32";
		break;
		
		case "noel_32":
			dialog.text = "Amiral Yardımcısı, onurlu bir adam olduğunuz belli. Böylesine cesur bir deniz subayı elbette öyle olmalı...";
			link.l1 = "Hmm... Sanırım sizi tam olarak anlamadım, monsieur...";
			link.l1.go = "noel_33";
		break;
		
		case "noel_33":
			dialog.text = "Monsieur de Maure, size bir şey sormak istiyorum: Efendiniz, Genel Vali Philippe de Poincy hakkında ne düşünüyorsunuz?";
			link.l1 = "Bir subayın görevi komutanını düşünmek değil, onun emirlerini yerine getirmektir.";
			link.l1.go = "noel_34";
		break;
		
		case "noel_34":
			dialog.text = "Ah, bırakın bunu Amiral Yardımcısı, ne kışladayız ne de de Poincy'nin salonunda. Şöyle söyleyeyim: sizce de monsieur de Poincy... yetkisini kötüye kullanmıyor mu? Hâlâ Saint-Martin Kalesi'nin toplarından neredeyse batıyorduk, onu unutamıyorum. Eminim Hollanda hainliğinin bir sebebi vardı.";
			link.l1 = "Adayı fethetmek istiyorlardı.";
			link.l1.go = "noel_35";
		break;
		
		case "noel_35":
			dialog.text = "Evet, evet, ama neden tam da ben incelemeye karar verdiğim anda oldu bu? Neden bir ay önce değil? Ya da iki ay sonra? Bunun tesadüf olduğuna inanmıyorum, monseigneur. Hiç şüpheniz yok mu? Orada ikimizin de hayatı tehlikedeydi.";
			link.l1 = "Her gün hayatımı riske atıyorum, Mösyö Forget. Bunu anladığınızı düşünüyorum...";
			link.l1.go = "noel_36";
		break;
		
		case "noel_36":
			dialog.text = "Cesaretinize şüphe yok. Ama söylemek istediğim bu değildi. Bakın... Sizin özgürlüğe kavuşturduğunuz Saint-Martin'de görevimi yaparken, adanın derinliklerinde bir madenle ilgili yerel halktan fısıltılar duydum. İnsanlara bunu sordum ama aptalca davrandılar. Korkuyorlardı... Belli ki bana pek güvenmiyorlardı, ama bu sadece şüphelerimi artırdı: Acaba bu gizemli maden tüm bunların sebebi olabilir mi, Monsieur de Maure? Sonuçta savaşlar altın yüzünden çıkar, değil mi?";
			link.l1 = "There are numerous mines in the archipelago. Most of them are exhausted and have become worthless. I know of one major operating gold mine; it is owned by the Spaniards on South Main. But I've never heard of gold mining on Saint-Martin.";
			link.l1.go = "noel_37";
		break;
		
		case "noel_37":
			dialog.text = "Konuşma sanatında ustasınız, Amiral Yardımcısı! Anlıyorum: bana güvenmiyorsunuz. Burada yeniyim... Monsieur de Maure, ama Paris'te etkili biriyim. Maliye Bakanı yakın dostumdur. Kralı düzenli olarak ziyaret ederim. Yetkim, elbette resmiyette, Philippe de Poincy'ninkinden çok daha fazladır, çünkü burada Genel Vali en yetkili kişidir. Ama dürüst olmak gerekirse, burada, kolonilerde, güçlü olanın sözü geçer.";
			link.l1 = "Bu konuda tamamen sana katılıyorum.";
			link.l1.go = "noel_38";
		break;
		
		case "noel_38":
			dialog.text = " Ama Paris'te değil. Orada en etkili kişiler Kral ve Maliye Bakanı... benim yakın dostum. Monsieur de Maure, siz harika bir askersiniz, fakat inanıyorum ki Phillipe de Poincy sizi kendi çıkarları için kullanıyor. Zekisiniz, bu yüzden şüpheleriniz olmalı. Bana güvenebilirsiniz. Size tam bir gizlilik ve Paris'teki yetkililerin desteğini garanti ediyorum. Ünvanım üzerine yemin ederim.";
			link.l1 = "***POINCY'E SADIK KAL***";
			link.l1.go = "noel_39"; // развилка
			link.l2 = "***BARON FORGET'İN TARAFINI TUT***";
			link.l2.go = "noel_53";
		break;
		
		case "noel_39":
			dialog.text = "";
			link.l1 = "Sizi anlıyorum, Mösyö Forger. Yerel düşünce tarzına yabancı biri için de Poincy'nin davranışları gerçekten de tuhaf görünebilir. Ben de Takımadalar'a ilk geldiğimde burada olup bitenler karşısında gerçekten şaşkına dönmüştüm. Hâlâ bana söylenen ilk sözleri hatırlıyorum: 'Eğer korumasız bir İspanyol gemisiyle karşılaşırsan, ele geçirmeyi deneyebilirsin.' İhanet, hile, aldatmaca – burada her köşe başında karşına çıkıyor. Korsanlık, yağma, soygun...";
			link.l1.go = "noel_40";
		break;
		
		case "noel_40":
			dialog.text = "";
			link.l1 = "Avrupa'da İspanya ile barış içindeyiz. Ama burada, amansız düşmanız. Hollandalılar bugün dostça ve zararsız görünebilir, ama yarın bir Şirket yetkilisi mallarına el koyar, sadece bir anda ithalatının yasaklandığını duyurdukları için, senin bundan haberin olmasa bile. İngiliz subayı açıkça korsanlık yapıyor, Şirketin gemilerini batırıyor, Şirket ise kendini hayalet gemi gibi gösteren bir haydutu tutup İngiliz tüccarlarını dehşete düşürüyor...";
			link.l1.go = "noel_41";
		break;
		
		case "noel_41":
			dialog.text = "";
			link.l1 = "In this wolf's den, we sometimes have to make strange decisions that may not be obvious to those unfamiliar with it all. And what seems suspicious to you is, in fact, the only correct course of action. It is difficult to sit on several chairs at once and still manage to send profits to the parent state. Chevalier de Poincy handles this perfectly; he is an experienced administrator and a visionary politician. Of course, he can make mistakes, but we all do at some point in our lives...";
			link.l1.go = "noel_42";
		break;
		
		case "noel_42":
			dialog.text = "";
			link.l1 = "Ve sen her şeyle ve herkesle hesaplaşmak zorundasın. Yeni Dünya'nın tamamının kendilerine ait olduğuna inanan İspanyolların hırslarıyla, Hollandalı tüccarların açgözlülüğüyle, İngilizlerin soğukkanlı ihtiyatı ve acımasız zalimliğiyle. Hatta korsanlarla bile.";
			link.l1.go = "noel_43";
		break;
		
		case "noel_43":
			dialog.text = "Korsanlarla mı?!";
			link.l1 = "Yes, you heard right. The Dutch and the British are actively cooperating with pirates... unofficially, of course. The Brethren of the Coast is a serious force that can challenge any nation in the region; they are in constant conflict with everyone they encounter, and no one is capable of stopping them. The only thing that makes them slightly less dangerous is the fact that they are scattered and act on their own behalf. Did you know that the former governor of Tortuga, Levasseur, actually created a state within a state, relying completely on pirates?";
			link.l1.go = "noel_44";
		break;
		
		case "noel_44":
			dialog.text = "Bununla ilgili bir şeyler duymuş olabilirim...";
			link.l1 = "Tortuga limanında adayı koruyan birkaç güçlü korsan gemisi sürekli demirliydi. Levasseur, Fransa'ya ihanet etti ve burada bir tür yerel otoriteye dönüştü. Şimdi ise, Tortuga'daki korsan yuvası efendileriyle birlikte yok edildikten sonra, korsanlar Fransızlara karşı fena halde öfkeliler...";
			link.l1.go = "noel_45";
		break;
		
		case "noel_45":
			dialog.text = "Yok artık!";
			link.l1 = "Evet. Bunu yapmak zorundaydık, yoksa Tortuga'yı kaybederdik, gerçi elde ettiğimiz sonuç pek de iyi olmadı. Artık Karayipler'de hiçbir Fransız ticaret gemisi kendini güvende hissedemez. Korsan baronlarıyla anlaşması olmayan İspanyolların bile en azından güçlü kalyonlardan ve filibusterleri püskürtebilecek savaş gemilerinden oluşan filoları var. Tıpkı Hollandalıların Doğu Hindistan gemileri ve xebec'leri gibi. Ama ne yazık ki biz böyle şeylerle övünemeyiz. Üstelik Fransız korsanlar sık sık Fransız tüccarları soyuyor.";
			link.l1.go = "noel_46";
		break;
		
		case "noel_46":
			dialog.text = "Bu delilik! Buna bir son vermenin hiçbir yolu yok mu?";
			link.l1 = "Birçok kişi denedi. Sonunda, savaşmak yerine sadakatlerini altınla satın alıyorlar. Yani korsanlık fermanları veriyorlar.";
			link.l1.go = "noel_47";
		break;
		
		case "noel_47":
			dialog.text = "Hmm...";
			link.l1 = "So, speaking from experience, a French trading company here in the Archipelago would be a very bad idea. Do you understand now what difficulties you will have to face? How many bastards want to get their share of the income here? And they are not going to let go of it easily. And pirates, they are capable of unthinkable things; call them crazy if you want, but they almost always achieve their dirty goals. In order to protect merchant ships, you would have to maintain a massive military fleet, but will that be profitable from a financial standpoint?";
			link.l1.go = "noel_48";
		break;
		
		case "noel_48":
			dialog.text = " Ama Fransız tüccarlar burada bir şekilde işlerini yürütüyor, öyle mi? ";
			link.l1 = "Aynen öyle, bir şekilde. Özellikle şimdi, Levasseur'un Tortuga'daki korsan kalesi ele geçirilmişken...";
			link.l1.go = "noel_49";
		break;
		
		case "noel_49":
			dialog.text = "Sözlerin de Poincy'nin söyledikleriyle örtüşüyor.";
			link.l1 = "Gerçek bu. Takımadalarda işler böyle yürür, hep de böyle olmuştur.";
			link.l1.go = "noel_50";
		break;
		
		case "noel_50":
			dialog.text = "Söylediklerinde ne kadar heveslisin. Ben bile bunların çoğunu bilmiyordum ve, haklısın: hâlâ da bilmiyorum. Sanırım Poincy hakkındaki şüphelerim yersizmiş. Gözümü açtın. Sana teşekkür ederim, Amiral Yardımcısı. Ama Fransız bakanı Şirket’in kurulmasına güveniyor. Kral’ın paraya ihtiyacı var...";
			link.l1 = "I understand. But please take what I have just said into consideration; if the creation of the French West Indies is unavoidable, then please make sure that we have a strong military fleet to protect it.";
			link.l1.go = "noel_51";
		break;
		
		case "noel_51":
			dialog.text = "Asaletiniz gerçekten hayranlık uyandırıcı, Amiral Yardımcısı! Ne kadar soylu bir karakteriniz var! Bu kadar uzun süredir burada olmanıza ve eve dönmek için acele etmemenize hiç şaşırmıyorum. Ama tekrar görüşeceğiz: Altı ay sonra buraya döneceğim. Fransız Ticaret Şirketi yükselecek. Korsanlar konusunda ise, bence biraz abartıyorsunuz. Sonuçta, elimizde savaş gemileri ve sizin gibi cesur kaptanlar var.";
			link.l1 = "I am sorry, Baron, but I am just one man, and besides me France has only one strong ship in the archipelago, 'Eclatant'. It won't be enough; we will lose far more than we will gain... Eh, whatever, it is what it is. I suppose we will think of something in the meantime... When will you be heading off to France?";
			link.l1.go = "noel_52";
		break;
		
		case "noel_52":
			dialog.text = "İki hafta sonra Saint Christopher'a döneceğim ve oradan da eve gideceğim. Monsieur de Poincy bana güzel bir gemi verdi - 'Favory' adında bir brig ve harika bir kaptan. Gemi hızlı, kaptanı tecrübeli ama elbette seninle daha güvende hissediyordum. Takımadalar boyunca yaptığımız yolculukları hatırlıyorum Amiral Yardımcısı, gerçekten harika bir deneyimdi.";
			link.l1 = "Güzel sözleriniz için teşekkür ederim, Baron. Sanırım artık yollarımızı ayırmanın zamanı geldi...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToPirates");
		break;
		
		case "noel_53":
			dialog.text = "";
			link.l1 = "Burada herkes birbirini kullanır. Şövalye, donanmada subay olmadan çok önce beni işlerinde kullanmıştı.";
			link.l1.go = "noel_54";
		break;
		
		case "noel_54":
			dialog.text = "Ve bu kabul edilebilir mi? Ne düşünüyorsun?";
			link.l1 = "Hayır. Ama Şövalye bana başka bir seçenek bırakmadı: ya onun emirlerine uyacaktım, ya da kardeşim ömrünün sonuna kadar parmaklıklar ardında kalacak ve ailemin iyi adı mahvolacaktı.";
			link.l1.go = "noel_55";
		break;
		
		case "noel_55":
			dialog.text = "Korkunç! Bu düpedüz terörizm! Böyle tehditler için bir sebebi var mıydı?";
			link.l1 = "Kardeşim onun güvendiği adam olma talihsizliğini yaşadı. Şimdi de ben aynı durumdayım.";
			link.l1.go = "noel_56";
		break;
		
		case "noel_56":
			dialog.text = "Kardeşin şimdi nerede?";
			link.l1 = "I managed to free him, but I lost him the very next day; he chose not to serve under anyone anymore.";
			link.l1.go = "noel_57";
		break;
		
		case "noel_57":
			dialog.text = "Poincy'nin iddia ettiği kişi olmadığını biliyordum! Koyun postuna bürünmüş bir kurt! Amiral Yardımcısı, bana güvenebilirsiniz. Ben onurlu bir adamım. Ve eğer onun suçlarına dair somut kanıt bulabilirsek, sizi o 'haminizin' boyunduruğundan kurtaracağım. Bu Stuyvesant'la ilgili sıkıcı hikaye hakkında bir şey biliyor musunuz? Açıkça konuşun, endişelenmeyin – siz sadece bir askersiniz ve size verilen emirleri yerine getirmek zorundaydınız.";
			link.l1 = "Biliyorum. Gerçekten de Saint-Martin'de bir maden var. Ama oradan altın değil, tuz çıkarıyorlar. Tuz, İspanyollar arasında çok rağbet görüyor. Poincy, İspanyollarla doğrudan ticaret yapamıyordu, bu yüzden Stuyvesant aracı olarak devreye girdi.";
			link.l1.go = "noel_58";
		break;
		
		case "noel_58":
			dialog.text = "Yani Poincy ve Stuyvesant iş ortağı mı?";
			link.l1 = "Eskiden öyleydi. Sen Saint-Martin'i incelemek istediğini söyleyince, Stuyvesant Poincy'yi oyundan çıkarmaya karar verdi ve tuz madeninin tüm kazancını kendine aldı. Poincy kimseye bir şey söyleyemedi... Ama gördüğümüz gibi, Stuyvesant yanlış hesap yaptı.";
			link.l1.go = "noel_59";
		break;
		
		case "noel_59":
			dialog.text = "Sence maden hâlâ çalışıyor mu?";
			link.l1 = "Bundan eminim. Görünüşe göre Poincy'nin artık yeni bir ticaret ortağı var. Hem de bizzat Albay Doily'nin kendisi.";
			link.l1.go = "noel_60";
		break;
		
		case "noel_60":
			dialog.text = "Bakanlığa herhangi bir kanıt sunabilir miyiz?";
			link.l1 = "Hmm. Madeni ele geçirdiğimizde, bu arada bunu Hollandalılar değil, İspanyollar yaptı, sahibini yakaladık. Hâlâ gemimde. Onunla konuşabilirsin. Özgürlüğü karşılığında sana ilginç şeyler anlatma ihtimali var.";
			link.l1.go = "noel_61";
		break;
		
		case "noel_61":
			dialog.text = "Hemen gemine gidelim. Esirinin kamarana götürülmesini emret. Onunla konuşmam lazım.";
			link.l1 = "Pekâlâ, gidelim.";
			link.l1.go = "exit";
			npchar.greeting = "noel_4";
			AddDialogExitQuestFunction("Patria_CondotierToCabin");
		break;
		
		case "noel_62":
			dialog.text = "Harika, Koramiral. Onunla konuşacağım. Lütfen burada kalın.";
			link.l1 = "Elbette...";
			link.l1.go = "noel_63";
		break;
		
		case "noel_63":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "rld", "aloc1", "", -1);
			DoQuestFunctionDelay("Patria_CondotierInCabinTalk", 3.0);
		break;
		
		case "noel_64":
			dialog.text = "Tutsak aldığınızdan tüm delilleri yazdım ve o da altına imzasını attı. Şimdi ona verdiğim sözü yerine getirmeliyiz: uygun bir fırsat çıktığında Cartagena'ya uğrayıp onu karaya çıkarmalısınız. Ama her şeyi kendiniz de duydunuz.\nŞu bizim Poincy ne alçakmış! Adayı Hollandalılara kiralamış, orada yasa dışı işler çevirmiş ve İspanyolların gelip madeni işletmesine izin vermiş! Kralın hazinesinin onun bencilliği yüzünden ne kadar zarara uğradığını düşünmek bile istemiyorum!";
			link.l1 = "Bu delil Poincy'yi suçlamak için yeterli olacak mı?";
			link.l1.go = "noel_65";
		break;
		
		case "noel_65":
			dialog.text = "Ne yazık ki, sanırım yetmeyecek. Kanıt çok önemli, ama yeterli değil. Ama ikimizin de bildiği nedenlerle bu işlere karışmanı istemiyorum.";
			link.l1 = "İspanyol, komisyonunuz buraya geldiğinde ifade vermeyi kabul etti.";
			link.l1.go = "noel_66";
		break;
		
		case "noel_66":
			dialog.text = "Bu, en erken altı ay sonra gerçekleşecek, ve kim bilir bu İspanyol'a ne olacak ya da onu Cartagena'da daha sonra bulabilecek miyiz... Daha değerli kanıtlara ihtiyacımız var. Yani – madenin gizli faaliyetlerine devam ettiğine ve sevgili genel valimizin ceplerini hâlâ doldurduğuna dair bir kanıt.";
			link.l1 = "Yani Saint-Martin'e gitmemizi mi öneriyorsun?";
			link.l1.go = "noel_67";
		break;
		
		case "noel_67":
			dialog.text = "Evet. Madene nasıl gidileceğini biliyor musun?";
			link.l1 = "Yapıyorum.";
			link.l1.go = "noel_68";
		break;
		
		case "noel_68":
			dialog.text = "O zaman, gece olunca, seninle birlikte oraya sessizce sızacağız, kimse bizi görmeden, ve orada neler olup bittiğine bakacağız.";
			link.l1 = "Çok iyi.";
			link.l1.go = "noel_69";
		break;
		
		case "noel_69":
			dialog.text = "Peki ya Şövalye, ha? Şimdi anlıyorum neden bana bu kadar cesurca Fransız Ticaret Şirketi'ni Takımadalar'da kurmanın kârlı olmayacağını ima etti... Tabii ki, bu en çok onun işine gelmezdi!";
			link.l1 = "Artık müttefik olduğumuza göre, Baron, sana her şeyi açıkça anlatacağım. Poincy benden... burada Ticaret Şirketi kurmaman için seni ikna etmemi istedi.";
			link.l1.go = "noel_70";
		break;
		
		case "noel_70":
			dialog.text = "Demek öyle! Umarım en azından seni beni kılıçla ya da tabancayla öldürmeye göndermemiştir?";
			link.l1 = "Hayır. Başka bir şekilde ikna olman gerekiyordu.";
			link.l1.go = "noel_71";
		break;
		
		case "noel_71":
			dialog.text = "Poincy bunun bedelini ödeyecek, ama şimdi hemen Saint-Martin'e yelken açmamız gerek. İspanyol daha sonra Ana Karaya teslim edilecek. Hemen gidiyoruz, Amiral Yardımcısı!";
			link.l1 = "Benim gemimle adadan ayrılman biraz garip görünecek, sence de öyle değil mi?";
			link.l1.go = "noel_72";
		break;
		
		case "noel_72":
			dialog.text = "Bence de öyle değil. Beni ikna etmen gerekmiyor muydu? Tam da bunu yaptın, haha! Evet, Avrupa'ya yelken açmadan önce Şövalye'ye onunla aynı fikirde olduğumu ve Ticaret Şirketi'nin kurulmayacağını söyleyeceğim. Şimdilik, onu bu tatlı yalanın huzurunda bırak... Hadi gidelim!";
			link.l1 = "...";
			link.l1.go = "noel_73";
		break;
		
		case "noel_73":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierToSMartin", 5.0);
		break;
		
		case "noel_74":
			dialog.text = "Yol gösterin, Amiral Yardımcısı. Gece, karanlığının örtüsüyle bizi gizleyecek.";
			link.l1 = "Beni takip et...";
			link.l1.go = "noel_75";
		break;
		
		case "noel_75":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.Patria_Condotier_inMine.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inMine.win_condition.l1.location = "Location_reserve_03";
			pchar.quest.Patria_Condotier_inMine.function = "Patria_CondotierInMine";
		break;
		
		case "noel_76":
			dialog.text = "(fısıldayarak) Gördüm! Gördüm! Sen de gördün mü? Kırmızı ceketliler! Onlar İngiliz askerleri!";
			link.l1 = "Sana söylemiştim - Poincy artık işleri Albay Doily ile yürütüyor.";
			link.l1.go = "noel_77";
		break;
		
		case "noel_77":
			dialog.text = "Sen haklıydın. Yeterince gördüm. Şimdi fark edilmeden buradan olabildiğince çabuk çıkalım!";
			link.l1 = "Kabul...";
			link.l1.go = "noel_78";
		break;
		
		case "noel_78":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload2_back", "Patria_CondotierToBeach", -1);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "noel_79":
			dialog.text = "Sevgili Şövalyemizin 'ticari girişimlerinin' bizi ne hale getirdiğini görüyor musun! İngilizler Fransız adasında ev sahibi gibi davranıyor! Bu tam bir rezalet!";
			link.l1 = "Buradan hemen gitmeliyiz, yoksa biri kesinlikle buraya gelir. Tanınmayı göze alamayız.";
			link.l1.go = "noel_80";
		break;
		
		case "noel_80":
			dialog.text = "Amiral Yardımcısı, Saint-Martin'e yolculuğumuz boyunca hep düşündüm ve bir karara vardım: Peter Stuyvesant ile bir görüşme ayarlayabilir misiniz?";
			link.l1 = "Stuyvesant'la mı? Ama neden?";
			link.l1.go = "noel_81";
		break;
		
		case "noel_81":
			dialog.text = "Eski bir iş ortağı, Chevalier'lerin işin içinde olduğuna dair ciddi ipuçları ve sağlam kanıtlar bulmuş olabilir. Eminim Stuyvesant, Poincy'den hiç memnun değil ve özellikle son yaşananlardan sonra intikam almak isteyecektir...";
			link.l1 = "Bence de öyle, Baron. Ben şahsen Stuyvesant'ın sarayına gitmeye cesaret edemem. Onlara yaptıklarımdan sonra bu benim için fazla riskli...";
			link.l1.go = "noel_82";
		break;
		
		case "noel_82":
			dialog.text = "I've already thought about it. We'll go to Curaçao, disembark in a bay far from the city, and send our captive Spaniard from the mine with a letter to Stuyvesant. I won't mention you there; instead, I'll inform him that I'm conducting an investigation against Poincy or something of the sort. I think the Dutchman will come to the rendezvous.";
			link.l1 = "Hmm. I don't think this is a good idea. Stuyvesant is no fool; he takes what he can, he might even try to imprison you and demand a huge ransom. But if we make him believe that all that happened was because of Poincy, he might side with us. Well, if you are so determined, let's give it a try.";
			link.l1.go = "noel_83";
		break;
		
		case "noel_83":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			pchar.quest.Patria_CondotierCuracao.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCuracao.win_condition.l1.location = "shore22";
			pchar.quest.Patria_CondotierCuracao.function = "Patria_CondotierOnCuracao";
			AddQuestRecord("Patria", "81");
		break;
		
		case "noel_84":
			dialog.text = "Monsieur de Maure, lütfen aptallığımı bağışlayın. Stuyvesant konusunda haklıydınız. Sadece daha büyük bir düzenbazın de Poincy'ye meydan okuyabileceğini tahmin etmeliydim!";
			link.l1 = "Hah! Bir milyon... Poincy bir milyon istedi, Stuyvesant bir milyon istiyor... Sanki aynı şeyi tekrar tekrar yaşıyoruz...";
			link.l1.go = "noel_85";
		break;
		
		case "noel_85":
			dialog.text = "Ne diyorsunuz, Koramiral?";
			link.l1 = "Karayipler'e vardığımda, Poincy kardeşim için benden bir milyon fidye istedi.";
			link.l1.go = "noel_86";
		break;
		
		case "noel_86":
			dialog.text = "Ve o kadarını ödedin mi?";
			link.l1 = "Hak ettim ve ödedim. Tabii ki bir ayda değil. Doğrusunu söylemek gerekirse, o zamanlar tam bir karaciydim. Yine de Chevalier, Michel'i bırakmadı.";
			link.l1.go = "noel_87";
		break;
		
		case "noel_87":
			dialog.text = "Ve sonra Poincy için çalışmaya mı girdin? Gerçekten seni anlamıyorum.";
			link.l1 = "Fransa'ya ve sevdiklerime hizmet etmek için askere yazıldım, kral dışında kimsenin önünde eğilmem.";
			link.l1.go = "noel_88";
		break;
		
		case "noel_88":
			dialog.text = "Affedersiniz, Mösyö de Maure. Elbette, siz Fransa'ya ve Kral'a hizmet ediyorsunuz! Poincy her şeyin hesabını verecek! Size yaşattığı tüm acılar dahil.";
			link.l1 = "Pekala, Baron, ayırabileceğim bir milyon bulacağım. Gemine çık... Bu sorunu çözeceğim.";
			link.l1.go = "noel_89";
		break;
		
		case "noel_89":
			DialogExit();
			//chrDisableReloadToLocation = false; //17-add
			LAi_LocationFightDisable(&Locations[FindLocation("shore22")], false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10.0);
			pchar.questTemp.Patria = "epizode_12_stivesant";
			AddQuestRecord("Patria", "83");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Patria_CondotierStivesantTimeOver", 0, 0, 30, false); // таймер на месяц
		break;
		
		case "noel_90":
			dialog.text = "Benimle görüşmek istemişsiniz, Amiral Yardımcısı?";
			link.l1 = "Evet. Stuyvesant ile bir görüşmem oldu. İşte defteri.";
			link.l1.go = "noel_91";
		break;
		
		case "noel_91":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "İnanamıyorum! Hmm, bakalım... (okuyor)";
			link.l1 = "...";
			link.l1.go = "noel_92";
		break;
		
		case "noel_92":
			LAi_Fade("", "");
			dialog.text = "İşte bu! Sevgili Şövalyemiz mahvoldu. Bütün bu hesaplar Maliye Bakanı'nın önüne çıkınca... Ona ne olacağını hayal bile edemiyorum. Cartagena'dan o İspanyol'u aramamıza bile gerek kalmayacak. Monsieur de Maure, gerçekten bu kitap için bir milyon mu ödediniz?";
			link.l1 = "Yaptım. Başka bir şey deneseydim, Fransa iç savaş yüzünden Karayipler'deki kolonilerini kaybedebilirdi. Kazanabilirdim belki, ama kendi halkımla savaşan ne biçim amiral olurdum.";
			link.l1.go = "noel_93";
		break;
		
		case "noel_93":
			dialog.text = "Adınızın hakkını gerçekten veriyorsunuz. Size yemin ederim Amiral Yardımcısı, onu geri alacaksınız. Eminim ki Poincy'nin sandıklarında ve tefecilerinde yüklü bir miktar para bulacağız. Sadece Avrupa'dan bir görevle döneceğim altı ay boyunca beklemenizi istiyorum.";
			link.l1 = "Ve iyi eğitilmiş, silahlı bir alay asker getirmeyi de unutma. Bir de 'Eclatant' gibi bir gemi. Ayrıca, 'Eclatant'ın kaptanının zamanı geldiğinde bizim tarafımızda olacağına inanıyorum.";
			link.l1.go = "noel_94";
		break;
		
		case "noel_94":
			dialog.text = "Don't doubt it, he is also an honourable man. I have realised that moral values play a major role in making your own decisions. You did a great job in trusting me and exposing this state criminal. Now take me to Capsterville, where I will report to Poincy about the success of your mission – you managed to convince me, and I will abandon the idea of creating the trading company. Perhaps Poincy will even reward you for this – accept the reward with a clear conscience and do not worry about anything, you of all people deserve it. You will not be dragged into this, and your name will not be stained by the misdeeds of your superior; in fact, I will say all the best things about you when I meet with the king. Baron Forget is a man of honour and a man of his word.";
			link.l1 = "Memnun oldum, Baron. Hadi yola çıkalım!";
			link.l1.go = "noel_95";
		break;
		
		case "noel_95":
			DialogExit();
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			Island_SetReloadEnableGlobal("Curacao", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.Patria = "epizode_12_baronwin";
			AddQuestRecord("Patria", "85");
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_CondotierBaron_win.function = "Patria_CondotierBaronWin";
		break;
		
		case "noel_96":
			dialog.text = "Yani, Koramiral, sonunda vardık. Göreviniz sona erdi, şimdi sıra bende. Kendi işlerinize bakın, Fransa'nın çıkarlarını eskisi gibi savunun. Yaklaşık altı ay sonra bu rezil hikaye sona erecek. Size ihtiyaç duyduğumda bir ulak gönderirim. Elveda, Mösyö de Maure, burada onurlu bir adamla tanışmak benim için büyük bir şanstı! Bakan ve Kral sizden haberdar olacak, buna söz veriyorum. Ve yalnızca en iyisini duyacaklar.";
			link.l1 = "Teşekkürler, Baron. İyi yolculuklar!";
			link.l1.go = "noel_97";
		break;
		
		case "noel_97":
			DialogExit();
			AddQuestRecord("Patria", "86");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		case "noel_98":
			dialog.text = "Sizi görmek güzel, Koramiral. Söz verdiğim gibi yine buradayım. Ve yanımda Maliye Bakanı'nın Birinci Yardımcısı Baron Olivier Bourdin var.";
			link.l1 = "Chevalier de Poincy nerede?";
			link.l1.go = "noel_99";
		break;
		
		case "noel_99":
			dialog.text = "Olması gerektiği yerde, hapiste. Tutuklandı ve soruşturma ile yargılama için Fransa'ya götürülecek. Mevkiini düşünürsek, idamdan kesinlikle kurtulacaktır ama büyük bir para cezası, rütbe düşürülmesi ve muhtemelen hapis cezasından kaçamayacak.";
			link.l1 = "Tutuklama sakin geçti mi?";
			link.l1.go = "noel_100";
		break;
		
		case "noel_100":
			dialog.text = "Pek sayılmaz. Şövalyenin burada, konakta, ona bağlı bir grup sadık askeri vardı. Ama biz böyle bir durumun yaşanabileceğini önceden öngörmüştük.";
			link.l1 = "O halde, sizi tebrik ederim Baron! Belki artık Fransız Ticaret Şirketi'yle ilgilenirsiniz?";
			link.l1.go = "noel_101";
		break;
		
		case "noel_101":
			dialog.text = "Ben mi? Evet. Ekselansları Monsieur Bourdin, Chevalier de Poincy ile birlikte Fransa'ya dönecek. Ve siz, Amiral Yardımcısı, sizin için de bazı değişiklikler olacak. Artık yeni bir göreviniz var. Ekselansları size daha fazlasını anlatacak.";
			link.l1 = "...";
			link.l1.go = "noel_102";
		break;
		
		case "noel_102":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Finansist");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_103":
			dialog.text = "Monsieur de Maure! Bir dakika bekleyin!";
			link.l1 = "Evet, Baron. Dinliyorum.";
			link.l1.go = "noel_104";
		break;
		
		case "noel_104":
			dialog.text = "Stuyvesant'a ödediğin milyon konusunda... Bakanlığa bundan bahsetmedim, böylece... bazı sorulardan kaçınmak istedim, mesela bir Fransız subayının bu kadar parayı nasıl elde ettiği gibi. Bu senin için zararlı olabilirdi, çünkü muhtemelen senden Kral'ın hazinesine kendi paranla katkıda bulunmanı isterlerdi.";
			link.l1 = "Anladım, teşekkür ederim.";
			link.l1.go = "noel_105";
		break;
		
		case "noel_105":
			dialog.text = "Poincy'nin Casterville'de bulunan tüm parası Baron Bourdin tarafından el konuldu. Ama görünen o ki, Poincy'nin İngiliz tefecilerin onun için sakladığı gizli bir parası daha varmış. Yatırımların geri verilmesi konusunda onunla konuşacağım, sonra da seni telafi etmenin bir yolunu bulacağım.";
			link.l1 = "Korkarım İngiliz tefecilerinin elinden bir şey almak senin için hiç kolay olmayacak.";
			link.l1.go = "noel_106";
		break;
		
		case "noel_106":
			dialog.text = "Katılıyorum. Ama üzerinde çalışacağız ve seni sonuçlardan haberdar edeceğim.";
			link.l1 = "Nasıl istersen.";
			link.l1.go = "noel_107";
		break;
		
		case "noel_107":
			dialog.text = "Amiral yardımcısı, pek iyi görünmüyorsunuz, yoksa bana mı öyle geliyor? Sömürgelerdeki en yüksek mevkiye yeni atandınız!";
			link.l1 = "Hayır, hayır, hiç de öyle değil... Sadece her şey o kadar beklenmedik oldu ki, biraz kafam karıştı.";
			link.l1.go = "noel_108";
		break;
		
		case "noel_108":
			dialog.text = "Endişelenme. Yeni konumuna alışacaksın. Ayrıca, yarım yıl boyunca Saint-Martin valisi olarak oldukça başarılıydın, bu yüzden bu senin için yeni bir şey olmayacak.";
			link.l1 = "Ah, eminim alışırım. Karayipler'de geçirdiğim zaman boyunca daha kötü durumlarda da bulundum. Sanırım bunun da üstesinden gelirim.";
			link.l1.go = "noel_109";
		break;
		
		case "noel_109":
			// belamour legendary edition -->
			dialog.text = "Pekâlâ, tamam. Ayrıca, senin için bir sürprizim daha var. Eminim hoşuna gidecek. Ama önce, konuta dönmeni rica ediyorum. Orada bizi bekleyen biri olduğuna inanıyorum.";
			link.l1 = "Beni meraklandırdınız, Bay Forget. Peki, hadi geri dönelim.";
			link.l1.go = "noel_110";
		break;
		
		case "noel_110":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "ToEcliatonAward", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "noel_111":
			dialog.text = "Endişelenmeyin, Marki. Gerçek bir kaptan önce gemisine bakmalı, değil mi? Charles, savaş gemisi 'Eclatant'ın kaptanı Marki Hubert Dassier'i hatırlıyor musun?";
			link.l1 = "Elbette hatırlıyorum! O olmasaydı, bugün hayatta olmazdım. Donanma subayları arasındaki en sağlam dostluklar, omuz omuza verilen savaşlarda kurulur. Ve Mösyö Dassier, inanılmaz derecede tecrübeli bir kaptan olduğunu kanıtladı.";
			link.l1.go = "noel_112";
		break;
		
		case "noel_112":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_113":
			dialog.text = "Amiral Yardımcısı, size aşağıdaki hususu bildirmekten onur duyarım. Takımadadaki Fransız kolonilerinin Vali Vekili olarak atanmanıza ek olarak, amiral geminiz meselesini de gündeme getirdim.";
			link.l1 = "Amiral gemisi?";
			link.l1.go = "noel_114";
		break;
		
		case "noel_114":
			dialog.text = "Aynen öyle. Bildiğim kadarıyla, Fransa'nın hizmetine girdiğinizde size ağır korvet 'Gryffondor' tahsis edildi. Hiç şüphesiz harika bir gemi, ama yine de bir subay için uygun, bir amiral yardımcısı ve artık bir genel vali için değil. Burada Fransa'nın yüzüsünüz. Ve amiral geminiz de buna yakışır olmalı. Bu yüzden, Karayipler'de ilk savaşlarını veren geminin filonuza katılmasına karar verdik...";
			link.l1 = "Monsieur Forget, ne demek istiyorsunuz...";
			link.l1.go = "noel_115";
		break;
		
		case "noel_115":
			dialog.text = "Bundan böyle, Fransız Donanması'nın gururu, 66 toplu savaş gemisi 'Éclatant' emrinizde! Bu karar Kral tarafından onaylandı!";
			link.l1 = "Ama Baron, ben sadece alamam...";
			link.l1.go = "noel_116";
		break;
		
		case "noel_116":
			dialog.text = "Yapabilirsin, Charles. Bu konu tartışmaya açık değil. Fransa'da, 'Eclatant' özellikle senin için geliştirildi, çünkü anlaşıldı ki Karayipler'de Avrupa'daki gibi büyük deniz savaşları yok ve bu yüzden tek tek gemilere olan ihtiyaçlar daha yüksek. Burada her şeyi geminin özellikleri ve kaptanının tecrübesi belirler. 'Eclatant'ın gövdesi güçlendirildi, taşıma kapasitesi ve mürettebatı artırıldı, yelken donanımı rüzgara daha yakın seyredebilmesi için biraz değiştirildi ve tüm toplar tamamen yenilenerek elimizdeki en güçlü silahlar olan kırk iki kalibrelik toplarla değiştirildi.";
			link.l1 = "Evet, şimdi bu gemi gerçekten denizlerin efendisi... Ama Monsieur Forget, bu geminin kaptanı Marquis Hubert Dassier. Ondan alamam...";
			link.l1.go = "noel_117";
		break;
		
		case "noel_117":
			dialog.text = "Henüz size söylemedim ama Marki'nin bizzat sizin komutanlığınız altında hizmet etmeye istekli olduğunu belirttiğini biliyor muydunuz... Monsieur Dassier?";
			link.l1 = "...";
			link.l1.go = "noel_118";
		break;
		
		case "noel_118":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_119":
			dialog.text = "Evet, Bay Dassier, sanırım sizi daha fazla alıkoymayacağız.";
			link.l1 = "...";
			link.l1.go = "noel_120";
		break;
		
		case "noel_120":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			sld = characterFromId("Ecliaton_Cap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "EcliatonAwardNoelTalk", -1);
		break;
		
		case "noel_121":
			dialog.text = "Aramızda kalsın Charles, sana Markiyi yanında tutmanı şiddetle tavsiye ederim. Emin ol, onun kadar tecrübeli bir kaptan bulamazsın.";
			link.l1 = "Bana inanın Baron, İspanya ve Hollanda'ya karşı verilen savaşlarda buna bizzat şahit olma onuruna eriştim. Monsieur Dassier gerçekten de mükemmel bir muharebe subayıdır, ayrıca dostumdur.";
			link.l1.go = "noel_122";
		break;
		
		case "noel_122":
			dialog.text = "Şimdi müsaadenizle ayrılmam gerek, Ekselansları, Genel Vali! İşler beklemez: bir ticaret şirketi kurmanın çalışmaları daha ilk günden başlar. Yakında görüşmek üzere!";
			link.l1 = "İyi şanslar, Mösyö Forget. Ticaret girişimlerinizde de bol şans dilerim!";
			link.l1.go = "noel_123";
		break;
		
		case "noel_123":
			DialogExit();
			// ставим Эклятон после апгрейда в Европе
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_24";
			sld.DeckDialogNode = "ecliaton_cap_24";
			sld.Ship.Type = GenerateShipExt(SHIP_ECLIATON, true, sld);
			SetBaseShipData(sld);
			sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS42;
			UpgradeShipFull(sld);
			/* UpgradeShipParameter(sld, "SpeedRate");
			UpgradeShipParameter(sld, "TurnRate");
			UpgradeShipParameter(sld, "WindAgainstSpeed");
			UpgradeShipParameter(sld, "HP");
			UpgradeShipParameter(sld, "MaxCrew");
			sld.ship.HP = 11880; */
			sld.Ship.name = "Ecliaton";
			SetCrewQuantityFull(sld);
			AddCrewMorale(sld, 100);
			ChangeCrewExp(sld, "Sailors", 100);
			ChangeCrewExp(sld, "Cannoners", 100);
			ChangeCrewExp(sld, "Soldiers", 100);
			SetCharacterGoods(sld, GOOD_BALLS, 6000);
			SetCharacterGoods(sld, GOOD_GRAPES, 2000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 2000);
			SetCharacterGoods(sld, GOOD_BOMBS, 5000);
			SetCharacterGoods(sld, GOOD_FOOD, 4000);
			SetCharacterGoods(sld, GOOD_POWDER, 12000);
			SetCharacterGoods(sld, GOOD_WEAPON, 900);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(sld, GOOD_RUM, 200);
			SetCharacterGoods(sld, GOOD_PLANKS, 100);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 100);
			Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
			Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
			Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
			Group_SetTaskNone("Ecliaton_group");
			Group_LockTask("Ecliaton_group");
			
			bDisableFastReload = false;//открыть переход
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Patria", "90");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.GenGovernor = "true"; // Шарль генерал-губернатор
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			DoQuestReloadToLocation("Charles_Town", "reload", "reload3", "OpenTheDoors");
		break;
		// <-- legendary edition
		
		case "noel_final":
			dialog.text = "Size en içten şükranlarımı sunmama izin verin, Amiral Yardımcısı! O lanet korsanların elinden beni kurtararak hayatımı kurtardınız. Size ve Philippe de Poincy'ye teşekkür ederim. İtiraf etmeliyim ki, onun hakkında tamamen yanılmışım ve bunun için sizden özür dilerim. Siz ve Şövalye haklıydınız: Fransız Ticaret Şirketi burada çok zorluk yaşayacak ve görünüşe göre burada sadece para kaybedeceğiz. Ancak Poincy gibi tecrübeli insanlar ve sizin gibi cesur askerler, burada her adada yaşayan bu kurtlara karşı durabilir. Saraya gitmem gerekiyor, ardından da en kısa sürede Avrupa'ya dönüp bu kabusu unutacağım.";
			link.l1 = "Her şeyin yolunda gitmesine sevindim, Baron. Hoşça kal!";
			link.l1.go = "noel_final_1";
		break;
		
		case "noel_final_1":
			DialogExit();
			AddQuestRecord("Patria", "76");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		// капитан Эклятона
		case "ecliaton_cap":
			dialog.text = TimeGreeting()+", monsieur. Sizi 'Eclatant'ın güvertesine getiren nedir?";
			link.l1 = TimeGreeting()+", monsieur. Kendimi tanıtmama izin verin - Ben Kaptan Charles de Maure. Fransız kolonilerinin Genel Valisi Chevalier de Poincy'nin emriyle, Takımadalar'dan geliyorum. Geminizi filoma katmam ve komutam altına almam emredildi. İşte mektup...";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) link.l1.go = "ecliaton_cap_1";
			else link.l1.go = "ecliaton_cap_no";
		break;
		
		case "ecliaton_cap_no":
			dialog.text = "Bir yanlışlık olmalı, monsieur. Şu anda Fransız donanmasının bir hat gemisindesiniz ve ben yalnızca Kraliyet Donanması'nda görev yapanlardan emir alırım. Sizin ise ne bir rütbeniz var, ne de o filoya ait görünüyorsunuz. Belki de gemimizi başka bir gemiyle karıştırdınız.";
			link.l1 = "Ama...";
			link.l1.go = "ecliaton_cap_no_1";
		break;
		
		case "ecliaton_cap_no_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_no_2";
		break;
		
		case "ecliaton_cap_no_2":
			if(IsUniformEquip())
			{
				dialog.text = "Bu üniformayla seni tanıyamadım bile, Kaptan. Peki, hadi bakalım, mektubunu ver de içeriğine bir göz atayım.";
				link.l1 = "Al işte.";
				link.l1.go = "ecliaton_cap_1";
			}
			else
			{
				dialog.text = "Her şeyi zaten konuştuk, monsieur...";
				link.l1 = "Hmm...";
				link.l1.go = "ecliaton_cap_no_1";
			}
		break;
		
		case "ecliaton_cap_1":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Pekâlâ, bakalım... (okuyor) İlginç. Yani, gemim ve ben artık sizin emrinizdeyiz, Kaptan de Maure?";
			link.l1 = "Bu, Genel Vali'nin emridir.";
			link.l1.go = "ecliaton_cap_2";
		break;
		
		case "ecliaton_cap_2":
			dialog.text = "Evet, evet, emirler sorgulanmaz. Pekala. Kendimi tanıtayım: Ben Marquis Hubert Dassier, Fransız Donanması'na ait 66 toplu hat gemisi 'Eclatant'ın kaptanıyım, bu eğitimli mürettebatla birlikte, ve onurum üzerine yemin ederim ki, bu gemi Fransa'nın sahip olduğu en iyi gemilerden biridir.";
			link.l1 = "Bunu duymak güzel, çünkü Genel Vali tarafından bize verilen görev iyi bir seyir ve topçuluk bilgisi gerektiriyor.";
			link.l1.go = "ecliaton_cap_3";
		break;
		
		case "ecliaton_cap_3":
			dialog.text = "Bu yaklaşan operasyonun ayrıntılarını bana anlatacak mısın?";
			link.l1 = "Elbette. Buradan yaklaşık bir haftalık mesafede, güneydoğuda yer alan İspanyol adası Trinidad'a gideceğiz. San Jose kolonisinin koruyucu kalesine ani bir saldırı düzenleyip orayı yerle bir edeceğiz. Ardından, yakın zamanda Fransız yerleşimi Saint-Pierre'e yapılan saldırı nedeniyle İspanyollarla tazminatımız hakkında pazarlık yapacağız.";
			link.l1.go = "ecliaton_cap_4";
		break;
		
		case "ecliaton_cap_4":
			dialog.text = "Anladım. Ne zaman yola çıkıyoruz?";
			link.l1 = "Mümkün olan en kısa sürede. Bu işi bir ay içinde bitirmemiz gerekiyor, yani fazlasıyla zamanımız var.";
			if (GetCompanionQuantity(pchar) > 4) link.l1.go = "ecliaton_cap_5_1";
			else link.l1.go = "ecliaton_cap_5";
		break;
		
		case "ecliaton_cap_5":
			dialog.text = "Pekala, Kaptan de Maure. Emrinizle yola çıkacağız.";
			link.l1 = "";
			link.l1.go = "ecliaton_cap_6";
		break;
		
		case "ecliaton_cap_6":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_AddEcliaton();
		break;
		
		case "ecliaton_cap_wait":
			dialog.text = "Bir emriniz ya da belki bir sorunuz var mı, Kaptan de Maure?";
			link.l1 = "Henüz değil...";
			link.l1.go = "ecliaton_cap_wait_1";
		break;
		
		case "ecliaton_cap_wait_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
		break;
		
		case "ecliaton_cap_5_1":
			dialog.text = "Ama Kaptan de Maure, önce filonuzu küçültmeniz gerekiyor - gemim size katılamaz, yoksa filo fazla büyük olur.";
			link.l1 = "Hımm. Haklısın. Limanda bir gemi bırakacağım.";
			link.l1.go = "ecliaton_cap_5_2";
		break;
		
		case "ecliaton_cap_5_2":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_5_3";
		break;
		
		case "ecliaton_cap_5_3":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Filo sayınızı hâlâ azaltmadınız mı, monsieur?";
				link.l1 = "Evet, evet, hatırlıyorum, üzerinde çalışıyorum.";
				link.l1.go = "ecliaton_cap_5_2";
			}
			else
			{
				dialog.text = "Yani, 'Éclatant' filonuza katılmaya hazır, monsieur.";
				link.l1 = "O zaman ben gemime gideceğim, sen de yelken açmaya hazırlanmalısın.";
				link.l1.go = "ecliaton_cap_5";
			}
		break;
		
		case "ecliaton_cap_7":
			dialog.text = "Selamlar, Komodor. Önümüzde başka bir savaş daha mı var?";
			link.l1 = "Evet, öyle. Yine güçlerimizi birleştireceğiz. Philipsburg'a saldıracağız. Genel Vali, Saint-Martin'deki Hollandalıları temizlememizi emretti.";
			link.l1.go = "ecliaton_cap_9";
			link.l2 = "Yaparız, Kaptan, ama biraz sonra. Ne zaman olduğunu sana söyleyeceğim. 'Eclatant' her an yelken açmaya hazır olmalı.";
			link.l2.go = "ecliaton_cap_8";
		break;
		
		case "ecliaton_cap_8":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_7";
			npchar.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "ecliaton_cap_9":
			dialog.text = "Her şey açık. Zor bir görev olacak, monseigneur. Duyduğuma göre, Philipsburg kalesinde çok sayıda top var.";
			link.l1 = "Eminim dostum, ama üstesinden geleceğiz. Hazırlan, yakında yola çıkıyoruz.";
			link.l1.go = "ecliaton_cap_10";
		break;
		
		case "ecliaton_cap_10":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_BastionAddEcliaton();
		break;
		
		case "ecliaton_cap_11":
			dialog.text = "Sizi 'Éclatant'ın güvertesinde görmek ne güzel, Amiral Yardımcısı! Emirleriniz nedir?";
			link.l1 = "'Eclatant'ı yolculuğa hazırla. Önce Jamaika kıyılarına yelken açacağız, ardından Albay D'Oyley'in filosuyla birlikte Curaçao'ya saldıracağız.";
			link.l1.go = "ecliaton_cap_13";
			link.l2 = "Emirler olacak, Kaptan, ama sonra. Ne zaman olduğunu sana söyleyeceğim. 'Eclatant' her an denize açılmaya hazır olmalı.";
			link.l2.go = "ecliaton_cap_12";
		break;
		
		case "ecliaton_cap_12":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_11";
			npchar.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "ecliaton_cap_13":
			dialog.text = "'Éclatant' ve mürettebatı hazır, Amiral Yardımcısı!";
			link.l1 = "Mükemmel. O halde hemen yola çıkıyoruz.";
			link.l1.go = "ecliaton_cap_14";
		break;
		
		case "ecliaton_cap_14":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_CuracaoAddEcliaton();
		break;
		
		// belamour legendary edition -->
		case "ecliaton_cap_15":
			dialog.text = "Affedersiniz beyler, gemide emirler vermekle meşgul olduğum için size daha önce katılamadım. Zaten sizi konakta bulamayınca geç kaldığımı düşündüm ve bu yüzden tam gemiye dönmek üzereydim...";
			link.l1 = "...";
			link.l1.go = "ecliaton_cap_16";
		break;
		
		case "ecliaton_cap_16":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_111";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_17":
			dialog.text = "Sizinle yan yana savaşmak benim için bir onurdu, Monsieur de Maure! Sizin kadar yetenekli ve becerikli subaylara nadiren rastladığımı söylemeliyim. Eminim, Trinidad’daki o İspanyol kolonisinin kalesiyle ben bu kadar çabuk baş edemezdim!";
			link.l1 = "Kendinizi küçümsüyorsunuz, Monsieur Dassier. Bunun üstesinden birlikte geldik.";
			link.l1.go = "ecliaton_cap_18";
		break;
		
		case "ecliaton_cap_18":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_113";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_19":
			dialog.text = "That's right. Although I am a marquis, I am still a sailor. For me, the Caribbean archipelago is new, unexplored, and full of adventure. Last time I was here for only a few months, but when I returned to Europe, I found myself missing this place. I would like to serve our Fatherland here. And you are a very talented and experienced captain; you have managed to win my sincere respect and my friendship. I would be honoured to serve under your command, Vice Admiral!";
			link.l1 = "Pekâlâ, yapamam ve dahası! - Sana hayır demek de istemiyorum, Mösyö Dassier!";
			link.l1.go = "ecliaton_cap_20";
		break;
		
		case "ecliaton_cap_20":
			dialog.text = "Artık Eclatant'ın senin amiral gemin olduğunu da biliyorum, bu yüzden komutayı bizzat devralmak istersen seni gayet iyi anlarım. O durumda beni subayın olarak bırakabilir, bana başka bir gemi verebilir ya da görevimden tamamen alabilirsin – Mösyö Forget bana nazikçe söz verdi, o zaman Fransız Batı Hint Şirketi filosunda bana layık bir görev bulacakmış.";
			link.l1 = "Sana temin ederim dostum, iş oraya varmayacak. Tanıdığım en iyi kaptanlardan birisin ve sen yanımda olduğun sürece bizi kimse durduramaz.";
			link.l1.go = "ecliaton_cap_21";
		break;
		
		case "ecliaton_cap_21":
			dialog.text = "Böyle övgü dolu bir değerlendirme için teşekkür ederim. Ve bir şey daha, Koramiral. Şu anda filonuzun büyüklüğünü bilmiyorum, bu yüzden ne olur ne olmaz, sizi Capsterville'deki iskelede Éclatant'ın kaptan köprüsünde bekliyor olacağım. Gemiyi komutanız altına almaya karar verdiğinizde - bana sadece haber verin.";
			link.l1 = "Pekâlâ, Bay Dassier.";
			link.l1.go = "ecliaton_cap_22";
		break;
		
		case "ecliaton_cap_22":
			dialog.text = "O halde izninizi isteyerek ayrılıyorum. Amiral Yardımcısı, Baron...";
			link.l1 = "Yakında görüşürüz, Bay Dassier.";
			link.l1.go = "ecliaton_cap_23";
		break;
		
		case "ecliaton_cap_23":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_119";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	
		case "ecliaton_cap_24":
			dialog.text = "Amiral Yardımcısı, gemimize hoş geldiniz. Éclatant'ı komutanız altına almak ister misiniz?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				
				link.l1 = "Henüz değil, Marki. Emirleri bekleyin.";
				link.l1.go = "ecliaton_cap_24_1";
			}
			else
			{
				link.l1 = "Evet, Marki, sizden filoma katılmanızı rica ediyorum. Bu güzel gemi, Karayipler'de Fransa'nın büyüklüğünün ve gücünün simgesi olacak!";
				link.l1.go = "ecliaton_cap_25";
			}
		break;
		
		case "ecliaton_cap_24_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_24";
			npchar.DeckDialogNode = "ecliaton_cap_24";
		break;
		
		case "ecliaton_cap_25":
			dialog.text = "Size tamamen katılıyorum, Ekselansları!";
			link.l1 = "... Şimdi, gerçekten neler yapabileceğimizi görelim!";
			link.l1.go = "ecliaton_cap_26";
		break;
		
		case "ecliaton_cap_26":
			DialogExit();
			DeleteAttribute(npchar, "ShipHideImmortal");
			SetCharacterRemovable(npchar, true);
			npchar.CompanionEnemyEnable = true; 
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			npchar.DeckDialogNode = "hired";
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.Payment = true;
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			
			// удаление группы Эклятона, иначе клон-призрак
			pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
			pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
		break;
		// <-- legendary edition
		
		// д'Ойли на Антигуа
		case "doily":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE)
			{
				PlaySound("Voice\English\LE\Doily\Edvard_Doily_01.wav");
				dialog.text = "Ah, ne tanıdık ama! Bu, bizzat Kaptan Charles de Maure değil mi?! Duyduğuma göre artık Fransız donanmasında bir görevin varmış. Kimlere, ne diyelim, 'hizmet' ettiğini düşününce bu gerçekten sürpriz...";
				link.l1 = "Greetings, sir. Are you referring to the affair with Isla Tesoro? Oh, but it was not I who wrote the English laws, according to which the island was passed down to the heir of the explorer who discovered it, as per his will. So, I am not to blame for that; I only helped Miss Sharp to claim what was rightfully hers.";
				link.l1.go = "doily_1";
			}
			else
			{
				dialog.text = TimeGreeting()+", Kaptan. Sanırım Fransız donanmasının temsilcisi Antigua'ya önemli bir amaçla geldi, değil mi?";
				link.l1 = "Evet, efendim. Beni buraya Fransız kolonilerinin Genel Valisi Philippe de Poincy gönderdi. Saint Christopher, İspanyol ve Hollanda deniz filoları tarafından kuşatıldı. Şövalye, sizden ve Sir Jonathan Fox'tan da yardım istiyor. İşte size mektubu, Albay.";
				link.l1.go = "doily_3";
			}
		break;
		
		case "doily_1":
			dialog.text = "Merak ediyorum Kaptan, bundan ne kadar para kazandınız? Sanırım epeyce, çünkü o haydut Loxley’in hizmetlerini karşılayabildiniz; hiç de ucuz değildir. Eminim korsan baronları da adayı ellerinde tutmanız için size düzenli olarak pay ödüyorlar. İkimiz de çok iyi biliyoruz ki Helen Sharp sadece bir maske.";
			link.l1 = "Albay, ikimiz de biliyoruz ki korsan baronları çoğunlukla İngiltere'nin çıkarları doğrultusunda hareket ediyorlar, tabii ki resmî olarak değil... Onlar olmasaydı, bölgede İspanyol egemenliğine karşı koymak oldukça zor olurdu, siz de katılmıyor musunuz? Yani, siyasetçilerin gözünden bakarsak, Kıyı Kardeşliği'nin adayı kendi ellerinde tutması, belki de Isla Tesoro'nun bir İngiliz deniz üssüne dönüşmesinden daha kârlıydı...";
			link.l1.go = "doily_2";
		break;
		
		case "doily_2":
			dialog.text = "Bu tartışılabilir bir gerçek, Kaptan, ama... her neyse. Antigua'ya önemli bir amaçla geldiğinizi varsayıyorum? Belki de bunun, iki eski müttefik - Fransa ve Hollanda - arasındaki ilişkilerin ciddi şekilde kötüleşmesiyle bir ilgisi vardır?";
			link.l1 = "Kesinlikle doğru. Fransız kolonilerinin genel valisi Philippe de Poincy tarafından gönderildim. Saint Christopher, İspanyol ve Hollanda donanmaları tarafından kuşatıldı. Şövalye yardımınızı istiyor. İşte size yazdığı mektup, Albay.";
			link.l1.go = "doily_3";
		break;
		
		case "doily_3":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Bir bakayım... (okuyor)";
			link.l1 = "";
			link.l1.go = "doily_3_1";
		break;
		
		case "doily_3_1":
			LAi_Fade("", "");
			dialog.text = "Hmm... very intriguing! Captain, your commander certainly knows how to pique my interest; it's not unusual for people to call him a cunning fox. We should have done this long ago, instead of trying to befriend the Dutch. We know very well what the Dutch Company and their Director stand for. Well then, I think in this situation we really shouldn't refuse to help the besieged Casterville, and we have more than enough troops to do so.\nWhat are the numbers and types of ships in their squadrons, Captain?";
			link.l1 = "Altı gemi saydım: biri seksen toplu üçüncü sınıf bir hat gemisi, diğer beşi ise dördüncü sınıf. Ayrıca fırkateynleri ve kalyonları da olabilir.";
			link.l1.go = "doily_4";
		break;
		
		case "doily_4":
			dialog.text = "Hmm... Birinci sınıf yüz toplu bir gemi, iki dördüncü sınıf gemi ve ağır bir fırkateynden oluşan filomuzu onlarınkine karşı konuşlandırabiliriz.";
			if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
			{
				link.l1 = "Efendim, ayrıca Guadeloupe kıyılarından Saint-Christopher'ın savunmasına yardım etmek üzere yola çıkan 66 toplu bir savaş gemimiz, 'Eclatant', var.";
				link.l1.go = "doily_5";
			}
			else
			{
				link.l1 = "Birinci sınıf bir gemi yaklaşan savaşta büyük fayda sağlayacak.";
				link.l1.go = "doily_5_1";
			}
		break;
		
		case "doily_5":
			dialog.text = "Mükemmel. O halde, düşmanlarımızın menzilinin çok ötesindeyiz. Zafer bizim olacak.";
			link.l1 = "Ve kendi gemimi de unutmayalım, efendim. Böyle bir savaşı kaçıracak değilim, bunu aklınızdan bile geçirmeyin.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_5_1":
			dialog.text = "Doğru. Casterville kalesinin yardımıyla zafer bizim olacak.";
			link.l1 = "Ve kendi gemimi de unutmayalım, efendim. Böyle bir savaşı kaçıracak değilim, aklınızdan bile geçirmeyin.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_6":
			dialog.text = "Elbette, Mösyö de Maure. Durum ne olursa olsun, denizcilikteki yeteneklerinizin hikâyeleri tüm takımadalarda dilden dile dolaşıyor. Amiral geminiz filoya öncülük edecek.";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Filoumdaki diğer gemileri bekleteceğim, sonra sana döneceğim ve birlikte kuşatılmış olanlara yardıma koşacağız.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Kısa süre içinde gemimi hazırlayacağım ve kuşatma altındakilere yardıma koşacağız.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_7_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_7_2";
		break;
		
		case "doily_7_2":
			dialog.text = "Peki,   hazır mısın yola çıkmaya?";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Bir dakika bekleyin, efendim.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Evet, efendim.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_8":
			dialog.text = "O halde başlayalım, Tanrı yardımcımız olsun!";
			link.l1 = "...";
			link.l1.go = "doily_9";
		break;
		
		case "doily_9":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Patria", "42");
			Patria_SiegeAddEngSquadron();
		break;
		
		case "doily_10":
			dialog.text = "Başka bir sorunuz var mı, efendim?";
			link.l1 = "Hayır, Albay...";
			link.l1.go = "doily_11";
		break;
		
		case "doily_11":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			npchar.DeckDialogNode = "doily_10";
		break;
		
		case "doily_12":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_02.wav");
			dialog.text = "Stuyvesant için mektubu alın, bayım. Kim olduğumu bilmiyorsanız, kendimi tanıtayım: Albay Edward Doily, Port Royal valisi ve bu seferin komutanı!\nAçık konuşmak gerekirse, Willemstad olarak bilinen haydut sığınağını yerle bir etme isteğim çok büyük. Karayipler'deki en alçak, iki yüzlü ve aşağılık örgüt olan Hollanda Batı Hint Ticaret Şirketi, takımadadaki tüm ticaretin yalnızca kendi hakları olduğuna inanıyor ve İngiliz tüccarlarının gemilerini ele geçirmek ve batırmak için Jacob van Berg gibi adamları ve diğer korsanları tutuyorlar...";
			link.l1 = "...";
			link.l1.go = "doily_13";
		break;
		
		case "doily_13":
			dialog.text = "Bu rezil davranışlara son vermek için buradayım ve senin şansına, diplomatik bir çözüm öneriyorum. Şimdilik... Ama bu iğrenç örgütün yöneticisi görüşmeler için buraya gelmezse, işini yerle bir edeceğim. Şehre saldırdıktan sonra geriye sadece küller bırakacağım ve bulduğumuz barutu kalenizin mahzenine koyup havaya uçuracağız. Aynı akıbet plantasyonlarınızı da bekliyor olacak ve Stuyvesant'ın kendisi amiral gemimin serenine asılacak...";
			link.l1 = "...";
			link.l1.go = "doily_14";
		break;
		
		case "doily_14":
			dialog.text = "Sömürgeni yeniden inşa etmek için bir yıldan fazlasına ihtiyacın olacak, o zaman da entrikalarına ve planlarına vakit bulamayacaksın. Şu anda söylediklerimin hepsini 'Mynheer Direktör'üne aynen ilet, bunların şaka ya da boş tehdit olmadığını sakın unutma. Artık sabrım kalmadı, bunu tam olarak anlamalısın. Anladın mı, Subay?!";
			link.l1 = "Her şey tamamen açık, Albay.";
			link.l1.go = "doily_15";
		break;
		
		case "doily_15":
			dialog.text = "Harika. O zaman git. Sana bunu düşünmen için tam bir gün veriyorum. Eğer yirmi dört saat sonra Peter Stuyvesant burada, senin şu anda durduğun yerde olmazsa, bunun suçunu yalnızca kendinde arasın.";
			link.l1 = "...";
			link.l1.go = "doily_16";
		break;
		
		case "doily_16":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_17";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "doily_17":
			dialog.text = "Bence o sefil köpek Stuyvesant buraya gelecek. Gelmezse de, suçlu yalnızca kendisi olur!";
			link.l1 = "...";
			link.l1.go = "doily_17_1";
		break;
		
		case "doily_17_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_17";
			AddQuestRecord("Patria", "63");
			Patria_CuracaoParlamenterGo();
		break;
		
		case "doily_18": // д'Ойли на берегу
			dialog.text = "You've done a good job with the fort, monsieur de Maure. Now we will approach the city gates by land. I will take the cannons from here; the path is shorter and easier, and you will disembark your company of marines at Santa Maria Cape and advance towards Willemstad. If you encounter any enemies on the way, you know what to do. No one can be left behind us.";
			link.l1 = "Elbette, Albay. Sizi kapıda karşılayacağım!";
			link.l1.go = "doily_19";
		break;
		
		case "doily_19":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "61");
			npchar.dialog.currentnode = "doily_10";
			Patria_CuracaoGotoMarch();
		break;
		
		case "doily_20":
			dialog.text = "Pekala, demek ki görevimiz oldukça başarılı bir şekilde sona erdi. Tebrikler, Kaptan! Affedersiniz - Amiral Yardımcısı! Haydi gemilere dönelim. Adamlarıma nöbet tutmalarını söyleyeceğim - o aptal Stuyvesant geri çekilirken bize saldırmaya cesaret edemeyecektir muhtemelen, ama tedbirli olmakta fayda var.";
			link.l1 = "Hollandalıların yeni imzalanmış bir anlaşmayı bozmaya cesaret edeceklerinden emin değilim.";
			link.l1.go = "doily_21";
		break;
		
		case "doily_21":
			dialog.text = "Sizinle çalışmak büyük bir zevkti, Monsieur de Maure. Sanırım Port-Royal ya da Capsterville'de tekrar karşılaşacağız.";
			link.l1 = "Hiç şüphe yok, Albay. Şimdi adamlarımıza geri çekilmelerini söyleyelim.";
			link.l1.go = "doily_22";
		break;
		
		case "doily_22":
			DialogExit();
			AddQuestRecord("Patria", "64");
			Patria_CuracaoClear();
		break;
		
		case "doily_23":
			dialog.text = "Hollandalılar sonunda, top ateşimiz altındaki o dar patikadan kaleden bize yaklaşamayacaklarını fark etmiş olmalı. Şehirde sıkışıp kalanlar ise, tamamen delirmedilerse, bir çıkış yapmaya cesaret edemezler. Şimdi biraz panik yaratalım: toplarımızla şehri bombalayacağız. Gemimdeki adamlar bunu görecek ve karaya çıkmaya hazırlanıyormuş gibi davranacaklar. Bir iki saat sonra Stuyvesant’ın dizleri çözülecek ve ateşkes elçilerini göndermeye hazır olacak.";
			link.l1 = "Her şey planımıza göre gidiyor, Albay! Hadi yapalım!";
			link.l1.go = "doily_24";
		break;
		
		case "doily_24":
			DialogExit();
			Patria_CuracaoTownBombing();
		break;
		
		// голландский парламентёр под стенами Виллемстада
		case "holoff":
			dialog.text = "Buraya görüşmelere başlamak için geldim. Talepleriniz nedir?";
			link.l1 = "Şirketin Direktörü Peter Stuyvesant ile bir görüşme talep ediyoruz. Özellikle, hem şirketinin hem de kendisinin ihmali yüzünden Willemstad'ın şu anda yok olma tehlikesiyle karşı karşıya olduğunu konuşmak istiyoruz.";
			link.l1.go = "holoff_1";
		break;
		
		case "holoff_1":
			dialog.text = "Pekâlâ, bunu bay Stuyvesant'a ileteceğim ve heyetiniz için şehre güvenli bir giriş yolu ayarlayacağız...";
			link.l1 = "Peki ya güvenli bir çıkış?";
			link.l1.go = "holoff_2";
		break;
		
		case "holoff_2":
			dialog.text = "Anlamadım, efendim?";
			link.l1 = "Dedim ki: bizim için şehirden güvenli bir çıkış ayarlayacak mısınız? Bundan pek emin değilim. Korkarım ki bay Stuyvesant elçilerimizi tutuklamaya karar verebilir. Bu yüzden, bay Stuyvesant'ı müzakereler için buraya davet ediyorum.";
			link.l1.go = "holoff_3";
		break;
		
		case "holoff_3":
			dialog.text = "Ama...";
			link.l1 = "Subay, burada şartları biz belirliyoruz. Filonuz yok edildi, garnizon şehirden izole edildi ve eğer şehre saldırmaya karar verirsek Willemstad'ın savunmasını bir fırkateynin sandalınkini yarıp geçtiği gibi aşarız. Şimdi, bay Stuyvesant'a bir mektup alacaksınız ve onu davetimizle birlikte kendisine ileteceksiniz...";
			link.l1.go = "holoff_4";
		break;
		
		case "holoff_4": // перекидываем pchar на офицера и говорим с д'Ойли
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Curacao_parlamenter_1"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		// офицер-испанец на маяке Тринидада
		case "SanJoseSpanish":
			dialog.text = "Yani, Kaptan, ateşkes elçilerini çağırdın çünkü şartlarını dikte etmek istiyorsun?";
			link.l1 = "Kesinlikle haklısınız, señor. Trinidad'a geliş sebebimi kısaca açıklamama izin verin – bu, Saint-Pierre'e yaptığınız son saldırıya cevabımızdır. Şehre ciddi zarar verdiniz ve şimdi bunun bedelini ödemek zorundasınız. Tazminat bedeli üç yüz bin peso. Aslında bu, askerlerinizin Martinique'te işlediği alçakça fiilleri düşününce o kadar da fazla değil.";
			link.l1.go = "SanJoseSpanish_1";
		break;
		
		case "SanJoseSpanish_1":
			dialog.text = "Affedersiniz, señor, ama San Jose'nin Saint-Pierre'le ne ilgisi var? Neden bizim kolonimiz bedel ödemek zorunda?";
			link.l1 = "Saldırganlar İspanyol olduğu için, Hollandalı ya da İngiliz değil. O zaman faturayı Don de Mendoza adına Providence'a göndereceksiniz, en içten selamlarımı da ekleyerek. Anladığınız üzere, tazminatı ödemeyi reddederseniz adamlarıma karaya çıkmalarını emredeceğim ve o zaman San Jose çok daha fazlasını kaybeder. Koloninizin valisinin doğru kararı vereceğinden eminim. Cevap vermek için bir gününüz var. Size en iyi dileklerimi sunarım, señores.";
			link.l1.go = "SanJoseSpanish_2";
		break;
		
		case "SanJoseSpanish_2":
			DialogExit();
			npchar.dialog.currentnode = "SanJoseSpanish_3";
			Patria_SanJoseMayakSpanishGo();
		break;
		
		case "SanJoseSpanish_3":
			dialog.text = "";
			link.l1 = "Yani, anladığım kadarıyla vali doğru kararı vermiş, öyle mi?";
			link.l1.go = "SanJoseSpanish_4";
		break;
		
		case "SanJoseSpanish_4":
			AddMoneyToCharacter(pchar, 300000);
			dialog.text = "Üç yüz binini al ve kolonimizden defol.";
			link.l1 = "Mükemmel, señores. Size temin ederim - bu en iyi yoldu. Umarım bu, Don de Mendosa'yı ve diğerlerini kolonilerimize saldırmaktan vazgeçirir. Mesajı Providence'a ve ona şahsen göndermeyi unutmayın. Size iyi dileklerimi sunarım, baylar.";
			link.l1.go = "SanJoseSpanish_5";
		break;
		
		case "SanJoseSpanish_5":
			DialogExit();
			Patria_SanJoseMayakSpanishFin();
		break;
		
		// вестовой на 5 задание
		case "fraofficer":
			dialog.text = "Kaptan Charles de Maure, rapor vermeme izin verin: Şövalye Philippe de Poincy, Baron Noel Forget'in Saint-Martin'e gitmeye hazır olduğunu ve sizi iskelede bekleyeceğini bildirmek ister.";
			link.l1 = "Harika! Teşekkür ederim, monsieur.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			Patria_SanMartinSetBaron();
		break;
		
		case "fraofficer_2":
			dialog.text = "Kaptan Charles de Maure! Genel Vali şu anda sizi çağırıyor. Saint-Christopher kıyılarında güçlü bir düşman filosu ortaya çıktı!";
			link.l1 = "O halde vakit kaybetmeyelim!";
			link.l1.go = "fraofficer_3";
		break;
		
		case "fraofficer_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			Patria_SiegeHovernor();
		break;
		
		// патруль у рудника
		case "engofficer":
			dialog.text = "Sen kimsin? Burada ne yapıyorsun?";
			link.l1 = "Uhh...";
			link.l1.go = "engofficer_1";
		break;
		
		case "engofficer_1":
			dialog.text = "Buraya yabancılar giremez! Siz de kimsiniz, casus musunuz? Sizi komutanın ofisine götüreceğim, orada gereğini yaparlar.";
			link.l1 = "Ama komutanın ofisine gidemeyiz...";
			link.l1.go = "engofficer_2";
		break;
		
		case "engofficer_2":
			dialog.text = "Eğer kendin gitmeyeceksen - o zaman seni zorla sürüklemek zorunda kalacağız! Silahlarını teslim et!";
			link.l1 = "Anlaşma yok...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierBeachFight");
		break;
		
		// бывший управляющий рудника
		case "miner":
			dialog.text = "";
			link.l1 = "Peki, her şey anlaşıldı mı?";
			link.l1.go = "miner_1";
		break;
		
		case "miner_1":
			dialog.text = "Evet, monsieur. Mektup şahsen Mynheer Peter Stuyvesant ya da Mathias Beck'e teslim edilecek.";
			link.l1 = "Eminim Willemstad'dan Cartagena'ya bir gemi bulmakta zorlanmazsınız. Yolculuk ve konaklama için gereken tüm parayı size verdik. Ve gerekirse – altı ay sonra Fransız komisyonuna raporlarınızı onaylayacak mısınız?";
			link.l1.go = "miner_2";
		break;
		
		case "miner_2":
			dialog.text = "Monsieur, sözümde dururum.";
			link.l1 = "Pekala. O halde sana bol şans diliyorum. Bu yol Willemstad'a çıkar, takip et. Buradan çok uzak değil.";
			link.l1.go = "miner_3";
		break;
		
		case "miner_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Patria_CondotierOnCuracaoWait", 15.0);
			AddQuestRecord("Patria", "82");
			ReleasePrisoner(npchar);
		break;
		
		// курьер в Капстервиль
		case "cureer":
			dialog.text = "Amiral Yardımcısı Charles de Maure, değil mi?";
			link.l1 = "Kesinlikle. Kiminle konuşma şerefine nail oldum?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Baron Noel Forget'ten size bir mesajım var. En kısa zamanda Casterville'deki valinin sarayına gelmenizi söyledi.";
			link.l1 = "Oh! Harika bir haber! Teşekkür ederim, hemen yola çıkıyorum!";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			Patria_EuropePrepare();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		break;
		
		case "burden":
			dialog.text = "Selamlar, Amiral Yardımcısı. Baron Forget bana sizinle ilgili hikayeler anlattı. Hem de pek çok hikaye. Sömürgelerde Fransa'nın iyiliği için gösterdiğiniz sadık ve parlak hizmetiniz, ayrıca dolandırıcı de Poincy'nin oyunlarını ortaya çıkarmamıza yardım ettiğiniz için size en içten teşekkürlerimi sunuyorum. Şimdi, Maliye Bakanı ile birlikte onunla bizzat ilgileneceğiz ve siz de eski komutanınızın yerine geçeceksiniz. En azından şimdilik.";
			link.l1 = "Ama...";
			link.l1.go = "burden_1";
		break;
		
		case "burden_1":
			dialog.text = "İtiraz istemiyorum, amiral yardımcısı! Bu karar çoktan alındı ve Kral tarafından onaylandı. Bizzat onun imzaladığı bir emir var elimde; sizi Takımadalar’daki Fransız kolonilerinin fiili Genel Valisi olarak atıyor. Bu görev için sizden daha iyi bir adayımız yok. Savaş konusundaki üstün tecrübeniz, bölgeyi ve buradaki her şeyden sorumlu insanları tanımanız, yetenekleriniz ve becerileriniz bu yüksek ve saygın makamı fazlasıyla hak ediyor. Açık konuşmam gerekirse, bir süre sonra bu göreve 'fiili' kısmı olmadan yeniden atanacağınızı düşünüyorum.";
			link.l1 = "Ama ben Paris'e geri dönmeyi hayal etmiştim...";
			link.l1.go = "burden_2";
		break;
		
		case "burden_2":
			dialog.text = "Fransa'nın sana burada ihtiyacı var! Maliye Bakanı şu anda Avrupa'da bir donanma topluyor ve bizim burada, Takımadalar'daki varlığımız da gözden kaçmayacak. Senin asıl görevin kolonileri güçlendirmek ve tahkim etmek, filomuzun askeri gücünü artırmak olacak; Baron Forget ve Fransız Batı Hint Ticaret Şirketi ise ticaret ve iç gelişime odaklanacak! Ve Fransız donanmasını hazırlamaya senden başka kim yardım edebilir?\nO halde işinin başına geç, Genel Vali! Biliyorum, bütün gün bir odada oturmaktan hoşlanmıyorsun ama bu görev bunu bile gerektirmiyor!";
			link.l1 = "Derhal, Majesteleri! Emirler sorgulanmaz!";
			link.l1.go = "burden_3";
		break;
		
		case "burden_3":
			dialog.text = "Beni doğru anladığına sevindim. Ayrıca senden Chevalier de Poincy'yi ziyaret etmeni rica edeceğim: seninle tanışmakta ısrar etti. Paris'e gitmeden önce ona bu zevki çok görmeyelim, değil mi? Onu hapishanede bulacaksın.";
			link.l1 = "Pekâlâ, Majesteleri...";
			link.l1.go = "burden_4";
		break;
		
		case "burden_4":
			DialogExit();
			DoQuestReloadToLocation("Charles_prison", "goto", "goto19", "Patria_EuropePuancieInPrison");
		break;
		
		// Портной Пуанси Xenon
		case "Tailor":
			dialog.text = "...gecikecek, anlıyor musun? Bu malzemeleri birkaç ay önce sipariş ettim!";
			link.l1 = "...";
			link.l1.go = "Tailor_01";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "Peki ya ilk gemiye ne yüklenecek, ikinciye ne yüklenecek, buna nasıl karar verdiler?! Ben öyle taşradan gelmiş bir terzi değilim - hatta bizzat genel vali, Ekselansları Chevalier de Poincy'den siparişim var!";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_03":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor_02";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_04":
			dialog.text = "Peki, şimdi başka ne yapabilirim ki... Bekleyeceğim. Ama şunu bil: Yerine getirilmeyen emirlerden sorumlu tutulmam!";
			link.l1 = "Selam. Başınız dertte galiba?";
			link.l1.go = "Tailor_05";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_05":
			dialog.text = "Belada mı? Bu hafif kalır! Ah, sanırım seni tanıyorum... Sen yeni amiral yardımcısısın, değil mi?";
			link.l1 = "Çabuk kavradın. Doğru, karşında Fransız kolonilerinin ikinci adamı, Fransız filosunun Amiral Yardımcısı Charles de Maure duruyor.";
			link.l1.go = "Tailor_06";
			link.l2 = " Bırak bu resmiyetleri, gemide değiliz. Merak etme, beni hemen tanımadın diye muhafızları çağıracak değilim. Bana sadece Charles de Maure de.";
			link.l2.go = "Tailor_07";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tailor_06":
			AddCharacterExpToSkill(pchar, "Leadership", 300);//харизма
			dialog.text = "Yüce Efendim, sizi hemen tanıyamadığım için lütfen beni bağışlayın! Evet, haklısınız, beklenmedik durumlarla karşılaştım.";
			link.l1 = "Peki, o şartlar neymiş? Bildiğim kadarıyla, Paris'ten sana hiçbir malzeme getirmemişler?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_07":
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			dialog.text = "Ah, çok teşekkür ederim. Haklısınız, beklenmedik durumlarla karşılaştım, bu yüzden karşımda kimin olduğunu hemen fark edemedim.";
			link.l1 = "Peki, o koşullar neymiş? Bildiğim kadarıyla, sana Paris'ten hiçbir malzeme getirmemişler, doğru mu?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_08":
			dialog.text = "Evet, doğru. Onları birkaç ay önce sipariş ettim. Vali o zamanlar atamanız için emri imzaladı ve başkentte onaylanacağından emin olarak yeni bir amiral üniforması için gerekli tüm malzemeleri hazırlamamda ısrar etti.";
			link.l1 = "Ve malzemeler teslim edilmedi, öyle mi?";
			link.l1.go = "Tailor_09";
		break;
		
		case "Tailor_09":
			dialog.text = "Düşünebiliyor musun! Ne kadar önemli olduğunu anlattım, siparişi verdim... Ama onların daha acil sevkiyatları varmış! Ben şimdi ne yapayım? Malzemeleri getirmeye tenezzül ederler umuduyla siparişlerimi bir yıl önceden mi vermeliyim?";
			link.l1 = "Tam olarak neyi özlüyorsun? Belki Karayipler'de bulabilirsin?";
			link.l1.go = "Tailor_10";
		break;
		
		case "Tailor_10":
			dialog.text = "Mümkün olsa bile, nerede bulacağımı hiç bilmiyorum... Burada iyi malzeme bulamazsın. Ama... izin verirsen eski subay ceketini temel olarak kullanabilirim. Zaten amiral üniforman olunca ona ihtiyacın kalmayacak, değil mi?";
			link.l1 = "Eğer bir amiral üniformam varsa, tabii ki sıradan bir subay ceketine ihtiyacım olmaz. Başka ne var?";
			link.l1.go = "Tailor_11";
		break;
		
		case "Tailor_11":
			dialog.text = " Üniforma için kol düğmeleri ve bir yaka bulmam gerekiyor. Genellikle onları doğrudan Paris atölyelerinden sipariş ederim. Çok sade olsalar bile, üzerlerinde değişiklik yapıp daha düzgün bir hale getirebilirim. Ama o durumda, daha fazlasına ihtiyacım olacak... ";
			link.l1 = "Karayipler'de Paris atölyeleri olmadığına göre, sana çıkarılabilir yakalı ve manşetli bir sürü yerel kıyafet bulacağım. Başka ne istersin?";
			link.l1.go = "Tailor_12";
		break;
		
		case "Tailor_12":
			dialog.text = "Son dokunuşlar için çok kaliteli kumaşlara ihtiyacım var. Bir eğiricim var, kaba liften bile böyle bir kumaş yapabilir. Ama bunun için malzemeye ihtiyacım var – en iyisi pamuk olur. Bir balya fazlasıyla yeter.";
			link.l1 = "Bu da ayarlanabilir. Sırada ne var?";
			link.l1.go = "Tailor_13";
		break;
		
		case "Tailor_13":
			dialog.text = "Paris'ten bir amiral üçgen şapkası getirmeleri gerekiyordu, ama malzemelerim olursa kendim de yapabilirim. Senin için düşünülen şapka kumaştan olacaktı, fakat Karayiplerin tuzlu rüzgarları ve kavurucu güneşi için deri çok daha iyi olur. Daha uzun ömürlü olurdu.";
			link.l1 = "I'll get you the leather; don't worry. I won't even have to chase bulls through the jungles of Espanola. Is that all?";
			link.l1.go = "Tailor_14";
		break;
		
		case "Tailor_14":
			dialog.text = "Lyon'dan en kaliteli ipeği de getirmeleri gerekiyordu. Hafif, nefes alabilen, nemi kolayca emen ve çok hızlı kuruyan bir kumaş. En önemlisi de, esnemez ve şeklini korur.";
			link.l1 = "Evet, hangi ipekten bahsettiğini anladım. Ama kolonilerde onu bulmak biraz daha zor olabilir.";
			link.l1.go = "Tailor_15";
		break;
		
		case "Tailor_15":
			dialog.text = "Malzemeler bu kadar. Ayrıca Fransa'nın en yüksek ödülüne layık görüldüğünü de duydum... Aziz Louis Nişanı kemerine takılan bir süs eşyası değildir. Onun bir yeri vardır. Lütfen onu bana getir, olması gerektiği gibi dikeceğim.";
			link.l1 = "Pekala, ben de getireceğim. Yeter ki kaybetme!";
			link.l1.go = "Tailor_16";
		break;
		
		case "Tailor_16":
			dialog.text = "Kesinlikle hayır! Onu canım pahasına koruyacağım!";
			link.l1 = "Pekâlâ o zaman. Eğer başka bir şey yoksa, gidip malzemeleri alacağım.";
			link.l1.go = "Tailor_17";
		break;
		
		case "Tailor_17":
			dialog.text = "Bir şey daha var... Terzilik aletlerim artık kullanılamaz halde. Paris'ten yenilerini sipariş ettim ama ne yazık ki... Eğer gerekli malzemeleri bulup bana aletlerini ödünç verebilirsen – eğer varsa, sadece ödünç ver, yenilerini sonra alırım! – hemen dikişe başlarım.";
			link.l1 = "Peki, ne yapabilirim? İhtiyacın olan her şeyi sana getireceğim. Seni nerede bulabilirim? Liman yetkililerinin yanında beni beklemeyeceksin, değil mi?";
			link.l1.go = "Tailor_18";
		break;
		
		case "Tailor_18":
			dialog.text = "Atölyem, iskeleye yakın olan binada - karaya çıktığında sağında olacak.";
			link.l1 = "Anlaştık. Malzemeleri sana getireceğim.";
			link.l1.go = "Tailor_19";
		break;
		
		case "Tailor_19":
			DialogExit();
			AddQuestRecord("Patria", "65_1");
			chrDisableReloadToLocation = false;
			ChangeCharacterAddressGroup(npchar, "Charles_houseS3", "barmen", "Stay");
			npchar.dialog.currentnode = "Tailor_20";
			LAi_SetOwnerType(npchar);
			pchar.questTemp.PatriaTailor = true;
		break;
		
		case "Tailor_20":
			dialog.text = "Selamlar, Amiral Yardımcısı! Yeni üniformanız için gerekli her şeyi getirdiniz mi?";
			link.l1 = "Henüz değil, vaktim olmadı. Bekle, her şeyi halledeceğim.";
			link.l1.go = "Tailor_20_exit";
			if(CheckCoatItems())
			{
				link.l2 = "Evet, her şeyi getirdim. İşte eski ceketim, Nişan ve terzilik aletleri. Diğer malzemeleri ise tayfalarım birazdan atölyene getirecek.";
				link.l2.go = "Tailor_21";
			}
		break;
		
		case "Tailor_20_exit":
			npchar.dialog.currentnode = "Tailor_20";
			DialogExit();
		break;
		
		case "Tailor_21":
			RemoveItems(pchar, "talisman9", 1);
			RemoveItems(pchar, "suit1", 1);
			RemoveItems(pchar, "tailor_tool", 1);
			RemoveCharacterGoods(pchar, GOOD_CLOTHES, 1);
			RemoveCharacterGoods(pchar, GOOD_COTTON, 1);
			RemoveCharacterGoods(pchar, GOOD_LEATHER, 1);
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			dialog.text = "Harika! Açıkçası, bunların hepsini temin edebileceğini düşünmemiştim. Ben genellikle sadece Paris kumaşlarıyla çalışırım, ama anlaşılan yerel malzemelerle de gayet düzgün takımlar yapılabiliyormuş.";
			link.l1 = "Yeni üniformam ne zaman hazır olacak?";
			link.l1.go = "Tailor_22";
		break;
		
		case "Tailor_22":
			dialog.text = "Genellikle bu iş en az bir hafta sürer, ama müşterilerin kolonilerdeki Fransa'nın en yüksek iki yetkilisi olduğunu düşünürsek... Üç gün sonra yanıma gel, sana her şeyin en iyi şekilde hazır olacağına söz veriyorum! Ölçü almamıza gerek yok, her şeyi eski ceketine bakarak hallederim.";
			link.l1 = "Harika! O zaman üç gün sonra geri döneceğim.";
			link.l1.go = "Tailor_23";
		break;
		
		case "Tailor_23":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
			SetFunctionTimerCondition("Patria_Tailor_Done", 0, 0, 3, false);
		break;
		
		case "Tailor_24":
			if(CheckAttribute(pchar,"questTemp.PatriaTailorDone"))
			{
				dialog.text = "Amiral Yardımcısı! Sizi görmek büyük bir zevk!";
				link.l1 = "Anlaştığımız gibi, yeni üniformamı almaya geldim.";
				link.l1.go = "Tailor_27";
			}
			else
			{
				dialog.text = "Selamlar, Amiral Yardımcısı! Üzgünüm, ama üniformanız henüz hazır değil.";
				link.l1 = "Peki, en azından neler olup bittiğine şöyle bir göz atabilir miyim?";
				link.l1.go = "Tailor_25";
			}
		break;
		
		case "Tailor_25":
			dialog.text = "Hayır, hayır! Şu anda hiç gösterilecek gibi değil ve beklentilerinizi boşa çıkarmak istemem. Lütfen biraz sabredin.";
			link.l1 = "Tamam, bekleyeceğim.";
			link.l1.go = "Tailor_26";
		break;
		
		case "Tailor_26":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
		break;
		
		case "Tailor_27":
			dialog.text = "Evet, tabii ki! Söylemeliyim ki, Paris'te yapılanlardan hiç de aşağı kalır yanı yok! Haklıydın, kolonilerde de uygun malzeme bulmak mümkün, yeter ki nerede arayacağını bil. Bir saniye. İşte burada! Lütfen, incele ve dene.";
			link.l1 = "Teşekkür ederim. Mükemmel kalite! Ve tam da istediğim gibi oldu.";
			link.l1.go = "Tailor_28";
		break;
		
		case "Tailor_28":
			dialog.text = "Sadece iyi değil! Bunu kolonilerde Fransa'nın Koramirali olarak gururla taşıyabilirsin! Ve sana söz verdiğim gibi, Nişanın da artık hak ettiği yerde, kemerinden sallanmıyor.";
			link.l1 = "İyi iş çıkardın! Chevalier de Poincy ile karşılaştığında, ona memnun kaldığımı söyleyebilirsin.";
			link.l1.go = "Tailor_29";
		break;
		
		case "Tailor_29":
			dialog.text = "Ona mutlaka söyleyeceğim! Üniforman sana uğur getirsin! Bol şans!";
			link.l1 = "Teşekkürler! Hoşça kal.";
			link.l1.go = "Tailor_30";
		break;
		
		case "Tailor_30":
			DialogExit();
			npchar.dialog.currentnode = "first time";
			npchar.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.PatriaTailorDone");
			DeleteAttribute(pchar, "questTemp.PatriaTailor");
			//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			GiveItem2Character(pchar, "suit5");
			EquipCharacterbyItem(pchar, "suit5");
			GiveItem2Character(pchar, "hat5");
			EquipCharacterbyItem(pchar, "hat5");
			AddItems(pchar, "tailor_tool", 1);
			Log_Info("You have received the Vice-Admiral's uniform!");
			AddQuestRecord("Patria", "65_2");
		break;
		
		//belamour legendary edition
		case "BladeUpg":
			string sItem, attrL, attrB;
			ref rItem;
			aref arItems; 
			int i, n, iItemsNum;
			dialog.text = "Hangi kılıcı yükseltmek istersiniz?";
			
			i = 1;
			makearef(arItems, pchar.items);
			iItemsNum = GetAttributesNum(arItems);
			for(n=0; n<iItemsNum; n++)
			{
				sItem = GetAttributeName(GetAttributeN(arItems, n));
				rItem = ItemsFromID(sItem);
				if(!CheckAttribute(rItem, "groupID")) continue;
				if(rItem.groupID != BLADE_ITEM_TYPE) continue;
				if(rItem.price == 0) continue;
				if(IsEquipCharacterByItem(pchar, rItem.id)) continue;
				if(sItem != "" && rItem.groupID == BLADE_ITEM_TYPE) 
				{
					attrL = "l" + i;
					Link.(attrL) = GetItemName(rItem) + ": Attack - " + FloatToString(stf(rItem.attack),1) + ", balance - " + FloatToString(stf(rItem.Balance),1) + ", weight - " + FloatToString(stf(rItem.Weight),1);
					Link.(attrL).go = "bladeindex_"+GetItemIndex(rItem.id);
					i++;
				}
			}
			
			link.l500 = "Fikrimi değiştirdim";
			link.l500.go = "exit";
		break;
	}
} 

bool CheckCoatItems()
{
	if(GetSquadronGoods(pchar, GOOD_CLOTHES) > 0
	&& GetSquadronGoods(pchar, GOOD_COTTON) > 0
	&& GetSquadronGoods(pchar, GOOD_LEATHER) > 0
	&& GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0
	&& GetCharacterFreeItem(pchar, "talisman9") > 0
	&& GetCharacterFreeItem(pchar, "suit1") > 0
	&& GetCharacterFreeItem(pchar, "tailor_tool") > 0)
	return true;
	
	return false;
}
