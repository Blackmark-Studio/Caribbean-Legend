int questShips[50];
int questShipsNum = 0;

extern void InitGunExt(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin,   
				float  DmgMax, 
				float  EnergyP,
				bool   MultiDamage, 
				int    MisFire,     
				int    ChargeSpeed, 
				bool   isDefault );

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp, attr, companion;
	ref chref;
	int iTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string node = Dialog.CurrentNode;
	if(HasSubStr(node, "joruba_p3_ship_")) {
		iTemp = findsubstr(node, "joruba_p3_ship_", 0);
	 	companion = strcut(node, iTemp + strlen("joruba_p3_ship_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p3";
	}
	
	if(HasSubStr(node, "joruba_p4_off_")) {
		iTemp = findsubstr(node, "joruba_p4_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_p4_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p4_off";
	}

	if(HasSubStr(node, "joruba_o6_off_")) {
		iTemp = findsubstr(node, "joruba_o6_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_o6_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_o6_off";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Bunu görmemen gerekiyordu.";
			link.l1 = "Hata raporu hazırlama zamanı.";
			link.l1.go = "exit";
		break;
		
        case "native":
			dialog.text = "Uh-oh! Ta'kahi, genç adam. Kaba olmak istemem ama buraya nasıl girdin? Hanımefendiye burada kaldığım süre boyunca mekanı kapatmasını şiddetle tavsiye etmiştim.";
			link.l1 = "Gerçekten de, vay halimize. Seni buraya nasıl aldılar? Neden bu genelev hâlâ öfkeli, Tanrı’dan korkan insanlar tarafından yakılmadı?";
			link.l1.go = "native_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Panama");
		break;
		
        case "native_1":
			dialog.text = "Altın doblonlar tüm yolları açar ve beyaz adamları daha mutlu eder. Bunu bilmiyor muydun?";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+" Versailles'in o eski havasını neredeyse burnumda hissedebiliyorum, seni içeri o kadar sessizce aldıkları anı hatırlıyorum.";
			}
			link.l1 = "Bana öyle konuşma, kızarmış surat. Burada yeni olduğum doğru, ama bunu nasıl öğrendiğini bilmiyorum. Seni olduğun yerde vurabilirim ve gecemi telafi etmek için başka bir kızı bulurum.";
			link.l1.go = "native_var1";
			link.l2 = "Kim sana bu saçmalığı söyledi bilmiyorum, ama lafı güzelce çeviriyorsun, hakkını vermek lazım. Böylesine eğitimli bir yerliliği ilk kez görüyorum.";
			if (HasSubStr(pchar.model, "Sharle")) {
				link.l2 = link.l2+" Versailles, benim kıçım!";
			}
			link.l2.go = "native_var2";
		break;
		
        case "native_var1":
			dialog.text = "Hayır, Kaptan, hiçbir şey bilmiyorsunuz. Burada tamamen güvendeyim... şimdilik. Ama madem bu kadar çabuk samimi olduk, bir daha deneyelim. İçki?";
			link.l1 = "Bunu yapabilirim, kesinlikle ilgimi çektin.";
			link.l1.go = "native_play";
		break;
		
        case "native_var2":
			dialog.text = "Bravo! Görüyorum ki şimdiden birbirimize isimle hitap ediyor ve laf atıyoruz. Şimdi, barışa içip iş konuşmayı öneriyorum.";
			link.l1 = "Bunu yapabilirim, kesinlikle ilgimi çektin.";
			link.l1.go = "native_play";
		break;
		
        case "native_play":
			dialog.text = "Bu yerin amacını düşününce, yorumunuz beni epey endişelendiriyor Kaptan! Burada neredeyse bir aydır mahsur kaldım. Aklıma gelen her şeyi denedim, artık can sıkıntısı ve anlamsızlıktan duvarlara tırmanacak hale geldim.";
			link.l1 = "O zaman git. Bir değişiklik yapıp bir kiliseye uğra... gerçi seni içeri almazlar.";
			link.l1.go = "native_play_1";
		break;
		
        case "native_play_1":
			dialog.text = "O kadar basit değil, çünkü... sözleşmem gereği bu genelevde yirmi dört saat daha geçirmek zorundayım.";
			link.l1 = "Kulağa korkunç geliyor, elbette, ama benden acıma bekleme. Bir ay boyunca genelevi tamamen kiralamak, gerçek bir hayalin gerçekleşmesi!";
			link.l1.go = "native_play_2";
		break;
		
        case "native_play_2":
			dialog.text = "Arzularından kork, Kaptan. Buraya nasıl geldiğini bilmiyorum, çünkü bu ayı yalnız geçirmem gerekiyordu. Kadınlar ve şarapla baş başa, ama üçüncü gün civarında sadece şarapla idare edebildim. Ve bugün, ondan da bıktığım gündü.";
			link.l1 = "Peki, benden ne yapmamı istiyorsun? Bir sürü kız ve şarap mı paylaşayım seninle?";
			link.l1.go = "native_play_3";
		break;
		
        case "native_play_3":
			dialog.text = "Belki, ama önce bir kumar oynayalım derim! Kart başına bin gümüş! Bu arada, adım Agueybana.";
			link.l1 = "Benimki "+GetFullName(pchar)+". Tabii, oynayalım.";
			link.l1.go = "native_accept";
			link.l2 = "Benimki "+GetFullName(pchar)+" . Bin peso mu? Fena değil. Bir düşüneyim, ama söz vermiyorum.";
			link.l2.go = "native_decline";
		break;
		
        case "native_play_again":
			dialog.text = "Fikrini mi değiştirdin, kaptan? Devam edelim mi?";
			link.l1 = "Tabii ya, neden olmasın.";
			link.l1.go = "native_accept";
			link.l2 = "Henüz değil.";
			link.l2.go = "native_decline";
		break;
		
        case "native_decline":
			DialogExit();
			
			NextDiag.CurrentNode = "native_play_again";
		break;
		
        case "native_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1");
		break;
		
        case "native_cards_loss":
			dialog.text = "Oyun için teşekkürler, kaptan. İyi hissettirir sanmıştım ama olmadı. Lütfen beni yalnız bırak – bir şekilde bugün de kendi başıma idare ederim. Kahrolası herif!";
			link.l1 = "Hepsi bu mu? Doğrusu, hayal kırıklığım bu kadar çok para kaybetmenin acısından bile daha büyük.";
			link.l1.go = "native_cards_loss_1";
		break;
		
        case "native_cards_loss_1":
			dialog.text = "Burada olman bile gerekmiyordu, kaptan. Ama neyin peşinde olduğumuzu öğrenmek istiyorsan... kıtada eski bir tapınak ara. Ve yanında bolca tuunich kaane' bulunsun. Al, bir tane de benden.";
			link.l1 = "Bir yılan taşı mı? Deliği olan bir taş gerçekten de buraya uygun. Teşekkürler, Agueybana";
			link.l1.go = "native_cards_loss_2";
		break;
		
        case "native_cards_loss_2":
			dialog.text = "Elveda, kaptan.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game1LossGoAway");
		break;
		
        case "native_cards_win":
			dialog.text = "Vay canına! Teşekkür ederim, kaptan! Paraya yazık oldu ama en azından hayatın tadını yeniden aldım!";
			link.l1 = "Evet, böyle bir rotadan bu kadar heyecanlanan birini ilk kez görüyorum. Bu arada, o kadar parayı nereden buldun?";
			link.l1.go = "native_cards_win_1";
		break;
		
        case "native_cards_win_1":
			dialog.text = "Eşitine asla sormayacağın kadar kaba bir soru bu, kaptan! Ama gece daha genç, ve cebimde hâlâ epeyce param var. Bir rövanş ister misin?";
			link.l1 = "Neden olmasın? Hadi bir tane daha yapalım!";
			link.l1.go = "native_cards_win_2";
		break;
		
        case "native_cards_win_2":
			dialog.text = "Bu sefer zar oynayalım ve biraz daha yüksek oynayalım derim. Sana anlatacak bir hikayem de var, o yüzden ikimiz için üst katta bir oda kiralar mısın? Burada fazla kulak var! Odayı ödeyip Madam'a gidersen çok sevinirim. Maalesef benim hesabım sana yetmiyor.";
			link.l1 = "Burada mı oda kiralayacaksınız? Hem de iki kişilik mi? Lanet olsun sana, Agueybana! Ben gidiyorum buradan!";
			link.l1.go = "native_cards_rematch_decline";
			link.l2 = "Ah, neyse ne. Bu hikaye ya güzel bir anı olarak bitecek ya da çok pahalı bir kan banyosuna dönüşecek. Kılıcım bende kalıyor, o yüzden saçmalık yok, ha-ha! Burada bekle, ben halledeceğim.";
			link.l2.go = "native_cards_rematch_accept";
		break;
		
        case "native_cards_rematch_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinNoRematch");
		break;
		
        case "native_cards_rematch_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinRematch");
		break;
		
        case "native_dice":
			dialog.text = "Ee?";
			link.l1 = "Umarım beni buraya sadece içki ve kumar için çağırdın.";
			link.l1.go = "native_dice_1";
		break;
		
        case "native_dice_1":
			dialog.text = "Endişelenme kaptan, böyle saçmalıklarla ilgilenmiyorum! Gerçi, ilk gün burada belirseydin... ha ha! Başlayalım mı?";
			link.l1 = "Fortes fortuna adiuvat!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game2");
		break;
		
        case "native_dice_win":
			dialog.text = "Vay canına! Bu harika hissettiriyor! Zaferiniz kutlu olsun, Kaptan.";
			link.l1 = "Abartma. Şimdi bana burada neler olup bittiğini anlatmanın zamanı geldi, değil mi?";
			link.l1.go = "native_dice_story";
			link.l2 = "Garipsin, Agueybana. Şimdi, eğer buradan hemen ayrılmazsam, hem bir asilzade hem de bir erkek olarak itibarım sonsuza dek zedelenecek. Gümüşümü ver ve yollarımızı ayıralım.";
			link.l2.go = "native_dice_win_not_story";
		break;
		
        case "native_dice_loss":
			dialog.text = "Ne yazık, günü bambaşka bir şekilde bitirmeyi umuyordum...";
			link.l1 = "Hayatımda ilk kez bir adamın bu kadar sıradan bir oyunu kazandığı için bu kadar sinirlendiğini görüyorum. En azından artık bana burada neler olup bittiğini açıklayabilir misin?!";
			link.l1.go = "native_dice_story";
			link.l2 = "Siktir git, Agueybana! Artık buna tahammülüm kalmadı!";
			link.l2.go = "native_dice_loss_not_story";
		break;
		
        case "native_dice_story":
			dialog.text = "Elimden geldiğince, kaptan. Aslında buna hakkım var mı bilmiyorum ama yine de, son birkaç günümü aydınlattınız... Bu genelevde, yani.";
			link.l1 = "Ve bu ne hakkındaydı?";
			link.l1.go = "native_dice_story_1";
		break;
		
        case "native_dice_story_1":
			dialog.text = "Boşver... Dinle beni, beyaz adam! Ben, Taino halkının büyük reisi Agueybana'yım. Bazen yüz yıl önce doğmuş olmayı ve İspanyol istilacıları adalarımdan kovmayı hayal ediyorum! Ama onun yerine, üç bin kabile üyemi on altın dublon karşılığında madene sattım.";
			link.l1 = "Değerli bir hayat hikayesi. Birden seni vurup burada, bu ekşi, şarap kokan bataklıkta çürümeye bırakmak istedim, Agueybana.";
			link.l1.go = "native_dice_story_2";
		break;
		
        case "native_dice_story_2":
			dialog.text = "Ne yaparsan yap, kaptan. Tek istediğim senin gibi olmaktı.";
			link.l1 = "Beni mi kastediyorsun?";
			link.l1.go = "native_dice_story_3";
		break;
		
        case "native_dice_story_3":
			dialog.text = "Sizin gemilerinizi gördüm – insan dehasının harikaları – ve kendime bir tane istemişimdir. Sizin dar korseler içindeki kadınlarınızı gördüm, ve birini kendi ellerimle çıkarmayı hayal ettim. Sizin en beceriksiz komutanlarınızın bile bizim liderlerimizin hayal bile edemeyeceği bir güce sahip olduğunu izledim. Avrupa hakkında ve insanların sadece hayatta kalmak yerine yaşadığı o büyük taş evler hakkında hikayeler duydum. Ve hepsini yaşadım! Dahası, geçen yıl Avrupa'ya bile gittim ve bütün bunları gördüm!";
			link.l1 = "Çok fazla şarap içtin, reis. Avrupa'ya tek biletin zincirlerle olurdu, Vatikan'ın ve sokak göstericilerinin keyfine. Bahsettiğin şey, yaşadığımız dünyada imkânsız.";
			link.l1.go = "native_dice_story_4";
		break;
		
        case "native_dice_story_4":
			dialog.text = "İşte yaşadığımız dünya bu, kaptan. Bana çoktan dünyamızın yanlış, hayali olduğu ve her şeyin mümkün olabileceği söylendi.";
			link.l1 = "Sana bunu kim söyledi, o akıllı bıdık kimmiş? Görünen o ki, seni genelevlere olduğu kadar tımarhanelere de alıyorlarmış!";
			link.l1.go = "native_dice_story_5";
		break;
		
        case "native_dice_story_5":
			dialog.text = "Hikayemin asıl noktasına geliyoruz şimdi. Burada işlerin nasıl yürüdüğünü biliyorsun, değil mi? İspanyollar ve İngilizler savaş esirlerimizi silah, alet ve barutla satın alıyor. Ben de kendi kabile halkımı senin paranın karşılığında aldım. Sence neden böyle oldu?";
			link.l1 = "Beni aydınlatmak üzere olduğunu hissediyorum.";
			link.l1.go = "native_dice_story_6";
		break;
		
        case "native_dice_story_6":
			dialog.text = "Yalnızca tanrılar en derin ve en utanç verici arzularımızı yerine getirebilir. Eğer istediğin hayatı yaşayamıyorsan, kaderine müdahale etmeleri için onlardan yardım iste. Sadece onlar en derin ve en gizli arzularımızı gerçekleştirebilir. Yol budur. Ama işte mesele şu: Tanrılarımızın neredeyse hepsi çoktan öldü ve hayatta olsalar bile altınla hiç ilgilenmezlerdi. Neyse ki doğa boşluk sevmez ve eski piramitlerden birinde yeni bir tanrı ortaya çıktı. Kim olduğun onun umurunda değil: yerli ya da Avrupalı, kötü ya da kahraman – yeter ki öde, istediğini alırsın! Bunu bütün kabileler bilir, senin bazı adamların da. Ben de altınla bedelimi ödedim ve sizin gibi yaşadım. Yarın bir yıl olacak.";
			link.l1 = "Hangi tanrı? Bir yılda Avrupa'ya gidip döndün mü? Ve yolculuğunun en ilginç anısı Karayipler'deki berbat bir genelev miydi? Aman neyse. Sarhoşun masalına benziyor, ben de öyle kabul ediyorum. Hadi bir içki içelim ve hikayene devam et.";
			link.l1.go = "native_dice_story_7";
		break;
		
        case "native_dice_story_7":
			dialog.text = "Sana anlattığım her şey doğruydu. Anlatacak başka bir şeyim yok.";
			link.l1 = "Bizim dünyamızda yeterince uzun süre yaşamadın, Agueybana. Her içkiyle beslenen hikaye, hele ki bir genelevde sarhoşken anlatılıyorsa, mutlaka bir dersle bitmeli. Salonu hakkıyla bitirmeden önce kesinlikle biraz felsefe yapmalıyız.";
			link.l1.go = "native_dice_story_8";
		break;
		
        case "native_dice_story_8":
			dialog.text = "Genelde nasıl biterler?";
			link.l1 = "Sen bilmiyor musun? Tabii ki katılımcının cinsiyetine bağlı! Erkeklerle yumruk dövüşü, kadınlarla yatak muhabbeti. Ama bazen modaya göre tam tersi de olur. Yani, masalının ahlâkı ne? Para mutluluk getirmez mi diyorsun? Sıkıcı!";
			link.l1.go = "native_dice_story_9";
		break;
		
        case "native_dice_story_9":
			dialog.text = "Bu, senin dediğin gibi, hikayemin ana fikri değil. Ama madem sen başlattın, şunu söylemem gerek: Senin fikrine katılmıyorum. Tam tersine, paranın mutluluk getirdiğine ve insanları daha iyi yaptığına inanıyorum.";
			link.l1 = "Saçmalık! Şimdi kendinle çelişiyor gibisin. Kendi halkını ticaretle büyük bir servet topladın. Ne kadar kâr ettiğini hatırlıyor musun? Neredeyse otuz bin altın sikke? Bir düşün istersen, ama bana göre paranın sana mutluluk getirmediği ortada. Yine de bu güzel odayı parayla aldın.";
			link.l1.go = "native_dice_story_10";
		break;
		
        case "native_dice_story_10":
			dialog.text = "Pekala, ilk baştaki fikrimi düzelteceğim: para hayatı ve insanları daha iyi yapar.";
			link.l1 = "Bu daha iyi, ama bunun insanları daha iyi yaptığına neden inanıyorsun? Yani artık erdemin timsali misin? Peki ya fazla parası olmayanlar? Onları kötü insanlar olarak mı damgalayacağız?";
			link.l1.go = "native_dice_story_11";
		break;
		
        case "native_dice_story_11":
			dialog.text = "Biliyor musunuz kaptan, bu sohbeti gerçekten takdir ediyorum. Bir kez daha açıklamama izin verin: para hayatı ve insanları daha iyi yapar, ama yalnızca içinde zaten bir nebze erdem taşıyanları.";
			link.l1 = "Dinleyin, dinleyin! Demek sende hiç kıvılcım yok, öyle mi?";
			link.l1.go = "native_dice_story_12";
		break;
		
        case "native_dice_story_12":
			dialog.text = "Hayır. Ben halkımın lideriydim ve para bir yana, güç insanı kesinlikle yozlaştırır. Biliyor musun, kaptan? Şimdi sana bakıyorum da, bir gün sen de aynı ikilemle karşılaşacaksın.";
			link.l1 = "Tanrın sana kehanet yeteneği de mi verdi? O zaman Santiago'ya gitmelisin, orada her türlü medyum ve falcıya özellikle ilgi gösterdiklerini duydum.";
			link.l1.go = "native_dice_story_13";
		break;
		
        case "native_dice_story_13":
			dialog.text = "Salonumuzu... öhöm, kavga ya da yatak muhabbetine girmeden bitirelim lütfen. Hikayeme bir ders bulamadım, bu yüzden onun yerine bir kadeh kaldırmak istiyorum.";
			link.l1 = "Tamamen kayboldun, şef. Ama bir konuda haklısın. Hadi bir içki içelim!";
			link.l1.go = "native_dice_story_14";
		break;
		
        case "native_dice_story_14":
			dialog.text = "İsteklerimizin her zaman ihtiyaçlarımızla örtüşmesine! Teşekkür ederim Kaptan, bu... akşamımız için güzel bir son oldu. Eğer hikayemin doğruluğunu bir gün sınamak istersen, kıtaya git ve orada eski bir tapınak bul. Yanında yüz on üç tuunich kaane' götür. Bende doksan dokuz tane kaldı - al onları, ve elveda!";
			link.l1 = "Deliklerle dolu bir taş yığını mı? Buraya gayet uygun. Akşam için teşekkürler, Agueybana. Seni tekrar görecek miyim?";
			link.l1.go = "native_dice_story_15";
		break;
		
        case "native_dice_story_15":
			dialog.text = "Hayır, yapmayacaksın. Hoşça kal, kaptan.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_BuyAmulets");
		break;
		
        case "native_dice_win_not_story":
			dialog.text = "Anladım, kaptan. İyi ya da kötü, sana hazineyle ilgili bir ipucu vereceğim. Sonuçta, son günlerimi... Yani bu genelevdeki zamanımı aydınlattın. Anakarada eski bir tapınak ara ve oraya bir yığın tuunich kaane' götür. Al, sana bir tane vereyim.";
			link.l1 = "Bir yılan taşı mı? Ne hoş, ve deliği olan bir taş buraya kesinlikle uyuyor. Senin muamelen yeter artık!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_loss_not_story":
			dialog.text = "Üzgün olduğunu anlıyorum, kaptan. İyi ya da kötü, sana hazineyle ilgili bir ipucu vereceğim. Sonuçta, son günlerimi aydınlattın... Bu genelevde, yani. Büyük topraklarda eski bir tapınak ara ve oraya bir yığın tuunich kaane' götür. Al, sana bir tane vereyim.";
			link.l1 = "Bir yılan taşı mı? Ne hoş, ve delikli bir taş gerçekten de buraya yakışıyor. Senin davranışlarından artık bıktım!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_not_story":
			dialog.text = "Hoşça kal, kaptan.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotBuyAmulets");
		break;
		
		case "joruba":
			dialog.text = "Bir tane daha mı? Allah kahretsin, sizlerden bıktım artık!";
			link.l1 = "A-a-ah! Defol!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_1";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_1":
			dialog.text = "Ha? Evet, doğru. Önümde eğil, ölümlü! Piramidimin gücüne tanık ol!";
			link.l1 = "(çaresizce bağırır)";
			link.l1.go = "joruba_2";
			link.l2 = "(canavarı öldür)";
			link.l2.go = "joruba_3";
		break;
		
		case "joruba_2":
			dialog.text = "Doğru. Mütevazı factoríama hoş geldiniz, kaptan.";
			link.l1 = "Sen... sen de kimsin?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_3":
			DialogExit();
			
			NextDiag.CurrentNode = "joruba_3_next";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_3_next":
			dialog.text = "Sabrınız için sizi takdir ediyorum. Sıradaki hamleniz ne olacak, kaptan? Biraz ticaret yapmaya ne dersiniz?";
			link.l1 = "Sen... sen nesin?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_4":
			dialog.text = "Ne olduğumun bir önemi yok, önemli olan yaptığım iş. Şu anda, bu delikteki sakinlerle karşılıklı çıkar için ticaret anlaşmaları yapıyorum.";
			link.l1 = "Fare deliği mi? Şu tapınaktan mı bahsediyorsun?";
			link.l1.go = "joruba_6";
			
			AddDialogExitQuestFunction("ChickenGod_JorubaToNormal");
		break;
		
		case "joruba_6":
			dialog.text = "Your first and final warning, captain! However, this pyramid is indeed rather cramped; obviously, I've outgrown it.";
			link.l1 = " Ticaret dediniz. Ne tür bir ticaretten bahsediyorsunuz? ";
			if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
				link.l1.go = "joruba_7A";
			} else {
				link.l1.go = "joruba_7";
			}
		break;
		
		case "joruba_7":
			dialog.text = "İnsanlara en çok ihtiyaç duyduklarını veririm.";
			link.l1 = "Dilek mi gerçekleştiriyorsun? Masal kahramanı bir cin gibi mi? Aman Tanrım, burada neler oluyor?!";
			link.l1.go = "joruba_7_1";
		break;
		
		case "joruba_7_1":
			dialog.text = "Saçmalama! Ben sadece insanlara bu dünyaya ne için geldilerse onu en hızlı ve en keyifli şekilde elde etmelerinde yardımcı oluyorum.";
			link.l1 = "Sen bir şaman falan mısın?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_7A":
			dialog.text = "Agueybana ile tanıştın ya, bu sana bazı fikirler verebilir.";
			link.l1 = "Şu zavallı, kaybolmuş ve sarhoş Hintli senin işin miydi?";
			link.l1.go = "joruba_7A_1";
		break;
		
		case "joruba_7A_1":
			dialog.text = "Onun kabilesini birkaç bin pound altına satan ben değildim, boğazından fıçı fıçı içkiyi aşağıya indiren de ben değildim, ve kesinlikle yüzlerce fahişeden bilinen ve bilinmeyen her türlü hastalığı kapmaya onu zorlayan da ben olmadım. Beni bir beyaz aristokrata dönüştürmemi o istedi, ben de yaptım. Kaderinin bana buyurduğu gibi.";
			link.l1 = "Dilek mi gerçekleştiriyorsun? Masal cinleri gibi mi? Aman Tanrım, burada neler oluyor?!";
			link.l1.go = "joruba_7A_2";
		break;
		
		case "joruba_7A_2":
			dialog.text = "Saçmalama! Ben sadece insanların bu dünyaya geldikleri şeyi en hızlı ve en keyifli şekilde elde etmelerine yardımcı oluyorum. Agueybana, halkını Avrupalı işgalcilerin boyunduruğundan kurtarmalıydı, ama onun yerine komutanın kızının korsesine fazlasıyla göz dikti ve sonunda kendi onurunu rehin bırakmaya karar verdi.\nO andan itibaren, hayatında kalan tek anlam, yaptığı hatanın derinliğini fark edip yeniden başlamak oldu. Avrupa'da geçen bir yıl, siroz ve ikinizin genelevde geçirdiği zaman buna yardımcı olmuştur mutlaka. Ama kabul etmeliyim, harika bir tatil geçirdi, ha ha!";
			link.l1 = "Siroz mu dedin? Sen bir şaman falan mısın?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_8":
			dialog.text = "Ya da başka bir şey. Ama teklifimi beğeneceksin. Hem, bu sefer yardım etmekten gerçekten memnun olacağım.";
			link.l1 = "Peki. Ne kadar?";
			link.l1.go = "joruba_9A";
			link.l2 = "Neden? Ben özel miyim?";
			link.l2.go = "joruba_9B";
		break;
		
		case "joruba_9A":
			dialog.text = "Fena değil, kaptan. Ya akıllısın ya da eşek kadar aptalsın, ama şansın az da olsa arttı. Fiyat artık sorun olmayacak.";
			link.l1 = "Birini öldürmemi mi istiyorsun? Onu yapmam.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_9B":
			dialog.text = "Çünkü bu hayattaki amacın, benim iyi bir dostumu delik deşik etmek, ha ha!";
			link.l1 = "Birini öldürmemi mi istiyorsun? Onu yapmam.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_10":
			dialog.text = "İlk olarak, evet. İkinci olarak, dört büyük ve dört küçük iş yapacağız. Her biri seni çok daha güçlü kılacak ve bu acımasız, tuhaf dünyada şansını artıracak. Eğer hepsini başarırsan, bir gün tanrılarla bile eşit şartlarda savaşabileceğine garanti veriyorum, sıradan ölümlülerden bahsetmiyorum bile.";
			link.l1 = "Kulağa eğlenceli geliyor. Anlat bakalım.";
			link.l1.go = "joruba_11";
		break;
		
		case "joruba_11":
			dialog.text = "Akıllıca bir seçim! Genelde konuşmalarım Blueweld'e kalp krizi şüphesiyle taşınan insanlarla biter, ama sen gayet iyi dayanıyorsun. İşte görev listesi: halletmeni beklediğim birkaç takas işi var. Son tarih yok, hehe.";
			link.l1 = "İlginç. Listeyi sonra okurum. Başka bir şey var mı?";
			link.l1.go = "joruba_12";
		break;
		
		case "joruba_12":
			dialog.text = "Evet, ilk büyük anlaşma bu. Fiyatı iki bin dublon.";
			link.l1 = "Belki kabul ederim... Ama bu çok para! Neden bu kadarına ihtiyacın var? Peso olarak ödeyebilir miyim?";
			link.l1.go = "joruba_13";
			link.l2 = "Sen deli misin? O parayla bir fırkateyn alabilirim!";
			link.l2.go = "joruba_insult";
		break;
		
		case "joruba_13":
			dialog.text = "Piramitin onarıma ihtiyacı var - duvar taşları bazen müşterilerin başına düşüyor ve bu iş için hiç iyi değil. Adamlarım her gün yamamaya çalışıyor, ama bu durumu kökten çözmek için örgütümüzün dışarıdan acil bir para desteğine ihtiyacı var. Peso'lara gelince - onlara pek güvenmiyorum, çünkü kurları epey dalgalı.";
			link.l1 = "Dürüst pesolara karşı oldukça haksızlık ediyorsun... Bir dakika, burada yalnız değilsin, değil mi?";
			link.l1.go = "joruba_14";
		break;
		
		case "joruba_14":
			dialog.text = "Hayır, ben sadece ciddi bir örgütün vitrinindeyim. Peki, var mısın?";
			link.l1 = "Düşüneceğim, ama önce bu kadar yüklü bir meblağ karşılığında ne alacağımı bilmek isterim.";
			link.l1.go = "joruba_15";
		break;
		
		case "joruba_15":
			dialog.text = "Sürprizi neden bozayım ki? Hem, o parayı vergi olarak düşün. Asıl değerli kazancın, bir sonraki fırsatların kapısını açmak olacak. Ödüller ise inanılmaz olacak. Üstelik eşsizler, unutma, başka hiçbir yerde bulamazsın!";
			link.l1 = "Pekala. Adın neydi tekrar?";
			link.l1.go = "joruba_16";
		break;
		
		case "joruba_16":
			dialog.text = "Aruba, muhteşem ada. Son bir şey daha, "+pchar.name+", piramide giriş günde sadece bir kez izinlidir. Diğer müşterileri bekletme ve beni boş yere rahatsız etme.";
			link.l1 = "Bir kuyruk oluştuğunu görmüyorum... Elveda, majesteleri.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			AddDialogExitQuestFunction("ChickenGod_GiveFirstTask");
		break;
		
		case "joruba_wait":
			dialog.text = "Ah, kaptan. Benim için ne getirdin?";
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1.Completed") && PCharDublonsTotal() >= 2000) {
				link.p1 = "Here are your doubloons. It's hard enough to carry that damned metal around... but it is even harder to part with it!";
				link.p1.go = "joruba_p1";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2.Completed") && GetCharacterItem(pchar, "cannabis7") >= 15) {
				link.p2 = "I kept my end of the bargain. Here's your herb, Aruba.";
				link.p2.go = "joruba_p2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed") && ChickenGod_FindQuestShips()) {
				for (i = 0; i < questShipsNum; i++) {
					sTemp = "p3_" + (i + 1);
				
					chref = GetCharacter(questShips[i]);
					sld = GetRealShip(sti(chref.ship.type));
					link.(sTemp) = "Aruba, ahoy! " + GetStrSmallRegister(XI_ConvertString(sld.BaseName)) + " '" + chref.Ship.Name + "' is all yours!";
					link.(sTemp).go = "joruba_p3_ship_" + questShips[i];
					if (FindCompanionShips(SHIP_PINK) && sti(pchar.questTemp.ChickenGod.Tasks.Schyot) <= 1 && startHeroType != 4)
					{
						link.(sTemp) = "Aruba, ahoy! Pink '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_PinkOtkaz";
					}
					/*if (FindCompanionShips(SHIP_GALEON_SM))
					{
						link.(sTemp) = "Aruba, ahoy! Galeon '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_HolyMercy";
					}*/
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_p4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Lady") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Completed")) {
				link.o2 = "I am bringing you a bride and troubles with the Spanish authorities, sir. The lady is taking a stroll outside, well protected by my men. I will not give her to you until you convince me of the nobility of your intentions.";
				link.o2.go = "joruba_o2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3.Completed") && GetCharacterFreeItem(pchar, "cirass4") >= 1) {
				link.o3 = "Here's your armor, Aruba. Make sure my reward will make up for it.";
				link.o3.go = "joruba_o3";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4.Completed") && GetPrisonerQty() >= 30) {
				link.o4 = "I have the prisoners you asked for.";
				link.o4.go = "joruba_o4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5.Completed") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.p2 = "I brought you your junk. Here, a hundred and thirteen stones, just like you asked for.";
				link.p2.go = "joruba_o5";
			}
			
			bOk = (PCharDublonsTotal() >= 25000) || (ChickenGod_HaveOfficers());
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.Completed") && bOk) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_o6";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.respec = "(Respec character's stats)";
				link.respec.go = "joruba_respec";
			}
			
			link.exit = "I am just passing by.";
			link.exit.go = "joruba_wait_1";
			
			NextDiag.TempNode = "joruba_wait";
		break;
		
		case "joruba_wait_1":
			dialog.text = "Bir dahaki sefere o zaman.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "joruba_p1":
			dialog.text = "Fena değil, o altını iyi değerlendireceğim. Al, bu küçük süs eşyası bir zamanlar çok erdemli bir Taíno reisininmiş. Altın yığınlarını taşımana yardımcı olur. Ona bayağı yaramıştı, heh-heh...";
			link.l1 = "Teşekkür ederim, umarım pişman olmam. Sıradaki anlaşma ne?";
			link.l1.go = "joruba_p1_1";
			link.l2 = "Bir dakika. Sana bir yığın altın verdim ve karşılığında bir avuç çamur mu aldım? Güzel, o zaman paramı geri istiyorum!";
			link.l2.go = "joruba_insult";
			
			RemoveDublonsFromPCharTotal(2000);
			pchar.questTemp.ChickenGod.Gold = 2000;
			
			pchar.questTemp.ChickenGod.Tasks.p1.Completed = true;
			GiveItem2Character(pchar, "talisman13");
			//Log_info("You received Taino Figurine");
			PlaySound("interface\important_item.wav");
		break;
		
		case "joruba_p1_1":
			dialog.text = "Ha? Evet, sıradaki anlaşma. Bu altın şimdilik yeter, şimdi biraz daha manevi kazançları düşünmenin vakti geldi. Kendime bir çare bulmalıyım.";
			link.l1 = "Neden, kendini iyi hissetmiyor musun?";
			link.l1.go = "joruba_p1_2";
		break;
		
		case "joruba_p1_2":
			dialog.text = "Ruhum öyle. Bak, o Engizisyon olayı yüzünden rahipler artık mütevazı piramidime uğramıyor, bu yüzden daha geleneksel yöntemlere başvurmak zorundayız. Bana, yani aslında faktoryama, işlerimizin devamı için on beş magarosa bitkisi lazım.";
			if (!ChickenGod_TalkedToAmelia()) {
				link.l1 = "Bu bir ot mu?";
			} else {
				link.l1 = "Ne olduğunu biliyorum, heh-heh.";
			}
			link.l1.go = "joruba_p1_3";
		break;
		
		case "joruba_p1_3":
			dialog.text = "Dürüst olacağım - bu, büyük değeri olan nadir bir ot. Tüm takımadada yıllarını harcamaya gerçekten hazır mısın, iyi düşün.";
			link.l1 = "Söz veremem, ama sana sağlıklı günler dilerim ve ot için alacağım ödülün buna değmesini umarım.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveSecondTask");
		break;
		
		case "joruba_p2":
			dialog.text = "All right, I am officially calling it my day off! A bargain such as this is worth a real treasure. Behold!\nThis machete was once this close to splitting that imbecile Kanek's head! Therefore, it's very dear to me and I humbly ask you to take good care of it. It's old, but crafted extremely well; they don't make steel like this anymore.";
			link.l1 = "Kanek mi? O da kim?";
			link.l1.go = "joruba_p2_1";
			
			TakeNItems(pchar, "cannabis7", -15);
			pchar.questTemp.ChickenGod.Tasks.p2.Completed = true;
			if (pchar.rank >= 21)
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 80.0;
			}
			else
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 60.0;
			}
			GiveItem2Character(pchar, "machete2");
			//Log_info("You received Machete Conquistador");
			PlaySound("interface\important_item.wav");
			SetAlchemyRecipeKnown("bullet_double");
			SetAlchemyRecipeKnown("grapeshot_double");
			ChickenGod_InitAmmo();
		break;
		
		case "joruba_p2_1":
			dialog.text = "Ah, siz ikiniz tanışacaksınız. Umarım el emeğini küçümseyen o kendini beğenmiş ukalalardan biri değilsindir? Eğer öyleysen, şansın yok, çünkü ödülün ikinci kısmı çift doldurulmuş cephane şemaları.";
			if (pchar.HeroParam.HeroType == "HeroType_4") {
				link.l1 = "Ah, onları severim. Ama onları özel kılan ne? Çifte barut yükü yeni bir şey değil, demek ki sen müze palasından beri piramidinden dışarı adım atmamışsın.";
			} else {
				link.l1 = "Hepsi bu mu? Hey...";
			}
			link.l1.go = "joruba_p2_2";
		break;
		
		case "joruba_p2_2":
			dialog.text = "Akıllılık taslama ve dinle! Her aptal bir fıçıya iki avuç barut koyup kör olmayı, yüzünü yakmayı ya da burnunu kırmayı göze alabilir. Ben sana küçük bir sihir numarası sunuyorum: Barutun kalitesini dikkatlice kontrol et, doğru kıvama kadar öğüt, içine bir mermi ya da saçma koy, üstüne de doğranmış bir dublon ekle. O patlama, zırhı bile paramparça eder!";
			link.l1 = "Parayla ateş etmek ha? Tam da senin tarzın.";
			link.l1.go = "joruba_p2_3";
		break;
		
		case "joruba_p2_3":
			dialog.text = "Çekilmezsin! Peki, bir el havanı ve yanında bir düzine el bombası al. Madem bu kadar akıllısın, el bombası şemalarını da kendi başına hemen bulursun!";
			link.l1 = "Çok teşekkür ederim, efendim. Sırada ne var?";
			link.l1.go = "joruba_p2_4";
			
			//Log_info("You received Hand mortar");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "mortairgun");
			TakeNItems(pchar, "grenade", 10);
		break;
		
		case "joruba_p2_4":
			dialog.text = "Bunu pek sevmeyeceksin. Bir gemiye ihtiyacım var... hayır, o gemiye ihtiyacım var. Hani, arkasında bir hikaye olanlardan.";
			link.l1 = "Neden? Sen daha kaptan bile değilsin.";
			link.l1.go = "joruba_p2_5";
		break;
		
		case "joruba_p2_5":
			dialog.text = "Sana ne! Sen ödülüne odaklan, çünkü istersem seni bu piramidi tepeden tırnağa temizletirim, yine de bana borçlu kalırsın!";
			link.l1 = "Sen kesinlikle bir kaptan değilsin, yoksa bir geminin yanaşmak için bir iskeleye ya da koya ihtiyacı olduğunu bilirdin. Nasıl oluyor da gemiyi senin piramidinin içine sokmamı bekliyorsun?!";
			link.l1.go = "joruba_p2_6";
		break;
		
		case "joruba_p2_6":
			dialog.text = "Piramitimin arkasında dev bir göl fark ettin mi hiç? Aynen öyle. Filodaki doğru gemiyi yakına yanaştır, gerisini adamlarım halleder. Şimdi defol buradan, sırayı tutuyorsun.";
			link.l1 = "Elbette. Hoşça kal!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveThirdTask");
		break;
		
		case "joruba_p3":
			sld = GetCharacter(sti(companion));
			pchar.questTemp.ChickenGod.Tasks.p3.ship = sld.ship.type;
			RemoveCharacterCompanion(pchar, sld);
			AddPassenger(pchar, sld, false);
						
			npchar.ship.type = pchar.questTemp.ChickenGod.Tasks.p3.ship;
			SetCharacterShipLocation(npchar, "Temple");
						
			sld = GetRealShip(sti(pchar.questTemp.ChickenGod.Tasks.p3.ship));
					
			dialog.text = "Güzel! Anladım!";
			link.l1 = "Akıllı geçinmeyi bırak da, ödülümü ver!";
			link.l1.go = "joruba_p3_1";
			switch (sti(sld.BaseType)) {
				case SHIP_MAYFANG:
					dialog.text = "Ya diğer ikisi? Onları kendine saklayamaz mıydın? Heh-heh.";
				break;
				
				case SHIP_MIRAGE:
					dialog.text = "Ya diğer ikisi? Onları kendine saklayamaz mıydın? Heh-heh.";
				break;
				
				case SHIP_VALCIRIA:
					dialog.text = "Ya diğer ikisi? Onları kendine saklayamaz mıydın? Heh-heh.";
				break;
				
				case SHIP_FRIGATE_L:
					dialog.text = "Vay canına, onu kendine saklamak istememene şaşırdım. İşte buna hikayesi olan bir gemi derim! Kahretsin William... Keşke eve dönüp hep hayalini kurduğun o büyük bankayı kursan.";
				break;
				
				case SHIP_CORVETTE_QUEST:
					sTemp = "privateer";
					if (isMainCharacterPatented()) {
						sTemp = GetStrSmallRegister(GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)));
					}
					
					dialog.text = "Şuna bak hele! Görevinin yüz karasısın, "+sTemp+"!";
				break;
				
				case SHIP_POLACRE_QUEST:
					dialog.text = "Charlie Prince eski piramidimdeki suçlayıcı kanıtlardan kurtulmaya mı karar verdi? Bunu onaylıyorum!";
				break;
				
				case SHIP_ECLIATON:
					dialog.text = "Amiral, amiral gemisinin kaybını üstlerinize açıklamak size kolay gelsin. Ah, pardon, artık Genel Vali oldunuz.";
				break;
				
				case SHIP_CURSED_FDM:
					dialog.text = "Batıl inançlı bir aptal mısın, yoksa sadece aptal mı? O servet değerinde! Adil bir takas olduğundan emin değilim, ama neyse.";
				break;
				
				case SHIP_FDM:
					dialog.text = "Sen batıl inançlı bir ahmak mısın, yoksa sadece ahmak mı? O servet değerinde! Adil bir takas olduğundan emin değilim ama neyse.";
				break;
				
				case SHIP_RENOVATED_FDM:
					dialog.text = "Batıl inançlı bir ahmak mısın yoksa sadece ahmak mı? O servet değerinde! Bunun adil bir takas olduğundan emin değilim ama neyse.";
				break;
				
				case SHIP_ELCASADOR:
					dialog.text = "İyi karar! Kastilyanları severim, biliyor musun. Belki işim bitince onu onlara geri veririm.";
				break;
				
				case SHIP_HIMERA:
					dialog.text = "Gerçekten de kalpsizsiniz, Kaptan. Bu gemi ihanetten kokuyor. Onu alıyorum.";
				break;
				
				case SHIP_PINK:
					if (startHeroType == 4)
					{
						dialog.text = "Bu geminin bir geçmişi olabilir... ama elde etmesi fazla kolay olmadı mı? Neyse. Senin durumun farklı, canım, bu yüzden kabul ediyorum. En azından gençliğimden bazı anıları hatırlatıyor.";
						Achievment_Set("ach_CL_127");
					}
					else 
					{
						dialog.text = "Evet, bu geminin bir geçmişi olabilir... ama elde etmesi biraz fazla kolay olmadı mı? Neyse, boşver. Tamam Kaptan, bu seferlik görmezden geleceğim, çünkü listedeki işleri gayet iyi hallettin. Alıyorum. En azından gençliğimden bazı anıları canlandırıyor.";
					}
				break;
				
				case SHIP_GALEON_SM:
					dialog.text = "Papazı gördün mü? Neyse, yakında tanışırsın. Çift atışlık tabanca mermilerinden bolca almanı tavsiye ederim. O da işe yaramazsa, bir tahta kazık dene.";
				break;
				
				case SHIP_LADYBETH:
					dialog.text = "Papazı gördün mü? Görüşeceksin. Çift atışlık tabanca mermilerinden bolca almanı tavsiye ederim. O da işe yaramazsa, bir tahta kazık dene.";
				break;
				
				case SHIP_MEMENTO:
					dialog.text = "Papazı gördün mü? Neyse, yakında tanışırsın. Çift atışlık tabanca mermisi stoklasan iyi olur. O da işe yaramazsa – bir tahta kazık dene.";
				break;
			}
		break;
		
		case "joruba_p3_PinkOtkaz":
			dialog.text = "Evet, bu geminin bir geçmişi olabilir... ama elde etmesi fazla kolay olmadı mı? Yok artık! Hâlâ yapılacaklar listende bir sürü işin var. Onları bitirdiğinde, bu fedakârlığı tekrar konuşuruz.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "joruba_p3_1":
			dialog.text = "Seni kutsuyorum, "+GetFullName(pchar)+" . Deniz sana dost olsun. Şimdi, bir sonraki alışverişimizi konuşalım...";
			link.l1 = "Ne? Ne diyorsun? Akıl çağında köylü aptalları bile böyle saçmalıklara kanmaz! Sadaka kutuna bir kuruş bile atmadım, sana tam teşekküllü bir savaş gemisi verdim!";
			link.l1.go = "joruba_insult";
			link.l2 = "Bir saniye bekle. Senin kutsaman benim için tam olarak ne anlama geliyor?";
			link.l2.go = "joruba_p3_2";
			
			pchar.questTemp.ChickenGod.Tasks.p3.Completed = true;
		break;
		
		case "joruba_p3_2":
			dialog.text = "Artık komuta ettiğin her geminin gövdesi daha sağlam olacak, düşmanların ise tam tersi. Ayrıca, denizde zaman senin için daha yavaş akacak. Ve eğer bu bile şu lanet yeri dizlerinin üstüne çökertmene yetmiyorsa, en iyisi babana gidip parasını geri iste!";
			link.l1 = "Eğer işe yaramazsa, yemin ederim bu gece geri gelip piramidini yakarım! Şimdi, bir sonraki anlaşmadan bahset!";
			link.l1.go = "joruba_p3_3";
			notification("+10% hull defence", "None");
			notification("+10% damage to enemy ships hull", "None");
			notification("+5% speed on the Global Map", "None");
			PlaySound("Interface\new_level.wav");
		break;
		
		case "joruba_p3_3":
			dialog.text = "Buna alışmaya başladın, değil mi kaptan? Ne yazık ki, ben de öyleyim. Ofis olarak bu piramidi seçmemin sebebini sanıyorsun?";
			link.l1 = "Muhtemelen cadı avı hâlâ devam ettiği için?";
			link.l1.go = "joruba_p3_4";
		break;
		
		case "joruba_p3_4":
			dialog.text = "Heh-heh, hayır, tam olarak değil. İşimi burada yürütüyorum çünkü en iyi anlaşmalar kan gerektirir. Bu piramit kan ister. Ben kan isterim. Hep böyleydi, böyle de olacak.";
			link.l1 = "Bunu aklından bile geçirme, sen bir canavarsın. Senin öldürmen için kurbanlar teslim etmeyeceğim!";
			link.l1.go = "joruba_p3_5";
		break;
		
		case "joruba_p3_5":
			dialog.text = "Ve sen kaç kişiyi öldürdün, ha? Bekle, sana tam sayısını bile söyleyeyim: şahsen sen öldürdün "+(Statistic_AddValue(pchar,"Solder_s",0)+Statistic_AddValue(pchar,"Citizen_s",0)+Statistic_AddValue(pchar,"Warrior_s",0)+Statistic_AddValue(pchar,"Solder_g",0)+Statistic_AddValue(pchar,"Citizen_g",0)+Statistic_AddValue(pchar,"Warrior_g",0))+" insanlar! Hırsınız ve servet arzunuz uğruna bir ceset dağı yığdınız! ";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+"Kardeşinin borcu, ortalama bir Avrupa savaşından daha fazla insanın ölümüne sebep oldu! ";
			}
			dialog.text = dialog.text+"Burada bana ahlak dersi vermeye kalkma, hele ki ben seni yargılamayacakken. Kimilerinin başarısı her zaman başkalarının trajedisiyle ödenir, tanrılar da, ah tanrılar, izler ve paylarını alırlar!";
			link.l1 = "Şu anda sana bir cevap veremem... Buradan çıkmam lazım.";
			link.l1.go = "joruba_p3_6";
		break;
		
		case "joruba_p3_6":
			dialog.text = "Kafanı toparlamaya acil mi ihtiyacın var? Peki, önce beni dinle. Sana güç ve bedeninle zihnin üzerinde tam kontrol vereceğim, eğer bana değerli bir adam getirirsen. Sıradan biri değil, sokaklarda kaybolmuş silik bir fare ya da pis kokulu ambarlardan bir sıçan değil. Bana seni takip eden ve trajikomedyanda önemli bir rol oynayan bir adam getir.";
			link.l1 = "Subaylarımdan biri mi? Daha ne kadar alçalabilirsin, Aruba! Eğer bu duyulursa...";
			link.l1.go = "joruba_p3_7";
		break;
		
		case "joruba_p3_7":
			dialog.text = "Gizliliği her zamanki gibi ben hallederim. Ve yine sızlanmaya başlamadan önce, sana başka bir yol daha olduğunu söyleyeyim.";
			link.l1 = "Bu da ne demek oluyor? Yani kendi adamlarımı zorla nikah masasına sürüklemem gerekmiyor mu?";
			link.l1.go = "joruba_p3_8";
		break;
		
		case "joruba_p3_8":
			dialog.text = "Hayır, ama diğer seçeneği beğenmeyeceksin. Kanla ödemek istemiyorsan, altınla ödeyebilirsin. Üç bin doblon ve huzurlu bir vicdan. Para bunu da yapar, daha fazlasını da – bayılıyorum!";
			link.l1 = "Elveda, Aruba. Artık seninle konuşmak istemiyorum.";
			link.l1.go = "joruba_p3_9";
		break;
		
		case "joruba_p3_9":
			dialog.text = "Beni nerede bulacağını biliyorsun.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveFourthTask");
		break;
		
		case "joruba_p4":
			dialog.text = "Bunu İspanyol Engizisyonu gelmeden çabucak halledelim. Sangre u oro?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Altın olsun. Al, üç binin burada, ama bu ıssız yerde bu kadar büyük bir parayı nasıl harcayacağını gerçekten aklım almıyor.";
				link.l1.go = "joruba_p4_1";
			}
			if (ChickenGod_HaveOfficers()) 
			{
				link.l2 = "Kan.";
				link.l2.go = "joruba_p4_other";
			}
			link.l3 = "Boş ver.";
			link.l3.go = "exit";
		break;
		
		case "joruba_p4_1":
			dialog.text = "...";
			link.l1 = "İşin bitti mi? Şimdi ödülümden konuşalım.";
			link.l1.go = "joruba_p4_reward_1";
			RemoveDublonsFromPCharTotal(3000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 3000;
		break;
		
		case "joruba_p4_other":
			dialog.text = "Öyle olsun. İsmi söyle.";
			
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Irons");
		break;
		
		case "joruba_p4_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand bir subay değil, acımasız bir paralı asker, bu yüzden başka bir kurban seç.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Bağışını kabul ediyorum. İzlemek zorunda değilsin.";
			link.l1 = "Hayır, bilmiyorum. Bir saat sonra ödülümü almak için geri geleceğim.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_p4_reward";
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
		break;
		
		case "joruba_o6_money":
			dialog.text = "Harika bir seçim. Sunağın üstündeki bütün o kanı temizlemekten nefret ediyorum, bu yüzden altın daha iyi. Al, bu iksir – iyi bir dostumdan sana bir hediye.";
			link.l1 = "Tadı hiç de fena değil...";
			link.l1.go = "exit";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			RemoveDublonsFromPCharTotal(25000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 25000;
			
			if (sti(pchar.questTemp.ChickenGod.Gold) >= 30000) {
				Achievment_Set("ach_CL_87");
			}
			
			notification("+3 P.I.R.A.T.E.S. point", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_p4_reward":
			dialog.text = "";
			link.l1 = "İşin bitti mi? Şimdi ödülümden konuşalım.";
			link.l1.go = "joruba_p4_reward_1";
		break;
		
		case "joruba_p4_reward_1":
			dialog.text = " Kaderini değiştirmek istediğinde benimle istediğin zaman konuşabilirsin. ";
			link.l1 = "Ama bu benim için tam olarak ne anlama geliyor?";
			link.l1.go = "joruba_p4_reward_2";
		break;
		
		case "joruba_p4_reward_2":
			dialog.text = "Kendine hakim ol! Bir gün dene, çok seveceksin. Bu arada, sana sıradaki anlaşmadan bahsedeyim. En önemlisinden.";
			link.l1 = "Artık buna değip değmeyeceğinden emin değilim!";
			link.l1.go = "joruba_p4_reward_3";
			link.l2 = "Hadi ama, söyle artık.";
			link.l2.go = "joruba_p4_reward_3";
		break;
		
		case "joruba_p4_reward_3":
			dialog.text = "Kaderini değiştirmekle kalmayıp, çağımızın dahileri ve tanrılarıyla yan yana durma fırsatın var. Evet, artık bedenini ve zihnini istediğin kadar değiştirebilirsin, ama asla kendi sınırlarının ötesine geçemezsin; çünkü sıradan bir insan her konuda mükemmel olamaz. Benim önerim, o sınırları aşman.";
			link.l1 = "Bunun bana maliyeti ne olacak? Daha fazla kan mı? Altın mı?";
			link.l1.go = "joruba_p4_reward_4";
		break;
		
		case "joruba_p4_reward_4":
			dialog.text = "Evet. Ya bana yirmi beş bin doblon getirirsin ya da arkadaşlarından birini. İşimiz bittiğinde başka bir anlaşma olmayacak.";
			link.l1 = "Biraz düşüneceğim.";
			link.l1.go = "joruba_p4_reward_5";
		break;
		
		case "joruba_p4_reward_5":
			dialog.text = "Beni nerede bulacağını biliyorsun. Ve kaderini değiştirmek istediğinde, ne zaman istersen beni ziyaret etmekten çekinme.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			
			pchar.questTemp.ChickenGod.Tasks.p4.Completed = true;
			AddDialogExitQuestFunction("ChickenGod_GiveFifthTask");
		break;
		
		case "joruba_respec":
			dialog.text = "Dediğiniz gibi olsun.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ChickenGod_Respec");
		break;
		
		case "joruba_o2":
			dialog.text = "Öncelikle, o benim karım, gelinim değil. İkincisi, senin derdin Kastilyalılarla, benimle değil. Ve son olarak, onu zaten aldım ve adamlarını gönderdim. Şerefli niyetlere gelince... Şuna bir bak, ben tam anlamıyla saygın bir centilmen değil miyim? Tlazolteotl, ona da bir gün gerçek bir kadın nasip etsin. Ya da bir erkek.";
			link.l1 = "Siktir git, Aruba!";
			link.l1.go = "exit";
			
			notification("+ 10 HP, + 10 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(10.0);
			pchar.questTemp.ChickenGod.Tasks.o2.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			sld = CharacterFromID(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
			LAi_SetCitizenTypeNoGroup(sld);
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o3":
			dialog.text = "Fena değil, teşekkür ederim. Açıkçası, buna pek ihtiyacım yok ama belki bir salonda ya da başka bir yerde takarım. İştar adına seni kutsuyorum. Şimdi git ve günah işle.";
			link.l1 = "Ne tuhaf bir his...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o3.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			TakeItemFromCharacter(pchar, "cirass4");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o4":
			dialog.text = "Onları alacağım. Ne var? Benim de senin gibi mürettebatımda ölü adamlara ihtiyacım var, ama senden farklı olarak meyhanelerde dolaşıp adam toplayamıyorum. Şimdi, Bast, kahramanı gelecekteki işlerinde korusun.";
			link.l1 = "Ne tuhaf bir his...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o4.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
			
			AddDialogExitQuestFunction("ChickenGod_RemovePrisoners");
		break;
		
		case "joruba_o5":
			dialog.text = "Evet, onları yine dağıtmamız gerekecek, çünkü insanlar sürekli kaybediyor ve bizim de müşterilere ihtiyacımız var. Freya, bu büyük taş koleksiyoncusunu koru.";
			link.l1 = "Ne tuhaf bir his...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o5.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6":
			dialog.text = "Bunu İspanyol Engizisyonu gelmeden çabucak halledelim. Sangre u oro?";
			
			if (PCharDublonsTotal() >= 25000)
			{
				link.money = "Here's your gold, you greedy bastard.";
				link.money.go = "joruba_o6_money";
			}
			
			if (ChickenGod_HaveOfficers())
			{
				link.blood = "Blood.";
				link.blood.go = "joruba_o6_blood";
			}
			link.l3 = "Boş ver.";
			link.l3.go = "exit";
		break;
		
		case "joruba_o6_blood":
			dialog.text = "Adı söyle.";
			
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Irons");
			
			if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Helena");
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Mary");
			}
		break;
		
		case "joruba_o6_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Mary" || pchar.questTemp.ChickenGod.Sacrifice == "Helena") {
				pchar.questTemp.ChickenGod.Tasks.o6.gf = true;
				sTemp = "future wife";
				sld = CharacterFromID(pchar.questTemp.ChickenGod.Sacrifice);
				if (sld.lastname == pchar.lastname) {
					sTemp = "current wife";
				}
				
				dialog.text = "Bu oldukça cazip, ama bu seferlik bir istisna yapacağım - fedakarlığını kabul etmeyeceğim. Bunu kimseye söylemeyeceğim "+sTemp+", muhtemelen yapmam gerekse de. Unutma, onsuz hiçbir şeysin. Şimdi kaybol ve bugün beni rahatsız etme.";
				link.l1 = "";
				link.l1.go = "exit";
				
				AddDialogExitQuestFunction("ChickenGod_KickedFromTemple");
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand bir subay değil, acımasız bir paralı asker, bu yüzden başka bir kurban seç.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Olsun. Al, bu iksiri al – iyi bir dostumdan sana bir hediye.";
			link.l1 = "Tadı hiç de fena değil...";
			link.l1.go = "joruba_o6_reward";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			notification("+3 P.I.R.A.T.E.S. points", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6_reward":
			dialog.text = "Bir dahaki sefere kadar, kaptan.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.OnExitKick = true;
		break;
		
		case "joruba_final":
			dialog.text = "Sonunda, her şey bitti!";
			link.l1 = "Ha?";
			link.l1.go = "joruba_final_1";
		break;
		
		case "joruba_final_1":
			dialog.text = "Burada işimiz bitti, Kaptan. Anlaşmalar yapıldı, herkes memnun, geri ödeme için yer yok. Ofisimiz kapanıyor ve başka bir yere taşınıyor.";
			link.l1 = "Bir dakika bekle, Aruba. Sana bolca altın verdim, kan döktüm, bu şeytani inine kadınlar ve esirler getirdim. Karayipler'de olup biten doğaüstü olaylarla başa çıkabilirim. Ama seninle yaptığımız 'alışverişler' her türlü mantığın ötesinde. Lütfen açıkla.";
			link.l1.go = "joruba_final_2";
		break;
		
		case "joruba_final_2":
			dialog.text = "You know what? I'll tell you.\nI'm fed up with this world, and I want out. Every day, it's the same old routine: an ancient pyramid with a crumbling ceiling, those loathsome identical palm trees, and a never-ending stream of captains, each with their own ingenious ideas. Yes, I provide people with what they desire; it's my calling, and I take pride in it. But by the gods, how I detest all of you!";
			link.l1 = "Seni burada tutan biri mi var? Çıkış tam orada, dahiyane!";
			link.l1.go = "joruba_final_3";
		break;
		
		case "joruba_final_3":
			dialog.text = "Kesinlikle haklısın, artık kimse beni burada tutmuyor. Artık değil. Ve bunun hepsi senin sayende, dostum.";
			link.l1 = "Bu ani bir fikir değişikliği oldu. Bir hikaye bekliyordum, ama şimdiye kadar duyduğum tek şey, tozlu bir piramitteki aşağılık küçük bir tanrının anlamsız saçmalıkları.";
			link.l1.go = "joruba_final_4";
		break;
		
		case "joruba_final_4":
			dialog.text = "Eh, herkesin arada bir içini dökmeye ihtiyacı vardır, değil mi? Buraya geldiğine gerçekten sevindim çünkü sayende nihayet bu dünyadan ayrılabileceğim. Altın, tayfa, teçhizat ve bir gemi, dostum. Hatırlıyor musun? Tanıdık geldi mi? Tek ihtiyacım olan buydu ve hepsini sen sağladın.";
			link.l1 = "Rica ederim. Yine de, tuhaf konuşma tarzını ve neredeyse ilahi güçlerini bu açıklamıyor. Eğer gerçekten bu kadar güçlüysen, kendi gemini, tayfanı ve altınlarını çoktan yaratabilirdin!";
			link.l1.go = "joruba_final_5";
		break;
		
		case "joruba_final_5":
			dialog.text = "Gördüğün gibi, ben de öyle yaptım. Herkesin kendi yöntemi var.";
			link.l1 = "Ama bu da ne? Sen kimsin, tam olarak?";
			link.l1.go = "joruba_final_6";
		break;
		
		case "joruba_final_6":
			dialog.text = "Pekala... ben de zaten bunu yaparım. Yeni dünyada görüşürüz, "+GetPersonaName()+". Umarım bir dahaki sefere gerçekten yeni bir şey olur. Teşekkürler ve hoşça kal.";
			link.l1 = "Hayır, seni bir daha asla görmek istemiyorum.";
			link.l1.go = "exit";
			link.l2 = "O zaman görüşürüz, Aruba... bu ilginçti.";
			link.l2.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_FinalGood");
		break;
		
		case "joruba_insult":
			dialog.text = "Anlaşılan tüm anlaşmalar bozuldu. Gitme vakti, kaptan.";
			link.l1 = "Sıra sende, defol...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Insult");
		break;
		
		case "ChickenGod_TheInquisition_1":
			dialog.text = "İspanyol Engizisyonu adına, adını söyle!";
			link.l1 = "Kaptan "+GetFullName(pchar)+". Ve dedikleri doğru, kimse İspanyol Engizisyonu'nu beklemez...";
			link.l1.go = "ChickenGod_TheInquisition_2";
		break;
		
		case "ChickenGod_TheInquisition_2":
			dialog.text = "... Bu şaka her zaman yerini bulur, gerçi epey masum Hristiyanı kazığa göndermiştir.";
			link.l1 = "...";
			link.l1.go = "ChickenGod_TheInquisition_3";
		break;
		
		case "ChickenGod_TheInquisition_3":
			dialog.text = "Şaka yapıyorum, Kaptan. Siz şaka yaptınız, ben de yaptım. Benim adım Padre Emilio Bocanegra ve bu Mesih’in askerleri benim silahlı korumalarım.";
			link.l1 = "Size nasıl yardımcı olabilirim, padre?";
			link.l1.go = "ChickenGod_TheInquisition_4";
		break;
		
		case "ChickenGod_TheInquisition_4":
			dialog.text = "Aruba adında bir señor tanıyor musun?";
			link.l1 = "Evet, kısa bir süre öncesine kadar bu eski piramitte yaşıyordu.";
			link.l1.go = "ChickenGod_TheInquisition_5";
		break;
		
		case "ChickenGod_TheInquisition_5":
			dialog.text = "Orada yaşadığını mı söylüyorsun? Orada yaşamak mümkün mü? Ve neden 'kısa bir süre öncesine kadar' diyorsun?";
			link.l1 = "Bu señor bizi birkaç dakika önce bir gemide bıraktı.";
			link.l1.go = "ChickenGod_TheInquisition_6";
		break;
		
		case "ChickenGod_TheInquisition_6":
			dialog.text = "Bunu nereden biliyorsun? En yakın koy günlerce uzakta!";
			link.l1 = "Bu göl göründüğünden daha büyük olmalı. Sana başka bir açıklama sunamıyorum, padre.";
			link.l1.go = "ChickenGod_TheInquisition_7";
		break;
		
		case "ChickenGod_TheInquisition_7":
			dialog.text = "Genel Valiliğin topraklarında garip şeyler oluyor.";
			link.l1 = "Buralar İngiliz toprakları, padre.";
			link.l1.go = "ChickenGod_TheInquisition_8";
		break;
		
		case "ChickenGod_TheInquisition_8":
			dialog.text = " Bırak sapkınlar böyle düşünmeye devam etsin. Biz de elbet hakkımızı geri alacağız. Bu kadar çok soru sorduğum için beni affet, oğlum: Santiago bana bu piramit... ve önceki sakini hakkında resmi bir soruşturma yürütmemi emretti.";
			link.l1 = "Tam olarak ne oldu, padre?";
			link.l1.go = "ChickenGod_TheInquisition_9";
		break;
		
		case "ChickenGod_TheInquisition_9":
			dialog.text = "Bu dava muhtemelen kapanacağı için, sana küçük bir hikaye anlatabilirim.\nBir süredir bu yerle ilgili söylentiler tüm ana karada dolaşıyor. Bölge tarihinde önemli izler bırakmış bazı kişilerin geçmişte buraya düzenli olarak geldiklerine dair güvenilir raporlar almıştık.\nAncak Santiago, Panama olayı sonrası bu söylentilere gerçekten kulak vermeye başladı.\nBir Hintli, o görkemli şehirde epey bir yankı uyandırmış ve hatta oldukça felsefi birkaç vaaz vermişti. Ne yazık ki, Panama'nın sakinleri bu olaydan yüzeysel sonuçlar çıkardılar ve kendilerini bu piramidin akıl almaz hazineler barındırdığına ve her dileği yerine getirdiğine inandırdılar.\nElbette bu, en saf haliyle sapkınlıktı... Bu yüzden bazı Panamalı sakinlere ve bu Hintli Aguebana'ya karşı dava açmak zorunda kaldık.";
			link.l1 = "Panama yetkilileri neden buna göz yumdu?";
			link.l1.go = "ChickenGod_TheInquisition_10";
		break;
		
		case "ChickenGod_TheInquisition_10":
			dialog.text = "Her zamanki gibi, böyle durumlarda büyülendiklerini iddia ettiler. Bu yasal boşluk, Aguebana'yı sorgulayabilseydik kapanabilirdi, ama o aniden öldü.";
			link.l1 = "Nasıl öldü?";
			link.l1.go = "ChickenGod_TheInquisition_11";
		break;
		
		case "ChickenGod_TheInquisition_11":
			dialog.text = "Onu sarhoşluk öldürdü. Ancak ölümü sorunlarımızı çözmedi, çünkü sapkınlık tüm takımadada kök salmıştı ve yüzlerce insan bu eski tapınağa adeta bir tür hac yolculuğuna çıktı.";
			link.l1 = "Burada daha önce hiç bu kadar kalabalık görmemiştim... Yani ne, Aruba'yı işgal edip onu yargılamaya mı götürecektin?";
			link.l1.go = "ChickenGod_TheInquisition_12";
		break;
		
		case "ChickenGod_TheInquisition_12":
			dialog.text = "Elbette hayır, oğlum. Engizisyonun hükmü serttir ama adildir. Bir yargılama için mutlaka geçerli bir sebep olmalı. Hayır, ben sadece señor Aruba'nın ifadesini alıp Santiago'ya götürecektim.";
			link.l1 = "Eh, bu senin için talihsizlik olmuş.";
			link.l1.go = "ChickenGod_TheInquisition_13";
		break;
		
		case "ChickenGod_TheInquisition_13":
			dialog.text = "Ne olacağını asla bilemezsin, oğlum. Her şey Allah'ın takdiri.";
			link.l1 = "Hoşça kal, padre.";
			link.l1.go = "ChickenGod_TheInquisition_14";
		break;
		
		case "ChickenGod_TheInquisition_14":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Temple", "reload2", false);
			LAi_SetActorType(npchar);
			//LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "ChickenGod_TheInquisitionLeave", -1);
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition = "ChickenGod_TheInquisitionLeave";
		break;
		
	}
} 

void ChickenGod_InitAmmo() {
	if(LoadSegment("items\initItems.c")) {
		InitGunExt(		 "pistol1", "t3", 	 "bullet_double",               "", 100.0, 300.0,    0.0,  0, 0,  20, 0);
		InitGunExt( 	 "pistol2", "t2", "grapeshot_double",               "",  60.0, 160.0,      0.0,  1, 0,  20, 0);
		InitGunExt(		 "pistol3", "t2", "grapeshot_double",               "",  80.0, 180.0,    0.0,  1, 2,  20, 0);
		InitGunExt(		 "pistol4", "t3",    "bullet_double",               "",  70.0, 270.0,     0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol5", "t3", 	 "bullet_double",               "", 130.0, 330.0,     0.0,  0, 2,  30, 0);
		InitGunExt(		 "pistol6", "t3",    "bullet_double",               "", 100.0, 300.0,     0.0,  0, 0,  20, 0);
		InitGunExt(		 "pistol8", "t4", "grapeshot_double",               "",  50.0, 100.0,    5.0,   1, 0,  20, 0);
		InitGunExt(		 "pistol9", "t3", 	 "bullet_double",               "", 100.0, 320.0,     0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol10", "t3",   "bullet_double",               "", 140.0, 280.0,    0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol11", "t3",   "bullet_double",               "",  10.0, 700.0,   40.0,   0, 0, 100, 0);
		InitGunExt(		 "pistol12", "t3",   "bullet_double",               "",  80.0, 290.0,    0.0,   0, 0,  20, 0);
		InitGunExt(		 "pistol13", "t3",   "bullet_double",               "", 130.0, 300.0,  15.0,    0, 0,  30, 0);
		InitGunExt(		 "howdah",  "t3", "grapeshot_double",	            "",  50.0, 140.0,   5.0,    1, 0,  30, 0);
		InitGunExt(		 "pistol14", "t3",   "bullet_double",               "", 130.0, 330.0,   0.0,    0, 4,  34, 0); // Дуэльный двухзарядный пистоль cle 1.3
		
		InitGunExt(		"mushket1", "t3",    "bullet_double",      			"", 240.0, 440.0,  0.0,    0, 0,  20, 0);
		InitGunExt(		"mushket2", "t3", 	 "bullet_double",      			"", 270.0, 470.0,  0.0,    0, 0,  15, 0);
		InitGunExt(		"mushket5", "t3", 	 "bullet_double",      			"", 400.0, 600.0,  15.0,   0, 0,  15, 0);
		InitGunExt(		"mushket7", "t3", 	 "bullet_double",      			"", 300.0, 440.0,   0.0,   0, 0,  18, 0); // Качественный мушкет cle
		InitGunExt(		"mushket8", "t3", 	 "bullet_double",      			"", 200.0, 400.0,  0.0,    0, 0,  20, 0); // Четырехзарядный штуцер cle
		InitGunExt(	  "mushket2x2", "t3", 	 "bullet_double",      			"", 360.0, 560.0,  15.0,   0, 0,  15, 0);
		
		InitGunExt(		"mushket3", "t2", "grapeshot_double",	            "", 140.0, 240.0,    0.0,    1, 0,  13, 0);
		InitGunExt(		"mushket6", "t3", "grapeshot_double",	            "", 180.0, 310.0,  20.0,   1, 0,  15, 0);
		InitGunExt(		"mushket9", "t3", "grapeshot_double",	            "", 140.0, 240.0,   0.0,   1, 0,  23, 0);
		InitGunExt(	  "mushket10",  "t3", 	 "bullet_double",      			"", 360.0, 440.0,   0.0,   0, 0,  21, 0);
		
		UnloadSegment("items\initItems.c");
	}
	
	CGInitGrapeGunExt(	"pistol2",	"t2",		3,		50,		4.25,	5.0,	3);		// трёхствольный дробовик, двойной заряд
	CGInitGrapeGunExt(	"pistol3",	"t2",		4,		40,		6.0,	5.0,	4);		// тромбон, двойной заряд
	CGInitGrapeGunExt(	"pistol8",	"t4",		4,		110,	5.0,	3.0,	2);		// бландербуз, двойной заряд
	CGInitGrapeGunExt(	"howdah",	"t3",		3,		85,		3.0,	5.5,	2);		// гауда, двойной заряд
	CGInitGrapeGunExt(	"mushket3",	"t2",		3,		60,		6.0,	3.0,	3);		// аркебуза, картечь
	CGInitGrapeGunExt(	"mushket6",	"t3",		3,		90,		4.0,	3.5,	2);		// башенный мушкетон, картечь
	
	ref itm;
	
	makeref(itm, items[FindItem("mushket9")]);
	
	itm.type.t3.basedmg  = 3;
	itm.type.t3.shards  = 110;
	itm.type.t3.width   = 8.5;
	itm.type.t3.height  = 7.85;
	itm.type.t3.area    = XI_ConvertString("grapes_area_4");
		
	if(CheckAttribute(itm, "UpgradeStage"))
	{
		int iUpgradeStage = sti(itm.UpgradeStage);
		
		switch (iUpgradeStage)
		{
			case 2:	
				itm.type.t3.basedmg  = 3;
				itm.type.t3.shards  = 120;
				itm.type.t3.width   = 7.0;
				itm.type.t3.height  = 5.75;
				itm.type.t3.area    = XI_ConvertString("grapes_area_4");
			break;
			
			case 3:	
				itm.type.t3.basedmg  = 4;
				itm.type.t3.shards  = 130;
				itm.type.t3.width   = 5.5;
				itm.type.t3.height  = 4.5;
				itm.type.t3.area    = XI_ConvertString("grapes_area_3");
			break;
			
			case 4:	
				itm.type.t3.basedmg  = 5;
				itm.type.t3.shards  = 130;
				itm.type.t3.width   = 4.5;
				itm.type.t3.height  = 3.75;
				itm.type.t3.area    = XI_ConvertString("grapes_area_2");
				itm.type.t3.ChargeSpeed = 18;
			break;
		}
	}
}

void CGInitGrapeGunExt(string id, string sAttr, int basedmg, int shards, float width, float height, int dispersion)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).basedmg = basedmg;
	gun.type.(sAttr).shards = shards;
	string sArea = "grapes_area_"+dispersion;
	gun.type.(sAttr).area = XI_ConvertString(sArea);
	gun.type.(sAttr).width = width;
	gun.type.(sAttr).height = height;
}

