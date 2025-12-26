// Джозеф Лодердэйл - английский военный офицер
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
				dialog.text = "Defol, efendi! Masumlara saldırıyor, sıradan bir haydut gibi kavga ediyorsun! Gözüm görmesin seni!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "İyi günler, efendim. Burada bir soyluyla karşılaşmak beni memnun etti.";
				link.l1 = TimeGreeting()+" Aslında Karayipler'de geçirdiğim onca zaman boyunca halkın arasında o kadar uzun süre kaldım ki, soylu olduğumu unutmaya başladım.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetFullName(pchar)+"! Seni görmek güzel! Ne dersin?";
				link.l1 = LinkRandPhrase("Günaydın, Joseph! Adada ne var ne yok?","Adada yeni bir şey oldu mu?","Bana son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sana sadece selam vermek istedim. Hoşça kal!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ah, hem de alçakgönüllü bir soylu! Gerçek bir centilmen! Sanırım seninle iyi arkadaş olacağız – sen o kendini beğenmiş Başrahip gibi değilsin... Kendimi tanıtayım: Kaptan Joseph Lauderdale, İngiliz Donanması'ndan.";
			link.l1 = "İyi karşılandınız, Kaptan. "+GetFullName(pchar)+" hizmetinizdeyim!";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Burada hayat oldukça sıkıcı, bu yüzden akşam meyhaneye uğra, birer kadeh şarap içip beyefendiler gibi sohbet edelim.";
			link.l1 = "Bunu aklımda tutacağım, efendim. Şimdilik hoşça kalın!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("İyi günler, Joseph. Nasıl gidiyor?","Adada yeni bir şey oldu mu?","Bana son dedikoduları anlatır mısın?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Sana ada hakkında birkaç soru sormak istiyorum.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sorularınızı yanıtlamak benim için bir zevk olur, efendim.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Buraya nasıl geldin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Adada ne tür hizmetler bulabilirim?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Bir denizci olarak, burada korsanların hakimiyeti hakkında ne düşünüyorsun?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Adanın etrafında çok sayıda kilitli sandık gördüm. İnsanlar birbirine güvenmiyor, değil mi?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorunuz yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Vazifemi yapıyordum. Bir İspanyol savaş şalopuyla çarpışıyordum, birkaç İngiliz tüccarını yağmalamakla suçlanan bir gemiydi. Çatışma saatlerce sürdü. Neredeyse onları yakalıyorduk ki, aniden çıkan bir fırtına her şeyi altüst etti: iki gemimiz de dış halkada karaya oturdu.\nKaderin tuhaf bir mizahı var, çünkü hem ben hem de İspanyol rakibim hayatta kaldık. Belki onunla çoktan karşılaştın - adı Lorenzo Solderra, ender rastlanan bir Papist piçi. Ondan sakın.";
			link.l1 = "Hikayen için teşekkür ederim, uyarını dikkate alacağım...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "If you need to rest, visit Sancho's tavern. He'll always provide you with food, drink, and a bed. If you need powder, shot, cold steel and the like, go to Axel Yost; he owns the local shop. Brother Julian offers medicines and sells holy amulets in his church.\nThe Narwhals have a very talented blacksmith, name of Jurgen Schmidt. They say that he crafts the most exquisite blades. There's another talented craftsman among the Narwhals, but I never learned anything about him.\nIf you run afoul of the pirates or the other clans, see Giuseppe Fazio; he functions as a sort of local diplomat between the clans.";
			link.l1 = "Bilgi için teşekkürler!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "I can't say I like it, but there's nothing I can do about it - and even I must admit they established peace on the island in record time. Before the pirates arrived, the clans fought each other almost daily with no regard for the innocents caught in the middle.\nMoreover, the pirates sell food at a fair rate; citizens get good nutrition cheaply. But the pirates gouge the clans as revenge for attacking them when they first arrived.\nI know a very smart man among the pirates: Layton Dexter. He's in charge of all their trade. I had a talk with him once. I wonder how such a talented and educated man - who knows tactics, cartography and economics - wound up joining a band of pirates.\nYou know it only took him a few days to make a map of this whole island? I saw it, it has almost everything. I believe he made it in anticipation of a war between the clans...";
			link.l1 = "Anladım...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Bu ihtiyat, dostum, ihtiyat. Eskiden adada hırsızlığın yaygın olduğunu söylerlerdi – ta ki tüm sandıklara yeni kilitler takılana kadar.\nAma yine de... sandıkları açabilen biri var. Yalnızca rom ve ucuz takı çalıyor, asla altın ya da para değil.\nHer kilit eşsizdir, yedek anahtar yok – Jurgen Schmidt buna özellikle dikkat etti. Sadece kılıç değil, kilit ve anahtar da yapar. Dışarıdaki sandıklarda değerli bir şey olmadığını, önemli eşyaların her zaman gemilerde saklandığını duydum.";
			link.l1 = "İlginç...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ben seni asil biri sanmıştım, meğerse sıradan bir hırsızmışsın!","Beni soymaya mı kalkıyorsun, ha? Sana Kraliyet Donanması'nda hırsızlarla nasıl başa çıktığımızı göstereceğim!","Ellerini deniz sandığımdan çek, hırsız!!");
			link.l1 = "Ah, kahretsin!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Hırsız! Biri şu hırsızı durdursun!";
			link.l1 = "Kes sesini!";
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
			dialog.text = LinkRandPhrase("Beyefendi, lütfen kılıcınızı yerine koyun. Herkesin dikkatini çekiyorsunuz.","Kılıcını kınına sok, yoksa birisi seni buna zorlayabilir.","Bir erkekte cesareti takdir ederim, ama belki de şimdi kılıç sallamanın zamanı değildir...?");
			link.l1 = LinkRandPhrase("Pekâlâ.","Nasıl istersen...","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Şu numaralarını bırak, beyefendi. Kılıcını yerine koy.","Beyefendi, lütfen kılıcınızı indirin. Herkesin dikkatini çekiyorsunuz.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Nasıl istersen...","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Beyefendi, lütfen kılıcınızı indirin. Dikkat çekiyorsunuz.","Bir adamda cesareti takdir ederim, ama belki de şimdi kılıç sallamanın zamanı değildir...");
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
