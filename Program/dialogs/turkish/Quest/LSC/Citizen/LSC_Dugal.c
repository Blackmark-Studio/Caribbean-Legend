// Дугал Эббот - дворянин
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
				dialog.text = "Sizinle konuşmayacağım, efendim. Masum insanlara sebepsiz yere saldırıyorsunuz. Gözüm görmesin sizi!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Selamlar efendim. Kendimi tanıtayım: Dougall Abbot. Burada bir soyluyu görmek güzel. Bu köylüler çok yorucu. Hayatımın geri kalanını böyle aşağı tabakadan insanlarla geçirmek zorunda kalacağımı hiç düşünmemiştim.";
				link.l1 = TimeGreeting()+" . Benim adım "+GetFullName(pchar)+". Tanıştığımıza memnun oldum. Peki, neden buradaki yerlileri sevmiyorsun?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Size nasıl yardımcı olabilirim?";
				link.l1 = LinkRandPhrase("Dougall! Adadan ne haber var?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu merak ettim. Hoşça kal!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Onları tanıdıkça anlarsın. Yeni mi geldin? Yeni bir gemi kazası duyduğumu hatırlamıyorum...";
			link.l1 = "Buraya küçük bir barkla geldim. Gece yarısı aniden battı.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Evet, olur böyle şeyler – gemiler batar ve sadece birkaç kişi kendini kıyıya atar. Bazen insanlar burada aylarca yaşar, ama onlarla hiç karşılaşmazsın.";
			link.l1 = "Anladım. Sizinle tanışmak güzeldi, Bay Abbot. Hoşça kalın!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Selam, Dougall! Ne var ne yok?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Sana ada hakkında birkaç soru sormak istiyorum.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Dinliyorum.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Buraya nasıl geldin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Buradaki yerliler hakkında bana ne anlatabilirsin?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Kabileler hakkında bana ne söyleyebilirsin?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Hava nasıl? Burada sık sık fırtına olur mu?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorunuz yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "It was five years ago, but I still remember it as if it were yesterday. I'd set sail from Port Royal for Belize on a fluyt stuffed with high-value cargo.\nThe next day, things started to go wrong: first, my boatswain got drunk and fell overboard; then we almost hit a reef; then my navigator made a mistake and sent us north instead of south.\nA Spanish brig and galleon happened upon us. We fled and they gave chase. The galleon we left behind but the brig caught up to us.\nSince the galleon was too far back to support her smaller companion, I ordered that we come about and board the brig at once. The Spanish dogs weren't expecting that, he-he! (sigh) We won, but at the cost of most of my crew.\nMere hours later, a storm got up, and we couldn't weather it with so few crew, and now you see the result: my fluyt is wrecked somewhere on the outer ring, and me and  three other survivors live here now. Fuh!";
			link.l1 = "Gerçekten ilginç bir hikaye.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Pislik. Hepsi! Ptah! (tükürür) Her türden aşağılık insan. Richard Shambon tam bir suçlu - yüzünden okunuyor. Kassel mi? Onun için adam öldürmek nefes almak kadar doğal. Jasper Pratt bir mahkûm. Musket ise ayyaşın teki. Devam etmemi ister misin?\nJoseph Lauderdale burada düzgün tek adam - tabii senden başka. O bir İngiliz deniz subayı. Burada iki soylu var: Antonio de Betancourt ve Lorenzo Solderra - lanet olası İspanyol pislikleri! Onlarla aynı masaya bile oturmam.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "A bunch of bastards and scum. They don't harm us, though; they're far more interested in killing each other. And they've never stopped - can't live without violence.\nI don't like pirates either but I must admit the island has grown more peaceful since their arrival; they balance out the Narwhals and Rivados.";
			link.l1 = "İlginç...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Asla. Adayı çevreleyen fırtınalar sık sık olur ama adanın kendisi her zaman sakindir. Belki Tanrı'nın isteğidir, belki de bir büyü, bilmiyorum. Bazen sert rüzgar ve yağmur olur, ama hiçbir zaman zarar verecek kadar kötü olmaz.";
			link.l1 = "İlginç...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("A-ha! Seni ilk gördüğüm anda sıradan bir haydut olduğunu anlamıştım!","Eşyama dokunma, pislik!","Pis ellerini göğsümden çek! Bunun hesabını sana ödeteceğim!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Eşyalarımı çalmaya kalkma sakın, seni serseri! Defol buradan!";
			link.l1 = "Sakin ol, kadın!";
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
			dialog.text = LinkRandPhrase("Beyefendi, silahınızı indirin. Beni tedirgin ediyorsunuz.","Silahını indir, dikkat çekiyorsun.","Bu kadar silahlı dolaşmak birine zarar verebilir. Koyun onu yerine, efendim.");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Bu şehrin bir beyefendisi olarak, silahını indirmeni talep ediyorum!","Böyle bir beyefendinin silah sallamasına gerek kalmazdı, diye düşünürdüm.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ o zaman.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Beyefendi, silahınızı indirin. Beni tedirgin ediyorsunuz.","Silahınızı indirmenizi rica ediyorum, efendim. Beni tedirgin ediyorsunuz.");
				link.l1 = RandPhraseSimple("Pekâlâ.","Bunu kaldırıyorum.");
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