bool ChickenGod_FindQuestShips() {
	questShipsNum = 0;
	
	for(int i = 1; i < COMPANION_MAX; i++) {
		int index = GetCompanionIndex(pchar, i);
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		int shipIndex = sti(sld.ship.type);
		if (shipIndex == SHIP_NOTUSED) {
			continue;
		}
		
		ref realShip = GetRealShip(shipIndex);
		if (!CheckAttribute(realShip, "QuestShip")) {
			continue;
		}
		
		if (!GetRemovable(sld) || !GetShipRemovable(sld)) {
			continue;
		}
		
		if (CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip")) {
			if (sti(realShip.BaseType) == SHIP_MAYFANG || sti(realShip.BaseType) == SHIP_MIRAGE || sti(realShip.BaseType) == SHIP_VALCIRIA) {
				continue;
			}
		}
		
		questShips[questShipsNum] = sti(sld.index);
		questShipsNum++;
	}
	
	return (questShipsNum > 0);
}

void ChickenGod_AddOfficerLink(aref link, string prefix, string id) {
	if (GetCharacterIndex(id) < 0) {
		return;
	}
	
	if (!CheckPassengerInCharacter(pchar, id)) {
		return;
	}
	
	if (id == "Mary" && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) {
		return;
	}
	
	if (id == "Helena" && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
		return;
	}
	
	sld = CharacterFromID(id);
	
	if (!GetRemovable(sld)) {
		return;
	}
	
	link.(id) = GetFullName(sld) + ".";
	link.(id).go = prefix + id;
}

bool ChickenGod_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}

bool ChickenGod_HaveOfficers() {
	object fakelink;
	
	ChickenGod_AddOfficerLink(&fakelink, "", "Duran");
	ChickenGod_AddOfficerLink(&fakelink, "", "Baker");
	ChickenGod_AddOfficerLink(&fakelink, "", "Folke");
	ChickenGod_AddOfficerLink(&fakelink, "", "Avendel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tonzag");
	if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(&fakelink, "", "Longway");
	ChickenGod_AddOfficerLink(&fakelink, "", "Knippel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tichingitu");
	ChickenGod_AddOfficerLink(&fakelink, "", "Irons");
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
		ChickenGod_AddOfficerLink(&fakelink, "", "Helena");
		ChickenGod_AddOfficerLink(&fakelink, "", "Mary");
	}
	
	return (GetAttributesNum(&fakelink) > 0);
}
