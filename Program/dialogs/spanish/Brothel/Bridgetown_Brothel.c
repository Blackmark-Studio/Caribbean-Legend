// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas, "+ GetSexPhrase("joven","jovencita")+"?","¿Qué necesitas, "+GetSexPhrase("guapo","bonita")+"? Pregunta lo que quieras."),"¿Preguntas otra vez?","Vaya, otra vez lo mismo... preguntas...",
                          ""+ GetSexPhrase("Mm, ¿por qué no eliges una belleza para ti? Estoy empezando a sospechar de ti...","Mm, ¿por qué no eliges una belleza para ti? No tenemos chicos aquí, me temo, jeje...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión, discúlpame.","En realidad, olvídalo..."),"Yo... lo siento, no tengo preguntas, por ahora.",
                     "Tienes razón, es la tercera vez ya. Perdóname.","Tal vez la próxima vez, señora.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "He comprado un cargamento de caoba para comerciar y me dirijo a Blueweld. Todavía queda un largo camino, y mis hombres son pocos y están ansiosos... ¿Cuánto costaría dejar que cincuenta marineros descansen aquí por la noche?";
                link.l1.go = "BrothelDone";
            }
		break;
		
		case "BrothelDone":
			dialog.text = "Cincuenta marineros... quince mil.";
			link.l1 = "Una gran suma... Necesito pensarlo.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-7");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
