// Хосе Диос - картограф
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
			dialog.text = "Bir şey mi istiyorsun?";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "dios")
			{
				link.l3 = TimeGreeting()+"! Söylesene, sen haritacı Jose Dios musun?";
				link.l3.go = "island";
			}
			link.l1 = "Hayır, hiçbir şey.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "island":
			dialog.text = "Evet, benim. Sizi tanımıyorum, señor. Benden ne istiyorsunuz?";
			link.l1 = "Benim adım "+GetFullName(pchar)+" ve beni Jan Svenson gönderdi. Onu hatırlıyor musun?";
			link.l1.go = "island_1";
		break;
		
		case "island_1":
			dialog.text = "Ah, Bay Svenson! Elbette onu hatırlıyorum! Gelin, rahatınıza bakın... Saygıdeğer Jan nasıl, iyi mi?";
			link.l1 = "Teşekkürler, durumu iyi. Señor Dios, yardımınıza ihtiyacım var. Mesleğiniz gereği aşina olmanız gereken bir konuda sizinle görüşmek istiyorum. Jan, sizi Karayipler bölgesinin coğrafya uzmanı olarak tavsiye etti...";
			link.l1.go = "island_2";
		break;
		
		case "island_2":
			dialog.text = "Dinliyorum, Señor. Takımadaların coğrafyası hakkında ne bilmek istiyorsunuz?";
			link.l1 = "Küba'nın kuzeybatısında, Havana'nın ilerisinde, Meksika Körfezi ile ada arasında bir ada ya da başka bir oluşum olduğu söyleniyor. Bu ada hiçbir haritada yer almamış. Bu söylentilerin ne kadar doğru olduğunu öğrenmek isterim.";
			link.l1.go = "island_3";
		break;
		
		case "island_3":
			dialog.text = "Hm... Yıllardır içimde bir merak uyandıran bir şeyi sordun. Bahsettiğin bu yer, uzun zamandır coğrafyacıların merakını cezbediyor, ama şimdiye kadar kimse o bölgeyi keşfetmeye cesaret edemedi.";
			link.l1 = "Neden?";
			link.l1.go = "island_4";
		break;
		
		case "island_4":
			dialog.text = "The thing is, that place is some sort of natural anomaly. The probability of storms in that region is much higher than anywhere else. Perhaps the reason lies in the cold sea current, but that's just my hypothesis. Many ships have disappeared there, and that alone was enough to make sailors avoid the area; all the main sea routes pass far from that region anyway.";
			link.l1 = "Demek ki sen de gerçeği bilmiyorsun...";
			link.l1.go = "island_5";
		break;
		
		case "island_5":
			dialog.text = "Aynen öyle, Señor. Ama elimde birkaç tarihi belge ve bazı maddi kanıtlar var, bu yüzden o yerin var olma ihtimalinin yüksek olduğundan şüphelenmeye hakkım var.";
			link.l1 = "Bana biraz daha anlatır mısın?";
			link.l1.go = "island_6";
		break;
		
		case "island_6":
			dialog.text = "Elbette. En önemli kanıt, adayı 1620 yılında ziyaret eden Kaptan Alvarado'nun günlüğünden alınmış bölümler içeren tarihi bir belge. Oldukça ilginç bir hikaye, emin olabilirsiniz!";
			link.l1 = "Kaptan Alvarado mu? Bu ismi ikinci kez duyuyorum...";
			link.l1.go = "island_7";
		break;
		
		case "island_7":
			dialog.text = "I am not surprised. The story of Captain Alvarado has been part of folklore for years. It changed, became filled with rumours, lies and dreams, so here it is - the legend of the Island of the Abandoned Ships.\nGossip may change, but paper and ink do not; they remain intact for hundreds of years. Here, read this story - perhaps it will help you uncover what you are looking for.";
			link.l1 = "Teşekkürler! Başka bir şey var mı?";
			link.l1.go = "island_8";
		break;
		
		case "island_8":
			dialog.text = "O bölgede deniz tabanının yeterince yükselip geniş bir sığlık oluşturduğuna dair bir teori var. Akıntıdan da zaten bahsetmiştim. Denizcilerin anlattıklarına göre, orada martıların ve başka deniz kuşlarının büyük birikimi de var. Alvorado, Amiral Francisco Betancourt'un filosuna ait olan ve elli yıldan fazla bir süre önce kaybolan gemilerin isimlerini de andı. Bunun sadece bir tesadüf olduğundan şüpheliyim...";
			link.l1 = "Gemicime döneceğim ve Alvarado'nun notlarını dikkatlice okuyacağım. Yardımınız için teşekkür ederim, Señor Dios!";
			link.l1.go = "island_9";
		break;
		
		case "island_9":
			dialog.text = "You're welcome. Actually, I didn't help you at all; you haven't got the coordinates of the place, and neither have I. I can't even prove that there is an inhabited island out there. But as far as I understand, you intend to explore this area?\nIf so, then be aware that I will be truly grateful for any information, especially if it is supported by material proof. It seems that you are a wealthy man, but I will find a way to repay you.";
			link.l1 = "Güzel. O zaman anlaştık, Señor Dios. Belki bir gün notlarımı da biri okur... Hatta biri bir efsane bile yazabilir...";
			link.l1.go = "island_10";
		break;
		
		case "island_10":
			dialog.text = "Neden olmasın? Señor "+pchar.name+", Sizi çok gezen, maceracı bir adam olarak görüyorum, bu yüzden sizden bir şey rica etmek istiyorum.";
			link.l1 = "Evet? Dinliyorum.";
			link.l1.go = "island_11";
		break;
		
		case "island_11":
			dialog.text = "Biliyorsun, ben bir haritacıyım. Yani, iki yıldır Karayip takımadalarının haritalarını çiziyorum, Yeni Granada Genel Valisi'nin yarışması için amiralin atlasını hazırlıyordum. Ama yirmi dört haritamın hepsi, korsanlar tarafından esir alındığım sırada, hem de en pervasız şekilde evimden çalındı; beni kurtaran da Señor Svenson'dı.\nSaldırının haritalarımı ele geçirmek isteyen rakiplerimden biri tarafından düzenlendiğine eminim. Aradan uzun zaman geçti ama o setten tek bir haritamı bile bir daha görmedim.";
			link.l1 = "Anladım. Haritalarınızı geri getirmemi istiyorsunuz.";
			link.l1.go = "island_12";
		break;
		
		case "island_12":
			dialog.text = "Aynen öyle. Belki onları ilerideki maceralarında bulursun. Tanımak kolaydır – her birinin üzerinde benim işaretim var. Eğer mucizevi bir şekilde yirmi dört haritanın hepsini toplamayı başarırsan, seni cömertçe ödüllendireceğim.";
			link.l1 = "Pekâlâ. Bundan sonra takımadada bulduğum her haritayı dikkatlice inceleyeceğim. Neyse, şimdi gitmem gerek. İlginç sohbetiniz ve belge için teşekkür ederim.";
			link.l1.go = "island_13";
		break;
		
		case "island_13":
			DialogExit();
			AddQuestRecordInfo("LSC_Alvorado", "1");
			AddQuestRecord("SharkHunt", "4");
			pchar.questTemp.Saga.SharkHunt = "LSC";
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			pchar.questTemp.AdmiralMap = "true";
		break;
		
		case "Dios":
			dialog.text = "A-ah, sensin, señor "+GetFullName(pchar)+"? Bana anlatacak ilginç bir şeyin var mı?";
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 0 && CountAdmiralMapFromCharacter() < 24 && !CheckAttribute(npchar, "quest.mapinfo"))
			{
				link.l3 = TimeGreeting()+"Tanrım, lütfen bulduğum şu haritaya bir bakın. İşarete göre bu haritalardan biri size ait olmalı.";
				link.l3.go = "map_info";
			}
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 23)
			{
				link.l3 = TimeGreeting()+"! Señor Dios, size iyi haberlerim var. İstediğiniz gibi, eşsiz haritalarınızın tamamını toplamayı başardım. İşte yirmi dört haritanın hepsi.";
				link.l3.go = "amap";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Dios")) // был в LSC
			{
				link.l4 = TimeGreeting()+"Evet, gittim. Bahsettiğimiz o gizemli yerdeydim.";
				link.l4.go = "LSC";
			}
			link.l9 = "Şimdilik bir şey yok, Señor. Sadece nasıl olduğunu görmek istedim.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Dios";
		break;
		
		case "map_info":
			dialog.text = "Göster bana... (bakıyor) Elbette! Bu, amiralin atlası için hazırladığım haritalardan biri! Kaptan, senden hepsini bulmanı rica ediyorum! Biliyorum, neredeyse imkânsız, ama yine de... Umudumu kaybetmek istemiyorum.";
			link.l1 = "Bunu kaybetmeyin, Señor. Bu haritayı bulduğuma göre, kalanını da bulma şansım var. Hâlâ Karayipler'deler.";
			link.l1.go = "map_info_1";
		break;
		
		case "map_info_1":
			dialog.text = "İyimserliğiniz bana gerçekten cesaret veriyor, Señor kaptan. Belki de hâlâ Don Juan de Cordova'ya takımadadaki en iyi haritacı kimmiş gösterebilirim!";
			link.l1 = "Tüm rakip kötü niyetlileri alt edebileceksiniz. Haritalar gerçekten harika... Elveda, Señor!";
			link.l1.go = "exit";
			npchar.quest.mapinfo = "true";
			NextDiag.TempNode = "Dios";
		break;
		
		case "amap":
			Achievment_Set("ach_CL_110");
			dialog.text = "Gözlerime inanamıyorum! Gerçekten buldun mu onları? Hepsini mi?";
			link.l1 = "Evet. Kolay olmadı, ama bu işte şans yüzüme güldü. Al kartlarını — hepsi harika, şimdiye kadar gördüklerimin çok ötesinde.";
			link.l1.go = "amap_1";
		break;
		
		case "amap_1":
			RemoveAllAdmiralMap()
			Log_Info("You have given the complete set of admiral's maps");
			PlaySound("interface\important_item.wav");
			dialog.text = "İnanılmaz! Bu gerçekten inanılmaz! Açıkçası, bu anın geleceğine hiç inanmamıştım.";
			link.l1 = "Dum spiro, spero, Señor Dios. Artık Don Cordova'nın karşısına çıkabilirsin. Eminim yeteneklerine çok değer verecektir.";
			link.l1.go = "amap_2";
		break;
		
		case "amap_2":
			dialog.text = "Teşekkür ederim, Kaptan! Bana ne büyük bir iyilik yaptığının farkında bile değilsin. Söz verdiğim gibi, seni ödüllendireceğim. Ayrıca senin için bir hediyem var. Bir denizci olarak bunu çok faydalı bulacağına inanıyorum.";
			link.l1 = "Beni etkilediniz, Señor!";
			link.l1.go = "amap_3";
		break;
		
		case "amap_3":
			GiveItem2Character(pchar, "spyglass5"); 
			Log_Info("You have received a ship telescope");
			PlaySound("interface\important_item.wav");
			dialog.text = "Buyurun! Bu, kendi tasarımım olan bir gemi dürbünü. Eşi benzeri yoktur, başka hiçbir yerde bulamazsınız. Mercekleri, İspanya’daki en usta usta tarafından Avrupa’da yapıldı. Kutusu ise dost bir silah ustası tarafından hazırlandı. Özel bir üçayak, aleti dalgalara rağmen sabit tutmanıza yardımcı olur. İster bir gemi, ister bir kale olsun, ihtiyacınız olan her şeyi görebilirsiniz.";
			link.l1 = "Böylesine harika bir hediye! Teşekkür ederim, Señor Dios.";
			link.l1.go = "amap_4";
		break;
		
		case "amap_4":
			dialog.text = "Kullanın, Señor kaptan. Umarım dürbünüm size iyi hizmet eder.";
			link.l1 = "Hiç şüphem yok! Onu gemimin güvertesine yerleştirip içinden bakmak için sabırsızlanıyorum.";
			link.l1.go = "amapcopy_01";
		break;
		
		case "amapcopy_01":
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 1000); // харизма
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность (раз телескоп дали)
			ChangeCharacterComplexReputation(pchar, "nobility", 10);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 5);// репутация-авторитет
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			ChangeOfficersLoyality("good_all", 5);
			DeleteAttribute(pchar, "questTemp.AdmiralMap");
			dialog.text = "Hem de, madem işler böyle gelişti, sana başka küçük bir teklifim daha var.";
			link.l1 = "Ne oldu? Seni dikkatle dinliyorum.";
			link.l1.go = "best_map";
		break;
		
		case "best_map":
			dialog.text = "Şunu fark ettim ki bu haritalar bir kaşif için mükemmel, ama bir deniz kaptanının ihtiyaç duyduğu her şeyi sunmuyorlar. Düşünsene: tüm koylar, burunlar ve lagünler büyük bir hassasiyetle çizilmiş, ama bunlarla adalar arasında rota belirleyemezsin.";
			link.l1 = "Doğru, onlarla yol bulamazsın.";
			link.l1.go = "best_map_01";
		break;
		
		case "best_map_01":
			dialog.text = "Ama sana bir takımadalar haritası da çizebilirim! Hem de Hollanda Batı Hindistan Şirketi'nden satın alabileceğin türden değil, eşsiz ve mükemmel bir harita.";
			link.l1 = "Teşekkür ederim, señor Dios, ama böyle bir haritaya ihtiyacım yok. Yine de teklifiniz için çok teşekkür ederim!";
			link.l1.go = "best_map_02";
			link.l2 = "Şaka mı yapıyorsun?! Tanrım, nasıl olur da reddedebilirim? Sadece neye ihtiyacın olduğunu söyle - para ya da alet konusunda hiçbir masraftan kaçınmam!";
			link.l2.go = "best_map_04";
		break;
		
		case "best_map_02":
			dialog.text = "Pekala, teklif etmek zorundaydım. Her halükarda, sizinle iş yapmak bir zevkti, señor "+pchar.lastname+"!";
			link.l1 = "Aynı şekilde! Sana bol şans!";
			link.l1.go = "best_map_03";
		break;
		
		case "best_map_03":
			DeleteAttribute(pchar, "questTemp.AdmiralMapCopy");
			DialogExit();
			NextDiag.CurrentNode = "Dios";
		break;
		
		case "best_map_04":
			dialog.text = "Enstrümanlarım zaten var, teşekkür ederim. Standart bir takımadalar haritasına, bir pusulaya ve kalibreli bir kronometreye ihtiyacım olacak — harita kesinlikle doğru olmalı, aksi halde bu sabotaj olur. Ödeme olarak ise — bir sandık dublon istiyorum.";
			if(CheckAMapItems())
			{
				link.l1 = "Bahsettiğin her şey zaten bende var. Al, işte burada.";
				link.l1.go = "best_map_07";
			}
			link.l2 = "Takımadaların standart haritası, bir pusula, dereceli bir kronometre ve bir sandık doblon. Anlaşıldı! Hepsini en kısa zamanda getiririm — beni bekle!";
			link.l2.go = "best_map_07e";
		break;
		
		case "best_map_07e":
			DialogExit();
			NextDiag.CurrentNode = "best_map_waititems";
		break;
		
		case "best_map_waititems":
			dialog.text = "Selamlar, sevgili dostum! Takımadaların standart haritasını, pusulayı, onaylı kronometreyi ve doblon sandığını getirdin mi?";
			link.l1 = "Henüz değil, Señor Dios. Ama yapacağım, söz veriyorum!";
			link.l1.go = "best_map_07e";
			if(CheckAMapItems())
			{
				link.l2 = "Evet, Señor Dios. İşte, her şey burada — alın.";
				link.l2.go = "best_map_07";
			}
		break;
		
		case "best_map_07":
		    Log_Info("You handed over a regular map of the archipelago, a boussole, a tariffed chronometer, and a chest with doubloons.");
			TakeNItems(pchar,"chest", -1);
			TakeNItems(pchar,"map_normal", -1);
			TakeNItems(pchar,"bussol", -1);
			TakeNItems(pchar,"clock2", -1);
			dialog.text = "Pekala, o zaman işe koyuluyorum. Bir hafta sonra yanıma gel, söz veriyorum pişman olmayacaksın!";
			link.l1 = "Hiç şüphem yok, Señor. Bir hafta sonra görüşürüz!";
			link.l1.go = "best_map_08";
		break;
		
		case "best_map_08":
			SetTimerFunction("AdmAtlas_comlete", 0, 0, 7);
			NextDiag.CurrentNode = "best_map_wait";
			pchar.questTemp.AdmiralAtlas = true;
			DialogExit();
		break;
		
		case "best_map_wait":
			if(CheckAttribute(pchar,"questTemp.AdmiralAtlas") && pchar.questTemp.AdmiralAtlas == "complete")
			{
				dialog.text = "Ah, Señor "+pchar.lastname+", işte buradasın! Sana bildirmekten memnuniyet duyarım ki, takımadaların haritasını bitirdim! Ve rahatlıkla söyleyebilirim ki, senin bana verdiğinden çok daha üstün.";
				link.l1 = "Arkadaşım... Bu harita inanılmaz! Sanırım bir başyapıt! Bana yaptıkların için sana nasıl teşekkür edebilirim?";
				link.l1.go = "best_map_09";
			}
			else
			{
				dialog.text = "Selamlar, Señor! Özür dilerim, ama harita henüz hazır değil.";
				link.l1 = "Evet, bir haftaya ihtiyacın olduğunu hatırlıyorum. Sadece seni kontrol etmeye geldim.";
				link.l1.go = "best_map_wait_01";
			}
		break;
		
		case "best_map_wait_01":
			NextDiag.CurrentNode = "best_map_wait";
			DialogExit();
		break;
		
		case "best_map_09":
			dialog.text = "Ah, hadi ama dostum. Böyle bir haritayı gerçekten takdir edebilecek soylu bir kaptan için hazırlamak benim için zevkti. Ah, işte orijinal haritanız da geri geldi. Denizler size cömert davransın!";
			link.l1 = "Çok teşekkür ederim! Haklısınız — bu harita benim için gerçekten paha biçilemez. Elveda, Señor Dios!";
			link.l1.go = "best_map_10";
		break;
		
		case "best_map_10":
			TakeNItems(pchar,"Map_Best", 1);
			TakeNItems(pchar,"map_normal", 1);
			Log_Info("You received an excellent archipelago map!");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "Dios";
			DialogExit();
		break;
		
		case "LSC":
			dialog.text = "Gerçekten mi?! Buldun mu? Rahatına bak, sanırım önümüzdeki sohbet biraz sürecek, değil mi?";
			link.l1 = "Sana ada hakkında anlatacak çok şeyim var. Ama önce, bana bir söz vermeni istiyorum. Senin onurlu bir adam olduğunu görebiliyorum, bu yüzden sözünü tutacağına eminim...";
			link.l1.go = "LSC_1";
		break;
		
		case "LSC_1":
			dialog.text = "Ne diyorsun, Kaptan?";
			link.l1 = "Orada yaşayan insanlar var... ve birilerinin hayatlarına karışmasından hoşlanmazlar. Bir 'araştırma' filosunun muhtemel gelişi memnuniyetle karşılanmaz diye düşünüyorum.";
			link.l1.go = "LSC_1_1";
		break;
		
		case "LSC_1_1":
			dialog.text = "";
			link.l1 = "Bu yüzden senden, bu konuşmamızdan sonraki on yıl boyunca adanın yerini bulmaya yarayabilecek hiçbir bilgiyi yayımlamaman için bana namusun üzerine söz vermeni istiyorum. Buradaki insanlarla, onların hayatlarıyla ilgili istediğin her şeyi yayımlayabilirsin, ama adanın yerini açıklama.";
			link.l1.go = "LSC_2";
		break;
		
		case "LSC_2":
			dialog.text = "Katılıyorum, Kaptan. Bir soylu olarak size söz veriyorum ki, ne Adanın yerini ne de önümüzdeki on yıl boyunca oranın sakinlerine zarar verebilecek herhangi bir bilgiyi kimseye söylemeyeceğim.";
			link.l1 = "O zaman dinle hikayemi. İstersen yaz da. Şimdi, Ada geniş bir sığlıkta yatan birçok batık geminin gövdelerinden oluşuyor...";
			link.l1.go = "LSC_3";
		break;
		
		case "LSC_3":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later...", "LSC_FinalDiosStory", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "LSC_4":
			dialog.text = "İnanılmaz! Bana çok değerli bilgiler verdiniz, Kaptan! Amiral de Betancourt'un soyundan gelenler adada yaşıyor! Şimdi filosuna ne olduğunu biliyoruz. Ve artık Karayip takımadalarının haritasında bir kör nokta daha az... Hikayeniz için size çok teşekkür ederim, "+pchar.name+"!";
			link.l1 = "Şimdi neden bilgilerimi aktarırken bu kadar dikkatli olmanı istediğimi anlıyor musun?";
			link.l1.go = "LSC_5";
		break;
		
		case "LSC_5":
			dialog.text = "Anladım. Sözümü tutacağımdan emin olabilirsin. Söylesene... Adadan herhangi bir eşyan var mı?";
			if (CheckCharacterItem(pchar, "LSC_navigation_map"))
			{
				link.l1 = "Terkedilmiş Gemiler Adası'na giden rotalar elimde. Bak, işte burada. Bu talimatlar sayesinde küçük bir gemiyi kayalıklar ve enkaz arasından geçirip adaya güvenle yanaşabilirsin. Bu rotalar olmadan adaya ulaşmak imkânsız.";
				link.l1.go = "LSC_6";
			}
			else
			{
				link.l1 = "Maalesef, bende hiç yok.";
				link.l1.go = "LSC_7_1";
			}
		break;
		
		case "LSC_6":
			Log_Info("You have given sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "(bakıyor) Ne harika bir belge! Bunu haritacılıkta usta bir adam çizmiş. Ben bile bundan iyisini yapamazdım. İnanılmaz! Kaptan, neden bu seyir talimatlarını bana vermiyorsun? Hikaye hikaye de, bu kağıt mutlaka Eski Dünya'nın en ünlü coğrafyacılarına gösterilmeli!";
			link.l1 = "Señor Dios, maalesef bu belgeye kendim için ihtiyacım var. Daha önce de söylediğim gibi, adayı çevreleyen resiflerden bu olmadan geçmek imkânsız. Ama isterseniz talimatların bir kopyasını çıkarabilirsiniz, ve onları da yanınızda bulundurmanız beni fazlasıyla memnun eder.";
			link.l1.go = "LSC_10";
			//link.l2 = "Señor Dios, maalesef bu eşyaya kendim için ihtiyacım var. Dediğim gibi, onsuz adanın etrafındaki resifleri aşmak imkânsız. Bilim uğruna feda ederdim ama... Eminim beni anlıyorsunuzdur.";
			//link.l2.go = "LSC_7";
		break;
		
		case "LSC_7":
			Log_Info("You received sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Elbette. Bu sizin hakkınız, gerçi yazık olmuş... Neyse, hikayeniz için teşekkürler! Coğrafyacılara, haritacılara ve diğer meraklılara büyük bir iyilik yaptınız.";
			link.l1 = "Rica ederim, Señor. Şimdi gitmem gerek. Hoşça kal.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_7_1":
			dialog.text = "Ne yazık... Yine de, hikayeniz için teşekkürler! Coğrafyacılara, haritacılara ve diğer meraklılara büyük bir hizmette bulundunuz.";
			link.l1 = "Rica ederim, Señor. Şimdi gitmem gerek. Hoşça kal.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_8":
			dialog.text = "Tabii, "+pchar.name+". Bana çok zaman ayırdınız. Señor Svenson'a selamlarımı iletin!";
			link.l1 = "Elveda, Señor Dios.";
			link.l1.go = "LSC_9";
		break;
		
		case "LSC_9":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 400);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 500); // харизма
			ChangeCharacterComplexReputation(pchar, "nobility", 5);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 2);// репутация-авторитет
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 5);
			DeleteAttribute(pchar, "questTemp.LSC.Dios");
			LAi_SetOwnerType(npchar);
		break;
		
		case "LSC_10":
			Log_Info("You received sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Çok teşekkür ederim! Bu gerçekten çok nazikçe. Biraz bekleteceğim...";
			link.l1 = "...";
			link.l1.go = "LSC_11";
		break;
		
		case "LSC_11":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 0);
			npchar.dialog.currentnode = "LSC_12";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LSC_12":
			//RemoveItems(pchar, "LSC_navigation_map", 1);
			dialog.text = "Çok teşekkür ederim! Bu gerçekten çok nazikçeydi. Artık elimizde sadece sözlü değil, aynı zamanda somut bir kanıt da var... Sizi ödülsüz bırakmayacağım, Kaptan. Sizin için küçük bir hediyem var.";
			link.l1 = "Ne tür bir hediye?";
			link.l1.go = "LSC_13";
		break;
		
		case "LSC_13":
			sld = characterFromId("Pirates_shipyarder");
			sld.quest.sextant = "true"; // атрибут Алексу на хронометр
			GiveItem2Character(pchar, "sextant1"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "Ben yalnızca haritacılık ve coğrafyaya değil, matematik ve astronomiye de meraklıyım. Enlem ve boylamı belirlemek için evrensel bir alet yaratmak adına bir yıl boyunca uğraştım. Ve bir miktar ilerleme kaydettim. Bakın, işte:\nBu benim sekstantım. Tasarımını tamamen kendim yaptım. Sorun şu ki, çalışmıyor. Son derece hassas bir kronometreye ihtiyaç duyuyor. En iyi ustaların yaptığı kronometreler bile zamanla kabul edilemez hatalar veriyor. Bu yüzden, şimdilik aletim hiçbir işe yaramıyor.\nAma siz çok seyahat ettiğiniz için, belki sekstantın çalışmasını sağlayacak kadar hassas bir kronometre bulabilirsiniz. Böyle bir saat bulduğunuzda, artık Boussole'a, pusulaya, astrolaba, kum saatlerine ya da başka güvenilmez kronometrelere ihtiyacınız kalmayacak—benim aletim hepsinin yerini alacak.";
			link.l1 = "Teşekkür ederim, Señor Dios. Umarım icadınızı çalıştıracak bir kronometre bulabilirim. Böyle bir alete... çalışır durumda sahip olmak isterim. Neyse, şimdi gitmem gerek. Hoşça kalın.";
			link.l1.go = "LSC_8";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Sen "+GetSexPhrase("Bir hırsız, görüyorum! Muhafızlar, yakalayın onu","Bir hırsız, görüyorum! Muhafızlar, yakalayın onu")+"!!!","İnanamıyorum! Bir saniye arkamı döndüm – ve sen eşyalarımı karıştırıyorsun! Dur, hırsız!!!","Gardiyanlar! Soygun! Hırsızı durdurun!!!");
			link.l1 = "Aaaah, şeytan!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

bool CheckAMapItems()
{
	return GetCharacterItem(pchar,"chest")      && 
		   GetCharacterItem(pchar,"map_normal") &&
		   GetCharacterFreeItem(pchar,"bussol") &&
		   GetCharacterFreeItem(pchar,"clock2");
}