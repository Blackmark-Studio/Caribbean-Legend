// шаман команчей Змеиный Глаз
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
			if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "calendar")
			{
				dialog.text = "Selamlar, solgun dostum.";
				link.l2 = "Seni görmek de beni mutlu etti, kızılderili kardeşim. Yine senin için önemli bir işim var.";
				link.l2.go = "calendar";
				break;
			}
			dialog.text = "Selam, solgun dostum.";
			link.l1 = "Seni görmek de beni mutlu etti, Yılan Göz.";
			link.l1.go = "exit";
			if (CheckAttribute(npchar, "quest.amulet") && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Indian) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Amulet) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Obereg))
			{
				link.l2 = "Sana istediğin tılsımları getirdim. Haydi takas yapalım.";
				link.l2.go = "SnakeEye_potion";
			}
			if (CheckAttribute(pchar, "questTemp.LSC")) // был в LSC
			{
				if (CheckAttribute(npchar, "quest.LSC_hello") && CheckCharacterItem(pchar, "buben"))
				{
					link.l2 = "Defini buldum, Yılan Göz. Şuna bir bak.";
					link.l2.go = "LSC_buben";
				}
				if (CheckAttribute(npchar, "quest.LSC_tube") && CheckCharacterItem(pchar, "smoking_tube"))
				{
					link.l2 = "İlginç bir Kızılderili piposu buldum, Yılan Gözü. Bir bak.";
					link.l2.go = "LSC_tube";
				}
				if (!CheckAttribute(npchar, "quest.LSC_hello"))
				{
					link.l2 = "Merhaba, şaman. Heykeli kullandım ve inanılmaz bir yolculuk yaşadım. Tamamen haklıydın. Gemi mezarlığını, beyaz kaptanı ve hatta erzak dolu ambarı bile buldum!";
					link.l2.go = "LSC_hello";
				}
				if (CheckAttribute(npchar, "quest.LSC_hello") && pchar.questTemp.Saga.BaronReturn == "shamane")
				{
					link.l3 = "Yılan Göz, yardımına ihtiyacım var.";
					link.l3.go = "Saga_nathaniel";
				}
			}		
			NextDiag.TempNode = "First time";
		break;
		
	//---------------------------------------- первая встреча------------------------------------------------
		case "SnakeEye":
			dialog.text = "Selamlar, solgun dostum.";
			link.l1 = "Merhaba, şaman. Neden benim dostun olduğumu düşünüyorsun?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Çok şey biliyorum, ama her zaman tam olarak ne bildiğimi bilmiyorum. Buraya bir amaçla geldin. Kader seni buraya getirdi ve ben de sana yardım etmek için buradayım.";
			link.l1 = "Bunu bilmek güzel! Gerçekten de yardımın için buradayım, kızılderili dostum. Açık konuşacağım: Hawk'un karısına Kukulcan'dan bahsederken ne demek istedin?";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "Ölü balıklar bile sürüklenip gider. Yaşayan bir adam ise kaderin peşinden, bir hedeften diğerine sürüklenir. Zincire vurulmuş kaptanın, kötü adamlar tarafından ormanda kovalanan kaptanın hedefi ise Kukulcan heykeliydi. Kendini feda ederse, buradan çok uzaklara gidebilirdi.";
			link.l1 = "Hiçbir şey anlamadım. Tanrınızın heykeli ne işe yarıyor, ve Hawk nasıl oldu da kimsenin hâlâ bulamadığı kadar uzağa yürüyebildi?";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Eğer Kukulcan Hawk'ı yuttuysa, onu istediği yere tükürebilir. Belki de başka bir dünyaya bile. Kukulcan beni üç kez yuttu. Ve her seferinde, kendimi bambaşka bir yerde buldum. Uzun zaman önce buraya geldim ve artık daha fazla risk almamaya karar verdim. Kukulcan'ın ağzına girmedim ve kurbanlarını nereye tükürdüğünü bilmiyorum.";
			link.l1 = "Tanrım, bu benim aklımın ötesinde! Bana gerçekten o taş putun insanları uzaklara ışınlayabildiğini mi söylüyorsun?";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "Sadece bu da değil. Kukulcan yalnızca mekâna değil, zamana da hükmediyor. Belki de daha fazlasına. Zincirlenmiş kaptana insanları yutan altın heykelden bahsettim. Belki de peşindekilerin yaklaştığını görünce risk almaya karar verdi...";
			link.l1 = "Bekle, heykel taştan yapılmış. Ama sen altından bir heykelden bahsediyorsun...";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "Gece yarısı, put canlanır ve altına dönüşür. O anda, Kukulcan'ın ruhu onun içinde yaşar. Yaklaşmaktan sakın, yoksa güneşi bambaşka bir yerden doğarken bulabilirsin. Hatta yıldızlar bile gökyüzünde yer değiştirebilir. Henüz doğmamış olanlarla karşılaşabilir, çoktan ölmüş ya da hiç doğmamış olanların doğumuna tanık olabilirsin.";
			link.l1 = "Ne... yine bilmeceler, yine bilmeceler... Merakımı cezbediyorsun, Yılan Göz. Üç kez inandığın tanrı Kukulcan'la karşılaşıp sağ çıktığını söyledin. O halde, ben de inanmadığım bir tanrının putuyla şansımı neden denemeyeyim?";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Yazık. Yazık ki inanmıyorsun. Belki de bizzat Kukulcan seni çağırdı ve atalarının topraklarından ayrılmanı sağladı. Ama onu henüz duymuyorsun. Her şeyin bir sebebi vardır. Eğer riske girmeye karar verirsen, bilmelisin ki ben her seferinde sadece harika Komançi iksirlerim sayesinde hayatta kaldım.";
			link.l1 = "Comanche mi? O da başka bir kabile mi?";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "That is what enemies call my people, whom I will never see again. The potion restores strength and endurance, and also heals and saves you from strong poisons. You need several flasks, but I have only three left.\nThere were four flasks, but I lost one in a strange place; it looks like a cemetery of white men's ships. That is where I began my journey in this world. Perhaps Kukulcan spat the captain out there. If so, I do not envy him.";
			link.l1 = "Burası da ne? Gemi mezarlığı mı?";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "Strange place... It should not exist, yet it does. People who kill because of skin colour live there. They keep their supplies inside a big ship where Kukulcan spat me out. I did not go into its hold, which they protect from thieves; they aren't trusting neighbours. If you get there - find another exit, don't go into the hold or there will be trouble.\nWhite Boy will help you find another statue if he still lives. Give him this white bead. He likes them.";
			link.l1 = "Hm. Başım zaten dönüyor ve işler giderek daha da ilginçleşiyor. Devam et, kızılderili kardeşim.";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			Log_Info("You have received a white pearl");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "jewelry52");
			dialog.text = "Eğer kaptanı sağ bulursan, durumu çok kötü olabilir. Ona iksirimi vermeye fırsatım olmadı. Orada defim için bak. Onu dedemden aldım. Kaybettiğim çantada birçok şey var ama bana sadece defim lazım. Onsuz ruhlarla konuşmak çok zor.";
			link.l1 = "Burası gerçekten çok ilginç bir yere benziyor! Umarım Hawk oraya ışınlanmıştır... Bana iksirini verir misin?";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Sana vereceğim. Ama karşılığında bana üç yerel muska getirmelisin: "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian)+", "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet)+" ve "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg)+"Her muska için bir şişe. Böylece adil olur. Tüm muskaları topladığında geri gel. O zaman onları takas ederiz. Açgözlü olduğumu düşünme. Belki de muskaları ararken fikrini değiştirirsin.";
			link.l1 = "Bunu düşünmeyeceğim. Beni bekle, Yılan Göz, yakında döneceğim.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			npchar.quest.amulet = "true";
			AddQuestRecord("BaronReturn", "3");
			AddQuestUserData("BaronReturn", "sItem1", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian));
			AddQuestUserData("BaronReturn", "sItem2", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet));
			AddQuestUserData("BaronReturn", "sItem3", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg));
			sld = characterFromId("Danielle");
			sld.quest.talk = "SnakeEye";
			pchar.quest.BaronReturn_out.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out.function = "Saga_DannyTalk";
			pchar.questTemp.HelenDrinking.GiveAmulets = true;
			
			//if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap4_Start"))
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))	// Временно так
			{
				// Квест "Путеводная звезда", начало 4 этапа
				PChar.quest.PZ_Etap4_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap4_Start.win_condition.l1.location = "Shore9";
				PChar.quest.PZ_Etap4_Start.win_condition = "PZ_Etap4_Start";
				locations[FindLocation("Shore9")].DisableEncounters = true;
			}
		break;
		
		// даёт зелья - идем на телепортацию
		case "SnakeEye_potion":
			dialog.text = "Güzel, dostum. Kukulcan'a gidebilmen için bana tılsımları getirdin mi?";
			link.l1 = "Evet. Bir zamanlar zincirli kaptan Nathaniel’in çıktığı o yolculuğa çıkmaya hazırım.";
			link.l1.go = "SnakeEye_potion_1";
		break;
		
		case "SnakeEye_potion_1":
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Indian, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Amulet, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Obereg, 1);
			TakeNItems(pchar, "Ultimate_potion", 3);
			Log_Info("You have given amulets");
			Log_Info("You have received three versatile potions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bu iksirleri al. Unutma, Kukulcan seni dışarı attıktan hemen sonra birini içmelisin, yoksa ya ölürsün ya da ağır hasta kalırsın. Ayrıca, solgun yüzlülerin erzaklarını sakladığı ambar bölümüne gitmemeni de unutma. Gemiden çıkmanın başka bir yolu var. Aslında iki yol var. İlk gece kırmızı kadını bul, bu çok önemli. Sana söyleyebileceğim hepsi bu.";
			link.l1 = "Bunu unutmayacağım, kardeşim.";
			link.l1.go = "SnakeEye_potion_2";
		break;
		
		case "SnakeEye_potion_2":
			dialog.text = "O halde git. Gece yarısı Kukulcan'a dokun ve seni yutmasına izin ver. Sana yol gösterecek ruhları çağıracağım.";
			link.l1 = "Teşekkür ederim, Yılan Göz. Benim için endişelenme, her şey yoluna girecek. Yine görüşeceğiz!";
			link.l1.go = "SnakeEye_potion_3";
		break;
		
		case "SnakeEye_potion_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Saga.BaronReturn = "first_teleport";
			pchar.questTemp.Dolly = true; // телепорты работают!
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", true); // не пускать офицеров в локу телепорта
			DeleteAttribute(npchar, "quest.amulet");
			AddQuestRecord("BaronReturn", "4");
			sld = characterFromId("Danielle");
			sld.quest.talk = "teleport";
			pchar.quest.BaronReturn_out1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out1.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out1.function = "Saga_DannyTalk";
			QuestPointerToLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		// пришёл из LSC
		case "LSC_hello":
			dialog.text = "Seni görmek güzel, dostum. Gemi mezarlığından nasıl döndün?";
			link.l1 = "Kukulcan'ın heykelini orada buldum, tam da söylediğin gibi. Beyaz Oğlan bana yardım etti – Ole Christiansen. Heykel denizin dibine batmıştı, ama ona ulaşmayı başardım. Beni Dominika'daki bir Kızılderili köyüne ışınladı.";
			link.l1.go = "LSC_hello_1";
			npchar.quest.LSC_hello = "true";
		break;
		
		case "LSC_hello_1":
			dialog.text = "Monkitekuvri orada seninle buluştu mu?";
			link.l1 = "Hm. Monkitekuvri? O da kim?";
			link.l1.go = "LSC_hello_2";
		break;
		
		case "LSC_hello_2":
			dialog.text = "O köyün reisi.";
			link.l1 = "Adını sormadım. Belki Monkitekuvri'ydi, belki de değildi.";
			link.l1.go = "LSC_hello_3";
		break;
		
		case "LSC_hello_3":
			dialog.text = "Başında kuş tüylerinden yapılmış gösterişli bir başlık mı vardı?";
			link.l1 = "Tabii ki vardı. Bir sürü tüy... Sanki ormandaki bütün papağanları yolmuş gibi.";
			link.l1.go = "LSC_hello_4";
		break;
		
		case "LSC_hello_4":
			dialog.text = "Ona Monkitekuvri diyorlar. Bunlar papağan tüyü değil, kartal tüyü. Bu başlık benimdi. Kukulcan beni geri tükürdüğünde onu Monkitekuvri'ye verdim. Sonra beni başka bir heykele götürdüler...";
			link.l1 = "Ne tuhaf! Onlar da beni Kukulcan'a 'kurban etmişler'! Ve kendimi burada, ilk heykelin yanında buldum.";
			link.l1.go = "LSC_hello_5";
		break;
		
		case "LSC_hello_5":
			dialog.text = "Evet, solgun dostum. Benim yolculuğum da burada sona erdi.";
			link.l1 = "Putlar bir çemberin içinde ışınlanıyor... Ama bunun amacı ne? Bir fikrin var mı, Yılan Göz?";
			link.l1.go = "LSC_hello_6";
		break;
		
		case "LSC_hello_6":
			dialog.text = "Sanırım heykeller düzgün çalışmıyor. Şu anda insanları oradan oraya taşıyorlar, ama aslında hepsini tek bir yere götürmeleri gerekirdi. Bir sorunları var.";
			link.l1 = "Ne düşündüğünü nereden çıkardın?";
			link.l1.go = "LSC_hello_7";
		break;
		
		case "LSC_hello_7":
			dialog.text = "Çünkü bir daire içinde ışınlanmak anlamsız. Kukulcan tüm kurbanları bir araya getirmeli, onları oradan oraya taşımamalı.";
			link.l1 = "Ve o tek yer neresi olabilir?";
			link.l1.go = "LSC_hello_8";
		break;
		
		case "LSC_hello_8":
			dialog.text = "Bu büyük bir sır, beyaz kardeş, benim için bile.";
			link.l1 = "Anladım. Peki, putlar da cehenneme gitsin. Bir daha onlara yaklaşmam. Zincirlenmiş kaptanı buldum, artık portalardan geçmeme gerek yok.";
			link.l1.go = "LSC_hello_9";
			AddQuestRecord("BaronReturn", "12");
		break;
		
		case "LSC_hello_9":
			dialog.text = "Gemi mezarlığındayken. Orada benim defim buldun mu?";
			if (CheckCharacterItem(pchar, "buben"))
			{
				link.l1 = "Bence de öyle. Bir bak.";
				link.l1.go = "LSC_buben";
			}
			else
			{
				link.l1 = "Hayır. Ne yazık ki henüz bulamadım. Ama adanın nerede olduğunu biliyorum ve oraya ulaşabilirim. Tefini arayacağım.";
				link.l1.go = "LSC_hello_10";
			}
		break;
		
		case "LSC_hello_10":
			dialog.text = "Bul onu, solgun dostum. Lütfen, senden rica ediyorum. Defim olmadan, ruhları iyi duyamıyorum.";
			link.l1 = "Pekala, Yılan Göz. Görüşürüz!";
			link.l1.go = "exit";
		break;
		
		case "LSC_buben":
			RemoveItems(pchar, "buben", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Bu benim tef’im. Teşekkür ederim, solgun dostum. Sana borcumu ödeyebilirim. Sana bu silahı sunuyorum, halkının daha uzun süre sahip olamayacağı bir silah. Bu silah, benim zamanımın solgun yüzlülerinin silahıdır.";
			link.l1 = "İlginç! Göster bakalım, kızılderili dostum...";
			link.l1.go = "LSC_buben_1";
		break;
		
		case "LSC_buben_1":
			GiveItem2Character(pchar, "pistol7");
			Log_Info("You have received a Colt revolver");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 3);
			dialog.text = "Al bunu. Sadece üç şarj kaldı, diğerlerini kullandım. Ama belki sen de bunun için şarj yapmayı öğrenirsin. Şarj için gereken parçalardan birkaç düzinesini gemi mezarlığında kaybettim, orada bulabilirsin.";
			link.l1 = "Oho! Bu bir tabanca! Daha önce böyle bir şey görmemiştim... ne tuhaf bir alet. Döner bir mekanizma... beş fişek! Güzel!";
			link.l1.go = "LSC_buben_2";
		break;
		
		case "LSC_buben_2":
			dialog.text = "Buna Colt revolver deniyor. Sizin zamanınızda bunun gibi başka bir tabanca yok. Kullanması kolay, sadece horozu çekip tetiği sıkıyorsunuz. İyi ateş ediyor.";
			link.l1 = "Teşekkürler! Teşekkürler, Yılan Göz! Bu, düşmanlarım için hoş bir sürpriz olacak... Keşke sadece üç atış olmasaydı...";
			link.l1.go = "LSC_buben_3";
		break;
		
		case "LSC_buben_3":
			dialog.text = "Kendine bir Colt tabancası için mermi yapmayı öğretmeye çalış. O zaman zamanının büyük bir savaşçısı olacaksın. Ah, solgun kardeşim, sana gemi mezarlığında pipomu bulmanı söylemeyi unuttum. Çok güzel bir pipoydu.";
			if (CheckCharacterItem(pchar, "smoking_tube"))
			{
				link.l1 = "Ha! Ben de bu boyalı piponun kime ait olabileceğini merak ediyordum. Bir bak bakalım.";
				link.l1.go = "LSC_tube";
			}
			else
			{
				link.l1 = "Pekala. Çubuğunu da arayacağım. Görüşürüz!";
				link.l1.go = "exit";
			}
			npchar.quest.LSC_tube = "true";
		break;
		
		case "LSC_tube":
			RemoveItems(pchar, "smoking_tube", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Bu benim pipom, kardeşim. Onu bulduğuna sevindim. Karşılığında sana başka bir hediye verebilirim. Bu, benim zamanımdan kalma akıllı bir beyazların kitabı. Ben anlamıyorum. Bu kitabı okuyup anlayabilecek zeki birini bulmaya çalış.";
			link.l1 = "Teşekkür ederim, Yılan Göz. Bununla ilgilenecek birini tanıdığımı düşünüyorum.";
			link.l1.go = "LSC_tube_1";
		break;
		
		case "LSC_tube_1":
			GiveItem2Character(pchar, "chemistry");
			Log_Info("You have received a Lavoisier's chemistry textbook");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ona ver, beyaz kardeş. Bu kitap, soluk yüzlülerin büyük bilgeliğinin sırlarını barındırıyor.";
			link.l1 = "Güzel. Görüşürüz, Yılan Göz!";
			link.l1.go = "exit";
		break;
		
		// лечение Натаниэля
		case "Saga_nathaniel":
			dialog.text = "Seni dinliyorum, solgun yüzlü kardeşim.";
			link.l1 = "Zincirlenmiş kaptanı, gemi mezarlığında aradığım adamı, yanıma getirdim. Durumu çok kötü. Onu yalnızca sen iyileştirebilirsin, bunu biliyorum...";
			link.l1.go = "Saga_nathaniel_1";
		break;
		
		case "Saga_nathaniel_1":
			dialog.text = "Kukulcan sağlığını tüketti. Sanırım iyileşmesine yardımcı olabilirim. Ama bu en az bir dolunay sürecek. Kukulcan kaptanı çok önce yedi ve hastalık içine derinlemesine yayıldı.";
			link.l1 = "Lütfen onu iyileştir, şaman! Sana ne gerekiyorsa getireceğim!";
			link.l1.go = "Saga_nathaniel_2";
		break;
		
		case "Saga_nathaniel_2":
			dialog.text = "Deneyeceğim, beyaz kardeş. Bana bir şey getirmen gerekmiyor. Her şeye sahibim. Zaman hastalığı güçlendirir, ama zincirlenmiş bir kaptan bir ay sonra yeniden sağlığına kavuşur.";
			link.l1 = "Teşekkür ederim, kızıl derili kardeşim. Bir kez daha hayatımı kurtardın.";
			link.l1.go = "Saga_nathaniel_3";
		break;
		
		case "Saga_nathaniel_3":
			dialog.text = "Zincirli kaptanı kulübeme bırak, beyaz kardeş, ve gönlün rahat olsun. Karısını da getir, kimse ayinlerimi görmeyecek.";
			link.l1 = "Pekâlâ, Yılan Gözü. Danielle'i yanıma alacağım. Görüşürüz!";
			link.l1.go = "Saga_nathaniel_4";
		break;
		
		case "Saga_nathaniel_4":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "treatment";
			sld = characterFromId("Nathaniel");
			RemovePassenger(Pchar, sld);
			LAi_SetStayType(sld);
			sld.location = "none";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1.location = pchar.location;
			pchar.quest.Saga_NatanTreatment1.function = "Saga_NatanTreatment";
		break;
		
		case "calendar":
			dialog.text = "Seni dinliyorum, dostum.";
			link.l1 = "Kukulcan heykelleri hakkında konuşmamızı hatırlıyor musun? 'İnsanları özel bir yere getirmeliler' demiştin.";
			link.l1.go = "calendar_1";
		break;
		
		case "calendar_1":
			dialog.text = "Hatırlıyorum, beyaz kaptan.";
			link.l1 = "O heykellerin, Kukulcan tarafından yenilen insanları nereye götürdüğünü biliyorum.";
			link.l1.go = "calendar_2";
		break;
		
		case "calendar_2":
			dialog.text = "Nerede?";
			link.l1 = "Eski Maya şehri Tayasal'a. Ana karanın derin ormanlarında yer alıyor.";
			link.l1.go = "calendar_3";
		break;
		
		case "calendar_3":
			dialog.text = "Çok ilginç. Bunu nereden biliyorsun?";
			link.l1 = "Uzun bir hikaye bu, Yılan Göz. Senin de buraya nasıl düştüğünü anlıyorum. Daha doğmamışsın bile, değil mi?";
			link.l1.go = "calendar_4";
		break;
		
		case "calendar_4":
			dialog.text = "Babam bile senin zamanında doğmadı. Ama ben senin zamanında yaşıyorum, işte bu büyük bir sır.";
			link.l1 = "Aslında açıklanabilir bir durum. Tayasal'da yaşayan Kanek adında bir Itza rahibi, Kukulcan'a bu dünyada bir ölümlü olarak doğması ve beyaz ırkın bilgeliğini özümsemesi için dua etmiş. Ayrıca zamanda bir delik açarak, gelecekte yaşayan birkaç adamı da bizim zamanımıza ışınlamış...";
			link.l1.go = "calendar_5";
		break;
		
		case "calendar_5":
			dialog.text = "Geleceğin insanlarının bilgeliğini Kukulcan'ın özümsemesine izin vermek mi?";
			link.l1 = "Evet. Ve Kukulcan, bilgeliği çoktan ölmüş Maya halkına ulaştırmak için geçmişe gitmeyi planlıyor. Tarih değişecek, Mayalar Amerika'ya ve belki de daha ötesine hükmedecek...";
			link.l1.go = "calendar_6";
		break;
		
		case "calendar_6":
			dialog.text = "";
			link.l1 = "Ama portallarda bir şey oldu ve insanları Tayasal'a götürmek yerine sürekli aynı yere ışınlamaya başladılar. İşte bu yüzden buradayım, sana danışmam gerek, Yılan Göz.";
			link.l1.go = "calendar_7";
		break;
		
		case "calendar_7":
			dialog.text = "Neden ben, beyaz kaptan?";
			link.l1 = "Çünkü Kukulcan tarafından yutuldun. Ve köyünün yakınındaki Kukulcan heykelinin üzerinde, bu haritada tuhaf bir işaret var; bu da Kanek’in ritüelleriyle yakından bağlantılı.";
			link.l1.go = "calendar_8";
		break;
		
		case "calendar_8":
			dialog.text = "Bana bu haritayı gösterir misin?";
			link.l1 = "Bak, şuna bir göz at...";
			link.l1.go = "calendar_9";
		break;
		
		case "calendar_9":
			RemoveItems(pchar, "skinmap", 1);
			dialog.text = "(bakıyor) Bu yuvarlak işaret, değil mi? Peki, bu ne anlama geliyor?";
			link.l1 = "Bilmiyorum, şaman. Bildiğim tek şey, üç Kukulcan heykelinden birinde bu işaretin olduğu. Ve bu işaretli heykel senin. O yüzden senin heykelinin özel olduğunu düşünüyorum. Bir fikrin var mı?";
			link.l1.go = "calendar_10";
		break;
		
		case "calendar_10":
			dialog.text = "Bana yarına kadar izin ver, beyaz kardeş. Bu deri haritayı burada bırak. Ruhlara danışmam gerek. Yarın geri gel.";
			link.l1 = "Pekâlâ, kızılderili kardeşim. Yarın burada olacağım. Bana yardım ettiğin için teşekkür ederim.";
			link.l1.go = "calendar_11";
		break;
		
		case "calendar_11":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarThink", 0, 0, 1, false);
			pchar.questTemp.Tieyasal = "calendar_think";
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_wait":
			dialog.text = "Daha sonra gel, beyaz kardeş. Şimdi beni rahatsız etme.";
			link.l1 = "Tabii, şaman...";
			link.l1.go = "exit";
			NextDiag.TempNode = "calendar_wait";
		break;
		
		case "calendar_12":
			dialog.text = "Sana söylemem gereken bir şey var, beyaz kardeş.";
			link.l1 = "Bir şey bulabildin mi? Ya da herhangi bir tahminin var mı?";
			link.l1.go = "calendar_13";
		break;
		
		case "calendar_13":
			dialog.text = "Atalarımın ruhları bana bir vizyon verdi ve haritayla birlikte Kukulcan'a gittim. Aradım ve buldum. Aradığın şey bu olmalı, beyaz kardeş.";
			link.l1 = "Ne buldun?";
			link.l1.go = "calendar_14";
		break;
		
		case "calendar_14":
			dialog.text = "Kukulcan heykelinde iki demir kelepçe ve bir oyuk var. Oyuk yuvarlak ve pürüzsüz. Deri haritandaki yuvarlak, düz eşyaya doğru bakıyor.";
			link.l1 = "Ne oldu?";
			link.l1.go = "calendar_15";
		break;
		
		case "calendar_15":
			dialog.text = "Bilmiyorum. Sadece yuvarlak, düz, küçük bir balkabağı büyüklüğünde ve belki bir parmak kalınlığında olduğunu biliyorum. Girintiye ve kelepçelere kendin bakabilirsin. Kelepçe onu tutacak kadar sağlam olmalı.";
			link.l1 = "Bir fikrin var mı? Ya da ne olabileceğine dair bir tahminin?";
			link.l1.go = "calendar_16";
		break;
		
		case "calendar_16":
			dialog.text = "Taşta ateşin izi var. Ona ne olduğunu biliyorum. Gökyüzünden gelen ateş ona çarptı.";
			link.l1 = "Yıldırım mı? Yıldırım mı çarptı?";
			link.l1.go = "calendar_17";
		break;
		
		case "calendar_17":
			dialog.text = "Bundan eminim. Miskitolara bu put hakkında sordum. Bir savaşçı, uzun zaman önce heykelin yanında birkaç güzel boyalı şey görüldüğünü söyledi. Taşa çok benziyorlarmış. Bana onların çok güzel kırmızı taşlar olduğunu anlattı. Beyaz köyden bir beyaz adam onları satın almış.";
			link.l1 = "Hm. Anladığım kadarıyla, yıldırım bu yuvarlak 'şeye' çarpmış, onu parçalara ayırmış ve sonra bu parçalar bir beyaz adama satılmış, öyle mi?";
			link.l1.go = "calendar_18";
		break;
		
		case "calendar_18":
			dialog.text = "Öyle görünüyor.";
			link.l1 = "Ve o beyaz adam kimdi? Savaşçın sana söyledi mi?";
			link.l1.go = "calendar_19";
		break;
		
		case "calendar_19":
			dialog.text = "Bana anlattı. Miskito halkının büyük bir dostuydu ve Blueweld köyünde yaşıyor. Adı Orman Şeytanı. Onu tanıyorum, sen de mutlaka tanıyorsundur.";
			link.l1 = "Jan Svenson? Bir dakika... kırmızıya boyanmış kayalar mı dedin? Sanırım bugün şansım yaver gitti. Bak buraya, şaman, şu kırmızı kayalara bak! Orman Şeytanı bana onları hediye etti.";
			link.l1.go = "calendar_20";
		break;
		
		case "calendar_20":
			Log_Info("You have given ornamental pattern fragments");
			RemoveItems(pchar, "splinter_js", 1);
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			dialog.text = "Onlar olmalı. Beş taş. Bak bir, beyaz kardeş. Eğer bunları böyle yerleştirirsen... (birleştirerek)";
			link.l1 = "...";
			link.l1.go = "calendar_21";
		break;
		
		case "calendar_21":
			dialog.text = "... o zaman yuvarlak bir parçamız var. Bak! Uyumlu görünüyorlar. Eskiden tek bir parçaydı bu.";
			link.l1 = "Lanet olsun! Ve bu şeyler cebimde ne zamandır duruyor... Dinle, şaman, eğer parçaları o oyuğa yerleştirirsem...";
			link.l1.go = "calendar_22";
		break;
		
		case "calendar_22":
			dialog.text = "Kukulcan, dediğin gibi kurbanı eski Kızılderili şehrinde dışarı atacak.";
			link.l1 = "Harika olurdu! Oraya gitmem lazım! Sence süs eşyası parçalara ayrılmışsa yine de işe yarar mı?";
			link.l1.go = "calendar_23";
		break;
		
		case "calendar_23":
			dialog.text = "Bence onları bir araya getirmeli ve ardından süsü oyuğa yerleştirmeliyiz.";
			link.l1 = "Onları bir araya getirmek mi? Ama onları nasıl tekrar birleştirebiliriz?";
			link.l1.go = "calendar_24";
		break;
		
		case "calendar_24":
			dialog.text = "Bunu bana ve ataların ruhlarına bırak, beyaz kardeş. Bunlar basit taşlar değil. Bu, mucizevi bir eşya. Üç gece sonra tekrar gel, beyaz kardeş. Ruhları, yaşayanların bilgeliğini ve ustalığını çağıracağım, ve parçaları birleştirmeye çalışacağım.";
			link.l1 = "İnanılmaz... Sana nasıl teşekkür edebilirim, Yılan Göz?";
			link.l1.go = "calendar_25";
		break;
		
		case "calendar_25":
			dialog.text = "Daha sonra teşekkür edersin, beyaz kardeş. Şimdi git. Üç gece sonra geri dön.";
			link.l1 = "Pekala. Umarım başarılı olursun...";
			link.l1.go = "calendar_26";
		break;
		
		case "calendar_26":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarDone", 0, 0, 3, false);
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_28":
			dialog.text = "Seni mutlu edebilirim, beyaz kardeş.";
			link.l1 = "Parçaları birleştirebildin mi?";
			link.l1.go = "calendar_29";
		break;
		
		case "calendar_29":
			dialog.text = "Evet. Kolay olmadı ve takvimde izler kaldı, ama şimdi tamamlandı.";
			link.l1 = "Takvim mi? Neden böyle diyorsun?";
			link.l1.go = "calendar_30";
		break;
		
		case "calendar_30":
			dialog.text = "Çünkü bu yuvarlak şey bir takvim. Onu dikkatlice inceledim. Üzerinde bir zaman sayacı var. Eski şehirden gelen yerliler geceleri, ayları, yılları ve çağları sayıyorlar.";
			link.l1 = "İnanılmaz... Yine de, Maya rahiplerinin neler yapabildiğini düşününce, bu takvimin yaratılması o kadar da olağanüstü gelmiyor.";
			link.l1.go = "calendar_31";
		break;
		
		case "calendar_31":
			GiveItem2Character(pchar, "calendar_maya");
			sld = ItemsFromID("calendar_maya");
			sld.shown = "0";
			Log_Info("You have received a Maya calendar");
			dialog.text = "Al bunu, beyaz kaptan. Onu heykeldeki oyuğa yerleştir. Belki o zaman seni Hint şehrine tükürür.";
			link.l1 = "Sana nasıl teşekkür edebilirim, Yılan Göz?";
			link.l1.go = "calendar_32";
		break;
		
		case "calendar_32":
			dialog.text = "Teşekkür et. Tanrılar yolunu aydınlatıyor, sen fark etmesen de. Beyazlar buna kader diyor. Kukulcan seni çağırdı, tanrılar sana yol gösteriyor. Şimdi git. İşini yap ve iyi ruhlar sana rehberlik etsin.";
			link.l1 = "Teşekkür ederim, Yılan Göz! Seni asla unutmayacağım.";
			link.l1.go = "calendar_33";
		break;
		
		case "calendar_33":
			TakeNItems(pchar, "Ultimate_potion", 4);
			Log_Info("You have received four versatile potions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bekle. Az kalsın en önemli şeyi unutuyorduk. Kukulcan insanları yer ve hayatlarını tüketir. Sana iksirler yaptım. Komançi iksirleri. Onları sana vereceğim. Dört şişe hazırladım, böylece yanında üç sadık ve cesur yoldaş götürebilirsin.";
			link.l1 = "Benim için çok şey yaptın, can kardeşim...";
			link.l1.go = "calendar_34";
		break;
		
		case "calendar_34":
			dialog.text = "Kardeş, Komançi kabilesinin yerlileri için sadece bir kelime değildir. Kukulcan şehrinden döndüğünde köyümüze uğra. Bolca saraiaka pişireceğiz. Seni görmekten memnun olacağım.";
			link.l1 = "Elbette, kızılderili kardeşim! Kesinlikle seni ziyaret edeceğim!";
			link.l1.go = "calendar_35";
		break;
		
		case "calendar_35":
			DialogExit();
			pchar.questTemp.Tieyasal = "calendar_place";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Tieyasal", "17");
			sld = ItemsFromID("skinmap");
			sld.price = 100; // кожаную карту можно выкладывать 270912 
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
