// Элен МакАртур - сомнительная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ne oldu?";
			link.l1 = "Hayır, önemli bir şey değil.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "Yardımınız için teşekkürler, kaptan!";
			link.l1 = "Tanrım... Hayal ettiğimden bile daha güzelsin!";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "Güzelliğim batsın! Başına ne dertler açtığını biliyor musun? İtibarım zedelenmese kendi burnumu keserdim. O alçak beni korvetten sağ çıkarmadı, sürekli 'çok şey biliyorsun' deyip durdu. Dün de beklemekten sıkıldığını, beni zorla alacağını söyledi\nDaha iyi bir zamanda gelemezdin! Ama bak, görgüsüzlük ediyorum, adım Helen McArthur. Babam bana Rumba derdi, çünkü onun 'elde ettiği' o narin porselenleri hep yanlışlıkla kırardım, bu yüzden tayfam da şimdi bana öyle diyor.";
			link.l1 = "Benim adım "+GetFullName(pchar)+" ve seni kurtarmaya geldim. Bayan Gladys uğruna seni bulmak için günlerdir Karayipler'i arşınlıyorum.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "Bayan Gladys!? O nasıl?";
			link.l1 = "Senin için çok endişelendim. Ama yakında onu göreceksin, Blueweld'e yelken açıyoruz. Oraya giderken başından geçen her şeyi bana anlatabilirsin.";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "Dürüst olmak gerekirse, "+pchar.name+", şu anda biraz yemek yiyip biraz kestirmek isterdim. O canavarın gemisinde geçirdiğim onca günden sonra çok yoruldum...";
			link.l1 = "Elbette, Bayan McArthur. Hizmetkâra size bir yemek hazırlamasını ve özel odanızda bir yatak hazırlamasını emredeceğim.";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "De Maure Kaptan, sizi zamanında kurtardığınız için kalbimin en derininden tekrar teşekkür ederim. Lütfen beni ve annemi ziyaret edin. Evimiz buradan çok uzakta değil, iskeleden gelirken solunuzda kalıyor. Ve şunu bilin "+pchar.name+", elveda demeden yelken açarsan seni asla affetmem!";
			link.l1 = "Zevk tamamen bana aitti, Bayan McArthur. Sizi mutlaka tekrar ziyaret edeceğim!";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "Ah, işte buradasınız, Kaptan de Maure! Sizi gördüğüme çok sevindim, size soracak o kadar çok sorum var ki.";
			link.l1 = "Üzgünüm, Bayan McArthur, ama sohbetimizi biraz ertelememiz gerekecek. Tatmin edici cevaplar verebilmem için önce biraz daha bilgi toplamam lazım. Şimdilik sizden ricam, sokağa çıkmamanız. Umarım bekleyişiniz uzun sürmez. Bana güvenin ve bekleyin.";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CanDrink")) {
				link.l1.go = "drinking_refuse";
				link.l2 = "Sen kendin söyledin, uğramazsam beni affetmeyeceğini.";
				link.l2.go = "drinking_accept";
				
				DeleteQuestCondition("HelenDrinking_NoVisit");
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CanDrink");
			} else {
				link.l1.go = "exit";
				NextDiag.TempNode = "Helena_wait";
			}
		break;
		
		case "Helena_hire":
			dialog.text = "Ah, işte buradasın, benim kaptanım! Gözlerin bana bana haberlerin olduğunu söylüyor!";
			link.l1 = "Kaptan Svenson senin benimle denize açılmak istediğini söyledi. İlgin için teşekkür ederim, ayrıca Bayan Gladys de denizi özlediğini söyledi. Gemimize hoş geldin, Bayan Helen McArthur!";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "Kaptan Svenson bana senin benimle denize açılmak istediğini söyledi. İlgin için teşekkür ederim, ayrıca Bayan Gladys de denizi özlediğini söyledi. Mürettebatıma hoş geldin, Bayan Helen Sharp!";
				link.l2.go = "Helena_hire_2";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 2;
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "Emredersiniz, kaptan! Bunu söylemekten hoşlanmıyorum ama kendimi savunabilirim ve erkeklerin haddini aşmasına asla izin vermem. Kopan ellerden ya da oyulan gözlerden ben sorumlu değilim.";
			link.l1 = "Merak etme, gemimde sarsılmaz bir disiplin vardır. Yine de sana bir şey sormam gerek...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "...Evet?";
			link.l1 = "Jan Svenson ve ben, Isla Tesoro'nun gerçek varisi olduğunuzu keşfettik. Evet, doğru, başınızı sallamayın! İddianızı kanıtlayan haritanın yarısı bende. Kolay olmayacak, ama Jan ve ben, adanın gerçek sahibi olmanız için elimizden geleni yapacağız.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+", ciddi misin? Zavallı bir kızı böyle kandırmak hiç hoş değil! Koca bir adaya sahip olmaya nasıl hakkım olabilir ki?!";
			link.l1 = "Son derece ciddiyim, Bayan McArthur. Ve size hakkınız olanı geri almanızda yardımcı olacağım. Hadi hemen yelken açalım!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "N-ne dedin? Helen Sharp mı? Neden Sharp?";
			link.l1 = "Helen, sen Beatrice Sharp'ın kızı ve Sharp hanedanının tek varisisin. Bu, Bayan Gladys'in tüm bu yıllar boyunca sakladığı haritanın yarısı. Isla Tesoro üzerindeki hakkının kanıtı bu. Kolay olmayacak, ama Jan Svenson ve ben, büyükbabanın adasını miras almanda sana yardım etmek için elimizden geleni yapacağız.";
			link.l1.go = "Helena_hire_3";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
			Notification_Approve(true, "Helena");
			npchar.lastname = "Sharp";
		break;
		
		case "Helena_hire_3":
			dialog.text = "Ah... Zavallı annem! Keşke bir gün mezarını bulup orada ruhu için dua edebilsem. Ama... dur! İmkansız!";
			link.l1 = "Ne oldu, Bayan Sharp?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "Çingene kadının kehaneti sonunda gerçekleşti... Şimdi nihayet anlıyorum.";
			link.l1 = "Ha? Hangi kehanet?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", belki saf olduğumu düşünebilirsin, ama yine de anlatacağım. Küçük bir kızken, bir çingene kadın bana şöyle demişti: 'Kaderin, dulun parasını almayan, ölünün altınını geri veren ve anneyi adını söyleyen adamın ellerinde olacak.'\nO zamanlar bunun saçmalık olduğunu düşünmüştüm, ama sen bir şekilde kehanetin her kısmını yerine getirdin. Bunu bilmenin hiçbir yolu yoktu!";
			link.l1 = "Kaderin diyorsun... Belki de haklısın. Seni hayal kırıklığına uğratmayacağım. Annenin mezarını birlikte arayacağız. Ve şimdi... Bayan Helen Sharp! Hazırlan, yola çıkıyoruz ve sakın geç kalma!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "Emredersiniz, kaptan!";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			AddQuestUserData("Saga", "sTimer", AddDaysToDateString(367));
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2, false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				AddQuestRecord("HelenDrinking", "3");
				
				SetFunctionLocationCondition("HelenDrinking_IslaTesoroAmbush", "Pirates_town", false);
				sld = &locations[FindLocation("Pirates_town")];
				sld.locators_radius.quest.detector1 = 4.0;
			}
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = "Kaptan "+pchar.name+"! Bir fikrim var...";
			link.l1 = ""+npchar.name+"?   Burada güvende değilsin, sana gemide kalmanı söylemiştim...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = "Charles, bu eski tekneye o kadar çok barut doldurmuşlar ki, patlarsa bütün ada doğrudan Aziz Petrus'un kapısına uçar! Bana saklanmamı söyleyip söylememenin hiçbir önemi yok, o yüzden beni dinle!";
			link.l1 = "Pekâlâ, çabuk konuş!";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "Korvet ve fırkateyn. Knive'ın gemisini düşman olarak görmüyorlar. Bu rahatlıklarını kendi lehimize kullanabiliriz. Birkaç varil barut alıp fitil takar, gemilere doğru yelken açarız.\nBizi yakına kadar sokacaklar, fitili ateşleriz, varili birinin üstüne bırakıp olabildiğince hızlı uzaklaşırız. Sonra da muhteşem bir patlamayı izleriz... Ne dersin?";
			link.l1 = "İmprovize bir yangın gemisi... çok kurnazca! Planın o kadar çılgın ki işe yarayabilir... eğer yeterince yaklaşabilirsek ve tanınmazsak.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Kaybedecek neyimiz var "+pchar.name+"? İki gemiyle birden savaşmak kolay olmayacak, ama şansımızı eşitlemek için bir fırsat yakalayacağız...";
			link.l1 = "Pekala. Hadi başlayalım! Çocuklar! Üç varil barut alın! Buradan defolup gideceğiz! Hayal gücüne bayılıyorum, "+npchar.name+"... Ben böyle bir fikre asla kendim varamazdım.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "Evet, kaptan, ne oldu?";
			link.l1 = "Jackman'ın gemisi Sabo-Matila Koyu'nda, ağır fırkateyn 'Centurion'. Bu gemi bir zamanlar Hawkes ailesine aitti, bu yüzden Jackman'ın kamarasında mutlaka önemli eşyalar ve belgeler olmalı... oraya çıkmamız gerek.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Söylemesi kolay. Bunu bizim polakremizle nasıl yapacaksın? Onların hem adamı hem topu bizden fazla.";
			link.l1 = "Haklısın. Jackman'ın adamları bizimkilerin en az iki katı ve hepsi de deneyimli dövüşçüler. Onlara önceden bir top atışı yapmadan saldırmak delilik olurdu. Ama uzun süren bir çatışma da en iyi seçenek değil. Bu yüzden ne yapmamız gerektiği üzerine düşünüyorum.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", henüz bizi düşman olarak tanımadılar, tıpkı o aptallar gibi Turks'ta... Hilemizi tekrar deneyebiliriz...";
			link.l1 = "Helen, I have just told you that we have to board and search the frigate; blowing it to kingdom come is not an option.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Bir dakika, "+pchar.name+", batırmayacağız onu. Biraz farklı yapalım.  Dinle, birkaç boş rom fıçısı alıp içine barut, saçma ve kısa fitiller dolduracağız. Sonra fırkateynlerine yaklaşacağız ve bu el yapımı patlayıcıları güvertelerine fırlatacağız.";
			link.l1 = "Ha! Kadın zekân beni hâlâ şaşırtmaya devam ediyor! Ateş gemisi yerine fougasse mi öneriyorsun? Sence işe yarar mı?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = " Neden olmasın? Onların bordası bizimkinden yüksek ama iki ya da üç adam ve bir makara yardımıyla dolu bir fıçıyı kolayca kaldırıp atabiliriz. Bağırırız: 'Knive'dan bedava rom var!' Ve fıçılar, tepki vermeye bile fırsat bulamadan patlar.";
			link.l1 = "Patlayan misket gülleleri, güvertedeki en iyi adamlarını kıyma haline getirecek... Kahretsin, kulağa çok cazip geliyor.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Kıç üstünden pupaya beş fıçı birden atalım. "+pchar.name+", sürpriz avantajımız var. Henüz hiçbir şeyden şüphelenmeyecekler! Sonra da, bize çıkma fırsatı bulamadan hemen yelken açıp uzaklaşacağız.";
			link.l1 = "Pekala, deneyelim. Patlayıcı varilleri onların güvertesine çıkarmadan önce kimliğimizi fark etmemeliler... Yaklaşmak kolay olmayacak. Jackman, Ghoul kadar aptal değil.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Hadi riske girelim, "+pchar.name+"! Daha önce de söylediğim gibi, kaybedecek neyimiz var?";
			link.l1 = "İyi söyledin... Hazır olun, çocuklar! Fougasseleri hazırlayın ve savaşa hazırlanın!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			//if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 11) {
				Achievment_Set("ach_CL_83");
			}
			
			if (sti(pchar.questTemp.Saga.HelenRelation) < 6)
			{
				dialog.text = "Pekala, sevgili kaptanım... Artık birbirimize veda etme zamanı geldi. Hizmetim sona erdi ve Isla Tesoro'nun Korsan Kraliçesi olmaya alışmam gerekiyor. Umarım amcamın layık bir halefi olabilirim. Yardımların için teşekkür ederim.";
				link.l1 = "Evet, seninle yolları ayırmak üzücü, ama kaderin cilvesi işte. Artık benim gemimde hizmet etmekten çok daha önemli sorumlulukların var.";
				link.l1.go = "result_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Mary")) {
					dialog.text = "Sana yakın olabilmek için geminde kalmayı çok isterdim... Ama bu imkansız. Mutlu ol, Charles. Ve umarım o kadın sana layıktır!";
					link.l1 = "Üzgünüm, Helen.";
					link.l1.go = "result_mary";
				} else {
					dialog.text = "Çok garip, "+pchar.name+"!   Koca bir adanın sahibi oldum ama Isla Tesoro'nun kraliçesi gibi hissetmiyorum... Sanırım Kardeşliğin yeni lideri koloniyi benden daha iyi yönetecek. Öğrenecek çok şeyim var.";
					link.l1 = "Merak etme Helen, kendine bakabilecek bir kadınsın - tıpkı ilk gemiye çıktığında bana söylediğin gibi.";
					link.l1.go = "result_9";
				}
			}
			
			DeleteQuestCondition("HelenDrinking_AtSHDN");
			DeleteQuestCondition("HelenDrinking_InBlueweldAfterCave");
		break;
		
		case "result_mary":
			dialog.text = "Peki, yine de arkadaş kalacağız, değil mi?";
			link.l1 = "Elbette... Helen, Isla Tesoro'da tekrar buluşacağız. Seni adana götüreyim mi?";
			link.l1.go = "result_12";
		break;
		
		case "result_1":
			dialog.text = "Haklısın... Bak, senin geminde seyrederken ganimetten payıma düşeni biriktirdim. Al bunu ve sakın teklifimi reddetmeye kalkma - sana borçlu kalmak istemem.";
			link.l1 = "Dur hele, bir dakika bekle...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "Ne söyleyeceğini biliyorum. Elbette, yardımın bu cılız hazine sandığından çok daha değerliydi. Ama şu anda elimde olan tek şey bu ve sana borcumu ödemeliyim. Al bunu, eğer kendin almazsan kamarana bırakacağım.";
			link.l1 = "Artık tek başına mı yelken açacaksın? Belki seni Isla Tesoro'ya götürebilirim?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("You have received a chest with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Buna gerek yok, "+pchar.name+". Adaya kendim gideceğim. Kılıcım ve tabancam yanımda, bir süreliğine yeter de artar... Isla Tesoro'nun Kraliçesi'nin gelir konusunda endişelenmesine gerek kalmayacak, oraya vardığımda bundan eminim.";
			link.l1 = "Baş üstüne, Majesteleri. Yeni hayatınızda bol şans dilerim.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "Yeter artık, şaka bile olsa. Senin için hâlâ Helen'im. Ama söylemek istediğim tek şey bu değildi. Babamı yeniden buldum, gerçi biraz tuhaftı. İngiliz soylusu olarak iyi ismiyle benim mirasımın bedelini ödedi ve bu beni rahatsız ediyor. İngilizler onu arıyor ve ben senin de, "+pchar.name+",   buna katılmak için.";
			link.l1 = "Kendine gel, Helen! O bir haydut ve korsan!";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = " Korsan mı? Ve sen de kimsin ki böyle bir şey söyleyebiliyorsun? O benim babam ve benim için önemli olan da bu! Ben ise, bir haydut ve korsanın kızı olarak, İngiliz adaletinin onun hakkında ne düşündüğünü umursamıyorum bile. Eğer babama zarar vermeye kalkarsan, senin benim için yaptığın tüm iyilikleri unuturum, bunu bil. Bunu bir uyarı olarak kabul et.";
			link.l1 = "Öyle mi? Aslında, kızım, biraz daha kibar olsan iyi edersin. Seni o Donovan denen sapığın elinden kurtarırken ya da ele geçirdiğimiz ganimetleri paylaşırken korsan tavırlarımdan şikayet ettiğini hiç duymadım!";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "Ben... Özür dilerim. Sözümü geri alıyorum, affet beni. Kendimi kaybettim... Ama yine de, senin dostun olarak kalmak isterim, ki bu, eğer babamın peşine düşersen imkânsız olur.";
			link.l1 = "Anlaşıldı. Ama sakın beni tehdit etmeye kalkma, kadın. Artık benim gemimde yolculuk ettiğine göre, kimseden ve hiçbir şeyden korkmadığımı biliyor olmalısın. Özellikle bir kadından – ister Korsan Kraliçesi ol ister olma – saygısızlığı asla kabul etmem. Centilmen olabilirim, ama sabrımın da bir sınırı var. Şimdi mesele kapandı, elveda. Sana bol şans diliyorum.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "Teşekkür ederim... Belki tekrar karşılaşırız, "+pchar.name+"...";
			link.l1 = "Ve neden olmasın? Gelecekte Isla Tesoro'ya birden fazla kez uğrayacağım. Orada görüşürüz... Hoşça kal, Helen.";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но её не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//закрыть локацию  // уже не надо.
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors лесник . чтобы бежала и исчезла а не стояла.
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться		
			if (CheckAttribute(pchar, "questTemp.LSC.MaryWait")) {
				pchar.questTemp.LSC.Mary = "return";
			}
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашёл Мэри - выбирай, какая девушка милее
			dialog.text = "Eminim. "+pchar.name+", senin geminde kalmak istiyorum, eğer izin verirsen. Seninle kalmak için...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "(choose Mary) You don't understand, Helen. Your whole future is ahead of you and there is nothing for you to worry about. All I have ahead of me is war, political intrigue and total uncertainty. You must build a life of your own; there is no room in it for a wild rover like me.";
				link.l1.go = "result_10";
				link.l2 = "(choose Helen) Bu, umduğumdan çok daha fazlası, Helen. Elbette seni kaybetmek istemem, ama Isla Tesoro'ya gitmen senin için daha iyi olur. Kim bilir, kaderim beni daha nereye sürükleyecek. Şu anda önümde savaş, siyasi entrikalar ve belirsizlik var.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "Beklediğimden de fazlası bu, Helen. Elbette seni kaybetmek istemem, ama Isla Tesoro'ya gitmen senin için daha iyi olurdu. Kim bilir, kaderim beni daha nerelere sürükleyecek. Şu anda önümde bir savaş, siyasi entrikalar ve belirsizlik var.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"!   Bana yalan söyleme. Sadece istemiyorsun...   Söylesene, kim o?   Terkedilmiş Gemiler Şehri'ndeki o kızıl saçlı fahişe, değil mi?";
			link.l1 = "Helen! Sana senin için en iyisini düşündüğümü anlatmaya çalışıyorum! Bunu nasıl anlamazsın?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "Tabii, tabii... Peki, nasıl oldu da seni baştan çıkardı, ha? Onun sahip olup da *benim* sahip olmadığım ne var?! Gerçekten o kadar mı iyi? Ha, "+pchar.name+"... Peki, bu senin kararın, bana kalan tek şey adama dönmek. Sizin aranıza giremem\nBenim için yaptığın her şey için teşekkür ederim Charles. Tanıdığım en iyi adamsın. Umarım arkadaş kalabiliriz?";
			link.l1 = "Elbette... Helen, seni Isla Tesoro'da tekrar göreceğim. İstersen seni oraya götürebilirim?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "Gerek yok. Yeni bir gemi alacağım. Senin komutanlığında çalışırken bir şalopa alıp donatacak kadar para biriktirdim. Yine yeni bir 'Rainbow' ile denize açılacağım.";
			link.l1 = "Memnun oldum, Helen, bu kadar... tutumlu davrandığın için. Ama bir şalopada yol almak, Isla Tesoro'nun Korsan Kraliçesi'ne yakışmaz. Yakında, kendi fırkateynin olmalı.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "Belki, "+pchar.name+". Peki. Tersaneye gideceğim, ama önce... bana bir veda öpücüğü ver... Lütfen...?";
			link.l1 = "Helen...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 0.5);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться
		break;
		
		case "result_15":
			dialog.text = "Kaderim seninle tanıştığımızdan beri seninkine bağlı. Bunu anlamıyor musun? "+pchar.name+"? Dünyanın sonuna kadar seninle gelirim!";
			link.l1 = "Ya baban? Laurence Beltrope? O benim düşmanım...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "Babam Sean McArthur'dı. Onu çok sevdim ve ölümüne çok üzüldüm. O benim tek babamdı. Ve o korsan... Onun hakkında konuşmak bile istemiyorum.";
			link.l1 = "Helen... Sevgili Helen'im!";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+", Sana her zaman söylemek istemiştim, tanıdığım en harika adamsın! Benim için öyle çok şey yaptın ki, sana asla borcumu ödeyemem. Seninle kalmak istiyorum. Sonsuza dek. Eğer istersen seninle evlenirim... Seni seviyorum.";
			link.l1 = "Birlikte olacağız. Söz veriyorum!"; // а куда же ты теперь денешься :)
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) {
				link.l1.go = "result_17A";
			} else {
				link.l1.go = "result_18";
			}
		break;
		
		case "result_17A":
			dialog.text = "Şu anda benim için bir şey yapacağına söz verir misin? Ve lütfen gülme!";
			link.l1 = "Söz veriyorum, sevgilim!";
			link.l1.go = "result_17A_1";
		break;
		
		case "result_17A_1":
			dialog.text = "Gerçek adımla seslen bana. Lütfen!";
			link.l1 = "Seni seviyorum, Helen Sharp.";
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+", sevgilim... Sarıl bana! Bu anı çok uzun zamandır bekliyordum!";
			link.l1 = "Helen, canım...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.																					   
			
			pchar.quest.HelenUpgradeShip.win_condition.l1 = "Timer";
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.day = GetAddingDataDay(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l2 = "location";
			pchar.quest.HelenUpgradeShip.win_condition.l2.location = "PortRoyal_town";
			pchar.quest.HelenUpgradeShip.function = "HelenUpgradeShip";
			
			// Квест Лонгвея "Путеводная звезда", начало 5 этапа
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap5_Start") && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! Bu... inanılmazdı! Başka hiçbir yere gitmek istemiyorum... Hadi sabaha kadar burada kalalım. Dünya bekleyebilir!";
			link.l1 = "Bunu bekleteceğiz, Helen!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
			npchar.SpecialRole = "fgirl";
			
			pchar.GenQuest.BrothelCount = 0;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
			
			// Выполнено требование для Дороже золота
			pchar.questTemp.GoldenGirl_Ready = true;
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "Kaptan! Jackman öldü... Ailem artık nihayet güvende mi?";
			link.l1 = "Evet, Helen, hepiniz güvendesiniz. Ama 'Centurion' batırıldı, ve bize annenin mezarını bulmamıza ve Isla Tesoro üzerindeki hakkını kanıtlamamıza yardımcı olabilecek tüm belgeler de onunla birlikte gitti... Eh... Şimdi Tortuga'ya tek başıma saldırmam gerekecek...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+", bu kadar endişelenme. Yapabileceğimiz bir şey yok. Benim için de endişelenme, o ada olmadan da iyi olacağım. Benim için yaptığın her şey için teşekkür ederim!";
			link.l1 = "Beni... terk edecekmişsin gibi geliyor, değil mi?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Evet, kaptanım. Yeterince para toplamayı başardım ve bir şalopa alıp donattım. Yine 'Gökkuşağım' ile denize açılacağım. Blueweld'de tekrar görüşeceğiz... Eve dönüyorum.";
			link.l1 = "Pekala... iyi şanslar, Helen!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "Pekala, benim kaptanım... Görünen o ki, başaramadık. Elveda. Evime dönüyorum. Senin komutanlığında yeterince para kazandım, kendime yeni bir şoner alabilirim. Denizde tekrar karşılaşacağız!";
			link.l1 = "İyi şanslar, Helen. Her şey için üzgünüm. Elveda.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "Kaptan! Jackman öldü... Demek ki ailem güvende, değil mi?";
			link.l1 = "Evet, Helen, artık güvendesin. Ama mutlu değilim, çok fazla zaman kaybettim ve Isla Tesoro artık bir İngiliz kolonisi oldu. Sen mirasından mahrum kaldın, bu yüzden Tortuga'yı kendim ele geçirmek zorunda kalacağım...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", avukat sana ne dedi?";
			link.l1 = "Çok fazla zaman kaybettim ve Isla Tesoro artık bir İngiliz kolonisi oldu. Sen mirasından mahrum kaldın, bu yüzden Tortuga'ya kendim saldırmak zorunda kalacağım... Ne yazık ki, kaybettik.";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Hayır, canım, bu işe yaramaz.";
				link.l1 = "E, neden olmasın?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0)// вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", bugün kendimi iyi hissetmiyorum. Lütfen kendini kötü hissetme, bu senin suçun değil. Bugün yapmayalım...",""+pchar.name+"Sevgilim, son birkaç gündür çok yorgunum. Açıkçası, sadece uyumak istiyorum. Beni affet. Bunu başka bir zaman yapalım.");
				link.l1 = RandPhraseSimple("Peki...","Sorun değil. Nasıl istersen...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+",   hava tam yerinde, hadi gidelim!",""+pchar.name+"   tabii, hiç soru sormadan! Hadi gidelim! ");
				link.l1 = RandPhraseSimple("İşte benim kızım...","Çok güzelsin, Helen...");
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			}
		break;
		
		case "sex_after":
			dialog.text = LinkRandPhrase(RandPhraseSimple("Harikaydı, "+pchar.name+"!..","Her zamanki gibi harikaydın, canım..."),RandPhraseSimple("Harikaydı, Charles!","Harika vakit geçirdim, canım!"),RandPhraseSimple("Seninle bir an bile sıkılmak mümkün değil, benim kaptanım!","Harikaydın, sevgilim!"));
			link.l1 = RandPhraseSimple("Seni seviyorum...","Seninle olmak her zaman güzel, Helen...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локаци.
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", biliyorsun ki her zaman memnuniyetle... Ama şimdi zamanı değil - o alçak Thibaut kaçmadan önce onu yakalamamız gerekiyor.";
				link.l1 = "Her zamanki gibi haklısın, Helen...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Hayır, canım, bu işe yaramaz.";
				link.l1 = "Peki, neden olmasın?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", bugün kendimi iyi hissetmiyorum. Lütfen üzülme. Bugün yapmayalım...",""+pchar.name+"Ah, sevgilim, son günlerde öyle yorgunum ki. Açıkçası, sadece uyumak istiyorum. Beni affet. Bunu başka bir zaman yapalım.");
				link.l1 = RandPhraseSimple("Peki...","Önemli değil. Nasıl istersen...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", Seni seviyorum! Hadi gidelim!",""+pchar.name+", tamam kaptan! Hadi gidelim!");
				link.l1 = RandPhraseSimple("Sen benim iyi kızımsın...","Çok güzelsin, Helen...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;
			//npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			//npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest3");
			DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest4", "LoveSex_Room_Go");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Evet, "+pchar.name+"?","Evet, benim kaptanım?","Dinliyorum. "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining");
				dialog.text = "Bunu izle, benim kaptanım!";
				link.l1 = "Vay canına, ne sıkı bir tutuş! Zaman kaybetmemişsin, Helen.";
				link.l1.go = "cutlass_training";
				NextDiag.TempNode = "Helena_officer";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && sti(pchar.GenQuest.BrothelCount) > 0 && !CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Sevgilim, genelevlere yaptığın ziyaretler hakkında.";
				npchar.quest.refusesex = true;
				link.l1 = "Ne? Helen, tamamen yanlış anladın! Ben sadece...";
				link.l1.go = "brothel_found";
				NextDiag.TempNode = "Helena_officer";
				SetFunctionTimerCondition("Helena_ClearRefuseSex", 0, 0, 180, false);
				DeleteQuestCondition("Helen_GiveSex");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Helen, Tayasal adındaki kayıp bir Kızılderili şehrini ziyaret edeceğim. Sana yalan söylemeyeceğim: bu yolculuk çok tehlikeli, dahası – bir put aracılığıyla ışınlanmayı gerektiriyor. Sen... benimle gelir misin?";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////казначей///////////////////////////////////////////////////////////
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Helen, geminin durumunu bana tam olarak anlat.";
			    Link.l11.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
				Link.l12 = "Her limana yanaştığımızda belirli malları satın almanı istiyorum.";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////казначей////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Emriniz üzerine geldim, kaptan.";
				Link.l2 = "Helen, sana birkaç emir vermem gerekiyor.";
				Link.l2.go = "Companion_Tasks";
				
				sld = GetCharacter(sti(npchar.RealCompanionIdx));
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Rainbow") && sld.ship.type == pchar.questTemp.HelenDrinking.Rainbow && CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
					DeleteAttribute(link, "");
					dialog.text = "Sence bu komik mi?";
					link.l1 = "Güzel gemi, değil mi? Senin için aldım, Helen! Bir düşün, Karayipler'de hangi adam sevgilisine gerçek bir gemi hediye eder, ha?";
					link.l1.go = "rainbow";
					
					NextDiag.TempNode = "Helena_officer";
					break;
				}
				
				NextDiag.TempNode = "Helena_officer";// не забыть менять в зависисомости от оффа
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Helen, sana danışmam lazım.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Helen, sana bir işim var...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, hadi birkaç saatliğine sadece ikimiz kamarada kalalım... ne dersin?","Sevgilim, önümüzdeki birkaç saati baş başa geçirelim mi? Bu fikir hoşuna gider mi?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, neden bir oda kiralayıp biraz baş başa vakit geçirmiyoruz... sadece ikimiz, birkaç saatliğine? Sence nasıl olur?","Sevgilim, önümüzdeki birkaç saati baş başa geçirelim mi? Bir oda kiralarız... ne dersin?");
				Link.l2.go = "room_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "town" && sti(pchar.money) >= 1000 && GetNpcQuestPastDayWOInit(npchar, "special_sex_date") >= 30 && !CheckAttribute(npchar, "quest.refusesex"))
			{
				Link.l2 = "Helen, canım, seni meyhanede biraz vakit geçirmeye davet edebilir miyim?";
				Link.l2.go = "special_sex";
			}
			if (CheckAttribute(pchar, "questTemp.MysteryPortRoyal_Helena")) {
				link.l4 = "Helen, galiba hayranın Francis’in vasiyetini buldum. Mirasını sana bırakmış.";
				link.l4.go = "MysteryPortRoyal_Helena_1";
			}
			if (CheckCharacterItem(pchar, "pirate_cutlass") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
				link.l4 = "Bence bu pala artık senin. Blaise senin sözde amcan...";
				link.l4.go = "give_cutlass";
			}
			link.l9 = "Şu anda hiçbir şey yok, Helen.";
			NPChar.id = "Helena"; // лесник . Идентификация Элен на всяк. случай . если потеряет сознание.
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		/////////////////////////// ответы для казнаячея - Элен ..(элен казначей - ужас!))///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, canım, hasta mısın yoksa bir derdin mi var? Ne yani, benden aşağı inip ambarı süpürmemi ve fareleri saymaya başlamamı mı bekliyorsun?";
			Link.l1 = "Tamam, özür dilerim canım, benim hatam...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Ve ben de yüz toplu, saatte yirmi knot hızla giden kendi savaş gemimi istiyorum. Senin gibi ben de hayatım boyunca kaptan oldum. Git kendine bir lanet muhasebeci bul ve bu saçmalıklarla onu meşgul et.";
			link.l1 = "Haklısın, Helen. Bunun için özür dilerim.";
			link.l1.go = "exit";
		break;
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Tamamen seni dinliyorum.";
			Link.l1 = "Gemimize biniş politikamız hakkında...";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Komuta ettiğin gemi hakkında...";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Şimdilik bir şey yok.";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Ne arzu edersiniz, benim kaptanım?";
			Link.l1 = "Hiçbir yere çıkmanı istemiyorum. Kendini ve adamlarını güvende tut.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "İlk fırsatta düşman gemilerine çıkmanı istiyorum.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Evet, benim kaptanım?";
			Link.l1 = "Gemiyi ele geçirdikten sonra başka bir gemiyle değiştirmemeni rica ediyorum. O benim için çok değerli.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Eğer bir gemiye çıkarsan, ödül gemisini iyice incele. Eğer işe yarar bir şeyse, onu kendine alabilirsin.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Pekala, düşüneceğim.";
			Link.l1 = "Bunu düşünecek... Sanki ona emir verebilirmişim gibi, değil mi.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Pekala, düşüneceğim.";
			Link.l1 = "Bunu düşünecek... Sanki ona emir verebilecekmişim gibi, değil mi.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Pekala, düşüneceğim.";
			Link.l1 = "Bunu düşünecek... Sanki ona emir verebilirmişim gibi, tabii.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Pekala, düşüneceğim.";
			Link.l1 = "Bunu düşünecek... Tabii, sanki ona emir verebilirmişim gibi.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "Emirler?";
            Link.l1 = "Burada dur!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Beni takip et ve yetiş!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Ateşli silahlarınız için mühimmat türünü değiştirin.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Mühimmat türünü seçin:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Hemen, kaptan!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Hemen, Kaptan!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "İşte buradasın! Sonunda seni buldum... Ne maceraydı ama, benim kaptanım! Böyle bir çatıdan koşup, o yükseklikten atlayan birini hiç görmemiştim! Kalbim yerinden fırlayacaktı! Bir gün bu numaralarınla beni öldüreceksin, sevgilim... Aa, yalnız değilsin... Bu kız kim?";
			link.l1 = "Bu, ünlü İngiliz Deniz Alayı 'Deniz Tilkileri'nin komutanı Albay Fox'un kızı Catherine Fox. Onu Antigua'ya götürüyoruz.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Öyle mi... Hoş geldiniz, Bayan Fox! Hayır, hayır, Kaptan de Maure'un koluna girmeyin, kendi başınıza gayet güzel yürüyebilirsiniz! Şimdi, hadi sandalımıza geçelim - buradan hemen çıkmamız gerekiyor."; 
			link.l1 = "Ha! Teşekkürler, Helen! Sensiz ne yapardım ben? Catherine, bizi takip et!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Sonunda uyandın, canım! Nasıl hissediyorsun? Beni ölümüne korkuttun...";
			link.l1 = "Helen, ne oldu? Başım çatlıyor...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Kaptanın kamarasına girdiğimizde, yerde hareketsiz yatıyordun. Kalbim neredeyse duracaktı! Çocuklar seni kaldırıp gemimize sürüklediler—tam zamanında, çünkü güvertede yatan ölü adamlar tekrar ayağa kalkmaya başladılar.   Ne korkunç bir şeydi bu! Az kalsın Tanrı'ya inanacaktım! Ne kılıçlarımız ne de kurşunlarımız onlara hiçbir zarar vermedi! Hemen halatları kestik ve uzaklaşmaya çalıştık, ama onların gemisinden gelen bir yaylım ateşi bizimkini ağır hasara uğrattı ve kontrolü kaybettik. Sonra yelkenlerini açıp bir anda gözden kayboldular.   Gemimiz karaya oturdu, bu yüzden fırtına onu tamamen yok etmeden önce bu kıyıya kaçmak zorunda kaldık. Bugün birçok iyi insan öldü, ama sonunda gemi hayatta kaldı... keşke onu terk etme emrini vermeseydim...";
			link.l1 = "Senin suçun değil, Helen. Doğru kararı verdin. Sensiz ne yapardım ki?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Seni tekneye sürükledim ve sonra karaya çıkardım. Ölü gibiydin, sadece kalbin çok hafif atıyordu. Bak! Ellerim hâlâ titriyor";
			link.l1 = "Teşekkür ederim, sevgilim. Sana borçlandım. Ne zamandır burada yatıyorum?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Tüm bir gün boyunca yaralarını temizleyip sardım, sana ilaç verdim ve biraz da rom içirdim. Şimdi iyileşmen gerek!";
			link.l1 = "Bu sefer ölmeyeceğim, sevgilim. Ama kendimi pek iyi hissetmiyorum... ugh....";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Söylesene... Gerçekten o meşhur 'Uçan Hollandalı' mıydı, Charles? Neden bize saldırdılar? Ve neden yaklaşırken ateş açmadılar da, gemiye çıkar çıkmaz bizi batırmaya çalıştılar?";
			link.l1 = "Kaptanları o muska için gelmişti, ben de o konuda Tuttuathapak adında bir Kızılderili şamanla konuşmuştum. Neden bu kadar önemliydi, bilmiyorum... ama liderleri muskayı alır almaz, bizi ortadan kaldırdılar... Tanrı aşkına, ne korkunç bir kâbus! Mürettebatı yaşayan ölülerden oluşan bir gemi! İnanılır gibi değil...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Şimdi de bizim sıramızdı 'Uçan Hollandalı'yla karşılaşmak. Ah! Tüylerim diken diken oluyor! Bir sonraki limanda kiliseye gideceğim, bir mum yakacağım ve mucizevi kurtuluşumuz için Rabbimiz İsa Mesih'e dua edeceğim. Hatta o kadar minnettarım ki, birkaç Katolik azizine bile dua edeceğim...";
			link.l1 = "Senin yanında olacağım, Helen. Uzun zamandır doğru dürüst bir günah çıkarmadım... Ama önce, o köye geri dönmemiz gerekiyor. Tuttuathapak'a her şeyi anlatmalıyım. O lanetli gemi bize musallat oldu çünkü muska yüzünden! Umarım o kızıl derili şeytan, şu yaşayan ölülerin o şeye neden ihtiyaç duyduğuna dair bir fikre sahiptir.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Pekala. Ama dikkatli olmalıyız – yaraların henüz tam iyileşmedi.";
			link.l1 = "Ama daha çabuk iyileşmem için bana yardım edeceksin, değil mi? Seni seviyorum, Helen...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "Ben de seni seviyorum, canım...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+",  sana bir kez söyledim, artık kaderlerimiz ortak. Senin kaderin benim kaderim. Ne zaman gidiyoruz?";
			link.l1 = "Bunu duyduğuma çok sevindim. Oraya gittiğimizde sana biraz daha anlatırım. Önce kendimizi hazırlamamız gerek.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Hazırım, benim kaptanım! Seninle dünyanın sonuna kadar gelirim!";
			link.l1 = "Teşekkür ederim, sevgilim...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "Oh, "+pchar.name+"! Seni görmek ne güzel! Seni Isla Tesoro'ya ne getirdi?";
			link.l1 = "Her zamanki gibi – iş güç. Sadece uğrayıp seni de görmek istedim. Her şey yolunda mı, Helen?";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			dialog.text = "Sevgili valimize ne oldu, Kaptan? Bu kez kimin kıçını tekmeleyeceğiz? İspanyolların mı, korsanların mı, yoksa daha beter birinin mi?";
			link.l1 = "Daha da kötü, Helen, hem de çok daha kötü. Vali pahalı bir metresiyle buluşmaya niyetli, ben de ona ilginçlik olsun diye eşlik edeceğim. Sevgilisine gerçek bir korsan, maceraperest ve deniz kurdu getireceğine söz vermiş. Yani beni sıkıcı sohbetler, aşırı pahalı şaraplar ve donuk soylular bekliyor.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Tam tersi, nazik bir hanımefendinin düzenlediği hoş bir davete davet edildim. Ekselansları bana eşlik etmemi isteyerek beni şaşırttı ama dürüst olmak gerekirse, işten biraz uzaklaşıp kafamı dağıtma fırsatı bulduğum için memnunum.";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Evet... Demek ki korkulan Kaptan Charles de Maure, onların eğlencesi için maymun gibi giyinip dans edecek? Ne hoş! Benim daha iyi bir fikrim var. Hadi yelken açıp buradan defolup gidelim. Eğer uzun zamandır hak ettiğin bir tatile hazırsan, Isla Tesoro'ya gidelim. Orada her zaman hoş karşılanırız. Güneşlenmek, beyaz kumlar, eski dostlar, rom punch, kafamızı dağıtmak... ne istersen.";
			link.l1 = "Bak, bütün bunlar harika geliyor ve ben de isterim... ama sonra. Valiye söz verdim, bu iş yaşlı adam için önemli ve...";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Peki ya ne? Soylu kanının onlar için bir anlamı olduğunu mu sanıyorsun? Fransız kanından olmayabilirim ama onların 'yüksek sosyetesini' gayet iyi bilirim ve onlar için Charles de Maure, adamların peşinden gittiği, hayatlarını emanet ettiği bir kaptan değil. Onlar gibi bir centilmen de değil. Gerçek centilmenler denize açılıp barut dumanı içinde savaşmaz. Charles de Maure onlar için sadece sofralarına ilginç bir ek. Bir evcil leopar ya da süslenmiş bir ev kölesi gibi! Süs bir oyuncak! Ne zamandan beri böyle bir muameleyi kabulleniyorsun?!";
			link.l1 = "Helen, lütfen sakin ol. Eminim, valinin memnuniyeti ve gelecekteki refahımız için birkaç rahatsız edici bakışa katlanabilirim. Güçlü dostlara sahip olmak iyidir. Sonuçta, bu bir gemiye çıkarma ekibine liderlik etmekten daha kolay olacak! Ve bu 'işe yaramazlar' her zaman öyle değildir. Yüksek sosyetede bile değerli insanlar var... en azından öyle olması gerekir.";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Her neyse. (Saçını savurur) Ama uyarıyorum - beni o süslü elbiselerden birine sokmanın imkânı yok. Eğer beni götürmeye kalkarsan, pantolonumu giyeceğim. Karayiplerdeki bütün hanımefendiler bayılsa da umurumda olmaz.";
			link.l1 = "Seni buna zorlamayacaktım. İkimizin de acı çekmesinin anlamı yok. Bu daveti atlatacağım ve sonra Isla Tesoro'ya yelken açacağız. Bir ödül olarak, ambarımda mükemmel bir İspanyol Madeira kasasını saklıyorum...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Oh ho ho, Charles! Yani sen diyorsun ki, ben böyle saygın bir topluluk için yeterince iyi değilim? Pantolon giyen bir kız geceni mahveder mi yani? Ne ilginç. Peki öyleyse, ama sen de kendini bir züppe gibi giyinmeyi unutma. Şık elbiseli maymunlar, bir saraylı kadının bile kalbine dokunabilir. Gösterinin tadını çıkar!";
			link.l1 = "Helen, bekle! Kahretsin... kadınlar!";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Evet, biraz dinlenmeyi hak ettik, orası kesin. Ama yemin ederim, bu iş için kendimi o süslü elbiselerden birine sokacak değilim. Senin kadınının erkek gibi, denizci gibi giyindiği dedikodusu sence ne kadar uzağa yayılır?";
			link.l1 = "Ah... Bence bu pek iyi bir fikir değil. Nasıl desem... bu, erkeklerin eşlerini ya da saygın hanımefendileri getirdiği bir etkinlik değil...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "Ha! Fahişeler ve sefahat! Ne harika - yani bir orgiye gidiyorsun! O zaman neden baştan doğru düzgün söylemedin? Şanslısın ki ben kıskanç bir kadın değilim de seni olduğun yerde vurmayacağım. En azından şimdilik.";
			link.l1 = "Helen, lütfen, yaptığım tek şey valimize eşlik etmek, bunu benden özellikle rica etti ve çok ısrarcıydı. Orada kesinlikle lanet olası fahişeler olmayacak\nBekle, yanlış oldu... Yani fahişelerle yatmak da olmayacak... Aman Tanrım! Sadece saygımı sunuyorum!";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "Bence saygılarını sunmak için şık giyinmelisin, Kaptan de Maure. Sonuçta orası yüksek sosyete. Yaka ve manşet olmadan oraya gitmek tam bir rezalet olur. Hatta bir orgi için bile. İyi eğlenceler.";
			link.l1 = "Helen, bekle! Kahretsin... kadınlar!";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Kelepçe ve bir tasma, Kaptan. Belki biraz dantel de olur. Duyduğuma göre yine moda olmuş. Ama ben ne anlarım ki!";
			link.l1 = "Oh Helen, hadi ama!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Şuna bak! Sevgili kaptanım, sefahat âleminden eve dönmüş!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Yerel soylular hâlâ yeni maymunlarından memnun mu? Duyduğuma göre, dün geceki gösterin dillere destan olmuş! Gemiler ve fahişeler üzerine kumar oynamak, soylu prenslere düello teklif etmek mi? Lütfen bana ne haltlar çevirdiğini açıklar mısın?";
			link.l1 = "Helen, açıklamama izin ver! O kadar basit değil. Kahretsin, üzgünüm ama Madame Botot'nun evinde geceyi geçirmek zorunda kalacağımı hiç düşünmemiştim. Sadece orada uyudum, evet, tek başıma, yemin ederim! Ve evet, bir kart oyununda bir fırkateyn kazandım. Düşünebiliyor musun?";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Pekâlâ! Ya büyük bir yalancısın, ya azizsin, ya da ahmak. Kazandığın fahişelerle gemileri sonra konuşuruz – şimdi bana düelloyu ve neden herkesin seni bir veliaht prensine meydan okuduğunu konuştuğunu anlat.";
			link.l1 = "Taç prensi değil, sadece bir kontun piçi. Çok nüfuzlu bir soylunun, Kont de Levi Vantadour'un oğlu. Bak, başlatan ben değildim! Önce o bana meydan okudu, şimdi de düelloyu kazanmalıyım ama onu fazla yaralamadan, yoksa babasının gazabını üzerime çekerim.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Ah, 'sadece bir kontun oğlu', öyle mi? Şaka mı yapıyorsun Charles?! Peki bunu nasıl başaracağız? Ya hile yaparsa? Seni öldürür!";
			link.l1 = "Bu yüzden Ekselansları bana asil şahitler verdi. Yanıma sadece onları alacağım – işler ters giderse, en azından her şeyin düello kurallarına ve yasalara uygun olduğunu kanıtlayabilirim. Yokluğumda fırkateyni göz kulak olmanı istiyorum.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Şunu bir netleştirelim... Bütün bir gün ve gece ortadan kayboldun, bir kart oyununda bir fahişe ve bir fırkateyn kazandın. Şimdi de, öldürmene izin verilmeyen bir soylu piçiyle dövüşmek üzeresin, ben ise burada öylece oturup bekleyeceğim, öyle mi? Bütün bunlar hakkında ne hissetmemi bekliyorsun?!";
			link.l1 = "Helen, dinle, bana kızmakta sonuna kadar haklısın ve gerçekten üzgünüm, ama sadece...";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Biliyor musun, artık yeter. Git işini hallet! Ben de kabinini tozlar, kirli çamaşırlarını yıkarım! Sakın paçayı kurtardığını sanma. Bu iş bittiğinde konuşacağız. Yeni fırkateynine de ben göz kulak olurum, büyük Kaptan de Maure, hiç merak etme. Ha, bir de Kaptan de Maure, ölmemeye çalış... çünkü seni öldürmeyi ben planlıyorum. Şimdi müsaadenle, kamarama kapanıp kabininde bulduğum şu güzel madeira şarabının bir şişesini içeceğim.";
			link.l1 = "Helen, bırak açıklamama izin ver! Kahretsin... Yine başlıyoruz!";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Son Paris modasına göre, beyefendilerin gemileri ve saraylı kadınları satın almak yerine kart oyunlarında kazanmaları gerekiyormuş! Üstelik, iyi bir izlenim bırakmak isteyenin, önceki sahiplerini düelloya davet etmesi şartmış. Bu sefer kendini neyin içine soktun sen, Allah aşkına?!";
			link.l1 = "Helen, o kadar basit değil. Kahretsin, üzgünüm ama Madame Botot'nun evinde geceyi geçirmek zorunda kalacağım aklımın ucundan geçmezdi! Dün gece tam anlamıyla yorucu ve acımasız bir zeka savaşına dönüştü. Ve evet, kartlarda kanlı bir fırkateyn kazandım. Düşünebiliyor musun?";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Harika. Bu durumda bir de metres mi kazandın? Peki ya kazandığın fırkateyn—ona karşı neyi ortaya koydun? Bizim gemiyi değil, öyle değil mi...";
			link.l1 = "Mecbur kaldım. Bak, artık önemi yok, sonuçta kazandım. Rakibim beni düelloya davet etti ve hile yapmakla suçladı. Kendisi son derece nüfuzlu bir soylunun, Kont de Levi Vantadur'un piç oğlu. Yani onu öldürmemek ya da fazla yaralamamak için elimden geleni yapmam gerekecek.";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Aynısını o da yapar mı? Aklını mı kaçırdın, Charles? Gemini, hayatını, başka bir kadın için riske atıyorsun?! Buna gerçekten değer mi? Benim senin için hiçbir anlamım yok mu?!";
			link.l1 = "Helen, kıskanman için hiçbir sebep yok, yemin ederim. Her şey kendiliğinden oldu. Bunu yapmak zorundaydım ve vali, her şeyin kurallara uygun olması için bana asil subayları şahit olarak verdi. Seni ya da adamlarımızdan kimseyi yanıma alamam. Ben yokken fırkateyni gözün gibi koru, lütfen.";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "Harika! Önce, tuhaf kadınlarla bir orgiye gidiyorsun, ertesi sabah çıkıp geliyorsun, ben de sana tek laf etmiyorum. Şimdi de bana, neredeyse gemimizi bir kumar oyununda kaybedeceğini ama bir fahişe kazandığını söylüyorsun! Ve şimdi de onun 'onuru' için, öldürmene bile izin verilmeyen soylu bir piçle dövüşmek üzeresin! Bütün bunlar karşısında ne hissetmemi bekliyorsun? Söyle bana.";
			link.l1 = "Helen, dinle, bana kızmakta sonuna kadar haklısın, ama bir açıklama yapmama izin ver...";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "Biliyor musun, artık yeter. Git ve şu lanet düellonu yap. Senin yeni fırkateyninle ben ilgilenirim, büyük Kaptan de Maure, hiç merak etme. Şimdi müsaadenle, kamarama kapanıp senin kamaranda bulduğum o nefis madeira şarabının bir şişesini içeceğim. Ama sana bir şey olursa, Tanrı şahidim olsun, bu kasabanın üstüne cehennem ateşi yağdırır, bu genelevi ve sevgili Ekselanslarının sarayını yerle bir ederim!";
			link.l1 = "Helen, her şey yoluna girecek, bana güven... Dur, nereye gidiyorsun?! Kahretsin! Yine başlıyoruz...";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, açıklaman gereken bazı şeyler var. Lütfen bana ne halt olduğunu anlatır mısın? Nöbeti düzgün tutmadım ve tayfa içiyordu... Birkaç alçak gemimize saldırıp biz uyurken bizi bağladı. Sonra o pislikler bana, seni kurtarmak için ne kadar ileri gideceğini sordular. Sonunda beni ambarın içine kilitlediler. Kaç gündür beklediğimi artık sayamıyorum!";
			link.l1 = "O alçak, ona yaşattığım utancın intikamını almak istedi. Sana bir şey yapmasından korktum! Tanrıya şükür, iyisin!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "Beni geri almak için bir şey yapmak zorunda kaldın, değil mi? Kötü bir şey, öyle mi?";
			link.l1 = "Önemli olan tek şey, tekrar yanımda olman. Sana karşı başarısız oldum, Helen. Çok üzgünüm! Umarım kalbinde beni affedecek bir yer bulabilirsin!";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Yaptım bile. Ne söylediğimi düşünmek için çok vaktim oldu... Ben de üzgünüm, Charles. Keşke o markizle işlerini bu kadar kişisel algılamasaydım. O gece doğru dürüst nöbet tutardım, tetikte olurdum. Ah! Ben sadece işe yaramaz bir kadınım!";
			link.l1 = "Bunu söylemeyi bırak, geçmiş geçmişte kaldı. Seni seviyorum ve bir daha asla seni bırakmayacağım. Söz veriyorum!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Sanırım tam olarak ne yaptığını bilmesem daha iyi olur, değil mi? Peki, yine birlikteyiz ve önemli olan da bu.";
			link.l1 = "Senden hiçbir şey saklamıyorum. Sana her şeyi anlatacağım...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Ne karmaşa... Biliyorum, başka seçeneğin yoktu, ama bunu Di Lu Parkes ve arkadaşlarına nasıl açıklayacaksın? Yani, artık bir suçlusun!";
				link.l1 = "Bu bedeli ödemeyi ben seçtim, ama aslında başka seçeneğim yoktu. Merak etme, bir yolunu bulup itibarımızı geri kazanacağım. Olmazsa da, Isla Tesoro'da her zaman hoş karşılanacağız! Sen yanımda olursan, her şeyin üstesinden gelirim.";
			}
			else
			{
				dialog.text = "Ne hikaye ama, Charles... Bence bu konuda seçeneğin yoktu, ama şimdi ne olacak? O İngiliz her şeyi düzeltecek mi, yoksa savaş mı çıkacak? O alçağı zincire vururlarken Basse-Terre'e gelip bunu görmek istemediğine emin misin?";
				link.l1 = "Biliyor musun Helen, iki hafta önce bunu asla kaçırmazdım. Ama bugün diyorum ki, cehenneme kadar yolu var! Artık onun hak ettiği cezayı bile umursamıyorum. Biz yine birlikteyiz, önemli olan sadece bu!";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Biliyorsun, her zaman yanında olacağım. Ha! Seninle ilk kez başımız belaya girmiyor ya. Yine başarırız.";
				link.l1 = "Doğru. Hadi yelken açalım, sevgili! Ufuk bizi bekliyor!";
			}
			else
			{
				dialog.text = "Düşünce tarzını beğendim, Charles! Artık soylular yok: Fransız, İngiliz, İspanyol - ne fark eder. Sanırım bir tatili hak ettik!";
				link.l1 = "Anlaştık. Sadece sen ve ben! Artık ne valiler, ne de soylu piçler var!";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Evet, kaptan!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Harika olur! Gidip çocuklara demir almaya hazır olmalarını söyleyeceğim! Ve Charles...";
				link.l1 = "Biliyorum, Helen, biliyorum. Birazdan sana katılacağım.";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, başardın! Portekizliler bana her şeyi anlattı! Ne hikaye ama!";
			link.l1 = "Tanrıya şükür, hayattasın Helen! Seni tekrar gördüğüme ne kadar sevindiğimi bilemezsin!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Bu arada, bana bir şey anlatacağına söz vermiştin, hatırlıyor musun? Hem büyük hem de karmaşık bir şey. İşte fırsatın, Kaptan. Ne oldu, anlat bakalım?!";
			link.l1 = "Seni seviyorum, Helen. Gerisi önemsiz.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Evet, bu gerçekten yardımcı oldu ama... Kahretsin, ben de, Charles. Ben de seni seviyorum. Tanrım, seni ne kadar çok özlemişim!";
			link.l1 = "Ben de. Gel benimle, bu gece seni burada bırakmam, gökyüzü bu zavallı kasabanın üstüne yıkılsa bile. Bir daha asla seni bırakmayacağım. Asla.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Sanırım tam olarak ne yaptığını bilmesem daha iyi olur, değil mi? Evet, yine birlikteyiz ve önemli olan da bu.";
			link.l1 = "Senden hiçbir şey saklamıyorum. Sana her şeyi anlatacağım...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "İnanılır gibi değil! Az önce Fransa ile İngiltere'nin benim yüzümden savaşın eşiğinde olduğunu mu söyledin?";
			link.l1 = "Hayır, Helen. Çünkü çok kötü bir hata yaptım. Ama seni geri getirmek ve her şeyi düzeltmek zorundaydım.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "Bunların hepsi çok dokunaklı ve romantik, hatta her şeyin nasıl başladığını neredeyse unutmaya hazırım. Neredeyse. Ama ciddi söylüyorum, seni tutukladılar çünkü Portekizliler o lanet brigantinin adını yanlış mı vermiş?";
			link.l1 = "Aksine, bana doğru olanı verdi! Bunu nasıl başardığını ve nedenini keşke bilseydim. Bu arada, kendisi nerede?!";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Gitti. Beni buraya getirdikten hemen sonra. Senin kazandığın o hayat kadınının 'misafirperverliğini' kabul etmek istemedim, bu yüzden Bartholomew'den bana bir oda kiralamasını istedim. Parayı ödedi ve tek kelime etmeden kayboldu. Aslında, dur, hayır, sana bir mektup bırakmış!";
			link.l1 = "Bir mektup mu? Portekizli Bartholomew'dan mı? Bu yeni bir şey. Bunun nereye varacağını hiç beğenmiyorum...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Pekala, ben çocuklara merhaba demeye giderken sen burada oku. Endişelenmiş olmalılar. O suratsız, mahzun yüzleri özleyeceğim aklıma gelmezdi! Bu arada, lütfen kendini yeni bir felakete daha sürükleme!";
			link.l1 = "Lanet olsun... Hâlâ seni geri getirdiğime inanamıyorum!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "Beyaz kum, berrak yeşil su, sen, ben ve güzel bir şarap – Charles, bu gerçekten çok romantik! Böyle yürüyüşlere daha sık çıkmalıyız, olur mu!";
			link.l1 = "Beğenmene sevindim. Bence artık buna daha çok zaman ayırmalıyız.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Charles, ne yapıyorsun ve neden diz çöküyorsun? Bu da nereden çıktı şimdi...";
			link.l1 = "Helen, seni seviyorum. Ve bana bahşedilen her günü seninle yaşamak istiyorum. Bu yüzden, burada ve şimdi, bu deniz ve gökyüzünün önünde, senden rica ediyorum - Helen Beatrice Sharp - bana insan ve Tanrı huzurunda, ölüm bizi ayırana dek yanında durma onurunu verir misin? Ben, Charles de Maure, Chevalier de Monper, sana soruyorum - benimle evlenir misin?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "Biliyor musun, bu resmiyetlerden hiç hoşlanmadım ama seninle dünyanın sonuna kadar varım. Ve soruna gelince, cevabım... ah, pardon, döktüm!";
				link.l1 = "Boşver, sadece şarap ve bu gömleği zaten hiç sevmezdim...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, elbette evet! Evet, evet ve tekrar evet!!! Ama umarım bizi ömrümüzün sonuna kadar şalgam yetiştirmek için tozlu bir aile şatosuna kapatmayı düşünmüyorsundur?";
				link.l1 = "Eh, bir aile şatomuz var ama tozlu değil ve orada kalmayacağız. Bizim hayatımız özgürlük ve ufuk avucumuzun içinde!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "O zaman sana, benim kaptanım, kocam ve düğünümüze bir kadeh kaldıralım!";
			link.l1 = "Sana, aşkım! Ve birlikte geçireceğimiz geleceğimize, bizi bekleyen o kadar çok şey var ki!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "O halde sana, kaptanım, kocam ve düğünümüze bir kadeh kaldıralım!";
			link.l1 = "Senin için, aşkım! Ve birlikte geçireceğimiz geleceğe, bizi bekleyen o kadar çok şey var ki!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Yani, Rahip Benoit geri döndü ve bizi evlendirmeye hazır. Ama bilmeni isterim, böyle bir gün için bile elbise giymem! Sence pantolon giymem olay yaratır mı?";
			link.l1 = "Helen, seni her kıyafette seviyorum, onlar da alışır. Önce, misafirler ve tören hakkında seninle konuşmak istedim.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "Evet, bir sorun var - en yakın dostlarımızın çoğu, bu günü birlikte kutlamak isteyeceğimiz insanlar, şehre bile alınmayacak, kiliseye girmeleri ise imkânsız. O yüzden - burada, olması gerektiği gibi, tüm önemli kişilerle evlenelim, sonra Isla Tesoro'ya gidip gerçek dostlarımızla asıl kutlamamızı yapalım. Ne dersin?";
			link.l1 = "Bana uyar! Benediktin Başrahibi Benoit ile konuşurum, ama davetiyeleri göndermemiz ve daha fazlasını yapmamız gerekiyor...";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "Sakin ol, kaptan. Sevgili müstakbel eşin yükün bir kısmını üstlenecek! Isla Tesoro'da her şeyi ayarlayacağım ve dostlarımıza yazacağım, sadece söyle: nasıl bir düğün istiyorsun?";
			link.l1 = "Sadece sen, ben ve en yakın dostlarımız. Buradaki tüm resmi tantanadan sonra, Martinique'te, biraz gerçek samimiyet isteyeceğiz.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Herkes bu günü hatırlamalı! Herkesi çağırın! Kimse dışarıda kalmayacak!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Sıcak ve samimi - tam da düşündüğüm gibi! Sharptown'a uğramamız gerekecek ve her şeyi ben ayarlarım. Sanırım elli fıçı rom ve iki düzine fıçı şarap yeterli olur. Ayrıca, yemek ve eğlence için üç yüz bin sekizlik altına ihtiyacımız olacak.";
			link.l1 = "Bana tekrar hatırlatır mısın – neden geminin hesaplarını yine sen yönetmiyorsun? Hepsini halledeceğim. Sadece başrahibe kısa bir uğrayacağım, sonra Sharptown'a yelken açıyoruz.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Yani, gerçek deniz kurtları gibi bir parti mi yapmak istiyorsun? Peki! Sharptown'a uğramamız gerekecek ve her şeyi ben ayarlarım. İyi bir hazırlık yapmamız lazım – sanırım yüz varil rom ve elli varil şarap yeterli olur. Diğer masraflar da en az beş yüz bin sekizlik tutar.";
			link.l1 = "Korsan Kardeşliği'nin tamamını mı davet ediyorsun? Aman neyse, hadi yapalım! Malzemeleri ben ayarlarım. Sadece rahibe kısa bir uğrayalım, sonra Sharptown'a yelken açarız.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Helen");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Charles, yüklemeyle ilgileneceğim, sonra barona davetiyeleri dağıtıp meyhaneciyle anlaşacağım. Çok uzun sürmez.";
			link.l1 = "Endişelenme sevgilim, kendime faydalı bir iş bulurum... Ya da kumda biraz kestiririm. Tanrı aşkına, kendi düğünümü planlamaktan Tortuga'yı basmak daha kolay olacak deseler inanmazdım.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Biraz dinlendin mi, Charles? Sana bir iyi, bir de kötü haberim var. Kötü haber şu ki, geçen hafta buradakiler o kadar eğlenmiş ki, lanet 'Yaşlı Ağaçkakan' meyhanesini yanlışlıkla yakıp kül etmişler! İyi haber ise şu: baron, biz dönene kadar meyhanenin eskisinden daha büyük ve güzel şekilde yeniden inşa edileceğine söz verdi. Ben de gerekenleri ayarladım, artık denize açılabiliriz.";
			link.l1 = "Umarım düğünümüzden sonra şehirde arkamızda böyle bir kül yığını bırakmayız. Ne yazık, 'Yaşlı Ağaçkakan'ı gerçekten seviyordum - sıcak, samimi, hafif bir kusmuk ve zift kokusuyla! Neyse sevgilim, haklısın - artık gitmeliyiz.";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Jan şimdiden Gladys ile birlikte şehirde, düşünebiliyor musun? Düğünüme gerçekten geleceklerini hiç düşünmemiştim! Aman Tanrım! O korkunç Hint tapınak şehrindeyken bile, şu anki kadar korkmamıştım!";
			link.l1 = "Her şey yolunda, sevgilim, her şey yolunda. Ben de endişeliyim – heyecan normal. Misafirler zaten geldiğine göre, Benoit Baba'nın yanına gidip ayinin ne zaman başlayacağını öğrenmeliyim.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Bugün gerçekten lanet olasıca uzun ve zor bir gün olacak... Jan ve Gladys'i görmeye gidiyorum.";
			link.l1 = "Onların gelebilmesine sevindim. Yaşlı Svensson seni kendi kızı gibi seviyor, Bayan McArthur ise belki daha da fazla. Bugün burada olmaları iyi oldu. Git ve endişelenme – her şey yoluna girecek.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Helen");
		break;
		
		case "LongHappy_20":
			dialog.text = "Evet.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Evet.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Evet.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Ben, Charles Henry de Maure, Monper şövalyesi, seni, Helen Beatrice Sharp, eşim olarak kabul ediyorum; bugünden itibaren, iyi günde ve kötü günde, zenginlikte ve yoksullukta, hastalıkta ve sağlıkta, ölüm bizi ayırana dek, sana sahip çıkacağıma ve yanında olacağıma söz veriyorum. Tanrı'nın kutsal yasasına göre, Tanrı'nın huzurunda, bu yemini ediyorum.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Ben, Helen Beatrice Sharp, seni, Charles Henry de Maure, kocam olarak kabul ediyorum; bugünden itibaren, iyi günde ve kötü günde, zenginlikte ve yoksullukta, hastalıkta ve sağlıkta, ölüm bizi ayırana dek yanında olacağıma söz veriyorum. Tanrı'nın kutsal yasasına göre, Tanrı'nın huzurunda, bu yemini ediyorum.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amin.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Helen Beatrice de Maure, Madame de Monper - ah, kulağa ne hoş geliyor, sevgili kocacığım!";
			link.l1 = "Bundan iyisini duymadım, karıcığım!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "Biliyor musun – bunun hiçbir şeyi değiştirmeyeceğini sanmıştım, belki de gerçekten öyle – seni zaten seviyordum ve hayatımın geri kalanını seninle geçirmek istiyordum, ama bugün, bu kutsal tören... Gerçekten mutluyum, Charles! Hiç olmadığım kadar mutluyum, bir de Gladys ve Jan'a bak – ışıl ışıllar! Etrafta ne kadar çok mutlu yüz var! Bu arada – artık misafirlerin arasına karışıp tebriklerini kabul etme zamanı. İşin bitince geri gel, unutma – Sharptown'da bizi bekliyorlar.";
			link.l1 = "Hemen hallederim, tatlım. Gitmeden önce bir öpücük ver!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Merhaba kocacığım, misafirlerle konuştun mu?";
			link.l1 = "Henüz değil, sabırlı ol, karıcığım, yakında döneceğim.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Evet, hiç bu kadar çok tebrik aynı anda duymamıştım. Ve biliyor musun - bence çoğu gerçekten içtendi!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "Evet, bu soylular şaşırtıcı derecede samimi – itiraf etmeliyim ki, daha fazla sahtekârlık ve ikiyüzlülük bekliyordum. Ya da belki de o kadar mutluyum ki hiçbir şeyi fark etmiyorum. Ama ne de olsa, dostlarımız bizi Sharptown'da bekliyor! Ne zaman yelken açıyoruz?";
			link.l1 = "Şimdi hemen. Kartal kanatlarında dostça bir ziyafete doğru süzüleceğiz. Umarım, karım, bu geceyi kamarada geçirmemize bir itirazın yoktur?";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Ah evet, kocacığım, ne kadar romantiksin! Ve öyle kıpırdanma, artık seni herkesin önünde öpebilirim... Evet, şimdi gidebiliriz!";
			link.l1 = "Seyirci, rotayı Sharptown'a çevir ve hiçbir sebeple bizi rahatsız etme! Üzerimize hayalet filosu gelse bile umurumda değil!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Ah sevgili kocam, çok mutluyum! Bugün harika bir gün...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Hadi ama Charles. Bu yalancı yere düşmeden ölecek!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "İyiyim, Charles, sorun yok. Nathan nasıl?";
			link.l1 = "Çok fazla kan... Dannie, nefes alıyor mu? Onun nefes aldığını görüyorum!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Daha hızlı, sevgilim, vakit kaybetme!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Charles, iyi misin? Ne kan gövdeyi götürdü! Üzgünüm, biz yukarıda sıkışıp kaldık, bir düzine o alçak vardı, önce onlarla uğraşmam gerekti!";
			link.l1 = "Sorun yok, hallettim. Jacques'la olan o hikayeyi sonunda bitirebildiğim için mutluyum... nihayet. Hak ettiğini buldu.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Pekala, canım, burada işimizi bitirelim ve geri dönelim. Nathan'ı düşünmeden edemiyorum, o nasıl? O kurşundan beni korudu!";
			link.l1 = "Haklısın, canım, ben de endişeleniyorum. Devam et, hemen arkandayım.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "Marcus'ı bulduk! Kargo ambarındaydı, bağlı ve baygındı.";
			link.l1 = "Hayatta mı?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Merak etme, sevgilim, Baron Tyrex hepimizden uzun yaşayacak. Daha yeni uyandı ama şimdiden kıpır kıpır, sürekli romunu, kılıcını ve köprüyü istiyor – tam da bu sırayla.";
			link.l1 = "İşte bizim eski Marcus! Biz burada işimizi bitirene kadar biraz dinlensin, sonra sahile geri döneriz.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Çok üzgünüm, canım... Önce sadık dostumuz Tichingitu, şimdi de Gino... Barbazon, yaptıklarının hesabını ödemek için on kere öldürülmeliydi!";
				link.l1 = "Ne yazık ki, bunu sadece bir kez yaptım. Ben de kendimi kötü hissediyorum... Ama kazandık ve o artık kimseye zarar veremeyecek.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Gino için kendimi çok kötü hissediyorum, Charles! Öğrendiğimde inanamadım! Sen nasılsın, sevgilim?";
					link.l1 = "Ben de inanamıyorum... böyle bir son... Bugünün böyle geçeceği aklımın ucundan bile geçmezdi.";
				}
				else
				{
					dialog.text = "Merak ediyorum, acaba gelecekteki tarihçiler Korsan Körfezi'ndeki büyük savaşı yazacak mı? Kıyı Kardeşliği'nin baronlarının açık savaşta karşılaştığı gün - eminim İspanyol Costa Garda şükürden gözyaşı döküyordur! Ama yine kazandık! Dostlarımız hayatta, düşmanlarımız ise toprak altında - ne muhteşem bir düğün hediyesi!";
					link.l1 = "Evet, tam bir kutlama oldu, ama başardık, meleğim. Başardık.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Hadi, Dannie kasabanın dışında bize bir ev buldu, şimdi gemiye dönmek istemiyorum, önce bir toparlansın. Oturup, aramızda olmayanlar için içelim.";
			link.l1 = "Evet, Helen, gidelim.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Gino için kendimi çok kötü hissediyorum, Charles! Öğrendiğimde inanamadım! Sen nasılsın?";
				link.l1 = "Ben de inanamıyorum... Ne biçim bir son... Bugünün böyle olacağını asla hayal etmemiştim.";
			}
			else
			{
				dialog.text = "Hawk'u gördün mü? Gino 'tehlike geçti' deyince Dannie beni dışarı çıkardı. Her şeyin yolunda olmasına sevindim. Dostlarımız hayatta, düşmanlarımız ise öldü - bundan daha güzel bir düğün hediyesi olamazdı!";
				link.l1 = "Ben de, sevgilim. Ve kazandık. Barbazon öldü, baronlar kalan adamlarını topluyor. Savaş bitti.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, ayakta zor durduğunu görüyorum, ama meyhaneye uğradım ve barmenin anlattıklarına inanamazsın.";
			link.l1 = "Evet, bunu Jan'dan duydum, o da oradaymış. Bana kalırsa sevgili Yerlimiz savaş yoluna girmiş. Hadi Sabo-Matila Koyu'na doğru yürüyelim, birkaç kişi onu o tarafa giderken görmüş.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Tanrım! İşte bu ruh, Tichingitu! Off, burada gülmekten kendimi kaybettim! Neden biz Avrupalılar da böyle bir geleneği benimsemiyoruz ki?! Ah Charles, ayakta uyuyacaksın neredeyse! Hadi, Dannie bize burada, kenarda bir ev bulmuş - biraz dinlenmen gerek.";
			link.l1 = "Öne geç ... Sanırım daha önce o sahilde uyuyakalmıştım.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "tonzag_jailed":
			dialog.text = "... Sorun değil.";
			link.l1 = "Bunu duymak güzel.";
			link.l1.go = "exit";
			link.l2 = "Gerçekten mi?";
			link.l2.go = "tonzag_jailed_1";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Evet.";
			link.l1 = "Duymak güzel.";
			link.l1.go = "exit";
			link.l2 = "Hadi ama, bir şeyin seni rahatsız ettiğini görebiliyorum!";
			link.l2.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Ben gayet iyiyim, bırak artık!\nCharles, cehenneme git! Zindanlardan nefret ediyorum, senden nefret ediyorum ve bu lanet adadan da nefret ediyorum! Hemen çıkar beni buradan!\nÜzgünüm... Zindanlardan gerçekten hoşlanmıyorum, bana dokunma!";
			link.l1 = "Üzgünüm. Hepimizin korktuğu bir şeyler var.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "AAAA! Bizi buradan çıkarın! Charles, bir şeyler yap!";
			link.l1 = "Kendine gel!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Kaptanım, düşman ikinci güverteden geminin gövdesini delip içeri sızdı ve bir çıkarma ekibi gönderdi. Geminin her yanında çarpışmalar sürüyor, topçu ekiplerinin çoğu etkisiz hale getirildi! Mürettebatımızı ve Hercule’ü kurtarmamız gerek! Sen mi gideceksin, yoksa ben mi gideyim?";
			link.l1 = "Bu sefer kendim gideceğim, Helen! Geminin komutasını al ve bizi buradan çıkar!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Emredersiniz, Benim kaptanım. Sizi hayal kırıklığına uğratmayacağım, lütfen siz de dikkatli olun!";
			link.l1 = "Biliyorum, Helen. Sen de dikkatli ol!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Zafer, Benim Kaptanım! Çıkarma birliği yok edildi, düşman geri çekilmeyi seçti ve güneye yöneldi. Geminin durumu kabul edilebilir. Hayatta kalan mürettebat: "+GetCrewQuantity(pchar)+" insanlar. Rapor tamamlandı!";
			link.l1 = "Teşekkür ederim, Helen, ve ne...";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Soy beni, galibim, ödülün benimle istediğini yapmak!";
			link.l1 = "Uh...";
			link.l1.go = "tonzag_after_victory_2";
			link.l2 = "Hadi gidelim!";
			link.l2.go = "tonzag_after_victory_2";
		break;
		
		case "tonzag_after_victory_2":
			dialog.text = "Ah, merhaba, Hercule. Kusura bakma, tam da uygun olmayan bir anda geldin! Ama seni sağ ve başkasının kanına bulanmış halde görmek harika - senin doğal halin bu, değil mi!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog");
		break;
		
		case "tonzag_after_victory_3":
			dialog.text = "";
			link.l1 = "Vay be, Helen, sen de neymişsin!";
			link.l1.go = "tonzag_after_victory_4";
		break;
		
		case "tonzag_after_victory_4":
			dialog.text = "Daha yeni başlıyorum, benim kaptanım. Kutlayalım mı?";
			link.l1 = "İkna edilmeye ihtiyacım yok!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Bakma, bakma, bakma... Burası başka bir dünya, benim kaptanım! Böyle olmamalı!";
			link.l1 = "Bence artık burası bizim dünyamız, sevgilim. Ve haklısın, hadi oyalanmayalım...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Korkarım bu salgın kızlarını kötü etkiliyor, Rodrigo. Onları örgü örmekle ya da başka bir şeyle meşgul et!";
			link.l1 = "Bu konuşmanın hiçbir yere varmayacağı belli. Yarın kiliseye gideceğimize söz verdik. Dua etmek için... tabii ki.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Seninle gurur duyuyorum, sevgilim!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Pekala, Charles...";
			link.l1 = "Yine ne düşünüyorsun, Helen?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "Karayipler'in en skandal çifti olarak iki koca adaya sahip olmamız! Benim korsan sığınağım Isla Tesora ve senin vaat edilmiş toprakların - sence medeniyet sonunda Batı Hint Adaları'na ulaştığında bunlar ne kadar dayanır?";
			link.l1 = "Hayatımız boyunca yetecek kadar uzun, sevgilim. Peki ya sonrası? Olanları biz kontrol edemeyiz. Başkaları bizim hikayemizi anlatacak. En önemlisi, sen ve ben burada ve şimdi, birlikte ve mutluyuz.";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Mutluluktan söz açılmışken... Şimdi yukarı çıkmam gerek: Mumları yakacağım, yatağı hazırlayacağım, belki günlüğüme bir şeyler yazarım...";
			link.l1 = "Ben burada biraz daha kalacağım, sonra yukarı gelip sana 'yatağı hazırlamada' yardım edeceğim.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Çok oyalanma...";
			link.l1 = "";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("LoveSex_Classic", 2.5);
			NextDiag.CurrentNode = "sex_after";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "drinking_refuse":
			dialog.text = "Gerçekten bu kadar meşgul müsün? Ne yazık, ama anlıyorum. Kendimi oyalayacak başka bir şey bulurum.";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
			
			pchar.questTemp.HelenDrinking.Result = "no_visit";
			CloseQuestHeader("HelenDrinking");
		break;
		
		case "drinking_accept":
			dialog.text = "Bunu hatırlaman güzel. Sana gerçekten minnettar olduğumu söylemek istedim. Her gün biri seni... sen de biliyorsun neyden, kurtarmıyor. Hadi bir şeyler içelim. Benden olsun.";
			link.l1 = "Helen... Gladys ne diyecek?";
			link.l1.go = "drinking_accept_1";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToHouse");
		break;
		
		case "drinking_accept_1":
			dialog.text = "Çok komiksin, Charles. Hadi, ve beni sinirlendirme.";
			link.l1 = "Bu bir randevu mu?";
			link.l1.go = "drinking_accept_1_1";
			link.l2 = "Geliyorum, sinirlenmene gerek yok.";
			link.l2.go = "drinking_accept_1_2";
		break;
		
		case "drinking_accept_1_1":
			dialog.text = "Ha-ha! Sen öyle san! Tamamen sarhoş olmam gerekirdi!";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_accept_1_2":
			dialog.text = "Bu daha iyi.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_in_tavern":
			dialog.text = "";
			link.l1 = "... birçok meziyeti vardı, ama içkiyi kaldıramazdı. Biz de böyle tanıştık.";
			link.l1.go = "drinking_in_tavern_1";
			link.l2 = "... babam askeri hizmette ısrar etti. Ben de razı oldum ve bir tavsiye mektubuyla Paris'e gittim. Ama verilen adrese hiç ulaşamadım ve bir sanatçı oldum.";
			link.l2.go = "drinking_in_tavern_2";
		break;
				
		case "drinking_in_tavern_1":
			dialog.text = "Ah, şimdi hangi erdemlerden bahsettiğini anladım. Adı neydi?";
			link.l1 = "Lulu.";
			link.l1.go = "drinking_in_tavern_1_1";
		break;
		
		case "drinking_in_tavern_1_1":
			dialog.text = "Lulu... Bu hikâyelerle Paris'i bana tamamen mahvettin. Orayı büyük bir hayatın şehri sanırdım, ama anlattıklarına bakılırsa koca bir lüks genelevden farksız.";
			link.l1 = "Genelevleri kınıyor musun?";
			link.l1.go = "drinking_in_tavern_1_2";
		break;
		
		case "drinking_in_tavern_1_2":
			dialog.text = "Evet, Kaptan, ve bu yerlere giden erkekleri hiç anlamıyorum.";
			link.l1 = "(kupaya dalgın dalgın bak)";
			link.l1.go = "drinking_in_tavern_1_4";
			link.l2 = "(korkunç bir öksürük tutar)";
			link.l2.go = "drinking_in_tavern_1_4";
			link.l3 = "Ee... herkesin kendi tercihi... sanırım?";
			link.l3.go = "drinking_in_tavern_1_4";
		break;
		
		case "drinking_in_tavern_1_4":
			dialog.text = "(güler) Ha! Yüzünü görmeliydin! Korktun mu? Bir tane daha içelim! Paris'e!";
			link.l1 = "Paris'e!";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_2":
			dialog.text = "(güler) S-sen mi?! Bir sanatçı? Demek ki İngiliz filosunun güzelliği ve gururu, bir tecavüzcü ve tam bir alçak olan Donovan, Parisli bir sanatçının ellerinde öldü? Ah, keşke o muhteşem jabot'unu kuşanıp gemiye öyle çıksaydın da o pisliği bastonunla dövseydin!";
			link.l1 = "Evet, gerçekten talihsiz bir tesadüf. O gün jabot yıkanıyordu, ne yapalım.";
			link.l1.go = "drinking_in_tavern_2_1";
		break;
		
		case "drinking_in_tavern_2_1":
			dialog.text = "(gülerek) Teşekkür ederim, Charles. Gecenin geri kalanı nasıl geçer bilmiyorum ama akşam şimdiden harika oldu. Belki portremi yapmana bile izin veririm. Ama dikkat et, Parisli kızlarını resmettiğin tarzda olmasın!";
			link.l1 = "Ha! Yani, seni resmetmeyi kabul edersem.";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_3":
			dialog.text = "Affedersin, kaptanım, maceralarını ve o asil... iki cinsten de saraylıların hayatlarını dinlerken, köpekbalığı ısırsa beni, zamanını daha değerli bir şeye harcayamadığına asla inanmam! Sakın bana bütün yaptığının tuvalleri karalamak ve babanın parasını çarçur etmek olduğunu söylemeye kalkma. Eğer gerçekten öyle olsaydı, bizimle bir gün bile hayatta kalamazdın.";
			link.l1 = "Başka uğraşlarım vardı...";
			link.l1.go = "drinking_in_tavern_" + pchar.HeroParam.HeroType;
		break;
		
		case "drinking_in_tavern_herotype_3":
			dialog.text = "";
			link.l1 = "Saray hayatını askerlikle birleştirdim, ama... hehe, tabii ki babamın istediği şekilde değil. Birkaç kez pencereden kaçıp, bir kavgaya karıştıktan sonra muhafızlarla arkadaş oldum. Doğal olarak, çok şey öğrendim, vücudum güçlendi. Büyüklerim bana darbeye dayanmayı, zırh giymeyi, kılıç kullanmayı ve gerçekten dinlenmeyi öğrettiler. Özellikle sonuncusu tam bana göreydi tabii. İnanmayacaksın ama, herkes sabahın köründen öğlene kadar kılıç sallayıp, sonra da öğleden ertesi sabaha kadar içebilecek kadar dayanıklı değil.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_1":
			dialog.text = "";
			link.l1 = "Sence başkentte, kötü bir şöhrete ve boş bir cebe sahip bir soylu için her şey kolay mıydı, daha ilk gün babamın tavsiye mektubunu kaybetmişken? Kendimi göstermek, kimsenin alay etmesine izin vermemek zorundaydım. Evde aldığım eskrim derslerini unutmadım, her küçümseyici bakışa bir düelloyla karşılık verdim. Sonra bu işten gerçekten keyif almaya başladım. Yine de kimseyi öldürmedim ve Paris'ten, beni kolayca alt edecek tecrübeli bir dövüşçüyle karşılaşmadan ayrılmayı başardım.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_4":
			dialog.text = "";
			link.l1 = "Mezarlıklarda çok vakit geçirdim. Kötü bir şey düşünme – sadece benim çevremde yaygın bir eğlenceydi. Cesaretimizi toplamak için geceleri mezarlığa gider, çitin üstüne boş şişeler dizer ve zamana karşı onlara ateş ederdik. Sabah olunca yüzlerce mermi ve bir kasa şampanya harcamış olurduk. Şimdi tabii ki böyle davranmaktan utanıyorum, ama o zamanlar kazanan iyi bir ödül alır ve saraylı hanımlardan bazı... iltifatlar görürdü. Her şeyden faydalanırdık – barut karışımlarıyla bile biraz uğraşmışlığım var. Ama neden hiçbirimiz kağıt fişek yapmayı öğrenmeyi akıl edemedik – hâlâ bilmiyorum.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_2":
			dialog.text = "";
			link.l1 = "Okudum, hem de oldukça gayretliydim – neredeyse Sorbonne’a kabul edilecektim. Bir süre ofiste çalıştım, ama bir noktadan sonra sıkıcı hale geldi; genel olarak ise her işten biraz yaptım. Babamın eski bir dostu olan öğretmenim, teoriden çok pratiğe önem verirdi, bu yüzden Paris’i her yönüyle görme ve her türden insanla – haydutlardan soylulara kadar – konuşma fırsatım oldu. Bütün bunlar burada fazlasıyla işime yaradı.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_4":
			dialog.text = "Ve... hepsi bu mu? Demek ki içinde hâlâ bir şeyler var, benim kaptanım. Senin bile henüz fark etmediğin bir şey. Senin şerefine!";
			link.l1 = "Şerefe!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernChange");
		break;
		
		case "drinking_my_background":
			dialog.text = "";
			link.l1 = "Hikayeni anlat bana, Helen. Başkentteki maceralarım, otuz yaşını bile doldurmamış bir kızın yüz kişilik bir şalopayı komuta etmesinin yanında sönük kalıyor.";
			link.l1.go = "drinking_my_background_1";
		break;
		
		case "drinking_my_background_1":
			dialog.text = "Otuzun altında, öyle mi Charles? Böyle cesur bir laf ettin, o zaman bir sonraki turu sen ısmarlayacaksın! Bütün adamlarım öldü, artık bir şalupa komuta etmiyorum. Açıkçası, bir daha komuta edebilecek miyim, bilmiyorum.";
			link.l1 = "Üzgünüm, Helen. Yaralı bir yerine dokunmak istememiştim. Ama neden kaptanlık kariyerinin bittiğini düşünüyorsun?";
			link.l1.go = "drinking_my_background_2";
		break;
		
		case "drinking_my_background_2":
			dialog.text = "Because my crew is dead, and a different one won't ever accept me. Eh! Fine, my captain, you've told me a lot about your life; now it's my turn! The truth is not at the bottom of this mug, so let's dispense with the mystery.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_3";
		break;
		
		case "drinking_my_background_3":
			dialog.text = "Benim durumum, Charles, benzersiz. Babam buraların en iyi denizcilerinden biriydi, Orman Şeytanı ona büyük saygı duyardı, tayfası ona tapardı ve o da beni hayatından çok severdi.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_4";
		break;
		
		case "drinking_my_background_4":
			dialog.text = "Bu şeylerden birini bile alsaydı, ya beni Londra'ya, o sözde medeniyete gönderirdi ya da burada annem gibi solup gitmeme izin verirdi. Başlarda her şey yolunda gitti: Özgürlük istiyordum, gerçek özgürlük, Charles, ve sadık bir mürettebatla bir savaş gemisine ustaca komuta etmek insana tam da bunu verir. Babam da bana elinden gelen her şeyi verdi. Onunla birlikte denize açıldım, on iki yaşımdaydım, ilk altı ayı ambarlarda fare kovalayarak geçirdim, ancak ondan sonra tayfalarla birlikte çalışmama izin verildi.";
			link.l1 = "Sean MacArthur seni gemi faresine mi çevirdi? Üzgünüm Helen, ama bundan dönüş yok! Mürettebat sana nasıl davrandı?";
			link.l1.go = "drinking_my_background_5";
		break;
		
		case "drinking_my_background_5":
			dialog.text = "Well, perhaps I'm exaggerating a bit for the sake of a good story? My father's crew accepted me; he gathered fine people. But since then, I've been afraid... of holds and any small dark spaces in general. Ha! Svensson almost killed my father when he found out!";
			link.l1 = "Senin için önemli biri. Kaderinde onun da en az Sean kadar payı olduğu belli.";
			link.l1.go = "drinking_my_background_6";
		break;
		
		case "drinking_my_background_6":
			dialog.text = "Evet. Tüm baronlar babama açıkça aptal olduğunu söylediler, ama Tayfa Rekorunu direğe tırmanarak kırdığımda ona onayını verip elini sıkan Orman Şeytanı oldu. O anı asla unutmayacağım: tayfanın zafer çığlıkları ve nereye baksam uzanan sonsuz deniz ufku. Ve babamın onaylayan bakışı—göremedim ama tüm kalbimle hissettim.";
			link.l1 = "Zaferim, Guadeloupe'a giden yolda ilk gün direklerden düşmemle sona erdi.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.TakeFolke")) {
				link.l1 = link.l1+" Dümencim Deluc'un da yüzünde çok şey anlatan bir ifade vardı."}
			link.l1.go ="drinking_my_background_7";
		break;
		
		case "drinking_my_background_7":
			dialog.text = "Ah-ha-ha! I can imagine! Don't worry, that was a long time ago; now you're a real sea wolf!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_8";
		break;
		
		case "drinking_my_background_8":
			dialog.text = "Zaferlerimize!";
			link.l1 = "Dinleyin, dinleyin!";
			link.l1.go = "drinking_my_background_12";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "... And then I gradually rose through the ranks, served at the captain's table in councils with my father and officers. Learned a lot. From the age of fifteen, they started taking me on military campaigns, and I killed a man in my very first battle. It was a disgusting campaign; we shouldn't have set sail on a Monday... Really shouldn't have!";
			link.l1 = "On beş yaşında mı? Beni korkutuyorsun, Helen.";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "Ne olduğunu bile anlayamadım. Hollandalı tüccarın öncüsü vardı - Şirketin paralı askerleri. Cesurca oynamaya karar verdiler ve kıç güvertemize karşı saldırıya geçtiler. Ben de, aptal gibi, hayatımdan hiç korkmadan, sarı kafamı dışarı uzattım. Hemen bir tabancanın dipçiğiyle kafama vurdular. Ama ondan bir an önce, rapierimi Şirketten bir ahmağın karnına saplamayı başardım.";
			link.l1 = "Aman Tanrım, ya Sean? O olaydan sonra seni neden karaya atmadı?";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_13":
			dialog.text = "Babam da o savaştan yara almadan çıkmadı, ve benim çatlak, aptal kafamı görmek de ona hiç iyi gelmedi. Yavaş yavaş çökmeye başladı, muhtemelen bunu benden başka kimse fark etmedi. Sonra da gitti. Vasiyetine göre, Rainbow'u mürettebatıyla birlikte ve gemiyi bir yıl yüzdürecek kadar parayla ben miras aldım.";
			link.l1 = "Peki, mürettebat seni kaptan olarak kabul etti mi?";
			link.l1.go = "drinking_my_background_14";
		break;
		
		case "drinking_my_background_14":
			dialog.text = "Biz bir masalda yaşamıyoruz, benim kaptanım. Babamın vasiyetine bazıları düşmanca yaklaştı – işler tatsız bir hal aldı\nEğer Gökkuşağı'ndan tek bir denizci bile benim komutamda hizmet etmeyi reddedip gemiyi terk etseydi, bu benim itibarım için felaket olurdu. Ama Svensson araya girdi ve herkesi hizaya soktu. O zamanlar, mürettebattan kimse açıkça ayrılmadı... o zaman. Yedi yıl boyunca güzelliğimin kaptanlığını yaptım, Orman Şeytanı için şüpheli mallar taşıdım, hazineler aradım, yaşadım... Ama şimdi, bunların hepsi geçmişte kaldı.";
			link.l1 = "Geçmişte değil. Senin yeniden kendi bayrağın altında yelken açacağına inanıyorum! Hadi buna içelim!";
			link.l1.go = "drinking_my_background_sea";
			link.l2 = "Gemiye tekrar kavuşamayabiliriz, ama rapirin hâlâ yanında.";
			link.l2.go = "drinking_my_background_land";
		break;
		
		case "drinking_my_background_sea":
			dialog.text = "Biliyor musun, bunu böyle söylediğinde ben de inanıyorum. Hadi içelim!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_COMMERCE, 5);
			AddCharacterSkill(npchar, SKILL_ACCURACY, 5);
			AddCharacterSkill(npchar, SKILL_CANNONS, 5);
			AddCharacterSkill(npchar, SKILL_SAILING, 5);
			AddCharacterSkill(npchar, SKILL_REPAIR, 5);
			AddCharacterSkill(npchar, SKILL_GRAPPLING, 5);
			AddCharacterSkill(npchar, SKILL_DEFENCE, 5);
			notification("Naval Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "sea";
		break;
		
		case "drinking_my_background_land":
			dialog.text = "Ama rapierim bana mutluluğu getirecek mi? Cevabı muhtemelen bu kupanın dibinde bir yerde. Hadi içelim!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_F_LIGHT, 5);
			AddCharacterSkill(npchar, SKILL_FENCING, 5);
			AddCharacterSkill(npchar, SKILL_F_HEAVY, 5);
			AddCharacterSkill(npchar, SKILL_PISTOL, 5);
			AddCharacterSkill(npchar, SKILL_FORTUNE, 5);
			AddCharacterSkill(npchar, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(npchar, SKILL_SNEAK, 5);
			notification("Personal Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "land";
		break;
		
		case "drinking_my_background_15":
			dialog.text = "Avrupa'daki hayatını düşündüm... Bak, sen şehirli bir züppesin, ben ise sıradan bir kızım, ama dünyanın en tehlikeli köşesinde şimdiden kendimize bir isim yaptık.";
			link.l1 = "Kulağa bir kadeh kaldırmalık geliyor! Peki, bizi birleştiren bir şey var mı?";
			link.l1.go = "drinking_my_background_16";
		break;
		
		case "drinking_my_background_16":
			dialog.text = "Babamın omuzlarında yükseliyorum ben. Bilmiyorum, senin ailenden de sana az etki gelmemiştir herhalde? Belki de henüz farkında değilsin?";
			link.l1 = "Kardeşimi hapisten çıkardıktan sonra ona sorarım.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernEmpty");
		break;
		
		case "drinking_game":
			dialog.text = "Pekala, bu kadar, benim kaptanım. Hikayelerimizi paylaştık, artık geceyi sonlandıralım.";
			link.l1 = "Hmm, akşamın başka bir şekilde biteceğini ummuştum.";
			link.l1.go = "drinking_game_1";
		break;
		
		case "drinking_game_1":
			dialog.text = "Gece henüz bitmedi. Bir oyun öneriyorum: kartlarını doğru oynarsan, belki duaların kabul olur.";
			link.l1 = "Kart oynayacağız mı? Ben varım!";
			link.l1.go = "drinking_game_2";
		break;
		
		case "drinking_game_2":
			dialog.text = "Sakin ol, deniz kurdu. Seninle striptiz pokeri oynamam.";
			link.l1 = "Evet, haklısın Helen. Burada hiç mahremiyetimiz yok.";
			link.l1.go = "drinking_game_3";
		break;
		
		case "drinking_game_3":
			dialog.text = "Bu eksik olan tek şey değil, Charles... Bu bir kart oyunu değil ama merak etme, eminim bunda da ustasındır. 'Hiçbir Zaman Hiç' oynadın mı, duydun mu?";
			link.l1 = "Tanıdık. Önceki bir hayattan. Ve sık sık çalar mısın?";
			link.l1.go = "drinking_game_4";
		break;
		
		case "drinking_game_4":
			dialog.text = "Her zaman denemek istemiştim, ama oynayacak kimsem yoktu.";
			link.l1 = "İlk kadehimizi paylaşırken böyle cesur bir oyun mu oynayacağız? Emin misin?";
			link.l1.go = "drinking_game_5";
			link.l2 = "Bu arada, herkes nerede? Burada yalnız mıyız?";
			link.l2.go = "drinking_game_6";
		break;
		
		case "drinking_game_5":
			dialog.text = "Evet, son yaşananlardan sonra biraz yaşamak istiyorum. Biraz çılgınlık yapmak, anlıyor musun?";
			link.l1 = "Hayır, bu işin sonu hep kötü biter, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Hadi başlayalım! Önce hanımlar!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_6":
			dialog.text = "Hepsini eve gönderdim - yabancıların kulak misafiri olmasına gerek yok.";
			link.l1 = "Hayır, bu işlerin sonu hep kötü biter, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Hadi başlayalım! Önce hanımlar!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_refuse":
			dialog.text = "Ne yazık, ama belki de haklısın. O zaman bir içki daha?";
			link.l1 = "Başlayalım! Önce hanımlar!";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_refuse_1":
			dialog.text = "Her şeyi ayarladım - üst kattaki oda senin. Orada önemli bir Fransız subayı kalıyordu, ama Orman Şeytanı'nın adamları ona nazikçe odayı boşaltmasını söylediler. Git biraz uyu - seni bu halde sokaklarda dolaşmana ya da daha kötüsü, denize açılmana asla izin vermem.";
			link.l1 = "Evet, hanımefendi!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToTavernRoom");
		break;
		
		case "drinking_game_accept":
			dialog.text = "Ha! Hık! Yani sen başlıyorsun!";
			link.l1 = "Dikkatli ol, sevgilim! Hmm. Ambarlarda hiç fare kovalamadım!";
			link.l1.go = "drinking_game_accept_1";
		break;
		
		case "drinking_game_accept_1":
			dialog.text = "Demek öyle mi? Demek ki sana karşı tetikte olmam lazım! (İçer)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_2";
		break;
		
		case "drinking_game_accept_2":
			dialog.text = "Brr! Sadece o anıyı hatırlamak bile... Neyse, sıkı dur yakışıklı: Direkten hiç düşmedim ben!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_3";
		break;
		
		case "drinking_game_accept_3":
			dialog.text = "";
			link.l1 = "Harika yaptınız! İzin verin, mademoiselle, sizin şerefinize içeyim! (İçer)";
			link.l1.go = "drinking_game_accept_4";
		break;
		
		case "drinking_game_accept_4":
			dialog.text = "";
			link.l1 = "Hiçbir zaman batıl inançlı olmadım.";
			link.l1.go = "drinking_game_accept_5";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 1;
			SetCamShuttle(loadedLocation);
			SetPitch(0.95);
		break;
		
		case "drinking_game_accept_5":
			dialog.text = "Ve sen kendine denizci diyorsun! Ne tür insanlar olduğumuzu çok iyi biliyorsun. Bu yolculuğun ne getireceğini, ne zaman ya da nerede karaya çıkacağını asla bilemezsin, belki de hiç göremeyeceksin. Cevapları haritaların ve pusulaların ötesinde aramalısın! Şerefine! (İçer)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_6";
		break;
		
		case "drinking_game_accept_6":
			dialog.text = "Ve bizzat resmettiğin kızlar... Sonuçtan memnun kaldılar mı?";
			link.l1 = "Resimleri her zaman beğenmezlerdi ama, ıı... sonuç – her zaman.";
			link.l1.go = "drinking_game_accept_7";
		break;
		
		case "drinking_game_accept_7":
			dialog.text = "Charles! O zamanlar tanışsaydık, ya seni vururdum ya da fidye için rehin alırdım. Bu arada, hiç fırça elime almadım.";
			link.l1 = "Hey!   Bu tamamen sıradan bir şey. Sevgili Helen, eğer senin hiç kalkışmadığın şeyleri saymaya başlarsam...";
			link.l1.go = "drinking_game_accept_8";
		break;
		
		case "drinking_game_accept_8":
			dialog.text = "Pekâlâ, tamam, adil oynayacağım. Sıra sende, benim kaptanım.";
			link.l1 = "(Yudumlar) Hık! Hmm... Modellerimin bana tabanca kabzasıyla vurduğu hiç olmamıştı.";
			link.l1.go = "drinking_game_accept_9";
		break;
		
		case "drinking_game_accept_9":
			dialog.text = "(Yudumlar) Off. Bu oyunu tamamen yanlış oynuyoruz, canım. Birbirimizi tanıyıp içki içeceğiz sanmıştım, ama onun yerine laf sokup... ve... ve... Hık. Kahretsin!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_10";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 2;
			SetCamShuttle(loadedLocation);
			SetPitch(0.90);
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Hadi işi biraz daha ilginç hale getirelim! Ve tercihen bir saat önce konuştuğumuz şeylerden olmasın!";
			link.l1 = "Bir içki âleminden sonra hiç yabancı bir yerde uyanmadım.";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Ah! Kahretsin, Charles! (İçer)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_11":
			dialog.text = "Ben... Hıç... inanamıyorum. İtiraf ediyorum, suçluyum - küçük Rumba eskiden kafayı çekmeyi severdi. Ama asla hapse girmedim!";
			link.l1 = "Nasıl başardın...?";
			link.l1.go = "drinking_game_accept_12";
		break;
		
		case "drinking_game_accept_12":
			dialog.text = "Hahaha! İç, iç!";
			link.l1 = "Bundan pişman olacağım. (İçer)";
			
			if (IsCharacterEquippedArtefact(pchar, "totem_01")) {
				link.l1.go = "drinking_game_accept_13";
			} else {
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_LightsOut");
			}
		break;
		
		case "drinking_game_accept_13":
			dialog.text = "Hadi ama, sevgilim. Son soru ve beni alt etmen için son şans!";
			link.l1 = "Hayır... Ben... Hadi biraz temiz hava alalım.";
			link.l1.go = "drinking_game_enough";
			link.l2 = "Çoğu zaman içmişimdir, ama hiç böyle değil... Bir kızla bu kadar s-sarhoş olmamıştım. Şerefim üzerine yemin ederim, i-çmek gerçekten b-büyük bir günah...";
			link.l2.go = "drinking_game_accept_14";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 3;
			SetCamShuttle(loadedLocation);
			SetPitch(0.85);
		break;
		
		case "drinking_game_enough":
			dialog.text = "Eh!";
			link.l1 = "";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_accept_14":
			dialog.text = "";
			link.l1 = "B-bekle... İçmiyor musun?";
			link.l1.go = "drinking_game_accept_15";
		break;
		
		case "drinking_game_accept_15":
			dialog.text = "Ah-ha-ha! Bu çok komik! Hedefin büyük, benim kaptanım. Olsun... hık!... bilmiş ol...";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_16";
		break;
		
		case "drinking_game_accept_16":
			dialog.text = "Tamamen erkeklerden oluşan bir mürettebat arasında yaşamak gibi bir talihsizliğim var ve dikkatli davranmak zorundayım. Ben dürüst bir kızım.";
			link.l1 = "Senin adına m-mutluyum, H-Helen.";
			link.l1.go = "drinking_game_accept_17";
		break;
		
		case "drinking_game_accept_17":
			dialog.text = "Sen daha da mutlu olacaksın, çünkü ben kazandım! Ama dürüst olmak gerekirse, ben de hiçbir adamla bu kadar sarhoş olmamıştım.";
			link.l1 = "(Sessizce bir yudum alır) S-sana. Tebrikler... h-hıç...";
			link.l1.go = "drinking_game_accept_18";
		break;
		
		case "drinking_game_accept_18":
			dialog.text = "Hey-hey-hey! Kaptan, nereye gidiyorsun? Yoksa gücendin mi?";
			link.l1 = "Biraz... ara mı versem? Sadece kılıcımı bulmaya gidiyorum...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_ExitTavern");
		break;
		
		case "drinking_at_svenson":
			dialog.text = "Kaptan, hazır mısın? Geri dönüş yok, ve eğer bir şey ters giderse, seni kendime eş yaparım.";
			link.l1 = "Of! Bari biraz nefes alayım! Bundan emin misin, Helen?";
			link.l1.go = "drinking_at_svenson_1";
		break;
		
		case "drinking_at_svenson_1":
			dialog.text = "Evet, kahretsin, öyle dikilip durma! Kendimi kaybetmem lazım, sadece bir gece bile olsa!";
			link.l1 = "Korkarım bu geceden sonra, kaybolmak isteyen ben olacağım. Hadi gidelim, yoksa bütün kasabayı uyandıracağız.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_EnterSvenson");
		break;
		
		case "drinking_give_key":
			dialog.text = "Cap, take the key and go upstairs. There should be a chest; you probably saw it when Svensson had it. Grab the barrel and head back immediately.";
			link.l1 = "Dur bir dakika, sevgilim, patronunu neden soymam gerekiyor?";
			link.l1.go = "drinking_give_key_1";
			
			GiveItem2Character(pchar, "key3");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_give_key_1":
			dialog.text = "Don't be silly. I've been here since childhood; if the owners return, I can handle it and cover for you. Come on, don't lower your sail now!";
			link.l1 = "Bıçak gibi keskin, tam bir kaçakçı! Bekle, hemen dönerim.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GotKey");
		break;
		
		case "drinking_got_whiskey":
			dialog.text = "Anladın mı?";
			link.l1 = "Tabii ki! Boşalttığım ilk sandık değil, sonuncusu da olmayacak!";
			link.l1.go = "drinking_got_whiskey_1";
		break;
		
		case "drinking_got_whiskey_1":
			dialog.text = "Seninle gurur duyuyorum! Haha! Birinci sınıf İrlanda viskisi, 'Bushmills'! Böyle bir içkiyi meyhanede bize vermezlerdi.";
			link.l1 = "Kulağa hoş geliyor, ama Svensson onun kaybolduğunu fark etmeyecek mi?";
			link.l1.go = "drinking_got_whiskey_2";
		break;
		
		case "drinking_got_whiskey_2":
			dialog.text = "Bunu kesinlikle fark edecek, ama kendisi içmiyor. Görünüşe göre onu korsan arkadaşı Dodson'a hediye etmek için saklamış, ama Dodson ya ortadan kayboldu ya da birini öldürdü...";
			link.l1 = "Bu korkunç! Böyle bir nimet ziyan olmamalı. Fıçıyı kap, hadi ortamı değiştirelim!";
			link.l1.go = "drinking_got_whiskey_3";
		break;
		
		case "drinking_got_whiskey_3":
			dialog.text = "Güzel söyledin, Kaptan. Ama bir şey daha - söyle bakalım, sandıktan başka bir şey aldın mı? Dürüstçe cevap ver.";
			if (HelenDrinking_RobbedSvenson()) {
				link.l1 = "Bir şey kaptım, bir alışkanlık, bilirsin.";
				link.l1.go = "drinking_got_whiskey_notbelieve";
			}
			
			link.l2 = "Hayır. Korsan olup olmadığımı bilmiyorum ama hırsız olmadığım kesin.";
			link.l2.go = "drinking_got_whiskey_believe";
			
			if (HelenDrinking_RobbedSvenson()) {
				link.l2.go = "drinking_got_whiskey_notbelieve";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 2;
				Notification_Approve(false, "Helena");
				pchar.questTemp.HelenDrinking.RobbedSvenson = true;
			}
		break;
		
		case "drinking_got_whiskey_believe":
			dialog.text = "Nasıl olduysa sana inanıyorum... ne aptalım!";
			link.l1 = "";
			link.l1.go = "drinking_get_out";
		break;
		
		case "drinking_got_whiskey_notbelieve":
			dialog.text = "Git ve bir sebepten dolayı hiçbir şey almadığından emin ol.";
			link.l1 = "";
			link.l1.go = "exit";
			if (!HelenDrinking_RobbedSvenson()) {
				AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
				TakeItemFromCharacter(pchar, "cask_whisky");
				sld = ItemsFromID("cask_whisky");
				sld.price = sld.pricebak;
				DeleteAttribute(sld, "pricebak");
			}
			
			NextDiag.TempNode = "drinking_got_whiskey_notbelieve";
		break;
		
		case "drinking_get_out":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
			TakeItemFromCharacter(pchar, "cask_whisky");
			sld = ItemsFromID("cask_whisky");
			sld.price = sld.pricebak;
			DeleteAttribute(sld, "pricebak");
		break;
		
		case "drinking_at_fort":
			dialog.text = "Hey, hey, canım! Dikkatini topla! Deniz meltemiyle öpülmüş yüzüm tam burada!";
			link.l1 = "Vay canına, kostümün gerçekten ilginçmiş! Kumaştan bayağı tasarruf etmiş olmalısın. Ve ben... hık! Çok şey gördüm! Ama bu... Ama bu şimdiye kadar gördüğüm en ilginç şey.";
			link.l1.go = "drinking_at_fort_1";
			locCameraFromToPos(-1.65, 44.45, 76.64, true, -5.93, 42.10, 70.13);
		break;
		
		case "drinking_at_fort_1":
			dialog.text = "Herkes öyle der, ama nedense sana inanıyorum! Gerçekten ciddi misin?";
			link.l1 = "Tabii ki, vücudunun hatlarını çok güzel ortaya çıkarıyor, ama...";
			link.l1.go = "drinking_at_fort_2";
		break;
		
		case "drinking_at_fort_2":
			dialog.text = "Ah, şimdi her şeyi berbat ettin!";
			link.l1 = "... sıradan insanlar arasında hayranlık uyandırdığından hiç şüphem yok!";
			link.l1.go = "drinking_at_fort_3";
		break;
		
		case "drinking_at_fort_3":
			dialog.text = "Bu yakıcı sıcakta, sıradan ya da o kadar da sıradan olmayan insanların ağır Avrupa kıyafetleri giymekteki bu tuhaf ve yaygın alışkanlığına hayran kalıyorum doğrusu. Köylerimiz bu yüzden daha da komik görünüyor... Kıyafetimi seviyorum, Charles. Onun içinde kendimi güzel hissediyorum ve bu bir kadın için önemli.";
			link.l1 = "O kıyafet olmadan da aynı güzellikte kalırdın, Helen.";
			link.l1.go = "drinking_at_fort_4";
		break;
		
		case "drinking_at_fort_4":
			dialog.text = "Dikkat et, benim kaptanım! Böyle tatlı sözler söylemek zavallı bir kızı yoldan çıkarabilir!";
			link.l1 = "Eğer o karşı değilse, ben de karşı değilim.";
			link.l1.go = "drinking_at_fort_5";
		break;
		
		case "drinking_at_fort_5":
			dialog.text = "Hihi! Bana başka bir şey sor istersen. Meraklı olman hoşuma gidiyor.";
			link.l1 = "O zaman kostümünüzle ilgili bir soru sıkıştıralım. Böyle bir kıyafetle denizcilerin bir kaptanı ciddiye alabileceğine inanmıyorum.";
			link.l1.go = "drinking_at_fort_6";
		break;
		
		case "drinking_at_fort_6":
			dialog.text = "Ve genel olarak denizcilerin bir kadını kaptan olarak kabul edebileceğine inanmıyorum, bu yüzden kıyafetim muhtemelen sorunlarıma katkıda bulunmadı. Ya da belki de henüz vakti olmadı, çünkü bu yeni bir şey. Kendim diktim!\nAh-ha-ha! Eskiden o şeylerden giyerdim... adı neydi onların? Bizim askerler hâlâ giyiyor! Brr... Şimdi onları görünce midem bulanıyor.";
			link.l1 = " Üniformalar mı? ";
			link.l1.go = "drinking_at_fort_7";
		break;
		
		case "drinking_at_fort_7":
			dialog.text = "Ah, evet, tam olarak bir üniforma! Kırmızı bir üniforma! Şu adamın giydiği gibi.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.GenQuest.BlockDialogCamera = true;
			AddDialogExitQuestFunction("HelenDrinking_OfficerAtFort");
		break;
		
		case "drinking_at_fort_7_1":
			dialog.text = "Ah, özür dilerim Binbaşı, izin verin size güzel bir İrlanda viskisi ısmarlayayım... hık!... özür olarak.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog2");
		break;
		
		case "drinking_at_fort_7_2":
			dialog.text = "Charles başını belaya sokmayacak, değil mi Binbaşı? Lütfen bana söyle, sokmayacak de, ne olur!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog4");
		break;
		
		case "drinking_at_fort_8":
			dialog.text = "Çok sevindim! Hadi bir içki içelim!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToVillage");
		break;
		
		case "drinking_at_miskito":
			dialog.text = "Ah. Şuna bak, ne buldum!";
			link.l1 = "Helen... Onu kullanıp... moralini mi yükselteceksin?!.. Sakın aklından bile geçirme! Datura insanı tamamen ele geçirir, gücünü emer, iradeni kırar! Farkına bile varmadan yaşayan bir ölüye dönüşürsün, sonra da çok çabuk, gerçek bir ölüye...";
			link.l1.go = "drinking_at_miskito_1";
		break;
		
		case "drinking_at_miskito_1":
			dialog.text = "Charles, ama... şu anda...";
			link.l1 = "İtiraz istemem. Sert davrandığım için üzgünüm, ama bu işin şakası yok. Bunu senden alıyorum. Ne düşündüğüne inanamıyorum... Al, şunu iç ve kendine gel.";
			link.l1.go = "drinking_at_miskito_2";
			
			GiveItem2Character(pchar, "cannabis7");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_at_miskito_2":
			dialog.text = "Üzgünüm, Charles. Tamamen haklısın, biliyorum. Bir anlık zayıflıktı. Bir daha olmayacak. Beni şeytanın ayartmasından kurtardığın için teşekkür ederim...";
			link.l1 = "Boşverelim bunu... Şimdi söyle bakalım, kasabada nasıl saygı kazandın, garnizon subaylarıyla iyi ilişkiler kurdun ve yerlilerle dost oldun?";
			link.l1.go = "drinking_at_miskito_3";
		break;
		
		case "drinking_at_miskito_3":
			dialog.text = "Svensson'a saygı duyuyorlar, bu saygının bir kısmı da bana yansıyor. Küçük kasabamız tamamen Jan'ın anlaşmaları sayesinde ayakta kalıyor. Kakao plantasyonlarından elde ettiği kârın bir kısmını kırmızı ceketlilerle paylaşıyor, Miskitolar ise ona tüm geçimlerini borçlu.";
			link.l1 = "Bu nasıl oldu?";
			link.l1.go = "drinking_at_miskito_4";
		break;
		
		case "drinking_at_miskito_4":
			dialog.text = "Kastilyalılar yönetimdeyken, yerlilere pek dokunmazlardı. Ama asiller olan Hidalgoları kovduktan sonra, bizimkiler yerel ormanların kontrolünü ele geçirmeye kalktı. Jan o zamanlar meseleyi oldukça kesin bir şekilde çözdü - hatta adamlarını Londra'ya bile gönderdi! Tabii bunu iyilikten yapmadı: her çalının sana düşman olduğu bir ormanda kakao çıkarmak umutsuz bir iş. Ama şimdi, yerliler sadece Jan'ın Porto Bello'dan Blueweld'e kaçakçılık yapmasına yardım etmiyor, aynı zamanda kendi ormanlarını da üç kuruşa kesiyorlar. Bravo, Orman Şeytanı, bravo!";
			link.l1 = "Yöntemlerini tamamen onaylamıyor gibisin.";
			link.l1.go = "drinking_at_miskito_5";
		break;
		
		case "drinking_at_miskito_5":
			dialog.text = "Miskito halkını seviyor ve saygı duyuyorum, ama Jan'ın stratejisine de saygı gösteriyorum. Bir masal diyarında yaşamıyoruz, benim kaptanım.";
			link.l1 = "Hm... Svensson'la olan ilişkin ilk bakışta göründüğünden daha karmaşık anlaşılan...";
			link.l1.go = "drinking_at_miskito_6";
		break;
		
		case "drinking_at_miskito_6":
			dialog.text = "Even more than you know. His wife has a good reason to be venomous towards me... Jan has been eyeing me since I was about fifteen. It was around the time I started walking the decks of the Rainbow as an equal, and apparently, something clicked in the Forest Devil's mind back then... But I've said too much, my captain. Let's not delve into this topic; gossiping about our patron is not very decent.";
			link.l1 = "O zaman konuyu değiştirelim. Demek istediğim, senin bu topluluğa gayet iyi uyduğun ve onların da seni kendilerinden biri olarak gördükleri.";
			link.l1.go = "drinking_at_miskito_7";
		break;
		
		case "drinking_at_miskito_7":
			dialog.text = "Benim için Kızılderililer, çingeneler ve diğer düzgün uyumsuzlarla birlikte olmak çok daha kolay, öyle denk geldi. Annemin güveçleri, sahildeki ateşler ve Rainbow’un çarmıhı – kendime sıcacık bir dünya kurmuştum, Kaptan. Her şeyi çözdüğümü sandığım anda o küçük dünyamın yerle bir olması ne kötü oldu.";
			link.l1 = "Fıçı neredeyse boşalmış... Son bir tur daha?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToShipyard");
		break;
		
		case "drinking_at_perlas":
			dialog.text = "Çok iyi geldi... Benimle vakit geçirmeyi kabul ettiğine sevindim, Kaptan. Buna gerçekten ihtiyacım vardı. Sanırım senin de vardı.";
			link.l1 = "Evet, uzun zamandır böyle rahatlamamıştım. Bu, hatırlanacak bir an olacak!";
			link.l1.go = "drinking_at_perlas_1";
		break;
		
		case "drinking_at_perlas_1":
			dialog.text = "Şu anda benim hakkımda Tanrı bilir neler düşünüyorsundur. Ben doğası gereği içine kapanık biriyim, Charles. Sadece... lanet olsun, sadece yaşadığımı hissetmek istedim! Sadece biriyle konuşmak istedim!";
			link.l1 = "Gladys ne olacak? Jan?";
			link.l1.go = "drinking_at_perlas_2";
		break;
		
		case "drinking_at_perlas_2":
			dialog.text = "Annem sürekli ağlıyor, Jan ise artık bambaşka biri gibi. Belki de bana öyle geliyor, bilmiyorum, ama sanki artık benden utanıyor gibi? Affet beni, ben... (burnunu çeker).\nYeter bu kadar, kızım. Kusura bakma, biraz kendimi kaybettim.";
			link.l1 = "Özür dilemene gerek yok. Her şeyi anlıyorum, ya da en azından öyle sanıyorum.";
			link.l1.go = "drinking_at_perlas_3";
		break;
		
		case "drinking_at_perlas_3":
			dialog.text = "Tüm bunları söylüyorum çünkü daha yeni tanıştık ve ben uzun zamandır tanıdıklarıma bile bu kadar açık olmaya alışık değilim. Bana Rumba derler, sözde karakterimden dolayı, ama gördüğün gibi bu pek de doğru bir lakap değil. İçki tamamen bitti mi?";
			link.l1 = "Bir süre önceydi, ve şafak çoktan sökmeye başladı.";
			link.l1.go = "drinking_at_perlas_4";
		break;
		
		case "drinking_at_perlas_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend") && !CheckAttribute(pchar, "questTemp.HelenDrinking.RobbedSvenson")) {
				dialog.text = "Üzgünüm, kaptanım, eğer bu akşam için başka beklentilerin vardıysa. Ben... yapamam. Bugün değil.";
			} else {
				dialog.text = "Akşam için teşekkür ederim, Kaptan. Kim bilir, belki bunu tekrar yaparız.";
			}
			link.l1 = "Elbette, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_PoormanTalk");
		break;
		
		case "ambush":
			dialog.text = "Beni buraya getirdiğin için teşekkür ederim, Kaptan. Hadi etrafa bir bakalım, olur mu? Mirasımı inceleyelim.";
			link.l1 = "Daha önce burada bulunmadın mı?";
			link.l1.go = "ambush_1";
		break;
		
		case "ambush_1":
			dialog.text = "No, it's quite a ways away; besides, I'm no pirate. This place has never been particularly fascinating, and after they killed Blaise... It's better not to linger here.";
			link.l1 = "Yapmayacağız. Seni buraya getirdiğime zaten pişmanım.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPrepareAmbush");
		break;
		
		case "after_ambush":
			switch (pchar.questTemp.HelenDrinking.IslaTesoroAmbush) {
				case "A":
					if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB") && !CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC")) {
						dialog.text = "Did you have to, Captain? Why so quick to fight? Well, one should not just a winner, I guess. Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
						pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
						Notification_Approve(false, "Helena");
					} else {
						dialog.text = "Kudos, my Captain, for trying to resolve the issue wisely before getting into a fight. Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
					}
					
					link.l1 = "Karaya çekilmiş o devasa gemi ne olacak?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "B":
					dialog.text = "You skillfully fooled those fools, my Captain! I almost burst out laughing, honest! Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					Notification_Approve(true, "Helena");
					
					link.l1 = "Kıyıya çekilmiş o devasa gemi ne olacak?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "C":
					dialog.text = "Dur biraz, bir kız nefesini toplasın! Gerçekten sen misin, Charlie Prince?";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					Notification_Approve(true, "Helena");
					
					link.l1 = "Hayatımda öyle bir zaman vardı, evet. Etkilendin mi?";
					link.l1.go = "after_ambush_c";
				break;
			}
		break;
		
		case "after_ambush_1":
			dialog.text = "Evet, haklısın. Orayı keşfetmek isterim ama dürüst olmak gerekirse, Charles, biraz korkuyorum. Hadi gidelim.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroGoToResidence");
		break;
		
		case "after_ambush_c":
			dialog.text = "Aman Tanrım, evet! Sonra bana her şeyi anlatacağına söz ver, olur mu? Çünkü ben sadece hikayelerini duydum... hem de pek ahlaksız hikayeler!";
			link.l1 = "Sana her şeyi anlatacağım... neredeyse her şeyi.";
			link.l1.go = "after_ambush_c_1";
		break;
		
		case "after_ambush_c_1":
			dialog.text = "I'll be waiting eagerly! Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
			link.l1 = "Karaya çekilmiş o devasa gemi ne olacak?";
			link.l1.go = "after_ambush_1";
		break;
		
		case "ambush_inresidence":
			dialog.text = "Daracık, soğuk bir kulübe ve saçma talepler. Şimdiden kendimi tuzağa düşmüş gibi hissediyorum!";
			link.l1 = "Şimdiye kadar potansiyel mülkle ilgili memnun olmadığını görüyorum?";
			link.l1.go = "ambush_inresidence_1";
		break;
		
		case "ambush_inresidence_1":
			dialog.text = "Hayır, Charles. Belki de fazla titizim, ama şu an için bu yer, korktuğum ve nefret ettiğim her şeyin bir özeti gibi. Umarım kiraya verebilirim... Gerçi, parayı nerede harcayacağımı da bilmiyorum.";
			link.l1 = "Kiranın değerini küçümseme. Ben kira ödemem, ama çoğu zaman tayfama ödeme yapmak için bir yol bulmam gerekir. Sen de kendine yeni bir gemi alırsın, 'Rainbow II' - kulağa hoş geliyor, sence de öyle değil mi?!";
			link.l1.go = "ambush_inresidence_sea";
			link.l2 = "Kendine para harcamanın birçok yolu var. Kişiye özel bir kılıç ve enfes bir şişe şarapla başla. Kendini şımart, Helen, bunu hak ediyorsun.";
			link.l2.go = "ambush_inresidence_land";
		break;
		
		case "ambush_inresidence_sea":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "sea") {
				dialog.text = "Teşekkür ederim, kaptanım. Bunu duymak beni mutlu etti. Özellikle ikinci kez duymak daha da güzel. Beni iyi tanıyorsun.";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
				Notification_Approve(true, "Helena");
			} else {
				dialog.text = "Teşekkür ederim, kaptanım. Bunu duymak beni mutlu etti.";
			}
			
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_COMMERCE, 5);
			AddCharacterSkill(sld, SKILL_ACCURACY, 5);
			AddCharacterSkill(sld, SKILL_CANNONS, 5);
			AddCharacterSkill(sld, SKILL_SAILING, 5);
			AddCharacterSkill(sld, SKILL_REPAIR, 5);
			AddCharacterSkill(sld, SKILL_GRAPPLING, 5);
			AddCharacterSkill(sld, SKILL_DEFENCE, 5);
		break;
		
		case "ambush_inresidence_land":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "land") {
				dialog.text = "Sence bunu hak ediyor muyum? Hiç böyle önemsiz şeylere para harcamadım, ama sanırım her şeyin bir ilki vardır. Beni denizden uzaklaştırmaya çalışmaktan vazgeçmeyeceksin anlaşılan, değil mi Kaptan? Belki de haklısındır...";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 3;
				Notification_Approve(false, "Helena");
			} else {
				dialog.text = "Sence bunu hak ediyor muyum? Hiç böyle önemsiz şeylere para harcamadım, ama sanırım her şeyin bir ilki vardır.";
			}
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_F_LIGHT, 5);
			AddCharacterSkill(sld, SKILL_FENCING, 5);
			AddCharacterSkill(sld, SKILL_F_HEAVY, 5);
			AddCharacterSkill(sld, SKILL_PISTOL, 5);
			AddCharacterSkill(sld, SKILL_FORTUNE, 5);
			AddCharacterSkill(sld, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(sld, SKILL_SNEAK, 5);
		break;
		
		case "ambush_inresidence_2":
			dialog.text = "Her neyse, inceleme tamamlandı. Burada değerli bir şey kalmamış gibi görünüyor - ayaktakımı her şeyi çoktan yağmalamış, eminim ikinci kat da aynı durumdadır.";
			link.l1 = "Sanki değişmişsin, Helen. Geçen sefer birlikteyken... bilmiyorum, daha açıktın sanki?";
			link.l1.go = "ambush_inresidence_3";
		break;
		
		case "ambush_inresidence_3":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Hiçbir şey değişmedi, benim kaptanım, ama zavallı bir kızın omuzlarına bir sürü yük bindi, haha! Seni kırmak istemedim. Şu anda sadece birçok şeyi düşünmem gerekiyor. Biliyor musun, hayatta böyle keskin dönemeçler her gün olmuyor. Hem birlikte geçirecek çok vaktimiz var!";
				link.l1 = "Bunu duymak güzel! Hadi buradan gidelim.";
			} else {
				dialog.text = "Much has changed, Captain. I'm afraid I have to be more mature now and look at life differently. It's not a fairy tale about a princess and inheritance; it's big politics, and I still have to realize my place in it. And my family's place too.";
				link.l1 = "Bu meseleyi netleştirdiğimize sevindim. Hadi buradan gidelim.";
			}
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroBeforeExit");
		break;
		
		case "ambush_inresidence_wait":
			dialog.text = "Evet?";
			if (CheckCharacterItem(pchar, "pirate_cutlass")) {
				link.l1 = "Hey, her şey yağmalanmamış! Bak, Helen! Bu kılıç efsanevi olmalı, çünkü buradaki ayaktakımı bile onu cebine atmaya cesaret edememiş.";
				link.l1.go = "ambush_inresidence_give_cutlass";
			}
			
			link.l2 = "Hayır, hiçbir şey.";
			link.l2.go = "exit";
			
			NextDiag.TempNode = "ambush_inresidence_wait";
		break;
		
		case "ambush_inresidence_give_cutlass":
			dialog.text = "Vay canına, bu... Blaise'in efsanevi pala kılıcı! Korsanlar ona o kadar saygı duyuyordu ki, ölümünden sonra bile kılıcını evinden almadılar. Parayı ve değerli eşyaları tabii ki götürdüler, ama darağacına gideceklerin bile biraz onuru kalmış demek ki...";
			link.l1 = "It looks like someone is clearly tidying up here. As if the owner will come back... This is not a home; it's a memorial!";
			link.l1.go = "ambush_inresidence_give_cutlass_1";
		break;
		
		case "ambush_inresidence_give_cutlass_1":
			dialog.text = "Dikkatin için teşekkürler, Charles. Sayende burası benim için tamamen mahvoldu, ha-ha!";
			link.l1 = "Bence bu pala artık senin. Blaise senin sözde amcan...";
			link.l1.go = "ambush_inresidence_give_cutlass_2";
		break;
		
		case "ambush_inresidence_give_cutlass_2":
			dialog.text = "Bunu daha da korkutucu hale getiriyorsun, benim kaptanım. Ben... yapamam. Kabul edersem, geçmiş hayatımın tamamen sona ereceğinden korkuyorum.";
			link.l1 = "O zaman bunu mirasın bir parçası olarak değil, yakışıklı bir adamdan bir hediye olarak kabul et.";
			link.l1.go = "ambush_inresidence_give_cutlass_3";
		break;
		
		case "ambush_inresidence_give_cutlass_3":
			dialog.text = "Kim olabilir ki? Şaka yapıyorum! Karanlık düşüncelerimi dağıttığın için teşekkür ederim, kaptan. Söz veriyorum, bu kılıca layık olmak için çok çalışacağım!";
			link.l1 = "Sen en iyi silahı hak ediyorsun, Helen. Hadi gidelim, burada işimiz bitti.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "give_cutlass":
			dialog.text = "Vay canına, bu... Blaise'in efsanevi pala kılıcı! Korsanlar, ölümünden sonra bile onun evinden bu kılıcı almaya cesaret edemeyecek kadar ona saygı duyuyordu. Parayı ve değerli eşyaları tabii ki almışlar, ama darağacına gideceklerin bile biraz onuru kalıyor\nBen... ben yapamam. Kabul edersem, geçmiş hayatımın tamamen sona ereceğinden korkuyorum.";
			link.l1 = "O zaman bunu mirasın bir parçası olarak değil, yakışıklı bir adamdan bir hediye olarak kabul et.";
			link.l1.go = "give_cutlass_1";
		break;
		
		case "give_cutlass_1":
			dialog.text = "Kim olabilir ki? Şaka yapıyorum! Karanlık düşüncelerimi dağıttığın için teşekkür ederim, benim kaptanım.";
			link.l1 = "En iyi silahı hak ediyorsun, Helen. Beğenmene sevindim.";
			link.l1.go = "give_cutlass_2";
		break;
		
		case "give_cutlass_2":
			dialog.text = "Söz veriyorum, bu kılıca layık olmak için çok çalışacağım!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "arrive":
			dialog.text = "Benim kaptanım! Charlie!";
			link.l1 = "Charlie mi? Bu yeni! Seni görmek güzel, canım.";
			link.l1.go = "arrive_1";
		break;

		case "arrive_1":
			dialog.text = "Yanlışlıkla ağzımdan kaçırdım, ha! Seni de görmek güzel...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog1");
		break;

		case "arrive_2":
			dialog.text = "Kardeş dayanışması bu kadar mıymış! Benim kaptanım, ben... Gerçekten çok endişelendim ve seni çok özledim!";
			link.l1 = "Peki, eve neden koşarak dönmen gerekti?";
			link.l1.go = "arrive_3";
		break;

		case "arrive_3":
			dialog.text = "Şey... Ah, doğru! Sana küçük bir hediyem var, al bakalım!";
			link.l1 = "Üç muska... Helen, neden? Beni takip etmek mi istedin?";
			link.l1.go = "arrive_4";
			
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Indian);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Amulet);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Obereg);
		break;

		case "arrive_4":
			dialog.text = "Buraya gel, aptal!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FirstKiss");
		break;

		case "after_kiss":
			dialog.text = "Sakın bu anı mahvetmeye kalkma - bunu hayatım boyunca hayal ettim!";
			link.l1 = "Yapmayacağım, Helen.";
			link.l1.go = "after_kiss_a";
			link.l2 = "Tüm hayatını benimle tanışmak için mi bekledin? Gurur duydum!";
			link.l2.go = "after_kiss_b";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l3 = "Helen, bir şey var... Adalet Adası'nda bir kadınla tanıştım ve...";
				link.l3.go = "after_kiss_c";
			}
			locCameraFromToPos(-19.00, 1.56, 19.07, true, -11.19, -0.90, 17.49);
		break;
		
		case "after_kiss_a":
			dialog.text = "Kesinlikle doğru! Bana her şeyi, her şeyi anlatacaksın! Gemide seni bekliyor olacağım, Kaptan!";
			link.l1 = "Bekle!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_b":
			dialog.text = "Aptal! Beni gücendirmek mi istiyorsun? Peki, gücendim! Ha-ha! Şimdi gemiye gidiyorum, yoksa Danny benimle daha çok dalga geçecek...";
			link.l1 = "Bekle!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_c":
			dialog.text = "Aptal! Sana anı mahvetmemeni söylemiştim! Tanıştın... yani, tanıştınız – ama parmağında hâlâ bir yüzük göremiyorum. Ama sakın paçayı sıyırdığını sanma – gemiye döndüğünde senden ayrıntılı bir hikaye bekliyor olacağım.";
			link.l1 = "Bekle!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "loot_good":
			dialog.text = "Kaptanım, ne haber? Solgun yüzünden anlıyorum ki avukat sana yardım etmek yerine yine başına dert açmaya karar vermiş.";
			link.l1 = "Haklısın, Helen. Loxley etkileyici bir avans istedi, davanın kendisi de bana epey pahalıya patlayacak. Gidip Jan'ı sarsacağım artık – yeterince sabrettim! Sanki Kardeşlik bütün masraflarını bana yıkmaya karar vermiş gibi!";
			link.l1.go = "loot_good_1";
		break;
		
		case "loot_good_1":
			dialog.text = "Bunda bir kötülük yok, Charles. Onlar böyle – gerekmedikçe parmaklarını bile kıpırdatmazlar. Eminim Jan sana yardım edecek, ben de boş durmayacağım.";
			link.l1 = "Biliyorum, Helen. Ne düşündüğünü anlat bana.";
			link.l1.go = "loot_good_2";
		break;
		
		case "loot_good_2":
			dialog.text = "Eskiden Jan için çalışırdım - Maine'in dört bir yanına değerli kereste kaçırırdım. Ama ben becerikli bir kadınım, bütün o yolculuklar sırasında kendime de bir şeyler ayırmayı bildim.";
			link.l1 = "Ve Jan hiçbir zaman öğrenmedi mi? Ne kadar akıllıca!";
			link.l1.go = "loot_good_3";
		break;
		
		case "loot_good_3":
			dialog.text = "İyi bir haznedarım vardı. Kısacası, hatırı sayılır bir miktar para topladım ve onu buraya pek de uzak olmayan bir yere sakladım. Şimdi Jan'a mı gidiyorsun? O zaman San Juan del Norte'ye uğrayalım. Yakında bir mağara var, sadece birkaç denizciye ihtiyacımız olacak, böylece her şeyi kendimiz taşımak zorunda kalmayız.";
			link.l1 = "Her şeyi zaten çözmüşsün, değil mi? Teşekkürler, Helen, zamanımız olursa mutlaka uğrarız.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "loot_bad":
			dialog.text = "Benim kaptanım, ne haber? Solgun yüzünden anlıyorum ki avukat sana yardım etmek yerine yine başına dert açmaya karar vermiş.";
			link.l1 = "Haklısın, Helen. Loxley etkileyici bir avans istedi ve işin kendisi de bana hatırı sayılır bir paraya mal olacak. Şimdi Jan'ı sarsmaya gidiyorum – artık yeter! Sanki Kardeşlik tüm masraflarını bana yıkmaya karar vermiş gibi!";
			link.l1.go = "loot_bad_1";
		break;
		
		case "loot_bad_1":
			dialog.text = "Bir masalın içinde olduğunu mu sandın? Merak etme, burada hepimiz aynı durumdayız ve sana yardım edeceğim. Sonuçta, benim de bir miras hakkım var, değil mi?";
			link.l1 = "Doğru... Söyle bakalım, aklından ne geçiyor!";
			link.l1.go = "loot_bad_2";
		break;
		
		case "loot_bad_2":
			dialog.text = "San Juan del Norte'de sakladığım bir şey var. Yakınlarda bir mağara var – sadece birkaç denizci toplamamız gerekecek, böylece her şeyi kendimiz taşımak zorunda kalmayız.";
			link.l1 = "Her şeyi zaten çözmüşsün, değil mi? Teşekkürler, Helen, zamanımız olursa mutlaka uğrarız.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "shdn":
			dialog.text = "İşte burası, Charles! Ama yalnız gitmek zorundasın – mağaralardan nefret ederim!";
			link.l1 = "Kapalı alanlar gibi, biliyorum Helen. Beni burada bekle.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoForLoot");
		break;
		
		case "shdn_ambush":
			dialog.text = "Bir sorunumuz var! Bir grup asker buraya doğru geliyor ve hiç de dostça görünmüyorlar. Dikkatli ol, Charles, bunlar sıradan sahil muhafızları değil - aralarında bir Fransız subayı var! Ne olur, lütfen aptalca bir şey yapma!";
			link.l1 = "Ben ne zaman aptalca bir şey yaptım ki?!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SpawnAmbushSoldiers");
		break;
		
		case "shdn_ambush_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Ha, ikinci seçenek kulağa daha cazip geliyor, ama umarım kendini fazla beğenmiş değilsin, Charles?";
			} else {
				dialog.text = "Şaşırdığımı söyleyemem, Charles...";
			}
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog1");
		break;
		
		case "shdn_ambush_2":
			dialog.text = "İşin bitti mi? Şimdi konuşma sırası bende!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_HelenKillFrancois");
		break;
		
		case "shdn_ambush_3":
			dialog.text = "Benim adım Helen MacArthur! Kaptan, kim olduğumu ve kimin için çalıştığımı biliyorsun! Adamlarına, özellikle de yerde yatan o süslü aptala, şimdi açıklayacağım bugünkü sonuçları bildir!";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "richard");
			sld = CharacterFromID("HelenDrinking_Richard");
			CharacterTurnByChr(sld, npchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath2");
		break;
		
		case "shdn_ambush_4":
			dialog.text = "İtiraz mı? Cromwell’in kendisine bile yazsan umurumda olmaz. Öncelikle, Monsieur de Maure bugün onurunu kaybetmedi.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_5";
			CharacterTurnToLoc(npchar, "quest", "richard");
		break;
		
		case "shdn_ambush_5":
			dialog.text = "İkincisi, Albay de Tavann bir kızı fahişe diye çağırdığı için, çok iddialı bir kıyafet giymiş bir kız tarafından vuruldu.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_6";
		break;
		
		case "shdn_ambush_6":
			dialog.text = "Üçüncüsü, askerlerini derhal geri çekiyorsun ve olanları unutuyorsun, yoksa Orman Şeytanı'nın bundan haberi olmasını mı istersin.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_7";
		break;
		
		case "shdn_ambush_7":
			locCameraSleep(false);
			dialog.text = "Sorunuz yok anlaşılan. İyi günler, Kaptan.";
			link.l1 = "Aman Tanrım, Helen, harika görünüyorsun!";
			link.l1.go = "shdn_ambush_8";
		break;
		
		case "shdn_ambush_8":
			dialog.text = "Daha sonra, Charles. Onlar şoku atlatmadan buradan çıkalım. Benim de elim ayağım titriyor. Blueweld'de konuşalım mı?";
			link.l1 = "Kabul.";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, pchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath3");
		break;
		
		case "duel_victory":
			dialog.text = "Şoktan kendilerine gelmeden önce buradan çıkalım. Demir ağacı hâlâ almamız gerekiyor, unutma. Blueweld'de konuşuruz.";
			link.l1 = "Vay canına! Bir tebrik bile yok mu? Peki, hadi gidelim.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory1");
		break;
		
		case "after_cave":
			dialog.text = "Sonunda, evdeyim...";
			link.l1 = "Sence olanlar hakkında ne düşünüyorsun?";
			link.l1.go = "after_cave_1";
		break;
		
		case "after_cave_1":
			dialog.text = "Düelloları anlamıyorum. Erkeklerin eğlencesi, genellikle iki cesetle biter, şanslı bir günde ise daha da fazlasıyla. Ve onur... Bence onur, sonuna kadar çatışmadan kaçınma arzusuyla inşa edilir, çünkü nadiren buna değer olduğunu kanıtlar. Ha! Şuna bak, ne saçmalıyorum ben böyle!";
			link.l1 = "İlginç bir bakış açısı, Helen. Ama herkes aynı fikirde olmayabilir.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Duel")) {
				link.l1.go = "after_cave_duel";
			} else {
				link.l1.go = "after_cave_notduel";
			}
		break;
		
		case "after_cave_duel":
			dialog.text = "Ne yazık ki onların oyununa geldin. Albayın takıntılı olduğu belliydi, diğerleri ise sadece biraz eğlence ve dedikodu peşindeydi. Neyse, üstüne gitmeyeceğim - bugünlük sana bu kadarı yeter.";
			link.l1 = "Evet, düellolardan sonra her zaman bir boşluk hissi olur. Bugünlük macera yeter. Şimdi ne yapmak istiyorsun?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_notduel":
			dialog.text = "Ah! Sadece şunu söylemek istedim: Bizimle gurur duyuyorum. Bugün gerçek bir cesaret gösterdin, benim kaptanım. Sadece bir kez olsun sana emir vermek isteyen tayfanın paniğine kapılmadın. Kırmızı üniformanın sahte gösterişine ve mavinin saplantısına karşı dimdik durdun. Albay açıkça ölüme meydan okuyordu ama uygunsuz bir yerinden yaralanmaktan fazlasını elde edemedi, ha-ha!";
			link.l1 = "Teşekkür ederim, Helen. Bizi felaketten ustaca kurtardın, tam bir deniz subayı gibi. Kendinle gurur duyuyor musun?";
			link.l1.go = "after_cave_notduel_1";
		break;
		
		case "after_cave_notduel_1":
			dialog.text = "Evet, buna ihtiyacım vardı. Keşke mavi bir üniforma değil de kırmızı olsaydı, ama en azından onu giyen hak ettiğini buldu.";
			link.l1 = "O kişi gerçekten de önemsiz, kabul ediyorum. Bugünlük macera yeter. Şimdi ne yapmak istersin?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_mild":
			dialog.text = "Eve gidiyorum, benim kaptanım. Mo... Gladys'i özledim. Ne yazık ki şu an evde, yoksa seni de davet ederdim!";
			link.l1 = "Gerçekten, bu çok yazık!";
			link.l1.go = "after_cave_mild_1";
		break;
		
		case "after_cave_mild_1":
			dialog.text = "Bukadar üzülme. Yakında, sevgilim. Bu arada...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, bu ilkinden bile daha güzel. Hatırlıyor musun? Putun orada?";
				link.l1 = "Bu, insanın kolay kolay unutacağı bir şey değil, canım.";
				link.l1.go = "after_second_kiss_1";
			} else {
				dialog.text = "Sakın ama sakın bu anı mahvetme - tüm hayatım boyunca bunu hayal ettim!";
				link.l1 = "Yapmayacağım, Helen.";
				link.l1.go = "after_second_kiss_a";
				link.l2 = "Beni bütün hayatın boyunca bekledin mi? Gurur duydum!";
				link.l2.go = "after_second_kiss_b";
			}
		break;
		
		case "after_second_kiss_1":
			dialog.text = "Ah! Kendine gel, kızım! Tekrar görüşene dek, benim kaptanım.";
			link.l1 = "O zamana kadar, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_a":
			dialog.text = "Kesinlikle doğru! Yakında görüşeceğiz, benim kaptanım.";
			link.l1 = "Tekrar görüşene dek, Helen. Tanrım, ne kadın ama...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_b":
			dialog.text = "Aptal! Beni gücendirmek mi istiyorsun? Peki, gücendim! Ha-ha! Yakında görüşürüz, benim kaptanım.";
			link.l1 = "Tekrar görüşene dek, Helen. Tanrım, ne kadın ama...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_cave_cold":
			dialog.text = "Eve gidiyorum, Kaptan. Sanırım avukatla olan para meselesi artık çözüldü? Önümüzde zorlu engeller var, bu yüzden bundan sonra başımızı belaya sokmamaya çalışalım. Zaten bela bizi kendi bulur.";
			link.l1 = "Gerçekten mi, yok artık?";
			link.l1.go = "after_cave_cold_1";
		break;
		
		case "after_cave_cold_1":
			dialog.text = "Kusura bakma, Kaptan. Benim kaderim de şu anda belirleniyor, biliyorsun.";
			link.l1 = "Biliyorum, bunu olabildiğince onurlu bir şekilde halletmeye çalışacağım. Gemide görüşürüz, Helen.";
			link.l1.go = "after_cave_cold_2";
		break;
		
		case "after_cave_cold_2":
			dialog.text = "Aynen, Kaptan!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveCold");
		break;
		
		case "after_cave_lewd":
			dialog.text = "Sırada ne var? Sana göstereceğim.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss1":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, bu birincisinden bile daha güzel. Hatırlıyor musun? Putun oradaki?";
				link.l1 = "Bunu kimse unutmaz, canım.";
				link.l1.go = "after_second_kiss1_1";
			} else {
				dialog.text = "Sakın ama sakın bu anı mahvetme - hayatım boyunca bunu hayal ettim!";
				link.l1 = "Yapmam, Helen.";
				link.l1.go = "after_second_kiss1_a";
				link.l2 = "Tüm hayatını benimle tanışmak için mi bekledin? Gurur duydum!";
				link.l2.go = "after_second_kiss1_b";
			}
		break;
		
		case "after_second_kiss1_1":
			dialog.text = "Kesinlikle doğru! Vay canına! Gladys şu an evde değil. İçeri girmek ister misin?";
			link.l1 = "Beni davet mi ediyorsun? Peki, ne yapacağız?";
			link.l1.go = "after_cave_lewd_accept";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l2 = "Hayır, Helen. Adalet Adası'nda beni bekleyen başka bir kadın var. Ona bunu yapamam.";
				link.l2.go = "after_cave_lewd_refuse_mary";
			}
			link.l3 = "Başka bir zaman, canım. Gerçekten isterim ama bugün beni neredeyse mahvetti. Sonra buluşuruz ve kaybettiğimiz zamanı fazlasıyla telafi ederiz.";
			link.l3.go = "after_cave_lewd_refuse_head";
		break;
		
		case "after_second_kiss1_a":
			dialog.text = "Kesinlikle doğru! Vay canına! Gladys şu an evde yok. İçeri girmek ister misin?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "Hayır, Helen. Adalet Adası'nda beni bekleyen başka bir kadın var. Ona bunu yapamam.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Başka bir zaman, sevgilim. Gerçekten isterdim ama bugün beni neredeyse bitirdi. Sonra buluşuruz ve kaybettiğimiz zamanı fazlasıyla telafi ederiz.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Beni davet mi ediyorsun? Peki, ne yapacağız?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_second_kiss1_b":
			dialog.text = "Aptal! Beni kızdırmak mı istiyorsun? Peki, kızdım işte! Ha-ha! Şimdi gönlümü almalısın, benim kaptanım. Şey! Gladys şu an evde yok. İçeri gelmek ister misin?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "Hayır, Helen. Adalet Adası'nda beni bekleyen başka bir kadın var. Ona bunu yapamam.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Başka bir zaman, canım. Gerçekten isterim, ama bugün neredeyse beni mahvetti. Sonra buluşuruz, kaybettiğimiz zamanı fazlasıyla telafi ederiz.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Beni davet mi ediyorsun? Peki, ne yapacağız?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_cave_lewd_refuse_mary":
			dialog.text = "Yani, baştan çıkarma sanatında yeterince usta değil miyim? O ise öyle mi? Kim bu kadın?";
			link.l1 = "Adı Mary Casper, ve onu seviyorum.";
			link.l1.go = "after_cave_lewd_refuse_mary_1";
		break;
		
		case "after_cave_lewd_refuse_mary_1":
			dialog.text = "Şu kırmızı üniformalı kızıl saçlı mı? Kırmızı üniformalı... Eh, bir işaret arıyorsam, işte burada. Demek ki kaderde yokmuş. Merak etme, Kaptan, bu durum geminizdeki görevimi etkilemez.";
			link.l1 = "Üzgünüm, Helen.";
			link.l1.go = "exit";
			
			pchar.questTemp.HelenDrinking.Mary = true;
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMary");
		break;
		
		case "after_cave_lewd_refuse_head":
			dialog.text = "Ah, kaptanım! Bir kadını böyle bir halde bırakmak tehlikeli! Sözünü tutmanı bekliyorum, şimdi git... Biraz yalnız kalıp kendi derdimle başa çıkmam gerek... kendi başıma! Gemide görüşürüz!";
			link.l1 = "Ne kız ama!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMild");
		break;
		
		case "after_cave_lewd_accept":
			dialog.text = "Endişelenme canım, kaybolursan sana yol gösteririm.";
			link.l1 = "Pekala... öyleyse yolumuza devam edelim!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveAccept");
		break;
		
		case "after_cave_bedroom":
			dialog.text = "Hiçbir şey söyleme, ne olur.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex1");
		break;
		
		case "after_cave_sex":
			dialog.text = "... tabii ki, bugüne kadar bu konudaki bilgim sadece 'Gökkuşağı' tayfasının kaba sohbetlerine dayanıyordu, eğer buna sohbet denirse, tabii ki.";
			link.l1 = "Peki, nasıldı? Gerçeklik beklentilerini karşıladı mı?";
			link.l1.go = "after_cave_sex_1";
		break;
		
		case "after_cave_sex_1":
			dialog.text = "Çok keyif aldım, ama sanki tam anlamıyla yaşayamamışım gibi hissediyorum. Hem de nasıl...";
			link.l1 = "Sana göstereyim! Devam edelim mi?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex2");
		break;
		
		case "after_cave_sex_again":
			dialog.text = "Ah, şimdi anladım! Gerçekten harikaydı, benim kaptanım!";
			link.l1 = "Beni gerçekten şaşırttın, en hafif tabirle!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysEnter");
		break;
		
		case "after_cave_gladys":
			dialog.text = "Ah-ha-ha! Bu gerçekten iyiymiş! Şimdi ya kulaklarını mumla tıkayacak ya da kalenin en yüksek kulesine kaçacak!";
			link.l1 = "Bu beklenmedikti ama çok komikti, ah-ha-ha!";
			link.l1.go = "after_cave_gladys_1";
			locCameraFromToPos(-0.62, 1.93, -0.39, true, -2.46, -1.20, 1.01);	// Sinistra - постельная камера
		break;
		
		case "after_cave_gladys_1":
			dialog.text = "Hazır mısın, benim kaptanım?";
			link.l1 = "Şimdiden mi?! Hayır, Helen, bana acı, ne olur. Gladys'in aniden ortaya çıkması kesinlikle ortamı bozdu.";
			link.l1.go = "after_cave_gladys_2";
		break;
		
		case "after_cave_gladys_2":
			dialog.text = "Pekala, ne yapabilirsin ki... Gerçi...";
			link.l1 = "Hayır, hayır, yelkenleri indir!";
			link.l1.go = "after_cave_gladys_3";
		break;
		
		case "after_cave_gladys_3":
			dialog.text = "Pekala, o zaman biraz birlikte kalalım. Geleceğimiz çok belirsiz ve korkutucu, ama uzun zamandır ilk kez hiçbir şeyden korkmuyorum. Biliyorum, yeni bir korku içime sızabilir, ama bugün değil. Bugün değil, benim kaptanım.";
			link.l1 = "Bugün değil, canım. Bugün değil.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveFin");
		break;
		
		case "give_potions":
			dialog.text = "Konuşabilir miyim, Kaptan?";
			link.l1 = "Evet, Helen?";
			link.l1.go = "give_potions_1";
		break;
		
		case "give_potions_1":
			dialog.text = "Bu Yılan Göz’ü tanıyorum – iyi biridir ama biraz tuhaf. Sürekli insanları ne olduğu belirsiz işlere gönderir. Görüyorum ki o şüpheli onur sana da nasip olmuş.";
			if (!CheckAttribute(CharacterFromID("SnakeEye"), "quest.amulet")) {
				link.l1 = "Evet, ona üç muska getirmem gerekiyor, yoksa bana Hawk'ın yerine gitmemde yardım edemeyecek. Ama komik olan ne biliyor musun? Zaten hepsi yanımdaydı! Belki de en başından beri bunu biliyordu?";
				link.l1.go = "give_potions_already";
			} else {
				link.l1 = "Evet, ona üç muska getirmem gerekiyor, yoksa bana Hawk'ın yerine ulaşmamda yardım edemeyecek. Şimdi onları nerede bulacağımı bilmiyorum ve zamanım da tükeniyor.";
				link.l1.go = "give_potions_3";
			}
		break;
		
		case "give_potions_already":
			dialog.text = "Ah, ne yazık! Fener bekçilerinden o muskalardan toplamak zorunda kalmadığına sevindim ama bu sefer sana bir faydam dokunur, kendimi kanıtlama fırsatı bulurum diye ummuştum.";
			link.l1 = "Saçmalama, Helen. Bana hiçbir şey kanıtlamak zorunda değilsin.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_3":
			dialog.text = "Sana yardım edeceğim! Kabul ediyorum, bu sefer sana bir faydam dokunur diye umut etmiştim, kendimi kanıtlamak istedim.";
			link.l1 = "Saçmalama, Helen. Bana hiçbir şey kanıtlamak zorunda değilsin.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_4":
			dialog.text = "Yine de sana yardım etmek istiyorum. Al, odamın anahtarını... yani, odamdaki sandığın anahtarını! Çok bir şey yok, ama belki işine yarar. Ve... Charles, lütfen şu an kahkahayı patlatmamaya çalış!";
			link.l1 = "Öhö, öyle bir niyetim yoktu. Bu şeylerle ilgilendiğini görüyorum?";
			link.l1.go = "give_potions_5";
		break;
		
		case "give_potions_5":
			dialog.text = "Ben de bir denizciyim, kaptan, tıpkı senin gibi. Bizim işimizde, Şans Tanrıçası'nı yanımıza çekmek için elimizden geleni yapmalıyız.";
			link.l1 = "Teşekkür ederim, Helen. Bunu gerçekten takdir ediyorum.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GivePotionsKey");
		break;
		
		case "upgrade":
			dialog.text = "Sevgilim, sana bir hediyem var!";
			link.l1 = "Anladım, işte orada – ayakta duruyor ve gülümsüyor!";
			link.l1.go = "upgrade_1";
		break;
		
		case "upgrade_1":
			dialog.text = "Ah-ha, yapma! Bir keresinde buradaki gemi ustasına güzel bir ipek partisi teslim etmiştim, şimdi bana bir gemiyi baştan aşağı yenileme borcu var. Bu iş için ona 'Gökkuşağı'nı vermeyi düşünmüştüm ama kısmet değilmiş. Öte yandan, senin teknen böyle bir bakımdan gerçekten fayda görebilir, sence de öyle değil mi?";
			link.l1 = "Gerçekten de harika bir hediye, Helen – tam sana göre!";
			link.l1.go = "upgrade_2";
		break;
		
		case "upgrade_2":
			dialog.text = "Beğenmene sevindim. Onu istediğin zaman ziyaret et ve seni benim gönderdiğimi söyle. Elinden gelenin en iyisini yapacaktır.";
			link.l1 = "Kesinlikle!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("HelenUpgradeShip1");
		break;
		
		case "give_sex":
			dialog.text = "Konuşabilir miyim, benim kaptanım?";
			link.l1 = "Elbette, canım.";
			link.l1.go = "give_sex_1";
		break;
		
		case "give_sex_1":
			dialog.text = LinkRandPhrase("Hanımefendiniz sizi özlemiş ve ilginizi talep ediyor. Onun için bir oda ayarlanmasını ve ona biraz zaman ayırmanızı rica edebilir miyim","Rapor veriyorum: Varlığınız yerel meyhanedeki bir yatakta gereklidir. Sadece beş dakikanızı alacak, ama tayfa biraz daha kalmanızı umuyor!","Gemide isyan çıktı, kaptan! Sana gizlice kara bir işaret vermem emredildi. Hemen benimle gel!");
			link.l1 = "He-he, öhöm! İsteğiniz kabul edildi, Memur Sharp!";
			link.l1.go = "give_sex_1_yes";
			link.l2 = "Bugün değil, canım. Şu anda çok fazla şey oluyor.";
			link.l2.go = "give_sex_1_no";
		break;
		
		case "give_sex_1_yes":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			DialogExit();
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "give_sex_1_no":
			dialog.text = "Ah, zavallı bir kız ne yapsın peki, ha? Peki, canım, o zaman başka bir sefere.";
			link.l1 = "";
			link.l1.go = "give_sex_2_no";
		break;
		
		case "give_sex_2_no":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			npchar.location = "None";
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			chrDisableReloadToLocation = false;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
		break;
		
		case "special_sex":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			SaveCurrentNpcQuestDateParam(npchar, "special_sex_date");
			
			dialog.text = "Ha! Bunu bana iki kere söylemene gerek yok! Tabii ki, hadi gidelim!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "rainbow":
			dialog.text = "Seni şimdi denize atarım!";
			link.l1 = "Hey, hey, hey! Sakin ol, canım!";
			link.l1.go = "rainbow_1";
		break;
		
		case "rainbow_1":
			dialog.text = "Buraya gel, seni serseri!";
			link.l1 = "Sadece şaka yapıyorum, Helen! Seni kırmak istememiştim!";
			link.l1.go = "rainbow_2";
		break;
		
		case "rainbow_2":
			dialog.text = "Gerçekten mi? Ne şakacısın...";
			link.l1 = "Sen dünyanın en güzeli, ve sana deliler gibi aşığım!";
			link.l1.go = "rainbow_3";
		break;
		
		case "rainbow_3":
			dialog.text = "Defol, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Rainbow");
			Achievment_Set("ach_CL_84");
		break;
		
		case "joan":
			dialog.text = "Asıl sen arsızsın! Jan seni namuslu bir kadın yaptığına şükret, yoksa hâlâ önüne gelene kendini satıyor olurdun!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog2");
		break;
		
		case "joan_1":
			dialog.text = "Orospu! Hadi gidelim, Charles!";
			link.l1 = "";
			link.l1.go = "exit";
			
			ResetSound();
			SetMusic("helendrinking_shanty");
			pchar.questTemp.lockedMusic = true;
			AddDialogExitQuestFunction("HelenDrinking_GoToFort");
		break;
		
		case "cutlass_training":
			dialog.text = "Pala elimde mükemmel duruyor! Nasıl anlatacağımı bilmiyorum... Hep başka türden kılıçlarla, mesela ince kılıçlarla ve uzun kılıçlarla zorlanmışımdır. Ama bu pala bambaşka! Harika hissettiriyor! Teşekkür ederim, Charles!";
			link.l1 = "Kaderin bizi bulma şekli vardır. Senin adına sevindim, Helen!";
			link.l1.go = "exit";
			notification("Medium Weapons +", "Helena");
		break;
		
		case "brothel_found":
			dialog.text = "Hikayelerini başkalarına sakla, bana işlemezler. Saf, aşık bir aptal gibi mi görünüyorum? Yani, sana deli gibi aşığım, ama bana aptal demek biraz abartı olurdu\n Bak canım, ne istersen yap, ama şunu unutma: benden daha iyisini bulamazsın. Eğer onu genelevlerde aramak istiyorsan buyur, ama o zaman hayatından tamamen kaybolurum.";
			link.l1 = "Helen, ben...";
			link.l1.go = "brothel_found_1";
		break;
		
		case "brothel_found_1":
			dialog.text = "Her şeyi anlıyorum, Charles. Sadece beni seviyorsun, bunlar ise sadece doğal dürtüler. Peki, benim doğal dürtüm ne biliyor musun? Adamımdan saygı görmek. Bir kadın sadece aşkla yetinmeyebilir, canım. Şimdilik bu yanlış anlamayı unutalım, ama söylediklerimi biraz düşün olur mu? Tamam mı?";
			link.l1 = "Peki, Helen.";
			link.l1.go = "exit";
		break;
		
		case "refuse":
			dialog.text = "Bilirsin nasıl olur. Önce bir kızın sakinleşmesine izin ver.";
			link.l1 = "İç çekiş...";
			link.l1.go = "exit";
		break;
		
		// Тайна Порт-Рояля
		case "MysteryPortRoyal_Helena_1":
			dialog.text = "Francis... Onu hatırlıyorum. Her zaman Port Royal'da gelişimi beklerdi ve tam bir romantikti. Denizden bu kadar uzak biriyle vakit geçirmek hoşuma giderdi – o şiirler, serenatlar... Hepsi benim için yeniydi. Hiç bilmediğim bir dünyaya kısa bir bakış gibiydi. Francis zengin, zeki ve yakışıklıydı – tam anlamıyla bulunmaz biriydi. Buradaki herhangi bir kız onun ilgisi için çıldırırdı ama o zamanlar ben daha çok Rainbow'u yüzdürmekle meşguldüm.";
			link.l1 = "Şairin hassas ruhu, reddini kaldıramamış anlaşılan. Yazdığı tüm mektuplarda sadece senden bahsetmiş, buluştuğunuz yerleri anmış. İstersen, geride bıraktığı her şeyi sana verebilirim.";
			link.l1.go = "MysteryPortRoyal_Helena_2";
		break;
		
		case "MysteryPortRoyal_Helena_2":
			dialog.text = "Onun hasta olduğunu bilmiyordum. Şimdi her şey çok saçma geliyor. Hediyesine gelince... Vasiyetler ve miraslardan artık bıktım. Bana güven, ihtiyacım olan her şeye – fazlasıyla – sahibim. En iyisi, onu sen sakla.";
			link.l1 = "Ne şekilde olursa olsun, onun mirası sonunda yine de sana hizmet edecek – demek ki farkında olmadan onun son dileğini yerine getirmişim. Ne hikâye ama.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.MysteryPortRoyal_Helena");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenDrinking_RobbedSvenson() {
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	if (!CheckAttribute(sld, "private1.items.chest")) { 
		return true;
	}
	
	if (sti(sld.private1.items.chest) < 2) {
		return true;
	}
	
	return false;
}
