void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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
		
		case "OZ_Kuznets_1":
			//PlaySound("VOICE\Russian\Master_05.wav");
			dialog.text = "Ne istemiştin, "+GetAddress_Form(NPChar)+"? Üzgünüm, ama yeni sipariş alamıyorum. Sadece... çok fazla işim var...";
			link.l1 = "Öyle mi? Duyduğuma göre yakın zamanda bir kart oyununda çok değerli bir şeyini kaybetmişsin, doğru mu?";
			link.l1.go = "OZ_Kuznets_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_2":
			dialog.text = "Eğer buraya alay etmeye geldiysen sıraya gir – sensiz de bunu isteyen yeterince insan var. Ama içlerinden hiçbiri bana yardım teklif etmedi. Kaderim pamuk ipliğine bağlı, tamamen Javier Castillo'ya bağlıyım, diğerleri ise sadece talihsizliğimle dalga geçmek istiyor.";
			link.l1 = "Başkalarının talihsizliğine gülen biri değilim. Anlat bakalım, nasıl oldu? Belki sana yardımcı olabilirim.";
			link.l1.go = "OZ_Kuznets_3";
			link.l2 = "Yardım mı? Neden sana yardım etmeli ki biri? Ben asla etmem. Kendi mutluluğunun da, talihsizliğinin de demircisisin sen. O yüzden mağduru oynamayı bırak – yaptıklarının sonuçlarını kabul et, bundan daha doğal bir şey olamaz.";
			link.l2.go = "OZ_Kuznets_NoAgree";
		break;
		
		case "OZ_Kuznets_NoAgree":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Kuznets_NoAgree");
		break;
		
		case "OZ_Kuznets_3":
			dialog.text = "O akşamın ölümcül olacağı aklımın ucundan bile geçmemişti. Sadece bir kupa rom içmek için meyhaneye uğramıştım; sonuçta Amiral Eugenio de la Torre bizzat benden büyük bir sipariş vermişti. Ama biraz sarhoşken, bir masaya oturup iskambil oynamaya başladım. İşte o anda Javier gözüne beni kestirdi\nBaşta şans benden yanaydı – hatta hatırı sayılır bir miktar kazandım, ama şansıma inanmaya başladığım anda her şey birden değişti. Javier sürekli kupama rom dolduruyordu, ben de kaybediyordum: önce yanımdaki tüm parayı, sonra malzeme için ayırdığım parayı, en sonunda da tüm birikimimi harcadım\nNe kadar kaybettiğimi fark ettiğimde artık geri dönmek için çok geçti. Tek bir düşünceye saplanıp kalmıştım – ne pahasına olursa olsun kaybettiklerimi geri almak. Ve sonra kitabımı ortaya koydum. O alçak Javier ona sadece beş bin peso değer biçti\nElbette değeri çok daha fazla, ama heyecandan gözüm hiçbir şeyi görmüyordu ve kabul ettim. Ve sonra... sanırım gerisini zaten biliyorsun. Kaybettim. Biliyor musun, daha önce hiç başıma böyle bir şey gelmemişti. Sanırım o herif içkime bir şey kattı.";
			link.l1 = "Peki, size nasıl yardımcı olmamı bekliyorsunuz? Masaya oturan sizdiniz, malınızı ortaya koyan sizdiniz, hepsini kaybeden de yine siz oldunuz. Şimdi ise sonuçlarını kabul etmek istemiyorsunuz, öyle mi? Ve bu kitapta sizi bu kadar üzen ne varmış, bu kadar değerli olan ne?";
			link.l1.go = "OZ_Kuznets_4";
		break;
		
		case "OZ_Kuznets_4":
			dialog.text = "Bu kitap, sahip olduğum en değerli şeydi. Yüzyıllardır ustadan çırağa aktarılan sırları barındırıyor. O, demirhanemin kalbi, zanaatımın ruhu. Kaybıyla çoktan yüzleştim, "+GetAddress_Form(NPChar)+", ama kitabı kaybetmekle nasıl barışabilirim? Javier'e kitabı için fidye teklif ettim – beş bin peso\nOnu geri almak için borca girmeye bile razıydım. Ama biliyor musun ne dedi? Yüz bin istedi! Yüz bin, "+GetAddress_Form(NPChar)+"! O kadar param yok. Fiyatı düşürmeyi ya da taksitle almayı da kabul etmiyor. Ona yalvardım... ama sadece bana güldü. Görüyorum ki sen "+GetSexPhrase("cesur bir adam, bir denizci... belki de bir kaptansın. Ve silahın orada sadece gösteriş olsun diye asılı değil","sıradan bir kadın değil, ve kesinlikle her erkeğe bir yol bulabilir")+"\nSana yalvarıyorum, Javier ile konuş. Belki seni dinler ve borcun ödemesini ertelemeye razı olur. Bu kitap olmadan... hayatımın hiçbir anlamı yok. Karşılığında, işlerim düzeldiğinde sana her zaman kaliteli malzemeleri iyi fiyata satabilirim, belki senin için özel bir şey de yaparım, kaptan.";
			link.l1 = "Konuşmakta bir sakınca yok. Ne olacağını göreceğiz. Ama önce kendimi tanıtmama izin verin: adım "+GetFullName(pchar)+", kendi gemimin kaptanıyım.";
			link.l1.go = "OZ_Kuznets_5";
		break;
		
		case "OZ_Kuznets_5":
			dialog.text = ""+GetSexPhrase("Ve ben Sebastian Cordoba...","Kendi gemisinin kaptanı olan bir kadın mı? Böylelerini duydum ama hiçbiriyle yüz yüze karşılaşmadım ya da sohbet etmedim.")+" Sizi tanıdığıma memnun oldum, kaptan "+pchar.lastname+". Ve teşekkür ederim. Şu günlerde başkalarının talihsizliğiyle alay edenleri bulmak, yardım etmeye gönüllü olanlardan daha kolay. Biliyor musunuz, eğer defterim bana geri dönerse yemin ederim: bir daha asla şans oyunları oynamayacağım.";
			link.l1 = "Daha teşekkür edecek bir şey yok. Önce kendi işimi halledeceğim, sonra zamanım kalırsa Javier ile konuşurum.";
			link.l1.go = "OZ_Kuznets_6";
		break;
		
		case "OZ_Kuznets_6":
			dialog.text = "Korkarım çok geç kalmış olabilirsin. Javier, sandığımdan çok daha hızlı davrandı\nKitap için alıcıyı bile bulmuş – Etienne Renoir, Fransız bir usta silahçı. Eğer amiral, benim yüzümden böyle bir hazine Fransızların eline geçtiğini öğrenirse... kafamdan olurum. Hapishane bunun yanında hafif bir ceza olurdu.";
			link.l1 = "Hmm... Pekala. Sorununuzla hemen ilgileneceğim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			AddDialogExitQuestFunction("OZ_Kuznets_Agree");
		break;
		
		case "OZ_Kuznets_repeat":
			dialog.text = "Kaptan "+pchar.lastname+"! Javier ile konuştun mu? Bir haber var mı?";
			link.l1 = "Henüz değil, ama şimdi meyhaneye gidiyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			if (CheckCharacterItem(PChar, "OZ_book"))
			{
				link.l1 = "Konuştum"+GetSexPhrase("","")+". Ve oldukça başarılı bir şekilde. Javier alelacele bu dünyadan ayrıldı, ama ondan önce kitabınızı geri getirmeyi başardı. Buyurun.";
				link.l1.go = "OZ_Kuznets_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "OZ_Kuznets_11":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", bunun benim için ne anlama geldiğini hayal bile edemezsin! Senin sayende tüm siparişleri yetiştirebileceğim, hatta amiralin işini bile! Ne yazık ki param yok, ama yine de senin için bir ödül hazırladım\nAl, bu zırhı al – aslında bir don için yapmıştım ama eminim biraz bekleyebilir. Ayrıca, eğer bir şeyler yapmak istersen işine yarayacak bazı malzemelerim de var.";
			link.l1 = "Teşekkür ederim, "+npchar.name+", çok cömertsiniz!";
			link.l1.go = "OZ_Kuznets_12";
			TakeItemFromCharacter(pchar, "OZ_book");
		break;
		
		case "OZ_Kuznets_12":
			dialog.text = "Bir de, malzemeye ihtiyacın olursa uğra. Tedariklerim ayda bir gelir, bu yüzden her zaman işine yarayacak bir şeyler bulursun – hem de iyi bir fiyata. Sözümden dönmem.";
			link.l1 = "Kesinlikle yapacağım! Peki, "+npchar.name+", kendine iyi bak. Ben gidiyorum, yapacak işlerim var.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Nagrada");
			GiveItem2Character(PChar, "cirass3");
			AddItems(PChar, "jewelry13", 10);
			AddItems(PChar, "jewelry12", 5);
			AddItems(PChar, "jewelry10", 5);
			AddItems(PChar, "jewelry11", 2);
			AddQuestRecordInfo("Useful_Acquaintances", "7");
		break;
		
		case "OZ_Kuznets_Fail":
			dialog.text = "Kaptan "+pchar.lastname+"! Javier ile konuştun mu? Bir haber var mı?";
			link.l1 = "Bakın... kitap benim elimdeydi. Ama... öyle bir durum oldu ki, kitap satıldı.";
			link.l1.go = "OZ_Kuznets_Fail_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_Fail_2":
			dialog.text = "Ne?! Sen... sattın mı?! Benim kitabımı?!";
			link.l1 = "Kart oyununda kaybettiğin kitap. Javier'in söz verdiği o Fransıza satıldı.";
			link.l1.go = "OZ_Kuznets_Fail_3";
		break;
		
		case "OZ_Kuznets_Fail_3":
			dialog.text = "Ama... şimdi her şey bitti. Kitap Fransızlarda, amiralin emri yerine getirilemeyecek... hayatım mahvoldu... ben... ben mahvoldum!";
			link.l1 = "Kendini köşeye sıkıştırdın. Bence bu sana iyi bir ders olacak. Elveda.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Fail");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "OZ_Shuler_1":
			PlaySound("Voice\English\tavern\Igroki v Tavernah-01.wav"); 
			dialog.text = "Hey, "+GetSexPhrase("sailor","tatlım")+", şansını kartlarda denemek ister misin? Otur, burada bahisler hafif... en azından yeni başlayanlar için.";
			link.l1 = "Aradığım kişinin tam olarak sen olduğunu hissediyorum. Sebastian'ı da aynen böyle kandırıp soyup soğana çevirmiştin, değil mi? Onun defterini geri almaya geldim.";
			link.l1.go = "OZ_Shuler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_2":
			dialog.text = "Pekâlâ, harika. Bana yüz bin ver – ve alabilirsin. O kitaba hiç ihtiyacım yok, kerpeteni çekiçten bile ayıramam.";
			link.l1 = "Sana beş bin vereceğim – bu, demirciyi yendiğinde bizzat senin koyduğun fiyattı.";
			link.l1.go = "OZ_Shuler_3";
		break;
		
		case "OZ_Shuler_3":
			dialog.text = "Ha! Beni aptal mı sandın? O kitabın gerçek değerini gayet iyi biliyorum. Yüz bin, bir kuruş eksik olmaz. Yoksa Fransızlara gider – onların parayla hiçbir derdi yok.";
			link.l1 = "İspanyol planlarını Fransızlara sattığını yetkililer görmezden mi gelecek sanıyorsun? Amiral bunu öğrendiğinde öfkeden deliye dönecek.";
			link.l1.go = "OZ_Shuler_4";
		break;
		
		case "OZ_Shuler_4":
			dialog.text = "Ah, hadi ama. Yetkililer bir kitaptan dolayı kimseyle uğraşmaz, zaten başları dertten kurtulmuyor. Amiral mi? Evet, Fransızlardan nefret ediyor, hem de bütün kalbiyle, ama ben onu bekleyecek değilim – o kadar parayla Yeni Dünya’daki herhangi bir kolonide aranan misafir olurum.";
			link.l1 = "O zaman bir anlaşma yapalım. Paranı alacaksın, ama hemen değil. Demirci borcunu taksitle ödeyecek ve kitap bugün ona, kaptanlık onurum adına, geri verilecek. Senin için hiçbir şey değişmiyor – o yine ödeyecek ve sen bir peso bile kaybetmeyeceksin.";
			link.l1.go = "OZ_Shuler_5";
		break;
		
		case "OZ_Shuler_5":
			dialog.text = "Beni dinlemiyorsun galiba. Açıkça söyledim – parayı hemen şimdi istiyorum. Bir hafta sonra değil, bir ay sonra değil, demirci parayı denkleştirince hiç değil, tam şu anda. Bu lanet adadan bir an önce kurtulmayı düşünüyorum. Yani ya paranın tamamı şu an elimde olur, ya da defter Fransızlara gider ve kaptanlık onurunu amiralin celladına rehin bırakırsın.";
			if (sti(pchar.Money) >= 100000 && GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
				link.l1 = "Şöyle yapalım: Oynayalım. Benim yüz binim kitaba karşı. Kazanırsan, adadan zengin bir adam olarak ayrılırsın. Kaybedersen – kitabı alırım. Yoksa sen sadece iskambil destesini hayatında ilk kez görenlerle mi oynuyorsun?";
				link.l1.go = "OZ_Shuler_6";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "OZ_Shuler_6_No_Money";
				AddDialogExitQuestFunction("OZ_GameCards_Fail");
			}
		break;
		
		case "OZ_Shuler_6_No_Money":
			DialogExit();
			Notification_Money(false, 100000, "peso");
			LAi_CharacterDisableDialog(npchar);
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
			Notification_Skill(true, 30, SKILL_SNEAK);
			}
			else
			{
			Notification_Skill(false, 30, SKILL_SNEAK);
			}
		break;
		
		case "OZ_Shuler_6":
			dialog.text = "Ha! Zengin olmama gerek yok – zaten zenginim! Bana bir yığın para getirecek bir şeyi neden riske atayım ki?";
			link.l1 = "Vay vay, Javier Castillo'nun kendisi oynamaya korkuyor mu? Ben de sanmıştım ki"+GetSexPhrase(""," sen")+", sen deneyimli bir oyuncuydun, sarhoş enayilerden para koparan bir üçkağıtçı değil.";
			link.l1.go = "OZ_Shuler_7";
			Notification_Money(true, 100000, "peso");
			Notification_Skill(true, 30, SKILL_SNEAK);
		break;
		
		case "OZ_Shuler_7":
			dialog.text = "Korkmuyorum, sadece zaten ihtiyacım olan her şeye sahipken masada oturmanın bir anlamı görmüyorum.";
			link.l1 = "Aman Tanrım, hadi ama, ilk kez elinde kart tutmayan birine karşı oynamak düşüncesiyle titrediğini görebiliyorum. Dur tahmin edeyim, buradan hemen gitmek istemenin sebebi utanman mı? Herkes zaten senden daha güçlü birini yenemeyeceğini çoktan anladı; sarhoş bir aptaldan başka kimseyi yenemiyorsun.";
			link.l1.go = "OZ_Shuler_8";
		break;
		
		case "OZ_Shuler_8":
			dialog.text = "Sen kim oluyorsun da bana böyle konuşuyorsun?! Seninle aynı masaya oturmayı bile kendine yediremeyenleri bile yendim ben! Öyle büyük oyunlar oynadık ki, kazanılan parayla gemi alınırdı, her oyuncuya da burnu havada bir kaptan düşerdi! Hadi oynayalım. Her karta beş bin, toplamda yüz bin; parası biten kaybeder. Bakalım kim kimi yenecek.";
			link.l1 = "Daha az laf, daha çok iş. Anlaştık.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards");
		break;
		
		case "OZ_Shuler_Win_1":
			dialog.text = "Şeytan! Bu olamaz...";
			link.l1 = "Ne oldu, başkası kazanınca o kadar eğlenceli olmuyor mu?";
			link.l1.go = "OZ_Shuler_Win_2";
		break;
		
		case "OZ_Shuler_Win_2":
			dialog.text = "Sen bir sahtekârsın! Hiçbir şey görmediğimi mi sandın? Beni kandırmana asla izin vermem! Seni parça parça ederim daha iyi.";
			link.l1 = "Bir hile mi? Ha-ha! Kaybetmeyi bilmiyorsun anlaşılan, dostum. Ama sonunla bu kadar aceleyle buluşmak istiyorsan – sana yardımcı olacağım. Silah başına!";
			link.l1.go = "exit";
			pchar.questTemp.OZ_Draka = true;
			AddDialogExitQuestFunction("OZ_GameCards_Duel");
		break;
		
		case "OZ_Shuler_Lose_1":
			dialog.text = "Ha! Pekâlâ, "+GetSexPhrase("kanka","tatlım")+", kazıklanmak nasıl bir his"+GetSexPhrase("","")+"? Kibir ikinci mutluluk derler, ama senin için geçerli değil.";
			link.l1 = "Kendini fazla önemseme. Sadece şansın yaver gitti.";
			link.l1.go = "OZ_Shuler_Lose_2";
		break;
		
		case "OZ_Shuler_Lose_2":
			dialog.text = "Kaybedenler her zaman böyle der. Neyse, oynadın"+GetSexPhrase("","")+" – kaybettin"+GetSexPhrase("","")+", bunu kişisel algılama. Bir gün tekrar yüz bin bulursan, şansını yine deneyebilirsin... Ama sonucun değişeceğinden pek şüpheliyim...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards_Lose");
			AddLandQuestMark(characterFromId("PortSpein_Tavern"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_1":
			dialog.text = "Merhaba, "+GetAddress_Form(NPChar)+" . Ziyaretinizi neye borçluyum?";
			link.l1 = "Selamlar. Ben Kaptan "+GetFullName(pchar)+", ve seninle Javier Castillo hakkında konuşmak istiyorum.";
			link.l1.go = "OZ_Felip_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_2":
			dialog.text = "Hmm... Eğer o serseri sana da borçluysa, korkarım uzun bir sıraya girmek zorunda kalacaksın. Javier hiçbir zaman borçlarını ödemekte acele etmez. Ama eline para geçerse, önce bana ödeyecek – başka seçeneği olmadığından emin oldum.";
			link.l1 = "Neyse ki, ben onun alacaklısı değilim. Size ne kadar borcu var? Ve tam olarak ne gibi önlemler aldınız?";
			link.l1.go = "OZ_Felip_3";
		break;
		
		case "OZ_Felip_3":
			dialog.text = "Borcunun toplam tutarı yüz elli bin peso. Sadece on binini ödemiş, herhalde bunun yeterli olacağına karar vermiş. Ama ona bunun büyük bir hata olduğunu hemen gösterdim. Adamlarım ondan yirmi bin daha aldı. Kalanı bir hafta içinde ödemesi gerekiyor ve sürenin dolmasına az kaldı. Neyse ki, yakında bir kitabı satarak iyi bir para alacağını duydum.";
			link.l1 = "Gerçekten sana borcunu ödeyeceğini mi düşünüyorsun? Bence buna ciddi şekilde güvenmemelisin. Javier, parayı alır almaz buradan kaçacağını gizlemiyor bile.";
			link.l1.go = "OZ_Felip_4";
		break;
		
		case "OZ_Felip_4":
			dialog.text = "Bunun farkındayım, Kaptan. Merak etmeyin, bana ödeme yapmadan kaçamayacağından emin oldum.";
			link.l1 = "Durumu kontrol altında tuttuğunu görüyorum. Yine de tecrübe gösteriyor ki, biraz daha tedbirli olmakta fayda var. Anlayacağın, ben bu işlerde biraz uzman sayılırım"+GetSexPhrase("","ess")+" alacak tahsilatında. Eğer benim sizin adınıza hareket etmeme izin verirseniz, paranızı geri alabilirim.";
			link.l1.go = "OZ_Felip_5";
		break;
		
		case "OZ_Felip_5":
			dialog.text = "Ne yazık ki, Kaptan, bu borcu tahsil etmek bana zaten fazlasıyla pahalıya mal oluyor, bir de sizin hizmetleriniz için ödeme yapacak gücüm yok...";
			link.l1 = ""+UpperFirst(GetAddress_Form(NPChar))+", bunun için endişelenmene gerek yok. Bu konuda benim de çıkarım var, o yüzden sana ücretsiz yardım edeceğim.";
			link.l1.go = "OZ_Felip_6";
		break;
		
		case "OZ_Felip_6":
			dialog.text = "Size sorabilir miyim, tam olarak ilginiz nedir?";
			link.l1 = "Diyelim ki, kart masasında yaptığı bazı numaraları cezasız bırakamam.";
			link.l1.go = "OZ_Felip_7";
		break;
		
		case "OZ_Felip_7":
			dialog.text = "Eğer bana bir maliyeti olmayacaksa, reddetmem için bir sebep göremiyorum. Sadece bir şey var, Kaptan – lütfen fazla ileri gitmeyin. O alçak borcunu ödemeden öte tarafa göçerse, bana hiçbir faydası olmaz.";
			link.l1 = "Endişelenme Felipe, dikkatli davranacağım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
			AddDialogExitQuestFunction("OZ_Felip_2");
			pchar.questTemp.OZ_Dolg = true;
		break;
		
		case "OZ_Felip_again":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! Bunu bu kadar çabuk halletmiş olamazsın, değil mi?";
			link.l1 = "Maalesef, henüz değil. Ama bunun üzerinde çalışıyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
		break;
		
		case "OZ_Shuler_11":
			if (CheckAttribute(npchar, "quest.OZ_Shuler_Lose"))
			{
				dialog.text = "Ah, "+GetSexPhrase("kapitan","tatlım")+" ukala! Yine sen mi? Ne oldu, birkaç bin daha mı kaybetmek istiyorsun?";
			}
			else
			{
				dialog.text = "Yine sen mi? Sana açıkça söyledim: Para masada olacak – yoksa defol git.";
			}
			link.l1 = "Sesini değiştir, Javier. Ve keseni çıkar – buraya boşuna gelmedim. Felipe Alarcon’a olan borcunu unutmadın, değil mi? Artık onun adına ben konuşuyorum. Seçimini yap: ya borcunu hemen ödersin, ya da öteki tarafa gittikten sonra cebinden o parayı ben çıkarırım.";
			link.l1.go = "OZ_Shuler_12";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_12":
			dialog.text = "Lanet olsun sana! Görmüyor musun, burada bir işim var? Birkaç saat sonra gel – o zaman konuşuruz.";
			link.l1 = "Beni duymadın galiba. Açıkça söyledim: Parayı hemen istiyorum. Bir hafta sonra değil, bir ay sonra değil, ne zaman toparlarsan da değil, tam şimdi. Yüz yirmi bin peso, bir kuruş eksik olmaz. Kitabı beş bin olarak saymaya razıyım.";
			link.l1.go = "OZ_Shuler_13";
		break;
		
		case "OZ_Shuler_13":
			dialog.text = ""+GetSexPhrase("Seni pislik herif","Serseri")+"! Eğer benimle bu kadar kolay başa çıkabileceğini sanıyorsan – bu, değersiz hayatındaki en büyük hata olur.";
			link.l1 = "Göreceğiz.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Shuler_Bitva");
		break;
		
		case "OZ_Frantsuz_1":
			//PlaySound("VOICE\Russian\tra_quest_1.wav");
			if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
			{
				dialog.text = "Ne manzara... İtiraf etmeliyim ki, "+GetAddress_Form(NPChar)+", bana büyük bir keyif verdiniz. Kılıcı harika kullanıyorsunuz. Kendimi tanıtmama izin verin – "+GetFullName(npchar)+" . Ve yanılmıyorsam, bu talihsiz adam Javier Castillo?";
				link.l1 = "Aynen, o işte. Ve ben de Kaptanım "+GetFullName(pchar)+".";
				link.l1.go = "OZ_Frantsuz_1_1";
			}
			else
			{
				dialog.text = "Ne manzara... İtiraf etmeliyim ki, "+GetAddress_Form(NPChar)+", bana büyük bir zevk verdin. Kılıcı harika kullanıyorsun. Bazen şartların nasıl değiştiği ne tuhaf – uğruna buralara kadar geldiğim kitap en beklenmedik şekilde el değiştirdi. Ama umarım buradan eli boş ayrılmam.";
				link.l1 = "Hmm... Peki, bu kitabı ne kadar değerli buluyorsun?";
				link.l1.go = "OZ_Frantsuz_2";
			}
		break;
		
		case "OZ_Frantsuz_1_1":
			dialog.text = "Görüyorsunuz Kaptan, özellikle bir kitap için epeyce yol katettim... Ve anlaşılan o kitap artık sizin elinizde. Umarım bir anlaşmaya varabiliriz – buradan eli boş ayrılmak istemem doğrusu.";
			link.l1 = "Hmm... Peki, bu kitabın değerini ne kadar görüyorsun?";
			link.l1.go = "OZ_Frantsuz_2";
		break;
		
		case "OZ_Frantsuz_2":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", gerçekten nadir şeylerin değerini bilirim. Seksen bin peso. Oldukça cömert bir teklif, bana inanın, böyle bir fırsat bir daha elinize geçmez.";
			link.l1 = "Doğru, kitap gerçekten değerli ve kabul ediyorum, ben sordum"+GetSexPhrase("","")+" sadece merakımdan sordum. Bir adamın kaderi üzerinden ticaret yapmaya niyetim yok. Üzgünüm, monsieur, bir anlaşma olmayacak – bu kitap gerçek sahibine geri dönmeli.";
			link.l1.go = "OZ_Frantsuz_3";
			link.l2 = "Gülünç bir miktar. Bu kitap, demircilik sanatının en usta ustalarının sırlarını barındırıyor. Yüz elli bin peso – ya kabul edersin ya da kitap sahibine geri döner. Pazarlık yok.";
			link.l2.go = "OZ_Frantsuz_4";
		break;
		
		case "OZ_Frantsuz_3":
			dialog.text = "Lütfen, hemen reddetmeyin. Bunun için uzun bir yol geldim. O adamla başa çıkma becerinize duyduğum saygının bir göstergesi olarak size yüz bin teklif etmeye hazırım.";
			link.l1 = "Söylemem gereken her şeyi söyledim. Şimdi, müsaadenizle, gitmem gerek.";
			link.l1.go = "OZ_Frantsuz_4_1";
		break;
		
		case "OZ_Frantsuz_4_1":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "OZ_Frantsuz_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", Güvenin için teşekkür ederim, ama yüz elli bin – bu bir fiyat değil, bu saçmalık. Bu anlaşmayı bir maskaralığa çevirmeyelim. Yüz bin peso makul bir miktar, kabul et – bu kitap için kimse daha fazlasını vermez.";
			link.l1 = "Galiba ortak bir nokta bulamadık. Pekâlâ, bu konuşmayı sürdürmek için bir sebep göremiyorum. Hoşça kalın, monsieur.";
			link.l1.go = "OZ_Frantsuz_5";
		break;
		
		case "OZ_Frantsuz_5":
			dialog.text = "Dur! Tamam, kazandın. Yüz elli bin. Anlaştık mı?";
			link.l1 = "Doğru seçimi yaptığına sevindim. Kitap senin. Sanırım bu kitapla Karayipler’in en usta ismi olacaksın.";
			link.l1.go = "OZ_Frantsuz_6";
			TakeItemFromCharacter(pchar, "OZ_book");
			AddMoneyToCharacter(pchar, 150000);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
			ChangeCharacterReputation(pchar, -5);
		break;
		
		case "OZ_Frantsuz_6":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", bu kitap olmasa bile kimseye boyun eğmezdim. Ama itiraf etmeliyim ki, böyle nadir bir ganimete sahip olmak hoşuma gidiyor. Ve şimdi, lütfen beni mazur gör – hakkında duyduğum övgü dolu sözlere gerçekten layık mı, bir an önce görmek için sabırsızlanıyorum.";
			link.l1 = "O halde, seni daha fazla tutmayayım. Hoşça kal.";
			link.l1.go = "OZ_Frantsuz_7";
		break;
		
		case "OZ_Frantsuz_7":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_2");
		break;
		
		case "OZ_Bandit_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Pekâlâ, pekâlâ, bu ne saçmalık? Sandığımızı boşaltıp kaçacağını mı sandın? Büyük hata, dostum. Şimdi seni o sandığın içine biz tıkacağız ve kapağını çivileyeceğiz!";
			}
			else
			{
				dialog.text = "Bak hele... Burada kimi görüyoruz? Yolunu mu kaybettin, güzelim? Sandığı boşaltıp sessizce sıvışacağını mı sandın? Büyük hata yaptın, tatlım. Şimdi seni güzelce arayacağız – bakalım ceplerinde ve başka nerelerde neler saklıyorsun...";
			}
			link.l1 = "Sizin gibi zavallı solucanlar için fazla laf ettim. Çekin kılıcınızı, gerçekten neye değersiniz görelim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Grot_4");
		break;
		
		case "OZ_Felip_11":
			dialog.text = "Kaptan! Javier’in senin sayende öteki dünyaya gittiğini çoktan öğrendim. Oysa ona hemen kıymanı istememiştim! Umarım paramı geri getirdin?";
			if (sti(pchar.Money) >= 100000)
			{
				link.l1 = "Aynen öyle. Onun sakladığı yeri bulmayı başardım, içinde yüz bin peso vardı. Sahip olduğu tüm para buydu.";
				link.l1.go = "OZ_Felip_12";
			}
			link.l2 = "Evet, onu öldürmek zorunda kaldım. Ama önce o bana saldırdı, kendimi savunmam gerekti. Cebinde tek bir kuruş bile yoktu. Maalesef borcu tahsil edemedim.";
			link.l2.go = "OZ_Felip_14";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.OZ_Dolg");
		break;
		
		case "OZ_Felip_12":
			dialog.text = "Yüz bin... Tabii ki bu tam miktar değil, ama Javier’i tanıyorsam, ondan fazlasını almak neredeyse imkânsız. Peki o zaman, teşekkürler Kaptan. Görünen o ki yanlış insanları tutmuşum. Siz gerçekten işinizin ustasısınız.";
			link.l1 = "Zor olmadı. Bu arada, üzgünüm ama artık gitmem gerek"+GetSexPhrase("","")+". İşler bekliyor.";
			link.l1.go = "OZ_Felip_13";
			AddMoneyToCharacter(pchar, -100000);
		break;
		
		case "OZ_Felip_13":
			dialog.text = "Elveda, Kaptan.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_good");
		break;
		
		case "OZ_Felip_14":
			dialog.text = "Sen "+GetSexPhrase("serseri","serseri")+"! Gözümün içine baka baka bana yalan mı söylüyorsun?! Bunun hesabını vereceksin!";
			link.l1 = "Argh...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_bad");
		break;
		
		case "OZ_Kuznets_Tovar":
			//PlaySound("VOICE\Russian\Master_02.wav");
			dialog.text = "Merhaba, "+pchar.name+"! Malzeme ya da mal satın almak ister misiniz?";
			link.l1 = ""+TimeGreeting()+". Ne varmış bakalım.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "Ve sana da merhaba, "+npchar.name+"! Teklifiniz için teşekkür ederim, ama sadece istemiştim"+GetSexPhrase("","")+" selam vermek için.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
			SetFunctionTimerCondition("OZ_Kuznets_Reset", 0, 0, 1, false);
			if (!CheckAttribute(npchar, "quest.OZ_Kuznets_tovar")) 
			{
				SetFunctionTimerCondition("OZ_Kuznets_Reset_2", 0, 0, 30, false);
				npchar.quest.OZ_Kuznets_tovar = true;
			}
		break;
		
		case "OZ_Kuznets_Tovar_repeat":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", sonunda bir şey almaya karar verdiniz mi?";
			link.l1 = "Aynen öyle. Bugün neleriniz var, gösterin bana.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "Üzgünüm, ben zaten gidiyorum.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
		case "OZ_Kuznets_Tovar_2":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
	}
}