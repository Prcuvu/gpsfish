#include "osl/ptype.h"
#include "osl/direction.h"
#include "osl/effect/liberty8Table.h"
#include "osl/pieceTable.h"
#include "osl/hash/hashKey.h"

#include "osl/move_generator/addEffect8Table.h"
#include "osl/progress/ptypeProgress.h"
#include "osl/progress/effect5x3Table.h"
#include "osl/pathEncoding.h"
#include "osl/effect/moveSignature.h"

#include "osl/centering3x3.h"
#include "osl/centering5x3.h"
#include "osl/effect_util/neighboring8Direct.h"
#include "osl/effect_util/neighboring8Effect.h"
#include "osl/effect_util/sendOffSquare.h"

#include "osl/checkmate/immediateCheckmateTable.h"
#include "osl/checkmate/proofNumberTable.h"

#include "osl/rating/featureSet.h"

#include "osl/eval/pieceEval.h"
#include "osl/eval/ppair/piecePairRawEval.h"
#include "osl/eval/ppair/piecePairPieceEval.h"
#include "osl/eval/endgame/attackKing.h"
#include "osl/eval/endgame/defenseKing.h"
#include "osl/eval/mobilityTable.h"
#include "osl/eval/progressEval.h"
#include "osl/eval/ml/openMidEndingEval.h"

#include "osl/container/boardMask.h"
namespace osl
{
#if 0
  /** y 座標に対応した進行度の係数、最初は0 (使用しない)*/
  const osl::CArray<int,10> osl::progress::PtypeProgressTable::yVals =
  {{   
    0,4,4,4,3,2,1,0,0,0
  }};

#endif
  const CArray<Offset,DIRECTION_SIZE> BoardTable::offsets = { {
    DirectionTraits<static_cast<Direction>(0)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(1)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(2)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(3)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(4)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(5)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(6)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(7)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(8)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(9)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(10)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(11)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(12)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(13)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(14)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(15)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(16)>::blackOffset(),
    DirectionTraits<static_cast<Direction>(17)>::blackOffset()
  } };
  const CArray<int,DIRECTION_SIZE> BoardTable::dxs = { {
    DirectionTraits<static_cast<Direction>(0)>::blackDx,
    DirectionTraits<static_cast<Direction>(1)>::blackDx,
    DirectionTraits<static_cast<Direction>(2)>::blackDx,
    DirectionTraits<static_cast<Direction>(3)>::blackDx,
    DirectionTraits<static_cast<Direction>(4)>::blackDx,
    DirectionTraits<static_cast<Direction>(5)>::blackDx,
    DirectionTraits<static_cast<Direction>(6)>::blackDx,
    DirectionTraits<static_cast<Direction>(7)>::blackDx,
    DirectionTraits<static_cast<Direction>(8)>::blackDx,
    DirectionTraits<static_cast<Direction>(9)>::blackDx,
    DirectionTraits<static_cast<Direction>(10)>::blackDx,
    DirectionTraits<static_cast<Direction>(11)>::blackDx,
    DirectionTraits<static_cast<Direction>(12)>::blackDx,
    DirectionTraits<static_cast<Direction>(13)>::blackDx,
    DirectionTraits<static_cast<Direction>(14)>::blackDx,
    DirectionTraits<static_cast<Direction>(15)>::blackDx,
    DirectionTraits<static_cast<Direction>(16)>::blackDx,
    DirectionTraits<static_cast<Direction>(17)>::blackDx
  } };
  const CArray<int,DIRECTION_SIZE> BoardTable::dys = { {
    DirectionTraits<static_cast<Direction>(0)>::blackDy,
    DirectionTraits<static_cast<Direction>(1)>::blackDy,
    DirectionTraits<static_cast<Direction>(2)>::blackDy,
    DirectionTraits<static_cast<Direction>(3)>::blackDy,
    DirectionTraits<static_cast<Direction>(4)>::blackDy,
    DirectionTraits<static_cast<Direction>(5)>::blackDy,
    DirectionTraits<static_cast<Direction>(6)>::blackDy,
    DirectionTraits<static_cast<Direction>(7)>::blackDy,
    DirectionTraits<static_cast<Direction>(8)>::blackDy,
    DirectionTraits<static_cast<Direction>(9)>::blackDy,
    DirectionTraits<static_cast<Direction>(10)>::blackDy,
    DirectionTraits<static_cast<Direction>(11)>::blackDy,
    DirectionTraits<static_cast<Direction>(12)>::blackDy,
    DirectionTraits<static_cast<Direction>(13)>::blackDy,
    DirectionTraits<static_cast<Direction>(14)>::blackDy,
    DirectionTraits<static_cast<Direction>(15)>::blackDy,
    DirectionTraits<static_cast<Direction>(16)>::blackDy,
    DirectionTraits<static_cast<Direction>(17)>::blackDy
  } };
}

