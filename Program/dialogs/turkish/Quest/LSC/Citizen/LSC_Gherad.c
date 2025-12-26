// Гхерад Смиитс - матрос
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
				dialog.text = "Defol git, dostum. Masum sivillere saldıranlarla konuşmam!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Selam dostum, ha-ha! Burada ne yapıyorsun?";
				link.l1 = TimeGreeting()+" . İyi günler! Sanırım sizinle henüz tanışmadık.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Hey-ho, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Size nasıl yardımcı olabilirim?";
				link.l1 = LinkRandPhrase("Hey-ho! Yeni bir haber var mı?","Adada yeni bir şey oldu mu?","Bana son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu merak ettim. Görüşürüz!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Tabii, tanışmadık ama artık tanıştık! Benim adım Gerard Smeets, denizciyim - Rotterdamlı bir gemici. Ve yanılmıyorsam sen de bir çavuş gibisin...?";
			link.l1 = "Öyle sayılır. Benim adım "+GetFullName(pchar)+". Tanıştığımıza memnun oldum.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Aslında, daha çok bir gemi sahibi ya da bir veznedara benziyorsun... Hiç şüphe yok ki iyi eğitimli bir adamsın. Tanıştığıma memnun oldum! Buraya nasıl geldin?";
			link.l1 = "Meksika Körfezi'ni keşfetmeye karar verdim. Küba'dan korsanlar bu bölgede haritada olmayan bir ada olduğunu söylediler ve doğru olup olmadıklarını görmek istedim.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Tek kurtulan sen misin? Gemin nerede battı, dış halkada mı?";
			link.l1 = "I'm indeed the only one. And my barque is at the bottom of the sea south of here; it didn't even reach the outer ring.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Ah. Eh, madem buraya sıkışıp kaldın, biraz rom almak için Sancho'ya uğra. Kederini içerek hafifletmek, burada kalışına iyi bir başlangıç olur, he-he.";
			link.l1 = "Teşekkürler... şimdilik hoşça kal!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hey-ho Smeets, yeni bir haber var mı?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Sana ada hakkında birkaç soru sormak istiyorum.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Tabii, dostum. Sor bakalım!.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Bana söyle, buraya nasıl geldin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Adadan ayrılıp eski hayatına dönmek ister misin?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Kabileler seni rahatsız ediyor mu?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Bu ada nasıl oluştu? Bir fikrin var mı?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorular yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "I got here with that puffed up peacock Abbot. I served on his ship. You know, people like him ought never set foot on a ship's deck - they bring bad luck. The devil must've put him on our tub.\nWe set sail on a voyage from Jamaica to Belize; easy as pie. But ill fate chased us: our boatswain fell overboard, our navigator steered us wrong, the bloody Spanish fell upon us, and a storm battered us to pieces. And here we are.";
			link.l1 = "Aman Tanrım!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "I used to, but... tell ye the truth, mate, I don't know. Life is fine here; plenty of rum and wine, good food - not a lot, but  better than weevilly ship's biscuits.\nThere are good blokes here, plenty of drink and gabbin'. I like it here. So I'm not sure... No, I reckon I don't want to leave. I used to live angry and hungry - look at my belly now, ha-ha!";
			link.l1 = "Harika! Senin adına sevindim.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "No, they don't. Just don't trespass against 'em, they don't abide that. The Narwhals are good lads - most of 'em were born here and they know no other life. Many of 'em are very skilled. Jurgen Schmidt for example; he's a god of blacksmithing, Hephaestus in the flesh!";
			link.l1 = "Bunu bilmek güzel.";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Storms and reefs, mate. The outer ring is made of ships top to bottom; ships get caught by a storm and thrown onto the reefs or the outer ring itself. That's how the island grows!\nThough I've no idea why the inner ships stay above the water. Probably there's a shoal beneath our feet, holding us up.";
			link.l1 = "Büyüleyici!";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Hey-ho, hırsız! Beni soyup soğana çevireceğini mi sandın, ha?","Arkamı döndüm, bak neler oluyor! Pis bir hırsız sürünerek geliyor!","Hey! Sandığıma dokunma, dostum!");
			link.l1 = "Ah, kahretsin!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Sandıklarımı mı karıştırıyorsun?! Buna nasıl cüret edersin!";
			link.l1 = "Lanet olsun...";
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
			dialog.text = LinkRandPhrase("Dostum, kılıcını indirir misin? Beni tedirgin ediyorsun.","Kimsenin seni elinde bıçakla dolaşırken görmesine izin verme. Onu yerine koy.","Kılıcını çekip şövalyelik taslama, tam bir aptal gibi görünüyorsun. Koy onu yerine...");
			link.l1 = LinkRandPhrase("Pekâlâ.","Dediğiniz gibi...","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, burada silahını çekip etrafta dolaşan aptallara göz yummayız. Onu yerine koy.","Bir adamın kılıcını bu kadar rahatça çekmesinden hoşlanmam. Kınına koy onu.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Ne halin varsa gör.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dostum, kılıcını indirir misin? Beni tedirgin ediyorsun.","Bir adamın kılıcını bu kadar rahatça çekmesinden hoşlanmam. Bu beni korkutuyor...");
				link.l1 = RandPhraseSimple("Anladım.","Bunu alıp götürüyorum.");
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
