// Жаклин Тьюрам - торговый капитан
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
				dialog.text = "Seninle konuşmak istemiyorum. Masum sivillere sebepsiz yere saldırıyor ve onları kavgaya kışkırtıyorsun. Hoşça kal!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "İyi günler, monsieur. Burada yenisiniz, değil mi?";
				link.l1 = TimeGreeting()+"Evet, sanırım öyleyim. Benim adım "+GetFullName(pchar)+". Peki ya sen kimsin?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, bonjour "+GetFullName(pchar)+"! "+TimeGreeting()+"! Bugün size nasıl yardımcı olabilirim?";
				link.l1 = LinkRandPhrase("Bonjour, Bay Turam! Anlat bakalım, son haberler neler?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu merak ettim. Hoşça kal!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Jacques Turam. Two years ago I was a respectable and wealthy merchant, owner and captain of my own fluyt. Alas, now I am as poor as a church mouse with no hope that my situation will change.\nSome people get lucky here; they find gold, jewels, ships filled with treasure, but I am not one of them. I found only a single chest of doubloons and few trinkets.\nAt least it's enough to buy food, so I don't starve... Pleasure to meet you, sir, I don't mind chatting.";
			link.l1 = "Ben de seninle tanıştığıma memnun oldum, Jacques. Au revoir!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Bonjour, Bay Turam! Bana en son haberleri anlat.","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Sana ada hakkında birkaç soru sormak istiyorum.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Tamamen seni dinliyorum.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Buraya nasıl geldin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Burada ne yapıyorsun?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Söyle bana... Adada kadınlar olduğunu görüyorum...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Geri dönmek ister misin, o engin dünyaya?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bir şey değil.";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "You want to hear my story? Fine. As you already know, I was a merchant. One day I sailed from Tortuga to Belize on my good old fluyt. My holds were filled with ebony and cacao - I spent all my money on the cargo.\nI'd arranged a very profitable deal with a man who wanted to buy my cargo for an extremely high price. I would've made a fortune. All was going well, not a single cloud in the sky, my ship as swift as a bird. Then trouble came.\nI was sailing near Cuba, avoiding Spanish patrols, when suddenly we were attacked by a pirate galleon. What were they doing there, in the middle of Spanish territory? We tried to flee, but the galleon was surprisingly fast.\nThe pirates caught us up and attacked. Their couleuvrines were loaded with grape shot - the first salvo took out half my crew demoralized the rest. I wanted to put up a good fight, but my crew and officers stopped me. We surrendered.\nThe pirates took our cargo and threw away our cannons. I hoped it was not the end for me; losing the cargo was a heavy blow, but I could still make money on freight contracts and until I got back on my feet.\nBut fate had other plans. The pirate bastards opened fire on my defenseless fluyt - we were a sitting duck without our guns. I can still hear the pirates' laughter...\nThe galleon sailed away and we clung to the wreck of our ship. Then a strong gale came and a wave carried me overboard. I managed to lash myself to a broken spar and stay afloat.\nI'll spare you the details about my brush with sharks. After an eternity the currents brought me to this island. That's how I survived.";
			link.l1 = "Evet, bu gerçekten üzücü bir hikaye.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ben de diğer yerliler gibi yaşıyorum: dış halkada değerli bir şeyler arar, bulduklarımı yiyecekle takas ederim. Bir gün bir Kızılderili reisinin hazinesini ya da İspanyol altınlarıyla dolu bir kalyonu bulmayı hayal ediyorum...\nBir de tuzlu et ve balıktan başka bir şey yemeyi hayal ediyorum - burada dev yengeçleri avlayan bir adam vardı. Ona bir pençesi için beş dublon verirdim, günlerce onunla karnımı doyururdum.\nYazık ki öldü... Gerçi kimse şaşırmadı diyemem - o yengeçleri avlamak gerçekten tehlikeli bir iş.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "I see what you're implying. Yes, love and intrigue exist here - and why wouldn't they? Man is made for woman as woman is made for man. That's nature. You may try Gillian and Tanneke; they are young, pretty and open to courting.\nI myself have already found a woman: Natalia. She is a waitress in Sancho's tavern. A great girl, I tell you. I believe she is the only reason I didn't lose my mind during those first months living here. She has helped me a lot and now we are together.";
			link.l1 = "Ah, romantik!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Güzel soru. Elbette isterdim. Ama düşününce... Beş parasızım. Tüm paramı yüküme yatırdım ve şimdi hem yüküm hem de gemim battı. Hiçbir şeyim kalmadı. Şu anda aklıma gelen tek para kazanma yolu Hollanda Batı Hindistan Şirketi için çalışmak - tabii eğer beni işe alırlarsa.\nBir şalopa ve biraz erzak alacak kadar param olsaydı keşke... ama yok, o yüzden adada kalmam daha iyi. En azından burada bir dilim ekmek için gün doğumundan gün batımına kadar çalışmak zorunda değilim.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Kim - ah, hırsız!","Eşyalarımdan elini çek, seni şeytan!","Bu benim sandığım! Ondan uzak dur!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Çekmecelerimi karıştırmaya nasıl cüret edersin!";
			link.l1 = "Sessiz ol!";
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
			dialog.text = LinkRandPhrase("Beyefendi, yalvarırım, silahınızı indirin. Beni korkutuyorsunuz.","Biliyor musun, silahın çekili halde etrafta koşuşturursan kendini yaralayabilirsin.","Kızları etkilemek için şövalyecilik yapmaya çalışma. Onu yerine koy...");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Ee, doğru...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Beyefendi, bu adanın bir sakini olarak sizden kılıcınızı indirmenizi rica ediyorum.","Silahınızı çekili halde dolaşmak tehlikeli, monsieur. Lütfen onu yerine koyun.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ, öyleyse.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Beyefendi, yalvarırım, silahınızı indirin. Beni korkutuyorsunuz.","Erkeklerin korsan gibi davranıp silahlarını hazır tutarak dolaşmalarından hoşlanmıyorum.");
				link.l1 = RandPhraseSimple("Üzgünüm, kaldırıyorum.","Bunu kaldırıyorum.");
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
