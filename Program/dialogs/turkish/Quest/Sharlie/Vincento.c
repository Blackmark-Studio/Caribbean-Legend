// отец Винсенто
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
			{
				dialog.text = "Nihayet, ünlü Fransız kaptanını görüyorum "+GetFullName(pchar)+"   karşımda canlı kanlısın. Hakkında çok şey duydum. Cesur bir askersin ve umarım Kutsal Roma Katolik Kilisesi’nin sadık ve itaatkâr bir evladısındır. Otur, evladım. Benim için ayakta durmana gerek yok. Dominus vobiscum! ";
				link.l1 = "Ve ruhunla beraber, Ekselansları. Buraya yolculuğum uzun ve zorluydu... Per aspera ad astra ve hepsi...";
				link.l1.go = "utensil";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
			{
				dialog.text = "Evet, gözlerinden bana haberin olduğunu görebiliyorum. Tüm dikkatimi sana verdim.";
				link.l1 = "Ekselansları, kayıp sekreterinizi buldum...";
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
			{
				dialog.text = "Bana San Jose'den haber getirdin mi, oğlum?";
				link.l1 = "Evet, Ekselansları. Ortak tanıdığımız Miguel Dichoso ve kayıp firkateyniyle ilgili gerçekte ne olduğunu öğrendim. Gemisi İspanya'ya doğru Atlantik'e açılır açılmaz, aniden ters bir fırtınaya yakalandı ve Karayipler'e geri savruldu.";
				link.l1.go = "guardoftruth_10";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
			{
				dialog.text = "Pax vobiscum, evladım... Senin için ne yapabilirim?";
				link.l1 = TimeGreeting()+" , Ekselansları. Anlaşmamızla ilgili bir haberiniz var mı?"link.l1.go ="guardoftruth_17";
				break;
			}
			dialog.text = "Bir şey mi istedin, oğlum?";
			link.l1 = "Hayır, hiçbir şey, Baba.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "utensil":
			dialog.text = "'Enter by the narrow gate; for wide is the gate and broad is the way that leads to destruction, and there are many who go in by it. Because narrow is the gate and difficult is the way which leads to life, and there are few who find it.' The path of righteousness is always difficult, my son. But the aim that is achieved fully rewards a righteous man for his works.";
			link.l1 = "Katılıyorum, Ekselansları. Bana verdiğiniz görevleri tamamladım. Kiliseden değerli kapları çalan o korkak korsan artık elinizde. Şimdi de alınan tüm eşyaları geri getiriyorum: sunak lambası, haç ve buhurdan. Bunları Santiago cemaatine teslim edin.";
			link.l1.go = "utensil_1";
		break;
		
		case "utensil_1":
			RemoveItems(pchar, "jewelry33", 1);
			RemoveItems(pchar, "jewelry34", 1);
			RemoveItems(pchar, "jewelry35", 1);
			dialog.text = "Benedicite! Aziz Kilise'ye ve Santiago cemaatine sadık hizmetin için sana yürekten teşekkür ediyorum, evladım. Yaptıkların karşılıksız kalmayacak. Cemaat, çalınan eşyalarını geri getiren cesur savaşçı için bir bağış topladı ve bunu memnuniyetle sana takdim ediyorum. 'İşçi, ücretini hak eder.'";
			link.l1 = "Teşekkür ederim, Ekselansları. Ne hoş bir sürpriz!";
			link.l1.go = "utensil_2";
		break;
		
		case "utensil_2":
			GiveItem2Character(pchar, "chest");
			Log_Info("You've received a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Anne Kilise'ye sadık hizmet her zaman sadakatle ödüllendirilir, "+pchar.name+" . Ben ise, Hristiyan âleminin savunması ve korunması için kendini adamış bir savaşçı olarak kalmanı umuyorum, zira başımızın üstünde efsanevi Damokles'in Kılıcı gibi ölümcül bir tehdit dolaşıyor.";
			link.l1 = "Bu ne olabilir, Ekselansları?";
			link.l1.go = "utensil_3";
		break;
		
		case "utensil_3":
			dialog.text = "Belki de yaklaşan karanlık güçlere ve bu dünyanın kötücül prenslerine karşı vereceğimiz savaşta bizim kurtarıcımız olman kaderinde yazılıdır, oğlum, zira yaklaşmakta olan bir kötülüğe dair pek çok işaret ve alamet var.";
			link.l1 = "İşaretler ve alametler mi?";
			link.l1.go = "utensil_4";
		break;
		
		case "utensil_4":
			dialog.text = "Çok var, oğlum... Bunlardan biri de, senin putperest Tayasal’ın kayıp Hint altınını arama tutkun. Çünkü onların hazinesinde saklanan şey, tüm Hristiyan dünyası için gerçek bir tehlike demek.";
			link.l1 = "Bana bu altın hakkında biraz daha bilgi verebilir misiniz, muhterem Peder? Kayboluşunun hikayesini zaten duydum, ama bahsettiğiniz tehlike tam olarak nedir?";
			link.l1.go = "utensil_5";
		break;
		
		case "utensil_5":
			dialog.text = "İyi dinle oğlum, ve bil ki şimdi duyacakların yalnızca senin kulakların için. Miguel Dichoso o putperest hazinesini eski bir Hint şehrinden çıkarmadan çok önce, Karayipler'deki görevimizle ilgili olarak Itza yerlilerinden bir adamı esir alıp sorgulattım. Itza halkı, Maya İmparatorluğu'nun torunlarıdır; bu kudretli imparatorluk, Kristof Kolomb ve adamları Yeni Dünya'ya ilk ayak bastıklarında bile asırlardır kayıptı. Maya İmparatorluğu, çevresindeki kabileleri demir yumrukla yönetir, şeytanlarla yaptıkları uğursuz anlaşmalar sayesinde tarif edilemez bir güç kullanırlardı. Nesiller boyu yapılan insan kurbanlarının kanıyla satın alınmış karanlık büyülerdi bunlar. \nBu Itza adamı Tayasal'dan, kayıp bir Maya şehrinden ve hâlâ içinde mühürlü duran korkunç kötülükten haberdardı. Bildiği her şeyi anlattı. O mühürler açılırsa, sonuçları kıyamet gibi olurdu. O andan itibaren, bu korkunç kötülüğün uyanmasını engellemek için elimden gelen her şeyi yaptım. Escorial ve Roma'ya mektuplar yazıp umutsuzca yardım istedim.\nDinlediler ve Don Ramon de Mendoza y Riba'yı gönderdiler; o da Providence'da üssünü kurup Tayasal'ı aramaya başladı. İşte o zaman iyi Don Mendoza'nın kayıp şehri bulmak için... bambaşka motivasyonları olduğunu keşfettim. Dünyanın sonunu engellemek yerine, Mesih'e değil Mammon'a hizmet etmek istiyordu.\nBu yüzden Tanrı onu terk etti ve ölüm meleğini kampına gönderdi. Tüm çabaları boşa çıktı ve yalnızca İspanyol askerlerinin ve sadık Hintli mühtedilerin anlamsız ölümlerine yol açtı. Escorial'a Ramon de Mendoza'nın görevden alınması için yetersizliği gerekçesiyle tekrar yazdım ve görevden alınmasına razı oldular, fakat...";
			link.l1 = "Miguel Dichoso geldi.";
			link.l1.go = "utensil_6";
		break;
		
		case "utensil_6":
			if (CheckAttribute(pchar, "questTemp.Dolly")) sTemp = "Kukulcan?! Sancta Maria, Mater Dei, ora pro nobis! Kukulcan again, that old serpent...";
			else sTemp = "Hm...";
			dialog.text = "Kesinlikle. O şeytanın gönderdiği maceraperest, Tayasal'ı ve eski Mayaların hazinelerini buldu. Fakat Don Mendosa'nın sevinci kısa sürdü. Tüm o hazineler, Dichoso ile birlikte İspanya'ya dönerken ortadan kayboldu. Muhtemelen, altın külçeler ve süs eşyalarıyla birlikte, Miguel yanında şeytani bir gücün kaynağını da götürdü: Kukulcan adında eski bir Maya iblis tanrısının korkunç maskesini.";
			link.l1 = sTemp+"Ama hangi kötülükten bahsediyorsunuz Ekselansları? Bundan nasıl haberdar oldunuz?";
			link.l1.go = "utensil_7";
		break;
		
		case "utensil_7":
			dialog.text = "Bu, Karayipler'deki, Yeni Dünya'daki ve belki de Eski Dünya'daki tüm vaftiz edilmiş Hristiyanlara ölüm getiren bir kötülük. Son, gece gelen bir hırsız gibi ansızın gelecek ve kimse ne olduğunu bile anlamayacak. Ve bunun alametleri şimdiden her yerde!";
			link.l1 = "Hangi alametler? Hiçbir şey anlamıyorum...";
			link.l1.go = "utensil_8";
		break;
		
		case "utensil_8":
			dialog.text = "Oğlum, gerçekten o kadar kör müsün ki onları fark etmiyorsun bile? Yirmi beş yıldır, neredeyse aralıksız yaşanıyorlar!";
			link.l1 = "Saygıdeğer Ekselansları, müsaadenizle belirtmek isterim ki, ömrümün tamamı tam olarak bu kadar bir süreyle sınırlı, üstelik yıllarımın çoğunu Avrupa’da geçirdim. Cehaletimin bir nebze mazur görülmesini rica ederim.";
			link.l1.go = "utensil_9";
		break;
		
		case "utensil_9":
			dialog.text = "Anladım. "+pchar.name+". Şimdi, Avrupa'dan buraya geldiğinden beri Karayipler'de tuhaf şeyler olduğunu fark etmedin mi? Cadılığın, kara büyünün ve başka ayinlerin burada, memlekette olduğundan çok daha güçlü olmasını garip bulmuyor musun? Hintli şamanların büyülediği pagan muskaları, onları eline alan herkesin hissedebileceği gerçek bir güce sahip.\nBizim Hristiyan simyacılarımız bile - Tanrı onlara doğru yolu göstersin! - büyülü eşyalar yapma sanatında ustalaştılar. Fakat farkında değiller ki, bunu yaparak bizzat Şeytan'a hizmet ediyorlar. Gözünün ucunda, hemen yanı başında, doğaüstü ve uğursuz bir şeyin varlığını hissetmiyor musun?";
			link.l1 = "Haklısın, baba. Başta buna şaşırmıştım ama şimdi sanırım alıştım... Sonuçta burası Yeni Dünya!";
			link.l1.go = "utensil_10";
		break;
		
		case "utensil_10":
			dialog.text = "Ama her zaman böyle değildi. Bahsettiğim karanlık buraya yaklaşık yirmi beş yıl önce geldi ve her geçen gün daha da güçleniyor. Bu da tek bir anlama gelir: 'o' zaten geldi, 'o' aramızda ve 'o' iş başında...";
			link.l1 = "Kimi kastediyorsun? Bu gizemli 'o' kim?";
			link.l1.go = "utensil_11";
		break;
		
		case "utensil_11":
			dialog.text = "Hristiyanların yeminli düşmanı, Kilise'nin ve tüm Hristiyan âleminin yok olmasını arzulayan.";
			link.l1 = "...Mesih Deccal'den mi bahsediyorsun?";
			link.l1.go = "utensil_12";
		break;
		
		case "utensil_12":
			dialog.text = "İster 'o' Deccal olsun, ister sadece 'bir' deccal, bunu söylemeye cüret etmeyeceğim. Bu yaratık, Kurtarıcımızın Enkarnasyonunun çarpık bir parodisi olarak ölümlü bir bedene büründüğünde hangi ismi taşıdığı önemli değil. Önemli olan, ne yapacağıdır. Ben onu durdurmak için buradayım ve sen de bana yardım edeceksin. Ama biraz fazla daldık. Sen harekete geçen bir adamsın. Muhtemelen doğrudan işe koyulmayı ve teolojiyi atlamayı tercih edersin, değil mi?";
			link.l1 = "Aksine, sizden çok yeni ve önemli şeyler öğrendim Ekselansları. Daha fazlasını dinlemeye hazırım.";
			link.l1.go = "utensil_13";
		break;
		
		case "utensil_13":
			dialog.text = "Nezaketli ve iyi yetiştirilmiş bir evlatsın, oğlum. Bu güzel. Şimdi, benimle görüşme sebebine dönelim. Ortak amacımız, Dichoso'nun ele geçirdiği Tayasal hazinelerini bulmak. Muhtemelen o hazineler arasında, Şeytan'a karşı yaklaşan savaşta kullanabileceğimiz bir silah da bulacağız.";
			link.l1 = "Ama ya Dichoso Karayipler'den ayrılıp şimdi İspanya'da bir yığın altının üstünde oturuyor olmasın ?";
			link.l1.go = "utensil_14";
		break;
		
		case "utensil_14":
			dialog.text = "Hayır. Bu hazinelerin hâlâ Karayipler'de olduğuna dair kanıtım var. Kaynaklarımı henüz bilmen gerekmiyor, bana güvenmek zorundasın. Ayrıca, bence Dichoso barona yalan söyledi.\nTayasal harabeleriyle ilgili anlattıkları, sorguladığım Itza yerlisinin söyledikleriyle hiç uyuşmuyor. Üstelik, Dichoso'nun Mosquito pususundan tek sağ kurtulan olması da fazlasıyla şüpheli.";
			link.l1 = "Don Mendoza'nın da böyle düşündüğünü varsayıyorum, çünkü Dichoso'yu bulmak için Saint-Pierre'e baskın yaptı?";
			link.l1.go = "utensil_15";
		break;
		
		case "utensil_15":
			dialog.text = "Baronun yaptıkları seni ilgilendirmemeli, oğlum. Onu harekete geçiren tek şey altına ve kişisel çıkara olan açgözlülüğü. Bu hırsı, boynunda bir değirmen taşı gibi olacak, etrafında ise iyi Hristiyan erkekler ve kadınlar cehennemin güçleriyle mücadele ediyor olacak.";
			link.l1 = "Dichoso ve hazineyi nerede aramamız gerektiğine dair bir ipucunuz var mı?";
			link.l1.go = "utensil_16";
		break;
		
		case "utensil_16":
			dialog.text = "Her dakika bunu düşünüyorum, oğlum, ama sana söyleyebileceğim belirli bir şey yok. Fakat burada bize yardım edecek biri var, Cenovalı bir tabiat filozofu. Onu buraya, Kilise'nin misyonuna faydalı olabilecek Yeni Dünya'nın şeylerini sınıflandırmamıza yardımcı olsun diye getirdim. O, Itza yerlisinin sorgusuna tanık oldu ve gördüğüm kadarıyla, duydukları onu hem şoke etti hem de tuhaf bir şekilde cezbetti.\nŞeytan onun merakını yem gibi kullanıp onu bedeniyle ve ruhuyla ele geçirdi. Tanrı ona tıp ve simya konusunda büyük bir yetenek vermişti, fakat Cenovalımız kara büyü ve sihrin cazibesine kapıldı. Benim iznim olmadan tutsak Itza'yla birkaç kez konuştu, sonra da ortadan kayboldu. Onu bulmalı ve ruhunu kurtarmalıyız.";
			link.l1 = "Onu bulmam mı gerekiyor?";
			link.l1.go = "utensil_17";
		break;
		
		case "utensil_17":
			dialog.text = "Evet, oğlum. O, hazineyi ve bize karşı tehdit oluşturan kötü güçlere karşı kullanabileceğimiz silahı bulmanın ilk adımı.";
			link.l1 = "Bu Cenovalı kim?";
			link.l1.go = "utensil_18";
		break;
		
		case "utensil_18":
			dialog.text = "Adı Gino Gvineili. Otuz yaşında, birkaç yıl fark edebilir. Yetenekli bir hekim ve simyacı. Dediğim gibi, şimdi kara büyüyle ilgileniyor. En güvenilir bilgilerime göre, Karayipler'deki İngiliz kolonilerinden birinde saklanıyor.\nGino Gvineili'yi bul, oğlum. Kilise eşyalarımızı çalan o korsanı bulmayı başardıysan, kaçak sekreterimi de bulup buraya getirebilirsin. Senin için Aziz Antonyus'un aracılığına dua edeceğim.";
			link.l1 = "Anladım, Ekselansları. Bir dakika daha kaybetmeyeceğim. Sonra görüşürüz!";
			link.l1.go = "utensil_19";
		break;
		
		case "utensil_19":
			DialogExit();
			AddQuestRecord("Guardoftruth", "35");
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
			{
				pchar.questTemp.Guardoftruth = "jino";
				AddQuestUserData("Guardoftruth", "sText", "I almost betrayed myself by a shout of surprise. Father Vincento ordered me to find and bring him his runaway secretary, a physician alchemist named Gino Gvineili. That same Gino who occupies the spare room on the second floor of my house in St. John's!");
			}
			else
			{
				pchar.questTemp.Guardoftruth = "merdok";
				AddQuestUserData("Guardoftruth", "sText", "I must find a man named Gino Gvineili, hiding somewhere in the English Caribbean colonies. He is a physician and an alchemist. Where can a man like him hide?");
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Bunu söyleyeceğine tamamen emindim, "+pchar.name+"Şimdi ise, İlahi Takdir’in bizzat eliyle bana gönderildiğine dair kesin inancım, imanımı daha da güçlendirdi. Nerede benim zavallı, haylaz oğlum?";
			link.l1 = "Korkarım duyacaklarınız hoşunuza gitmeyecek, ama başka seçeneğim yok. Sekreteriniz öldü.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Tanrı ruhunu korusun ve günahlarını affetsin... Nasıl oldu bu, oğlum?";
			link.l1 = "Antigua'da Gino'yu buldum. Orada, laboratuvarın altına inşa edilmiş eski binalardan birinde saklanıyordu. Sessizce benimle gelmeyi kabul etmedi. Senin adını duyunca ve zor kullanmaya hazır olduğumu görünce, uzun giysisinin kıvrımlarından şeffaf bir sıvı içeren bir şişe çıkardı ve bir anda içti...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "";
			link.l1 = "Ve sonra korkunç bir şey oldu: önce kıpkırmızı, sonra koyu maviye döndü. Yere yığıldı, kasılarak çırpındı ve bir dakika içinde korkunç bir acı içinde öldü. Odayı yoğun bir badem kokusu kapladı.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Gino... Zavallı ahmak... Hayatının son anlarını bile intihar ederek günahla geçirdi. Ne acı bir kayıp. Ruhu için dua edeceğim...";
			link.l1 = "O öldükten sonra, evini aradım ve bu defteri buldum. Belki ilginizi çeker ya da arayışımızda bize yardımcı olur mu? Burada tuhaf ve gizemli bazı notlar var...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			RemoveItems(pchar, "Almanac", 1);
			Log_Info("You've given the almanac");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bu, zavallı Gino'nun almanakı. Tüm keşifleriyle ilgili notlar almış içine. Ver bana, evladım, burada yazanları inceleyeceğim. Belki bir ipucu buluruz.\nGino Gvineili'yi bana geri getirmemiş olsan da, çabaların beni memnun etti, evladım. Şimdi sana bazı haberlerim var.";
			link.l1 = "Dikkatimi verdim, Baba.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = " Trinidad adasında Dichoso'nun fırkateyninin en son görüldüğüne dair bilgi edindim. Ayrıca yaklaşık bir tarih de biliyorum – 1654 yılının nisan ayı başları.  Trinidad'a git ve fırkateynin akıbetiyle ilgili ne bulabiliyorsan öğrenmeye çalış: nereye gidiyordu, kaptanın ne gibi planları vardı, eline ne geçerse. Biliyorum, aradan çok zaman geçti ve insanların hafızası sınırlı, ama boğulan biri saman çöpüne bile sarılır.";
			link.l1 = "Elimden gelen her şeyi yapacağım.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Geçiş izni mektubunu göreyim. San José kolonisini ziyaret etmen için de izin ekleyeceğim.";
			link.l1 = "Al bakalım.";
			link.l1.go = "guardoftruth_6a";
		break;
		
		case "guardoftruth_6a":
			RemoveItems(pchar, "VerifyPaper", 1);
			dialog.text = "İşte... bu kadar. Gemine İspanyol bayrağını çekmeyi unutma. İleri çık ve Tanrı'nın kutsamasını al, oğlum!";
			link.l1 = "Bir dakika, Ekselansları. Size bir soru sorabilir miyim?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Evet, tabii ki. Ne bilmek istersiniz?";
			link.l1 = "Son görüşmemizde, sana Tayasal hakkında bilgi veren bir Itza yerlisinden bahsetmiştin. Bunu çok düşündüm... Söylesene, o adamın üzerinde bir şey var mıydı? Herhangi bir nesne, yazı ya da buna benzer bir şey? Bu işimize yarayabilir.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Özel bir eşya yok, oğlum. Bir peştamal, ilkel takılar, içinde biraz ot bulunan bambu bir pipo ve ağız tıkacı olarak kullanılan kaba bir deri parçası.\nBunların hepsi Don Ramon de Mendoza y Riba'ya gönderildi. Ama emin olabilirsin, ilginç hiçbir şey yoktu.";
			link.l1 = "Anladım. Teşekkür ederim, baba. Bir dahaki sefere görüşürüz!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
			AddQuestRecord("Guardoftruth", "38");
			npchar.quest.skinmap = "true";
			pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Yüce Tanrı seni korusun ve yanında olsun... Miguel Dichoso'ya ne oldu? Bir şey öğrenebildin mi?";
			link.l1 = "Ne yazık ki, hayır. Şahitlerin bana söyleyebildiği son şey, Santa Quiteria'nın şiddetli rüzgarlarla Martinique yönüne sürüklendiğiydi. Geminin kurtulup kurtulmadığı kesin olarak bilinmiyor. Ama Miguel Dichoso'nun hayatta kaldığına dair şüphelerim var.";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Bunu neden böyle düşündün, oğlum?";
			link.l1 = "Anahtar nokta şu ki, fırkateyn Martinique yönünde bir yerde saklanıyordu. Ve çok yakın zamanda, Don Ramon de Mendoza'nın adamlarından biri olan Diego de Montoya adında cesur bir caballero, orada saklandığı söylenen Miguel Dichoso'yu bulmak amacıyla Saint-Pierre'e saldırdı.";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Demek baron, Dichoso'nun Fransızlarla birlikte saklandığını düşünüyor...";
			link.l1 = "Saint-Pierre'i ve Vali Jacques Dyel du Parquet'yi iyi tanırım, Ekselansları. Orada Miguel Dichoso adında bir İspanyol'u kimse tanımıyordu. Diego de Montoya'yı nasıl bulabileceğimi söyleyebilir misiniz? Dichoso hakkında onunla konuşmak istiyorum.";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Oğlum, seninle konuşmaya razı olacağından emin misin? Sanmıyorum, ancak kılıç ve tabanca ile konuşursan belki olur.";
			link.l1 = "Adını duymak onu daha yumuşak başlı yapar mı dersin?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Oh, "+pchar.name+"Don Mendoza'nın yeminli adamının seninle bir anlaşmaya varmaya istekli olacağından şüpheliyim. Onu benimle görüşmek üzere San Diego'ya çağırmak bir seçenek olabilir, ama Diego'nun bana tamamen samimi olacağından da emin değilim.";
			link.l1 = "Şimdi ne yapacağız, baba?";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Beni biraz yalnız bırak, oğlum. Bana anlattıklarını sindirmem ve ayrıca kendi kaynaklarımdan bildiğim her şeyi bir araya getirmem gerekiyor. Sonrasında bir sonraki adımımızı sana söyleyeceğim. Daha sonra uğra.";
			link.l1 = "Evet, Majesteleri. Hemen yaparım. Ara sıra uğrayıp haber veririm...";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			DialogExit();
			AddQuestRecord("Guardoftruth", "43");
			pchar.questTemp.Guardoftruth.Trinidad = "end";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
			NextDiag.CurrentNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_wait":
			dialog.text = "Tanrı seni korusun, evladım... Senin için ne yapabilirim?";
			link.l1 = "Bir haberiniz var mı, Ekselansları?";
			link.l1.go = "guardoftruth_wait_1";
		break;
		
		case "guardoftruth_wait_1":
			dialog.text = "Şu anda değil, oğlum. Ama umudunu kaybetme. Ben ve adamlarım bunun üzerinde çalışıyoruz. Sonra yine uğra.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Evet, oğlum. Miguel Dichoso hakkında bazı bilgilerim var. Dichoso'nun hâlâ hayatta olduğuna ve Karayipler'de bulunduğuna inanmam boşuna değilmiş. Görünen o ki, Don Diego de Montoya haklıymış. Miguel Dichoso'yu yüzünden tanıyan bir adamdan aldığımız doğrulamaya göre, kayıp beyefendi Santa Quiteria'nın kaybolmasından sonra, 1654 Nisan'ında Martinique'teki Le Francois adlı korsan yerleşiminde görülmüş...";
			link.l1 = "Yani, fırkateyn Martinique kıyılarında batmış mı?";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Sakin ol, oğlum. O dönemde Martinique açıklarında herhangi bir gemi kazası olduğuna dair elimizde hiçbir bilgi yok. Ayrıca bir fırkateyn, küçük bir tekne değildir. Böyle bir geminin yok olması mutlaka dikkat çekerdi ve yerel fırsatçılar için büyük bir ganimet olurdu.";
			link.l1 = "Sahili ve kumsalları aramak, gemiden geriye ne kaldıysa bulmak için değer mi?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Oğlum Don Diego de Montoya bunların hepsini zaten yaptı ama bir sonuç alamadı. Dinlemeye devam et. Providence'daki kaynaklarım, Baron'sun Santa Quiteria'nın hâlâ Karayipler'de başka bir isimle dolaştığına kesinlikle inandığını bildiriyor.\nBu yüzden Miguel Dichoso'nun peşine bu kadar umutsuzca düşmüş durumda. Ona göre, Santa Quiteria yakın zamanda Isla Tesoro civarında görülmüş ve kısa süre önce İngiliz bayrağı altında, bir askeri filoyla birlikte seyrediyormuş.";
			link.l1 = "Ne? Bu inanılmaz. Böyle bir fırtınaya dayanmanın imkânsız olduğunu söylemişlerdi... Ama şimdi Santa Quiteria sadece hayatta kalmakla kalmamış, İngiliz bayrağı altında yol alıyor? Bu iki bilgi birbirini tutmuyor. Baronu Santa Quiteria olduğuna ne ikna etti? Gerçekten bu kadar eşsiz bir gemi miymiş?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Ah evet. Bu fırkateyn Avrupa'daki en yeni tekniklerle inşa edildi. Sınıfına göre çok iyi silahlandırılmış, hızı sayesinde de ateş gücü daha üstün olanlardan bile kaçabiliyor. Kaynağım bana böyle söyledi.";
			link.l1 = "Ve şimdi ona Santa Quiteria demiyorlar mı?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "Ne yazık ki, bunu bilmiyorum... Isla Tesoro'ya git, "+pchar.name+", ve Dichoso'nun fırkateyni hakkında bir şeyler öğrenmeye çalış. Belki bu şekilde eski kaptanını da bulabiliriz, bir taşla iki kuş vurmuş oluruz. Ya da bir kapanla iki sıçan yakalamış.";
			link.l1 = "Emredersiniz, Ekselansları!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "59");
			// проверяем, жив ли Акула и где он, если жив
			if (GetCharacterIndex("Dodson") != -1)
			{
				sld = characterFromId("Dodson");
				if (sld.location == "Pirates_townhall") pchar.questTemp.Guardoftruth.Archy = "islatesoro";
				else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			}
			else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // немного развлечений
		break;
		
		case "tieyasal":
			dialog.text = "Seni görmeye karar verdiğine sevindim, oğlum.";
			link.l1 = "Merhaba, Ekselansları. Don Alonso de Maldonado ile görüştükten sonra sizi bir daha göreceğimi hiç düşünmemiştim.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Don Alonso de Maldonado benim doğrudan verdiğim emirlere karşı geldi. Ona seninle yüzleşmesini kesinlikle yasaklamıştım, oğlum, bunun onun için nasıl biteceğini biliyordum. Ve öngördüğüm şey gerçekleşti. Onun görevi seni Tayasal'a kadar eşlik etmekti, çünkü orada daha önce bulunmuştu.\nÜstelik, onun filosu ve bir grup İspanyol askeri de seni Itza ya da Mosquito saldırılarına karşı korumakla görevliydi. Alonso, bencil bir intikam arzusuyla hareket ederek kendine yakışmayan bir şekilde davrandı.\nSadece Tayasal seferini başarısızlığa uğratmakla ve kendisine emanet edilen askerleri ve gemileri felakete sürüklemekle kalmadı, aynı zamanda kalbine bana karşı güvensizlik ve öfke tohumları ekti. Sana temin ederim oğlum, tamamen senin tarafındayım. Bu karanlığa karşı birlikte durmalıyız.";
			link.l1 = "Buna inanmak isterim.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "İçin rahat ol, "+pchar.name+". Ben, Rabbimiz ve Kurtarıcımız İsa Mesih’in sadık ve adanmış bir hizmetkârı ve Kilisesi’nin temsilcisi olarak, tek bir amaçla hareket ediyorum: tüm ruhlar Kutsal Rabbimizin sözünü duyana dek dünyanın sonunu engellemek. Bu da şu anda şeytan tarafından ele geçirilmiş bir Kızılderilinin elindeki şeytani eseri durdurmamız gerektiği anlamına geliyor. En başından beri bundan şüpheleniyordum ve ancak şimdi tamamen emin oldum. Sen, Rab tarafından Şeytan’a karşı verilen bu savaşta O’nun şampiyonu olarak seçildin.";
			link.l1 = "Ama bunu neden söylüyorsun, baba?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Bunu, ne ben tüm ajanlarımla, ne Baron Mendoza ve Don Diego, ne de başka hiç kimse başaramadı. Sen ise o lanetli adayı bulup, Kukulcan'ın eserini aramayı başardın. Öyle değil mi?";
			link.l1 = "Evet, Kukulcán'ın maskesi bende.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Ve bütün bunların bir tesadüf eseri mi gerçekleştiğini iddia ediyorsun? Sadece bir rastlantı mı? 'İnsanın yüreği yolunu tasarlar, fakat Rab adımlarını yönlendirir.' Oğlum, Yüce Tanrı seni bu yola sevk etti! Savaşta elini güçlendirdi, ayaklarını doğru yola yönlendirdi ve tehlike anında seni korudu! 'İşte, Rab'bin kılıcı Edom'un üzerine, yok edilmek üzere adanmış halkın üzerine hüküm için iner!'";
			link.l1 = "Ehem... Baba, ama görev esasen zaten tamamlandı. Maske bende. Bu, Kukulcan'ın ele geçirilmiş bedeni artık tarihimizi değiştiremeyecek demek değil mi...?";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			dialog.text = "Yanılıyorsun, oğlum. O iblis, bu maskeye sahip olsun ya da olmasın, o kapıdan geçebilir. Maske sadece karanlık işlerini yapmasını kolaylaştırıyor. Onu durdurabilecek tek şey ise cehennem kapılarının tamamen yok edilmesidir.";
			link.l1 = "Don Alonso da bana aynı şeyi söyledi...";
			link.l1.go = "tieyasal_6";
		break;
		
		case "tieyasal_6":
			dialog.text = "Ve haklıydı! Rabbimiz İsa Mesih ve O'nun kutsal annesi adına, seni bu kötülüğe karşı Haç'ı kaldırmaya çağırıyorum, oğlum! Üzerine yüklenen bu büyük görevi reddedemezsin. Ben ve tüm Hristiyan âlemi sana güveniyoruz, oğlum.";
			link.l1 = "Ekselansları, bu gerçekten fazla oldu. Kendimi... oldukça tuhaf hissediyorum...";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Mütevazılığın sana yakışıyor, oğlum, ama şimdi utangaç bakire rolü yapmanın zamanı değil. Cesaretini kaybetme, korkma; çünkü Tanrın senin önünden gidiyor ve sana zafer kazandıracak! Bu savaşa sevdiklerin için gir, bütün Hristiyanlar için gir... ve eğer onlar için değilse, kendi iyiliğin için gir; çünkü o iblis galip gelirse, sen de herkesle birlikte yok olacaksın.";
			link.l1 = "Sana inandım galiba, baba. Tayasal'a bir sefer düzenleme konusunda kararsızdım, ama artık hiçbir şüphem kalmadı. Bana nasıl yardımcı olabilirsin?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Tayasal'a nasıl gidileceğini yalnızca iki adam biliyordu: Alonso de Maldonado ve Miguel Dichoso. Don Alonso öldü. Dichoso ise... Bana, onu yakın zamanda Isla Tesoro'daki Sharptown'da gördüklerini söylediler. Belki hâlâ oradadır. Dichoso'yu bulmalı ve onu rehberin olmaya ikna etmelisin.\nAltınla ya da zorla, bu adamı Tayasal'a seni götürmeye mecbur bırakmalısın. Orada cehennemin kapılarını bulacaksın ve orada onları mühürleyeceksin.";
			link.l1 = "   Peki ya erkekler?   ";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Elimdeki son asker birliği Alonso de Maldonado'nun emrindeydi. Ne yazık ki, bir daha İspanyol askerlerinden bir birlik toplama şansım yok. Buradaki garnizonda tüm kredimi tükettim. Kendi adamlarınla idare etmek zorunda kalacaksın, oğlum. Ama başka konularda elimden gelen yardımı yapacağım.";
			link.l1 = "Ne tür bir yardım?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Bu savaşta sahip olduğumuz her türlü avantajı kullanmalıyız, hem maddi hem de manevi olanları. Beş gün sonra burada, bu şapelde bana katılması için Rahip Adrian'dan ricada bulundum. Senin için yanında kutsal muskalar getirecek. Bu muskalar, Mesih'in savaşçılarına savaşta yardımcı olabilir. Ayrıca sana her türlü iksir de sağlayacak. Bana gelince, oğlum, bu kılıcı kabul et.\nBu, Tapınak Şövalyeleri'nin eski bir kılıcıdır, atalarımızın kudretli bir silahı. Hâlâ keskin ve Kilise'nin kutsamasıyla parlıyor. Yalnızca en büyük şövalyeler onu kullanma onuruna erişti. Al, gururla sahiplen ve İsa Mesih'in adını dudaklarında taşıyarak inancımızın düşmanlarını ez!";
			link.l1 = "Teşekkür ederim! Bu kılıç gerçekten harika. Ne diyeceğimi bilemiyorum...";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			sTemp = GetBestGeneratedItem("blade_32");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			sld.Weight = 4.5;
			Log_Info("You've received the Tanath");
			PlaySound("interface\important_item.wav");
			dialog.text = "Tanrı seni korusun, "+GetFullName(pchar)+", in this coming battle. I embower you with the Holy Cross. Almighty God, in whose hand victory rests and who also gave David miraculous strength to crush Goliath: humbly we pray your mercy to bless these weapons by your life-giving mercy; and grant your servant "+GetFullName(pchar)+" who wills to bear them, that he may use them freely and victoriously for defending Holy Mother Church against the attacks of all enemies visible and invisible. Through Christ our Lord. Amen.";
			link.l1 = "Amin!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "Ve şimdi git, oğlum. Tanrı seni korusun, seni asla yalnız bırakmasın; ne arayışında, ne yolunda, ne de savaşta. Miguel Dichoso'yu bul ve onun yardımıyla Tayasal'a git. Peder Adrian'ı unutma, sana ihtiyacın olan muskaları ve ilaçları verecektir. Şimdi ise Santiago'ya dönme vakti benim için geldi. Elveda, oğlum. Tanrı seninle olsun.";
			link.l1 = "Elveda, Peder Vincento...";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
