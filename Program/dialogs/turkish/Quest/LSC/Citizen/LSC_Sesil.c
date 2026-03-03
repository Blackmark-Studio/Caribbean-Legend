// Сесил Галард - бабулька
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
				dialog.text = "Seninle konuşmak istemiyorum. Masum sivillere sebepsiz yere saldırıyor ve onları kavgaya kışkırtıyorsun. Kaybol!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bir şey mi istiyorsun, genç adam?";
				link.l1 = TimeGreeting()+" . Kendimi tanıtayım - "+GetFullName(pchar)+". Ben bir yeniyim.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Size nasıl yardımcı olabilirim?";
				link.l1 = LinkRandPhrase("Merhaba, Cecille. Son zamanlarda ilginç dedikodular duydun mu?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu merak ettim. Görüşürüz!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "A-ah, demek adamız ve sakinleriyle tanışıyorsun?";
			link.l1 = "Tam olarak, Madam?..";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Halard. Cecille Halard.";
			link.l1 = "Sizi tanıdığıma memnun oldum, Madame Halard! Bu benim için bir zevk.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Benimki de... Peki sen buraya nasıl geldin, delikanlı? Son zamanlarda bir gemi kazası olduğunu hatırlamıyorum...";
			link.l1 = "İspanyol Ana Karası'ndan bir barkla yelken açtım ve bir fırtına beni buraya sürükledi... Gemim adanın pek uzağında batmıştı.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Bu durumda, adaya sağ salim ulaşabildiğin için gerçekten çok şanslısın. Fırtınalar adanın kendisine nadiren dokunur, ama çevresindeki sularda aniden ortaya çıkıp en sağlam gemileri bile darmadağın edebilirler!\nO yüzden kendini şanslı say ve buraya alışmaya bak. Seni üzmek istemem ama buraya gelmek kolay olsa da, adadan ayrılmak neredeyse imkânsız. Son on yılda bunu başarıp da hayatta kalan kimse olmadı.";
			link.l1 = "Beni affedin, ama öyle kolayca umutsuzluğa kapılmam. Sizi tanıdığıma memnun oldum, Madame Halard, bir dahaki sefere kadar!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Evet, genç adam?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Ve siz buraya nasıl geldiniz, madam?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Burada uzun zamandır yaşıyorsun, değil mi?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Buradaki yerliler hakkında bana ne anlatabilirsin?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Burada yaşayan en ilginç insanlar kimler?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorunuz yoksa, affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "O kadar uzun zaman geçti ki, nasıl olduğunu zar zor hatırlıyorum. Biliyorum, bir gemi kazası geçirdim ama ayrıntılar... (omuz silker)";
			link.l1 = "Hıh.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Küçük bir kızken beri. Bazen burada doğduğuma neredeyse inanıyorum... ama tabii ki bu doğru değil. Yine de, kesinlikle burada öleceğim.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sana fazla bir şey söyleyemem, delikanlı... Adalet Adası her türden insanı barındırır: beyazlar, zenciler, yerliler, kaçak köleler, soylular, devlet mahkumları, denizciler... ve eskiden daha da fazlası vardı. Herkesin bir hikayesi ve alışkanlıkları var. Kimi burada olmaktan memnun, kimi ise sürekli kaçmayı hayal ediyor.\nSonra klanlar var - Narvaller ve Rivados - ve onları da korsanlar dengeliyor. Burada, dünyanın başka hiçbir yerinde göremeyeceğin kadar farklı insan bir arada, hem de görece bir huzur ve uyum içinde...";
			link.l1 = "Büyüleyici...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Herr Schmidt, Narvaların tamirci-mucidi... Sancho Carpentero, buranın barmeni... Ve şimdi de Amiral Köpekbalığı Dodson ve arkadaşı Layton Dexter aramıza katıldı.\nAma asıl, bu insanlardan bazılarıyla bizzat tanışmalısın. Biz Adalet Adası sakinlerinin ne kadar ilginç hikayeleri olduğunu tahmin bile edemezsin.";
			link.l1 = "Bunu düşüneceğim...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ah, hırsız! Olduğun yerde kal!","Yaşlı bir kadını arkasını döndüğünde soymak mı? Sana nasıl cüret edersin!","Sandıklarımı yağmalamaya mı karar verdin? Bunu yanına bırakmam!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Yaşlı bir kadını arkasını döndüğünde soymak mı? Sana hiç yakışıyor mu!!";
			link.l1 = "Aptal kız!";
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
			dialog.text = LinkRandPhrase("Silahını indir, delikanlı. Sinirlerimi bozuyor.","Biliyor musun, bu adada silahını sallayanların başına kötü şeyler gelir. Koy onu yerine.","Genç adam, kılıcını kınına koy. Yaşlı bir kadını ödü koparacaksın!");
			link.l1 = LinkRandPhrase("Pekâlâ.","Tabii.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Silahını indir, delikanlı. Bu beni tedirgin ediyor.","Biliyor musun, bu adada silahını sallayanların başına kötü şeyler gelir. Koy onu yerine.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Tabii.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Silahını indir, delikanlı. Bu beni tedirgin ediyor.","Genç adam, kılıcını kınına koy. Yaşlı bir kadını ölümüne korkutacaksın!");
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