namespace osl
{
  const PieceTable Piece_Table;
  const BoardTable Board_Table;
  // PtypeTable depends on BoardTable
  const PtypeTable Ptype_Table;
#if 0
  // BoardTable, PtypeTable -> Liberty8Table
  const effect::Liberty8Table effect::Liberty8_Table;
#endif
#ifndef DFPNSTATONE
  const eval::PtypeEvalTable eval::Ptype_Eval_Table;
#if 0
  const eval::PtypeEvalTable eval::PieceEval::Piece_Value = eval::Ptype_Eval_Table;
  const eval::PtypeEvalTable eval::ProgressEval::Piece_Value = eval::Ptype_Eval_Table;
#endif
  eval::ml::OpenMidEndingPtypeTable eval::ml::OpenMidEndingEval::Piece_Value;
#endif
#if 0
  const hash::HashGenTable hash::Hash_Gen_Table;
  // PtypeTable, BoardTable -> AddEffectTable
  // PtypeTable, BoardTable -> AddEffect8Table
#ifndef DFPNSTATONE
  const move_generator::addeffect8::AddEffect8Table move_generator::Add_Effect8_Table;
#endif

#ifndef MINIMAL
  const effect::MoveSignatureTable effect::Move_Signature_Table;
#endif
  const PathEncodingTable Path_Encoding_Table;

#ifndef MINIMAL
  const progress::PtypeProgressTable progress::Ptype_Progress_Table;
#endif

  const Centering3x3::Table Centering3x3::table;
#endif
  const Centering5x3::Table Centering5x3::table;
#if 0
  const effect_util::Neighboring8Direct::Table Neighboring8Direct::table;
  const effect_util::Neighboring8Effect::Table Neighboring8Effect::table;
  const effect_util::SendOffSquare::Table effect_util::SendOffSquare::table;

#endif
  const container::BoardMaskTable5x5 container::Board_Mask_Table5x5;
  const container::BoardMaskTable3x3 container::Board_Mask_Table3x3;
  const container::BoardMaskTable5x3Center container::Board_Mask_Table5x3_Center;

  const checkmate::ImmediateCheckmateTable checkmate::Immediate_Checkmate_Table;
#if 0
  const checkmate::ProofNumberTable checkmate::Proof_Number_Table;
  const checkmate::EdgeTable checkmate::Edge_Table;
#ifndef MINIMAL
  const eval::ppair::PiecePairRawTable eval::ppair::PiecePairRawTable::Table;
  const eval::ppair::PiecePairPieceTable eval::ppair::PiecePairPieceTable::Table;
  eval::PtypeEvalTable eval::ppair::PiecePairPieceTable::Piece_Value
  = eval::Ptype_Eval_Table;

  eval::endgame::AttackKing::Table eval::endgame::AttackKing::table;
  eval::endgame::DefenseKing::Table eval::endgame::DefenseKing::table;
#endif
#ifndef DFPNSTATONE
  const progress::Effect5x3Table progress::Effect5x3_Table;
#endif
#ifndef MINIMAL
  const CArray<int, 9> eval::MobilityTable::rookVertical = { {
      -61,-43,-22,-9,-2,9,12,17,17,
    } };

  const CArray<int, 9> eval::MobilityTable::rookHorizontal={{
      -72,-47,-18,4,10,28,21,27,27,
    }};
  const CArray<int, 9> eval::MobilityTable::prookVertical={{
      -45,-26,-17,-13,-1,1,10,8,8,
    }};
  const CArray<int, 9> eval::MobilityTable::prookHorizontal={{
      -35,-23,-16,-10,-4,4,11,12,12,
    }};
  const CArray<int, 17> eval::MobilityTable::bishop={{
      -60,-30,-6,2,4,8,10,12,
      12,13,15,17,19,21,23,25,27
    }};
  const CArray<int, 17> eval::MobilityTable::pbishop={{
      -39,-30,-9,-6,-2,2,0,5,
      13,15,17,19,21,23,25,27,29
    }};
  const CArray<int, 9> eval::MobilityTable::lance={{
      -10,-7,2,6,18,25,27,24,24
    }};
#endif
#endif
}


// ;;; Local Variables:
// ;;; mode:c++
// ;;; c-basic-offset:2
// ;;; End:
