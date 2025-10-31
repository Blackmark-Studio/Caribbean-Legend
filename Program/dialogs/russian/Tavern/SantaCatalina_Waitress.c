// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Вопросы, " + GetAddress_Form(NPChar) + "?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Хм, уж не пристаёте ли вы ко мне, " + GetAddress_Form(NPChar) + "? ","Опять со странными вопросами? Девушка, выпили бы вы рому, что ли...") +"", "В течение этого дня вы уже третий раз говорите о каком-то вопросе..."+ GetSexPhrase(" Это знаки внимания?","") +"",
                          "Опять вопросы будете задавать, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить."), "Да нет, что ты, красавица...",
                      "Никак нет, дорогуша, склероз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "helendrinking":
			dialog.text = "Как вам спалось, месье? Мисс МакАртур приказала, чтобы мы обеспечили вам полный комфорт!";
			link.l1 = "Мне снился очень странный сон...";
			link.l1.go = "helendrinking_1";
		break;

		case "helendrinking_1":
			dialog.text = "Ах!";
			link.l1 = "Что такое, мадемуазель? Я могу вам чем-то помочь?";
			link.l1.go = "helendrinking_2";
		break;

		case "helendrinking_2":
			dialog.text = "Простите, капитан... Грех это, но не сдержусь! Умею я немного, но не откажите девушке, капитан! Вы такой красивый! Хочется мне вас порадовать, прикоснуться...";
			link.l1 = "И правда, полный комфорт... Ты тоже очень красивая! Ну давай, не стесняйся.";
			link.l1.go = "helendrinking_sex";
			link.l2 = "Лучше меня сейчас не касаться, мадемуазель, - от меня слишком разит ромом. А вот порадовать можно - завтрак был бы очень кстати!";
			link.l2.go = "helendrinking_nosex";
		break;
		
		case "helendrinking_sex":
			dialog.text = "Ой, ну что вы, что вы!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressSex");
		break;

		case "helendrinking_nosex":
			dialog.text = "Хам!";
			link.l1 = "Значит, завтрака не будет?";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressNoSex");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

