void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
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
		
		case "LEDR_Gonsalo_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Hey, delikanlı! Cesur bir denizciye benziyorsun, kavga işinden de anlıyorsundur bence. Benimle ufak bir baskına gelir misin, ha?";
			}
			else
			{
				dialog.text = "Hey, güzelim! Buraya kadar geldiğine göre çekingen biri olmadığın belli. Ne dersin, küçük bir baskında bana yardım etmek ister misin, ha?";
			}
			link.l1 = "Sanırım eski gemiyi bulmak için bir rehber arayan yaşlı adam sensin?";
			link.l1.go = "LEDR_Gonsalo_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LEDR_Gonsalo_2":
			dialog.text = "Heh... Demek dedikodular rüzgardan hızlı yayılıyor. Evet, o benim. Gonzalo Peralta – 'La Espada del Rey' enkazından sağ kalan tek kişi.";
			link.l1 = "Ve ben bir kaptanım "+GetFullName(pchar)+" . Gemini tekrar göz atmak ister misiniz?";
			link.l1.go = "LEDR_Gonsalo_3";
		break;

		case "LEDR_Gonsalo_3":
			dialog.text = "Evet. Bakın, son zamanlarda aynı kabus beni tekrar tekrar rahatsız ediyor. Ama asıl kötü olan bu değil... İnanır mısınız, her sabah, kabus biter bitmez uyanıyorum ve... karşımda lanet bir iskelet dikiliyor...";
			link.l1 = "Bana, bu masalı herkese anlattığını söylediler.";
			link.l1.go = "LEDR_Gonsalo_4";
		break;

		case "LEDR_Gonsalo_4":
			dialog.text = "Bir hayal mi? Heh... Keşke sadece o kadar olsa. Birkaç ay önce, emekli bir denizciye yakışır şekilde sakin bir hayat sürüyordum. Ama şimdi o kemik yığını her sabah çıkageliyor, bana bakıyor, tüyler ürpertici bir çığlık atıyor... kahretsin, herhangi bir çarkçı bile kanının donduğunu hissederdi... sonra da savaşa dalıyor. Ve biliyor musun? Her seferinde saldırıları daha da şiddetleniyor. İşte tam da bu yüzden gemiye bir an önce gitmek istiyorum—orada bulmam gereken bir şey olduğuna dair içimde bir his var, bir türlü kurtulamıyorum.";
			link.l1 = "Hmm... Oldukça ilginç bir iş. Bunca zamandan sonra orada ne bulmayı umuyorsun?";
			link.l1.go = "LEDR_Gonsalo_5";
		break;
		
		case "LEDR_Gonsalo_5":
			dialog.text = "Bilmiyorum, Kaptan, gerçekten bilmiyorum... Ama o gemiye karşı bir çekim hissediyorum, fırtınadaki eski bir tekne gibi. Rüyam, o iskelet ve bu tuhaf his... Denizin yanında, bir şekilde birbirlerine bağlılar. Sadece nasıl olduğunu çözemiyorum.";
			link.l1 = "Rüyanda tam olarak ne oluyor? Bu, yerlilerle bir şekilde bağlantılı mı?";
			link.l1.go = "LEDR_Gonsalo_6";
			link.l2 = "Yani, geceleri hayaller görüp sabahları bir iskeletle mi savaşıyorsun? Belki de sorun gemide değil, bir doktora görünmen gerekiyordur. Senin hayal gücüne kapılacak değilim. Git, saçmalıklarına inanacak başka bir enayi bul.";
			link.l2.go = "LEDR_Gonsalo_6_end";
		break;
		
		case "LEDR_Gonsalo_6_end":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_End");
		break;
		
		case "LEDR_Gonsalo_6":
			dialog.text = "Bağlantılı mı? Tabii ki öyleyim, kahretsin... O rüyada, ölü tayfamla birlikte 'La Espada del Rey'in güvertesindeyim. Hispaniola'daki Karayip köylerine baskın yapıyoruz, yolumuza çıkan herkesi öldürüyoruz—erkek, kadın, çocuk. Direnenler de, diz çöküp merhamet dileyenler de fark etmiyor. Yerleşimlerini bir bir yakıyoruz. Yerlilerin okları ve sopaları bize karşı, savaş kalyonuna karşı sızdıran bir tartaneden farksız. Karayipler çaresizce müzakere için yalvarıyor ve sonra...";
			link.l1 = "Aman Tanrım! Demek bütün o kanunsuzluklarda sen de vardın? Sana yardım değil, darağacı lazım!";
			link.l1.go = "LEDR_Gonsalo_7";
		break;
		
		case "LEDR_Gonsalo_7":
			dialog.text = "Hayır! Hayır, lanet olsun, bu doğru değil, anlıyor musun?! Neden bütün bunları rüyamda gördüğümü bilmiyorum... ama kutsal olan her şey üzerine yemin ederim ki, ne ben ne de mürettebatım böyle vahşetlere asla karışmadık!";
			link.l1 = "Umarım bu doğru olur. Devam et.";
			link.l1.go = "LEDR_Gonsalo_8";
		break;

		case "LEDR_Gonsalo_8":
			dialog.text = "Karayip yerlileri görüşme talep etti, kaptan da kabul etti. Hepimizi, ele geçirdiğimiz kulübelerden birine davet etti. Şefler geldiler—en az iki düzine, başlarında kraliçeleri Anacaona vardı. Ama kaptanın kendisi içeri girmedi... hiçbirimiz girmedik. Son şef de içeri girer girmez, kapı hızla kapatılıp kirişlerle sürgülendi. Ve sonra... lanet olsun... kulübeyi ateşe verdiler. Sadece kraliçeyi bağışladılar, ama o da uzun sürmedi. Ona, halkının diri diri yanışını izlettiler... Sonra da onu bir ağaca astılar.";
			link.l1 = "Ve bu her gece mi oluyor? Aynı rüya, tekrar tekrar mı? Biliyor musun, bunca şeyden sonra, o iskeletin sadece ateşli hayal gücünün bir ürünü olmasına hiç şaşırmam...";
			link.l1.go = "LEDR_Gonsalo_9";
		break;

		case "LEDR_Gonsalo_9":
			dialog.text = "Hepsi bu değil. Hayatta kalan Karayip yerlileri Küba'ya kaçtı, oradaki kabilelerden destek buldu ve kısa sürede bir reisin önderliğinde tek bir orduya toplandılar. Atuey—sanırım adı buydu. Onu son umutları olarak gördüler ve peşinden gittiler. Ama biz onları fazla zorlanmadan katlettik. Atuey yakalandı ve idama hazırlandı. Onu haça bağlayıp yakmaya hazırlanırken, bir rahip ona gerçek inancı sundu—acılarını hafifleteceğini ve cennete girmesini sağlayacağını söyledi. Atuey rahibe cennetin İspanyollara da açık olup olmadığını sordu. Rahip de tabii ki iyi İspanyollara açık olduğunu söyleyince, cacique hiç tereddüt etmeden, o zaman cenneti değil, cehennemi istediğini söyledi—böyle zalim insanlarla aynı yuvayı paylaşmak istemediği için. Sonra kendi dilinde birkaç kelime daha etti ve odunlar tutuşturuldu. Alevler bedenini sararken tek bir ses bile çıkarmadı. Deniz hakkı için yemin ederim, böyle bir şeye gerçekte tanık olmak istemezdim. Rüyam hep aynı şekilde bitiyor: kaptan oturuyor, kımıldamadan. Sadece yakındaki bir mum tütüyor ve o, yıpranmış bir günlüğü karıştırmaya devam ediyor. Yavaşça, sanki her kelime bir servet ağırlığında, kendi kendine bir şeyler mırıldanıyor. Rüyamda bile, "+GetSexPhrase("adam","kız")+", Anladım – bu bir işaret. Artık kılıcıma sarılma vakti, çünkü o çoktan saldırıya geçti.\nKaptan, bu kabusa bir son vermemde bana yardım et. Körfeze benimle gel. Oraya tek başıma gitmem – barutum az kaldı. Ama cevap vermeden önce seni uyarmalıyım: Sana ödeme yapamam. Ödeyebilseydim, kapının önünde yardım etmek isteyenlerin kuyruğu olurdu zaten. O yüzden tek umudum başka bir denizcinin yardımına kalmak.";
			link.l1 = "Pekâlâ, tamam. Eğer gemiye gitmek bu rüyalardan ve diğer gördüklerinden kurtulmana yardımcı olacaksa, sana yardım edeceğim. Gel, gemiye çık. İşimi bitirir bitirmez körfeze doğru yola çıkarız.";
			link.l1.go = "LEDR_Gonsalo_10";
		break;
		
		case "LEDR_Gonsalo_10":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_1");
			AddQuestRecord("LEDR", "2");
			AddQuestUserData("LEDR", "sSex", GetSexPhrase("ся","ась"));
		break;
		
		case "LEDR_Gonsalo_11":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				dialog.text = "İşte burada... Bir zamanlar İspanyol ticaret filosunun gururuydu, şimdi ise zar zor bir arada duran çürük tahtalardan ibaret.";
				link.l1 = "Böylesine bir devi yerde, kıyıda yatarken görmek pek sık rastlanan bir şey değil. Nasıl oldu da buraya geldi?";
				link.l1.go = "LEDR_Gonsalo_12";
				link.l2 = "O zaman etrafa bir bakalım. Belki burada gerçekten bir şey bulabilirsin.";
				link.l2.go = "LEDR_Gonsalo_20_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Nankör ya da korkak görünmek istemem... ama şu anda burada kendimi güvende hissetmiyorum. Güneş doğduğunda geri dönelim.";
				link.l1 = "Peki dostum, madem öyle diyorsun.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LEDR_Gonsalo_11";
			}
		break;
		
		case "LEDR_Gonsalo_12":
			dialog.text = "Santiago’dan yelken açtık, rotamız Sevilla’ydı. Fazla yükümüz yoktu, ama bir yolcumuz vardı—bayağı önemli biri, bizzat bir piskopos. Açıkçası, tayfa bu yolculuktan pek memnun değildi... ama bize kim ne zaman bir şey sordu ki?  Açık denize hiç çıkamadık. Turks yakınlarında bir korsan brigantini saldırdı—hızlı, çevik, silah dolu. Öyle sıradan serseriler değil, gerçek deniz kurtlarıydı. Başta kaptan kaçmak istedi—piskoposun hayatını riske atmak istemiyordu. Ama rüzgar öyleydi ki geri dönemiyorduk, güneyden de fırtına yaklaşıyordu. Yani başka çare yoktu—savaş başladı.";
			link.l1 = "İki ateş arasında kalmak, insanın başına gelebilecek en kötü şeylerden biri. Peki sonra ne oldu?";
			link.l1.go = "LEDR_Gonsalo_13";
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;

		case "LEDR_Gonsalo_13":
			dialog.text = "Dövüş uzun sürmedi. Onların baş direğini devirmeyi başardık ama korsanlar da boş durmadı—savrulan bir gülle dümen halatımızı kopardı ve sanki şeytanın işiymiş gibi gemi durdu, pruvası yaklaşan fırtınaya dönük kaldı. Fırtına öyle hızla yaklaşıyordu ki korsanlar—keşke zincir gülle ana yelkenlerini paramparça etse—kaçmayı seçip Türklerin koylarından birine kayboldular. Ve bizim yapabileceğimiz tek şey, fırtınanın bizi yutmasını beklemekti. Kaptan yelkenlerin indirilmesini ve dümen halatının değiştirilmesini emretti ama artık çok geçti.";
			link.l1 = "Yani, fırtına seni Turks yakınlarında yakaladı, buraya kadar sürükledi ve sonunda karaya mı attı?";
			link.l1.go = "LEDR_Gonsalo_14";
		break;

		case "LEDR_Gonsalo_14":
			dialog.text = "That's exactly how it happened. The ship was pure chaos. The wind tore the rigging apart, masts crashed down one after another, smashing the deck and crushing people. If you didn't have time to tie yourself down, you were swept overboard; if you did, you were crushed by the wreckage. It was no better below deck—cannons, crates, cannonballs flew back and forth like demons, grinding up everything in their path. When we were finally thrown ashore, I was unconscious. I came to on the sand. Boatswain Sergio found me. He had two others with him.";
			link.l1 = "Bu kadar büyük bir gemi için pek bir şey değil.";
			link.l1.go = "LEDR_Gonsalo_15";
		break;

		case "LEDR_Gonsalo_15":
			dialog.text = "Ah, kaptan... O kadar çok ceset vardı ki... Hemen anladık: orada kalamazdık. Dalgalar gemiyi, bizi de beraberinde sürükleyebilirdi. Yakında bir mağara bulduk—yorgunluktan, yere dokunduğumuz anda uyuyakaldık. Uyandığımda, mağarada ne Sergio'dan ne de diğer ikisinden eser yoktu.\nTüm sahili aradım, ama yıldırımlar çarpsın, hiçbir yerde yoklardı. Geminin üstüne tek başıma çıkamazdım, bu yüzden iç bölgelere gitmeye karar verdim. Böylece Sharptown'a vardım ve kendi aptallığımla işleri berbat ettim.\nHayatta kalanlar hakkında bir şeyler öğrenmek istedim, bu yüzden başımıza gelenleri herkese anlatmaya başladım. Ama o alçaklar ne bana ne de mürettebata ilgi gösterdi—tek dertleri, gemiden kapabilecekleri ganimetti. Haber hızla adaya yayıldı ve kısa sürede o hırsız sürüsü oraya akın etti.";
			link.l1 = "Yani, o insanlara ne olduğunu hâlâ bilmiyor musun?";
			link.l1.go = "LEDR_Gonsalo_16";
		break;

		case "LEDR_Gonsalo_16":
			dialog.text = "Gemiye geri dönmek fazlasıyla tehlikeliydi. Yağma için gizlice içeri sızmaya cesaret eden herkes, ganimet yüzünden kavga edip, yakındaki birine yanlışlıkla kurşun sıkabilirdi... ya da belki—hiç de yanlışlıkla değil. Deniz kenarında, bütün bir haftayı handa saklanarak geçirdim, körfeze giden herkese sorular sordum. Ama kimse ne mürettebatımdan, ne de onlara ne olduğundan haberdardı. Sonunda kabullenmek zorunda kaldım: Görünüşe bakılırsa, o lanetli fırtınadan sağ çıkan tek kişi benim. Belki de kader bana diğerlerinden daha çok güldü. Ya da belki... her şey, bir zamanlar genç Kaptan Eugenio de la Torre’nin bana verdiği tılsımın sayesinde oldu. Onu hep yanımda taşıdım. Ve kahretsin, gerçekten de bana şans getirmiş gibi görünüyor.";
			link.l1 = "Ve şimdi nerede? Görünüşe bakılırsa, iskeletlerden korumuyor, değil mi...";
			link.l1.go = "LEDR_Gonsalo_17";
		break;

		case "LEDR_Gonsalo_17":
			dialog.text = "Bahçemdeki kuyu başını tamir ederken boynumdan koparıldı. Bir kütük boynuma çarptı ve muska suya düştü. Kuyu zaten doluydu, kimse bir takı uğruna içini boşaltmakla uğraşmazdı.";
			link.l1 = "O andan itibaren kâbuslar görmeye mi başladınız?";
			link.l1.go = "LEDR_Gonsalo_18";
		break;

		case "LEDR_Gonsalo_18":
			dialog.text = "Hay aksi! Hiç böyle düşünmemiştim ama tam olarak böyle oldu! Kuyuyu inşa etmeyi bitirir bitirmez kâbuslar başladı.";
			link.l1 = "Ne tesadüf! İşte şimdi buradasın, tam da istediğin gibi. Peki, bundan sonra ne yapmayı düşünüyorsun?";
			link.l1.go = "LEDR_Gonsalo_19";
		break;

		case "LEDR_Gonsalo_19":
			dialog.text = "Bilmiyorum, Kaptan... Bilmiyorum. Önce etrafa bakalım – burada bulmam gereken bir şey olduğu hissi daha da güçlendi.";
			link.l1 = "Pekala. Umarım buraya boşuna gelmedik.";
			link.l1.go = "LEDR_Gonsalo_20";
		break;
		
		case "LEDR_Gonsalo_20":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
		break;
		
		case "LEDR_Gonsalo_20_1":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
			pchar.questTemp.LEDR_NoStory = true;
		break;
		
		case "LEDR_Gonsalo_21":
			dialog.text = "Dinle... Bu his gittikçe güçleniyor. Sanki bulmam gereken bir şeye bir adım kalmış gibi. O gemiye binmem lazım. Denize yemin ederim, orada o lanetli iskeletin peşimi neden bırakmadığını açıklayacak bir şey var.";
			link.l1 = "Yani, belki de buraya bu kadar hevesle gelmen boşuna değildi? Gemide değerli bir şey mi sakladın da şimdi hazineni almak için mi döndün?";
			link.l1.go = "LEDR_Gonsalo_22";
		break;

		case "LEDR_Gonsalo_22":
			dialog.text = "Ne saçmalık bu? Kırk yıl sonra birkaç dublon için bütün takımadaları baştan sona dolaşacağımı gerçekten mi sanıyorsun? O iskeletle bir kez bile karşılaşmak zorunda kalsaydın, böyle şeyler aklının ucundan bile geçmezdi.";
			link.l1 = "Pekala, pekala, sakin ol. Peki, gemiye tam olarak nasıl binmeyi planlıyorsun?";
			link.l1.go = "LEDR_Gonsalo_23";
		break;

		case "LEDR_Gonsalo_23":
			dialog.text = "Kıçta gizli bir kapı var. Kaptan onu bizzat kendisi kesip yaptı—bir baskında işler ters giderse diye. Yıldırım çarpsın beni, şu yaşlı bedenimi oradan tek başıma geçiremiyorum, ama ikimiz olursak...";
			link.l1 = "Pekâlâ, yolu göster de şu işi bitirelim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_5");
		break;
		
		case "LEDR_Gonsalo_24":
			DelLandQuestMark(npchar);
			dialog.text = "Top gülle boynuma gelsin, ne karmaşa! Neyse ki bunlar her sabah çıkan kadar azgın değildi. Şimdi bana inanıyor musun?";
			link.l1 = "Böyle bir gösteriden sonra, insanın etkilenmemesi zor. İyi misin?";
			link.l1.go = "LEDR_Gonsalo_24_1";
		break;

		case "LEDR_Gonsalo_24_1":
			dialog.text = "Bence de öyle. Kahrolası ölüler... bacaklarım kırık direkler gibi çöktü.";
			link.l1 = "Pekâlâ, eğer sapasağlam duruyorsan, burada oturmanın anlamı yok. Elini ver, seni kaldırayım.";
			link.l1.go = "LEDR_Gonsalo_24_2";
		break;

		case "LEDR_Gonsalo_24_2":
			CharacterTurnByChr(npchar, CharacterFromID("blaze"));
			dialog.text = "...";
			link.l1 = "Bu daha iyi. Görünüşe göre buraya nasıl girileceğini bilen ilk kişiler biz değiliz.";
			link.l1.go = "LEDR_Gonsalo_25";
			LAi_Fade("LEDR_GonsaloStay", "");
		break;

		case "LEDR_Gonsalo_25":
			dialog.text = "Görünüşe bakılırsa bunlar benim adamlarım. Fırtınadan sağ çıkanlar... Sergio'nun yeleğini tanıdım—ya da ondan geriye ne kaldıysa. Demek geri dönmüşler—ya hayatta kalanları aramak ya da ölüleri gömmek için. Ama anlaşılan o aynı bela onları da bitirmiş.";
			link.l1 = "Yelekten geriye sadece birkaç parça kalması tuhaf. Başka hiçbir şey yok.";
			link.l1.go = "LEDR_Gonsalo_26";
		break;

		case "LEDR_Gonsalo_26":
			if(CheckAttribute(pchar, "questTemp.LEDR_NoStory"))
			{
			dialog.text = "Piskoposun cübbesinden eser kalmamış — yolcumuzun cübbesinden bile. Şu zavallının elinde sımsıkı tuttuğu anahtara bakılırsa, o olmalı. O anahtarı bir an bile bırakmazdı. Diğerlerinden daha şanslı olmadığı belli. Denizin kenarında, bu ölüler öylece dolaşmıyordu. Burada onları tutan bir şey var... ya da bir şeyi koruyorlar.";
			DeleteAttribute(pchar, "LEDR_NoStory");
			}
			else
			{
			dialog.text = "Piskoposun cübbesinden geriye en ufak bir iz bile kalmamış. Şu zavallının elinde sımsıkı tuttuğu anahtara bakılırsa, o olmalı. O anahtarı bir an bile bırakmazdı. Diğerlerinden daha şanslı olmadığı belli. Denizin kenarında, bu ölüler burada öylece dolaşmıyordu. Bir şey onları burada tutuyor... ya da bir şeyi koruyorlar.";
			}
			link.l1 = "Şimdi burada bir şey bulmamız gerektiğini hissediyorum. Hadi bunu bitirelim — burada kalmaya mecbur olduğumuzdan bir saniye bile fazla kalmak istemiyorum.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_8");
		break;
		
		case "LEDR_Gonsalo_27":
			dialog.text = "Peki, kaptan, bir şey bulabildiniz mi?";
			link.l1 = "Sanırım bu piskoposun sandığıydı. İçinde bir şey buldum. Bir bak.";
			link.l1.go = "LEDR_Gonsalo_28";
		break;

		case "LEDR_Gonsalo_28":
			dialog.text = "Velasquez... Şimşek çarpsın beni... Bu günlüğü rüyalarımda gördüm! Kaptanın, o olmadan önce karıştırdığı tam da buydu...";
			link.l1 = "...";
			link.l1.go = "LEDR_Gonsalo_29";
		break;

		case "LEDR_Gonsalo_29":
			dialog.text = "Lanet olsun, ellerimi yakıyormuş gibi hissediyorum!";
			link.l1 = "Ellerini mi yakıyor? Hadi ama, bu sadece eski bir günlük. Yoksa gerçekten içinde karanlık bir güç olduğuna mı inanıyorsun?";
			link.l1.go = "LEDR_Gonsalo_30";
		break;

		case "LEDR_Gonsalo_30":
			dialog.text = "Tüm azizler adına yemin ederim, şaka yapmıyorum! O lanetli günlük ellerimde yanıyormuş gibi geliyor. Yok edilmeli! Parçala, yak, suda boğ—ne olursa! Hayır, dur... En iyisi yakmak. Evet, yak ki, küllerinden bile eser kalmasın!";
			link.l1 = "Dediğiniz gibi. O halde karaya çıkalım, bir ateş yakalım ve bu günahlar kroniğini ateşe atalım.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_10");
		break;
		
		case "LEDR_Gonsalo_31":
			dialog.text = "Pekâlâ, işte bu... Sanki göğsümden bir yük kalktı.";
			link.l1 = "Sence şimdi her şey bitti mi?";
			link.l1.go = "LEDR_Gonsalo_32";
			TakeItemFromCharacter(pchar, "LEDR_book");
		break;

		case "LEDR_Gonsalo_32":
			dialog.text = "Kim bilir... Ama deniz üzerine yemin ederim, kendimi yıllardır bu kadar hafif hissetmemiştim. Sanki eski bir borç nihayet affedildi. Yine de... Keşke o lanetli günlüğü hiç görmeseydim. Ya da içinde yazanları hiç öğrenmeseydim.";
			link.l1 = "Böyle rüyalar görmen şaşırtıcı değil. Bütün bunlara doğrudan karışmamış olsan da, günlüğe bir şekilde bağlı olan tek yaşayan kişi sensin.";
			link.l1.go = "LEDR_Gonsalo_33";
		break;
		
		case "LEDR_Gonsalo_33":
			dialog.text = "Ne altın ne de inanç, Velasquez’in emriyle yapılanları haklı çıkarabilir. Ve bizi ona hatırlatabilecek her şeyin yanmış olmasına seviniyorum. Böyle şeyler, onların yolundan gitmeye hevesli olanların eline asla geçmemeli.";
			link.l1 = "Velasquez sadece bir tanesi. Kim bilir, eski Avrupa’da daha kaç tane böyle günlük dolaşıyor, yeni fatihlerin açgözlülüğünü ve dokunulmazlığını körüklüyor? Bir şey kesin—bu günlük artık kimseyi zehirlemeyecek. Bu arada, piskoposun sandığında sadece günlük değil, hatırı sayılır miktarda dublon da vardı—toplamda üç yüz tane. Yarısı da haklı olarak sizin.";
			link.l1.go = "LEDR_Gonsalo_34_share";
			link.l2 = "Velasquez günahlarının bedelini ödedi, ve eğer birileri onun yolundan gitmeyi seçerse, aynı sona ulaşacaklar. Er ya da geç, kader herkese hak ettiğini verir.";
			link.l2.go = "LEDR_Gonsalo_34_silence";
		break;
		
		case "LEDR_Gonsalo_34_share":
			dialog.text = "Eğer durum buysa - hayır demem. Herkesin paraya ihtiyacı var, benimse şimdi her zamankinden daha çok. Artık kimse beni tayfa olarak almak istemiyor - bu iş için fazla yaşlandım. O yüzden teşekkür ederim, Kaptan, beni başkaları gibi geri çevirmediğiniz için.";
			link.l1 = "İtiraf etmeliyim ki, başta anlattıkların bir delinin saçmalıkları gibi gelmişti. Ama öyle bir inandırıcılıkla anlattın ki, insan istemese de inanmaya başlıyor. Yine de o ölümsüz yerlilerin ortaya çıkması beni hazırlıksız yakaladı.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "Sadece aklını kaçırıp kaçırmadığını görmek istedim. Biliyor musun, böyle hikayelere inanmak o kadar da kolay değil.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			RemoveDublonsFromPCharTotal(150);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.quest.LEDR_share = true;
		break;
		
		case "LEDR_Gonsalo_34_silence":
			dialog.text = "İnanmak istiyorum... Ama deniz kenarında, ne kadar karanlık olursa olsun, talihin yüzüne güldüğü çok kişiye rastladım. Belki de hesap günü gelir—ama burada değil, şeytanın kendi kazanında. Ve teşekkür ederim, Kaptan. Yüz çevirmediğiniz, dinlediğiniz, beni uğurladığınız için. Bu benim için gerçekten çok şey ifade ediyor, biliyor musunuz.";
			link.l1 = "İtiraf etmeliyim, başta anlattıkların bir delinin saçmalıkları gibi gelmişti. Ama öyle inandırıcı anlattın ki, insan istemese bile inanmaya başlıyor. Yine de, o ölümsüz Kızılderililerin ortaya çıkışı beni hazırlıksız yakaladı.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "Sadece aklını kaçırıp kaçırmadığını görmek istedim. Biliyor musun, böyle hikayelere inanmak kolay değil.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "LEDR_Gonsalo_35_1":
			dialog.text = "Şimdi o ölüleri ilk gördüğümde ne hissettiğimi anlıyorsun. Umarım sonsuza dek gitmişlerdir... Yoksa, bir daha öyle bir karşılaşmadan sağ çıkabileceğimi sanmıyorum.";
			link.l1 = "Pekala, burada işimiz bittiğine göre, artık buradan çıkma zamanı. Gemiye bin, seni Sharptown limanında bırakacağım.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "LEDR_Gonsalo_35_2":
			dialog.text = "Şimdi o ölüleri ilk gördüğümde ne hissettiğimi anladın. Umarım sonsuza dek gitmişlerdir... Yoksa, bir daha öyle bir karşılaşmadan sağ çıkabileceğimi sanmıyorum.";
			link.l1 = "Pekala, burada işimiz bittiğine göre, artık buradan çıkma zamanı. Gemiye bin, seni Sharptown limanında bırakacağım.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "LEDR_Gonsalo_36":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_12");
		break;
		
		case "LEDR_Gonsalo_37":
			dialog.text = "Bir kez daha teşekkür ederim, Kaptan "+GetFullName(pchar)+"Deniz kenarında, o tuhaf his kayboldu ve umarım lanet olası kemik torbasını da yanında götürmüştür. Ne dersin, bir içki içelim mi, ha?";
			link.l1 = "Davetin için teşekkürler Gonzalo, ama şu anda çok meşgulüm. Belki başka bir zaman. Bizim için de bir kadeh iç.";
			link.l1.go = "LEDR_Gonsalo_38";
		break;
		
		case "LEDR_Gonsalo_38":
			if (CheckAttribute(npchar, "quest.LEDR_share"))
			{
				dialog.text = "Anlıyorum. Ama şunu bil, Kaptan: bunca şeyi birlikte yaşadıktan sonra, sana teşekkür etmeden gidip de arkamı dönemem. Bu doğru olmazdı. Al, bunu sana veriyorum. Gençliğimde defalarca hazine peşinde koştum, deniz üstüne yemin ederim. Ama artık sağlığım eskisi gibi değil, belim de dertli. Ama sen—sen gençsin, tecrübeli bir denizcisin. Onu kolayca bulursun. Sana bol şans, "+GetFullName(pchar)+", adil rüzgarlar ve omurganın altında yedi ayak su olsun.";
				link.l1 = "Teşekkür ederim, Gonzalo. Sana da bol şans, elveda.";
				AddMapPart();
			}
			else
			{
				dialog.text = "O halde, artık veda etme zamanı. Rüzgarın bol, yolun açık olsun, Kaptan "+GetFullName(pchar)+"!";
				link.l1 = "Elveda, Gonzalo.";
			}
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_14");
		break;
		
		
		
	}
}