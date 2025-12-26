// Антонио Бетанкур - потомок Франциско Бетанкура
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Gözümün önünden kaybol! Masum insanlara sebepsiz yere saldıran haydutlarla işim olmaz. Defol!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Selam! Senin için ne yapabilirim, dostum?";
				link.l1 = TimeGreeting()+" . Benim adım "+GetFullName(pchar)+" . Kendimi tanıtmak istedim. Gördüğünüz gibi, yeni geldim ve şehri ve insanlarını yeni yeni tanıyorum.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Size nasıl yardımcı olabilirim?";
				if(CheckAttribute(pchar, "questTemp.LSC.Betancur"))
				{
					link.l4 = "Antonio, adanın tarihini iyi bildiğini söylüyorlar. Sana bir sorum var...";
					link.l4.go = "dolly";
				}
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Bir şey mi istiyorsun? ";
				link.l1 = LinkRandPhrase("Ne haber, Antonio?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Adanın hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu görmek istemiştim. Hoşça kal, efendim!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Harika. Adalet Adası'na hoş geldin! Burada iyi olacaksın, çünkü hepimiz büyük ve mutlu bir aileyiz - tabii Narvaller ve o pis Rivadoslar hariç.\nBenim adım Antonio, Antonio de Betancourt. Francisco de Betancourt'un torunuyum, eğer bu isim sana bir şey ifade ediyorsa.";
			link.l1 = "Francisco de Betancourt mu? Bu ismi daha önce duymuştum... Ah, evet! Jose Dios bana ondan bahsetmişti, bir de Ignacio Alvarado'nun notlarında okumuştum!";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Bu 'Jose Dios' dediğiniz kişiyi tanımam, ama Kaptan Alvarado bizi uzun zaman önce ziyaret etmişti – çocukken kendim gördüm onu. Adadan ayrıldı ve anılarında buradan bahsetti. Dedem Francisco ise kendi filosuna komuta eden bir İspanyol amiraliydi.\nRivados'un bu adadaki tarihinin bir parçası olmasının sebebi, onların filonun amiral gemisi Tartarus'un siyahi kölelerinden gelmeleridir. Narvaller ise ilk beyaz yerleşimcilerin çocuklarıdır: Tartarus, San Augustine ve San Geronimo'nun mürettebatı.";
			link.l1 = "İnanılmaz! Yani burada mı doğdun?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Aynen öyle. Adayı kolonileştiren adamın torunuyum.";
			link.l1 = "Anladım. Tanıştığımıza memnun oldum, Antonio. Hoşça kal.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестовая часть
		case "dolly":
			dialog.text = "Tabii dostum, sor bakalım. Elimden geldiğince sorularını yanıtlarım.";
			link.l1 = "Bana söyle, San Geronimo adında bir kalyonu hatırlıyor musun?";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Elbette biliyorum. Çok özel bir gemiydi. Gemide tuhaf bir Hint putu vardı, o pis putperest Rivados ona kurbanlar sunardı.";
			link.l1 = "Ne tür fedakârlıklar? Maya'lar gibi insanların kalbini mi çıkarıyor, kafalarını mı kesiyorlardı?";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = "No. When a victim was brought to the idol, it dragged them into itself and they disappeared forever. Devil's work! Thank God above the idol sank with the ship and will do none harm any longer.\nThe sacrifices were always made in the morning; the idol used to turn to gold in the  rising sun's rays, so that was when the savages brought their victims - mostly Narwhals they'd captured.";
			link.l1 = "Büyüleyici! Hiç kimse puta ulaşmaya çalıştı mı?";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "Tabii ki hayır! Birincisi, Rivados kendi halkı dışında kimseyi San Geronimo'ya yaklaştırmaz, ikincisi ise dürüst bir Katolik şeytanın oyunlarından uzak durmalıdır.";
			link.l1 = "Anladım... Demek ki Rivados'lardan pek hoşlanmıyorsun.";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Good Lord, I hate those dirty pagans! As I said, my grandfather - God rest his soul - was captain of the ship upon which the negroes revolted, led by their leader, Rivados. Giving that black bastard a slow death was the only right and just response such actions.\nI had a gorgeous key to the St. Anna's treasury. No one knows where the treasury now lies - probably at the bottom of the sea with crabs picking over it - but the key was a sweet memento to me, and it was stolen!\nI am certain the blacks did it - trying to find the treasury! I doubt they'll succeed; it has been too long, ha-ha! Scum...";
			link.l1 = "Evet... ıhm, her neyse, ilginç hikayen için teşekkürler!";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "Hoş geldin! Ne zaman istersen uğra!";
			link.l1 = "Elveda!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Betancur");
			AddQuestRecord("LSC", "16");
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Dinliyorum, dostum.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Yani, adadan hiç ayrılmadın mı?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Burada doğdun... ama Narval klanından değilsin? Tüm yerli beyazların Narval olduğunu sanıyordum.";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Peki, adada ne yapıyorsun?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Bana söyle, hiç adadan ayrılıp dünyayı görmek istedin mi?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorunuz yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Bir kez bile değil. Ama beni aptal ya da dar görüşlü sanma. Dedemden güzel bir kütüphane miras kaldı, babam da bana çok iyi bir eğitim verdi. Tarih, coğrafya, astronomi bilirim. İngilizce, Fransızca, İspanyolca, Latince konuşurum. Çürüyen gemi enkazlarından başka bir şey görmemiş olsam da, zihnimde Avrupa'yı, Çin'i, Hindistan'ı gezdim...\nAslında, dünyayı dolaşmış çoğu denizciden çok daha fazlasını bildiğimi söyleyebilirim.";
			link.l1 = "Belki...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = " Hepsi değil, ama çoğu. Ama ben bir Narval değilim ve onlardan biri olmak da istemiyorum. Neden olayım ki? Saatlerce güneşin altında nöbet tutmak ya da Rivados'la bir kavgada bağırsaklarımın deşilmesini mi bekleyeyim? Tanrım, bundan beni koru! Ben entelektüelim. Bağımsız yaşamayı ve kitap okumayı tercih ederim.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Babam bana hatırı sayılır bir miras bıraktı ve ben de onu akıllıca harcıyorum, bu yüzden yiyecek için takas edecek süs eşyaları bulmak adına eski gemi enkazlarında sürünmeme ya da var olup olmadığı bile belli olmayan hazinelerin peşine düşmeme gerek yok.\nKesin olarak bildiğim tek hazine St. Anna'nın hazinesi. Büyük bir demir sandığın içinde, ama henüz kimse onu bulamadı.\nBir gün, adanın yerel sözlü tarihine dayalı ayrıntılı bir kronik yazacağım - sence nasıl olur?";
			link.l1 = "Böylesi bir uğraş gerçekten değerli! Karayipler'de böyle bir kitap için iyi para ödeyecek en az bir adam tanıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Bazen. Eğer akıntılarla ve fırtınalarla başa çıkabilecek bir gemi gelseydi, belki de riski göze alırdım. Kitaplarımda özenle anlatılan o şeyleri görmeyi gerçekten çok isterim! Ama şimdilik, bunlar sadece hayal...";
			link.l1 = "Bazen hayaller gerçek olur... eğer onları gerçekleştirirsen.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ahh, imdaaat! Hırsız!!","Sen de ne düzenbazsın, arkamı döndüğümde beni soymaya kalkıyorsun!","Ellerini ondan çek! O sandık benim! Birisi, yardım etsin!");
			link.l1 = "Vay kahretsin!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Sandıklarımı açarak ne yaptığını sanıyorsun? Bunun yanına kar kalmayacak!";
			link.l1 = "Lanet olsun!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Kılıcınızı kınınıza koyun, efendim! Beni tedirgin ediyorsunuz.","Burada elinde kılıçla dolaşmak akıllıca değil, dostum. Kınına koy onu.","Ah, kılıcını çocuk gibi savurup durma, yerine koy onu.");
			link.l1 = LinkRandPhrase("Pekâlâ.","Nasıl istersen...","Özür dilerim...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Bu şehrin bir vatandaşı olarak, kılıcınızı indirmenizi talep ediyorum, efendim!","Kılıcınızı indirin efendim! Herkesin dikkatini çekiyorsunuz.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Nasıl istersen...","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dostum, lütfen kılıcını indir. Bu beni tedirgin ediyor...","Önümde silah sallayan adamlardan hoşlanmam. Bu beni korkutuyor...");
				link.l1 = RandPhraseSimple("Üzgünüm.","Onu kaldırıyorum.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
